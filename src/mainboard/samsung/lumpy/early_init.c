/* SPDX-License-Identifier: GPL-2.0-only */

#include <arch/hpet.h>
#include <stdint.h>
#include <string.h>
#include <arch/io.h>
#include <bootblock_common.h>
#include <cbfs.h>
#include <console/console.h>
#include <bootmode.h>
#include <northbridge/intel/sandybridge/sandybridge.h>
#include <northbridge/intel/sandybridge/raminit.h>
#include <northbridge/intel/sandybridge/raminit_native.h>
#include <southbridge/intel/bd82x6x/pch.h>
#include <southbridge/intel/common/gpio.h>
#include <superio/smsc/lpc47n207/lpc47n207.h>
#include "option_table.h"

void bootblock_mainboard_early_init(void)
{
	if (CONFIG(DRIVERS_UART_8250IO))
		try_enabling_LPC47N207_uart();
}

void mainboard_late_rcba_config(void)
{
	/*
	 *             GFX    INTA -> PIRQA (MSI)
	 * D28IP_P1IP  WLAN   INTA -> PIRQB
	 * D28IP_P4IP  ETH0   INTB -> PIRQC (MSI)
	 * D29IP_E1P   EHCI1  INTA -> PIRQD
	 * D26IP_E2P   EHCI2  INTA -> PIRQB
	 * D31IP_SIP   SATA   INTA -> PIRQA (MSI)
	 * D31IP_SMIP  SMBUS  INTC -> PIRQH
	 * D31IP_TTIP  THRT   INTB -> PIRQG
	 * D27IP_ZIP   HDA    INTA -> PIRQG (MSI)
	 *
	 * LIGHTSENSOR             -> PIRQE (Edge Triggered)
	 * TRACKPAD                -> PIRQF (Edge Triggered)
	 */

	/* Device interrupt pin register (board specific) */
	RCBA32(D31IP) = (INTB << D31IP_TTIP) | (NOINT << D31IP_SIP2) |
		(INTC << D31IP_SMIP) | (INTA << D31IP_SIP);
	RCBA32(D30IP) = (NOINT << D30IP_PIP);
	RCBA32(D29IP) = (INTA << D29IP_E1P);
	RCBA32(D28IP) = (INTA << D28IP_P1IP) | (INTC << D28IP_P3IP) |
		(INTB << D28IP_P4IP);
	RCBA32(D27IP) = (INTA << D27IP_ZIP);
	RCBA32(D26IP) = (INTA << D26IP_E2P);
	RCBA32(D25IP) = (NOINT << D25IP_LIP);
	RCBA32(D22IP) = (NOINT << D22IP_MEI1IP);

	/* Device interrupt route registers */
	DIR_ROUTE(D31IR, PIRQA, PIRQG, PIRQH, PIRQB);
	DIR_ROUTE(D29IR, PIRQD, PIRQE, PIRQG, PIRQH);
	DIR_ROUTE(D28IR, PIRQB, PIRQC, PIRQD, PIRQE);
	DIR_ROUTE(D27IR, PIRQG, PIRQH, PIRQA, PIRQB);
	DIR_ROUTE(D26IR, PIRQB, PIRQC, PIRQD, PIRQA);
	DIR_ROUTE(D25IR, PIRQA, PIRQB, PIRQC, PIRQD);
	DIR_ROUTE(D22IR, PIRQA, PIRQB, PIRQC, PIRQD);
}

static const uint8_t *locate_spd(void)
{
	typedef const uint8_t spd_blob[256];
	spd_blob *spd_data;
	size_t spd_file_len;

	u32 gp_lvl2 = inl(DEFAULT_GPIOBASE + 0x38);
	u8 gpio33, gpio41, gpio49;
	gpio33 = (gp_lvl2 >> (33-32)) & 1;
	gpio41 = (gp_lvl2 >> (41-32)) & 1;
	gpio49 = (gp_lvl2 >> (49-32)) & 1;
	printk(BIOS_DEBUG, "Memory Straps:\n");
	printk(BIOS_DEBUG, " - memory capacity %dGB\n",
		gpio33 ? 2 : 1);
	printk(BIOS_DEBUG, " - die revision %d\n",
		gpio41 ? 2 : 1);
	printk(BIOS_DEBUG, " - vendor %s\n",
		gpio49 ? "Samsung" : "Other");

	int spd_index = 0;

	switch ((gpio49 << 2) | (gpio41 << 1) | gpio33) {
	case 0: // Other 1G Rev 1
		spd_index = 0;
		break;
	case 2: // Other 1G Rev 2
		spd_index = 1;
		break;
	case 1: // Other 2G Rev 1
	case 3: // Other 2G Rev 2
		spd_index = 2;
		break;
	case 4: // Samsung 1G Rev 1
		spd_index = 3;
		break;
	case 6: // Samsung 1G Rev 2
		spd_index = 4;
		break;
	case 5: // Samsung 2G Rev 1
	case 7: // Samsung 2G Rev 2
		spd_index = 5;
		break;
	}

	spd_data = cbfs_map("spd.bin", &spd_file_len);
	if (!spd_data)
		die("SPD data not found.");
	if (spd_file_len < (spd_index + 1) * 256)
		die("Missing SPD data.");
	return spd_data[spd_index];
}

void mainboard_fill_pei_data(struct pei_data *pei_data)
{
	const uint8_t spdaddr[] = {0xa0, 0x00, 0x00, 0x00};
	const uint8_t tsaddr[] = {0x30, 0x00, 0x00, 0x00};

	/* TODO: Confirm if nortbridge_fill_pei_data() gets .system_type right (should be 0) */
	memcpy(pei_data->spd_addresses, &spdaddr, sizeof(pei_data->spd_addresses));
	/* Only this board uses .ts_addresses. Fill here to allow removal from devicetree. */
	memcpy(pei_data->ts_addresses, &tsaddr, sizeof(pei_data->ts_addresses));
	memcpy(pei_data->spd_data[2], locate_spd(), 256);
}

const struct southbridge_usb_port mainboard_usb_ports[] = {
	/* enabled power  USB oc pin  */
	{ 1, 1, 0 }, /* P0: Port 0      (OC0) */
	{ 1, 1, 1 }, /* P1: Port 1      (OC1) */
	{ 1, 0, -1 }, /* P2: MINIPCIE1   (no OC) */
	{ 1, 0, -1 }, /* P3: MMC         (no OC) */
	{ 0, 0, -1 }, /* P4: Empty */
	{ 0, 0, -1 }, /* P5: Empty */
	{ 0, 0, -1 }, /* P6: Empty */
	{ 0, 0, -1 }, /* P7: Empty */
	{ 1, 0, -1 }, /* P8: MINIPCIE2   (no OC) */
	{ 0, 0, -1 }, /* P9: Empty */
	{ 0, 0, -1 }, /* P10: Empty */
	{ 1, 0, -1 }, /* P11: Camera     (no OC) */
	{ 0, 0, -1 }, /* P12: Empty */
	{ 0, 0, -1 }, /* P13: Empty */
};

void mainboard_get_spd(spd_raw_data *spd, bool id_only)
{
	/* get onboard dimm spd */
	memcpy(&spd[2], locate_spd(), 256);
	/* read removable dimm spd */
	read_spd(&spd[0], 0x50, id_only);
}
