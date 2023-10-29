/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef AMD_BLOCK_ROOT_COMPLEX_H
#define AMD_BLOCK_ROOT_COMPLEX_H

#include <device/device.h>
#include <types.h>

#define SMN_IOHC_MISC_BASE_13B1	0x13b10000
#define SMN_IOHC_MISC_BASE_13C1	0x13c10000
#define SMN_IOHC_MISC_BASE_13D1	0x13d10000
#define SMN_IOHC_MISC_BASE_13E1	0x13e10000

#define NON_PCI_RES_IDX_AUTO	0

struct non_pci_mmio_reg {
	uint32_t iohc_misc_offset;
	uint64_t mask;
	uint64_t size;
	unsigned long res_idx; /* Use NON_PCI_RES_IDX_AUTO or a specific resource index */
};

void read_non_pci_resources(struct device *domain, unsigned int *idx);

uint32_t get_iohc_misc_smn_base(struct device *domain);
const struct non_pci_mmio_reg *get_iohc_non_pci_mmio_regs(size_t *count);

signed int get_iohc_fabric_id(struct device *domain);

void read_fsp_resources(struct device *dev, unsigned int *idx);

#endif /* AMD_BLOCK_ROOT_COMPLEX_H */
