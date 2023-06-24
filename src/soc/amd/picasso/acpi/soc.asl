/* SPDX-License-Identifier: GPL-2.0-only */

#include <soc/amd/common/acpi/pci_root.asl>

ROOT_BRIDGE(PCI0)

Scope(PCI0) {
	/* Describe the AMD Northbridge */
	#include "northbridge.asl"

	/* Describe the AMD Fusion Controller Hub */
	#include <soc/amd/common/acpi/lpc.asl>
	#include <soc/amd/common/acpi/platform.asl>
}

/* PCI IRQ mapping for the Southbridge */
#include "pci_int_defs.asl"

/* Describe PCI INT[A-H] for the Southbridge */
#include <soc/amd/common/acpi/pci_int.asl>

/* Describe the MMIO devices in the FCH */
#include "mmio.asl"

/* Add GPIO library */
#include <soc/amd/common/acpi/gpio_bank_lib.asl>

#if CONFIG(SOC_AMD_COMMON_BLOCK_ACPI_DPTC)
#include <soc/amd/common/acpi/dptc.asl>
#endif
