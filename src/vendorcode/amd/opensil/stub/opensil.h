/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef _OPENSIL_H_
#define _OPENSIL_H_

#include <acpi/acpi.h>

// Add the memory map to dev, starting at index idx, returns last use idx
void add_opensil_memmap(struct device *dev, unsigned long *idx);
// Fill in FADT from openSIL
void opensil_fill_fadt_io_ports(acpi_fadt_t *fadt);

void setup_opensil(void);
void opensil_xSIM_timepoint_1(void);
void opensil_xSIM_timepoint_2(void);
void opensil_xSIM_timepoint_3(void);

#endif
