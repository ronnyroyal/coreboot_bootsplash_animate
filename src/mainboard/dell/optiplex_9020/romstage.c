/* SPDX-License-Identifier: GPL-2.0-only */

#include <northbridge/intel/haswell/raminit.h>
#include <southbridge/intel/lynxpoint/pch.h>

void mainboard_config_rcba(void)
{
	RCBA16(D31IR) = DIR_ROUTE(PIRQA, PIRQC, PIRQD, PIRQA);
	RCBA16(D29IR) = DIR_ROUTE(PIRQC, PIRQA, PIRQD, PIRQH);
	RCBA16(D28IR) = DIR_ROUTE(PIRQD, PIRQC, PIRQB, PIRQA);
	RCBA16(D27IR) = DIR_ROUTE(PIRQD, PIRQC, PIRQB, PIRQG);
	RCBA16(D26IR) = DIR_ROUTE(PIRQD, PIRQC, PIRQF, PIRQA);
	RCBA16(D25IR) = DIR_ROUTE(PIRQH, PIRQG, PIRQF, PIRQE);
	RCBA16(D22IR) = DIR_ROUTE(PIRQB, PIRQC, PIRQD, PIRQA);
	RCBA16(D20IR) = DIR_ROUTE(PIRQD, PIRQC, PIRQB, PIRQA);
}

void mb_get_spd_map(struct spd_info *spdi)
{
	spdi->addresses[0] = 0x50;
	spdi->addresses[1] = 0x51;
	spdi->addresses[2] = 0x52;
	spdi->addresses[3] = 0x53;
}

const struct usb2_port_config mainboard_usb2_ports[MAX_USB2_PORTS] = {
	/* Length, Enable, OCn#, Location */
	{0x0000, 0, USB_OC_PIN_SKIP, USB_PORT_SKIP},
	{0x0000, 0, USB_OC_PIN_SKIP, USB_PORT_SKIP},
	{0x0040, 1, 1, USB_PORT_BACK_PANEL},
	{0x0040, 1, 2, USB_PORT_BACK_PANEL},
	{0x0040, 1, 3, USB_PORT_BACK_PANEL},
	{0x0040, 1, 3, USB_PORT_BACK_PANEL},
	{0x0040, 1, 0, USB_PORT_BACK_PANEL},
	{0x0040, 1, 0, USB_PORT_BACK_PANEL},
	{0x0040, 1, 4, USB_PORT_BACK_PANEL},
	{0x0040, 1, 4, USB_PORT_BACK_PANEL},
	{0x0040, 1, 5, USB_PORT_BACK_PANEL},
	{0x0040, 1, 5, USB_PORT_BACK_PANEL},
	{0x0040, 1, 6, USB_PORT_BACK_PANEL},
	{0x0040, 1, 7, USB_PORT_BACK_PANEL},
};

const struct usb3_port_config mainboard_usb3_ports[MAX_USB3_PORTS] = {
	/* Enable, OCn# */
	{1, 6},
	{1, 7},
	{0, USB_OC_PIN_SKIP},
	{0, USB_OC_PIN_SKIP},
	{1, 1},
	{1, 2},
};
