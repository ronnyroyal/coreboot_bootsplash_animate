/* SPDX-License-Identifier: GPL-2.0-only */

#include <device/pci_ops.h>
#include <device/pci_def.h>
#include <southbridge/intel/bd82x6x/pch.h>
#include <ec/lenovo/pmh7/pmh7.h>
#include <drivers/lenovo/hybrid_graphics/hybrid_graphics.h>
#include <northbridge/intel/sandybridge/sandybridge.h>

static void hybrid_graphics_init(void)
{
	bool peg, igd;
	u32 reg32;

	early_hybrid_graphics(&igd, &peg);

	if (peg && igd)
		return;

	/* Hide disabled devices */
	reg32 = pci_read_config32(PCI_DEV(0, 0, 0), DEVEN);
	reg32 &= ~(DEVEN_PEG10 | DEVEN_IGD);

	if (peg)
		reg32 |= DEVEN_PEG10;

	if (igd)
		reg32 |= DEVEN_IGD;
	else
		/* Disable IGD VGA decode, no GTT or GFX stolen */
		pci_write_config16(PCI_DEV(0, 0, 0), GGC, 2);

	pci_write_config32(PCI_DEV(0, 0, 0), DEVEN, reg32);
}

/* FIXME: used T530 values here */
const struct southbridge_usb_port mainboard_usb_ports[] = {
	{ 1, 1,  0 },
	{ 1, 1,  1 },
	{ 1, 2,  3 },
	{ 1, 1, -1 },
	{ 1, 1,  2 },
	{ 1, 0, -1 },
	{ 0, 0, -1 },
	{ 1, 2, -1 },
	{ 1, 0, -1 },
	{ 1, 1,  5 },
	{ 1, 0, -1 },
	{ 1, 0, -1 },
	{ 1, 3, -1 },
	{ 1, 1, -1 },
};

void mainboard_early_init(int s3resume)
{
	hybrid_graphics_init();
}
