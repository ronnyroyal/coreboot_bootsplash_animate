/* SPDX-License-Identifier: GPL-2.0-only */

/*
 * This file is created based on Intel Alder Lake Firmware Architecture Specification
 * Document number: 626540
 * Chapter number: 4
 */

#ifndef _SOC_ALDERLAKE_IOMAP_H_
#define _SOC_ALDERLAKE_IOMAP_H_

/*
 * Memory-mapped I/O registers.
 */
#if CONFIG(SOC_INTEL_ALDERLAKE_PCH_S)
#define PCH_TRACE_HUB_BASE_ADDRESS	0xfd800000
#define PCH_TRACE_HUB_BASE_SIZE		0x00800000
#else
#define PCH_TRACE_HUB_BASE_ADDRESS	0xfc800000
#define PCH_TRACE_HUB_BASE_SIZE	0x00800000
#endif

#define PCH_PRESERVED_BASE_ADDRESS	0xfc800000
#define PCH_PRESERVED_BASE_SIZE		0x02000000

#define UART_BASE_SIZE		0x1000

#define UART_BASE_0_ADDRESS	0xfe03e000
/* Both UART BAR 0 and 1 are 4KB in size */
#define UART_BASE_0_ADDR(x)	(UART_BASE_0_ADDRESS + (2 * \
					UART_BASE_SIZE * (x)))
#define UART_BASE(x)		UART_BASE_0_ADDR(x)

#define DMI_BASE_ADDRESS	0xfeda0000
#define DMI_BASE_SIZE		0x1000

#define EP_BASE_ADDRESS		0xfeda1000
#define EP_BASE_SIZE		0x1000

#define EDRAM_BASE_ADDRESS	0xfed80000
#define EDRAM_BASE_SIZE		0x4000

#define TBT0_BASE_ADDRESS	0xfed84000
#define TBT0_BASE_SIZE		0x1000

#define TBT1_BASE_ADDRESS	0xfed85000
#define TBT1_BASE_SIZE		0x1000

#define TBT2_BASE_ADDRESS	0xfed86000
#define TBT2_BASE_SIZE		0x1000

#define TBT3_BASE_ADDRESS	0xfed87000
#define TBT3_BASE_SIZE		0x1000

#define GFXVT_BASE_ADDRESS	0xfed90000
#define GFXVT_BASE_SIZE		0x1000

#define IPUVT_BASE_ADDRESS	0xfed92000
#define IPUVT_BASE_SIZE		0x1000

#define VTVC0_BASE_ADDRESS	0xfed91000
#define VTVC0_BASE_SIZE		0x1000

#define REG_BASE_ADDRESS	0xfb000000
#define REG_BASE_SIZE		0x1000

#define PCH_PWRM_BASE_ADDRESS	0xfe000000
#define PCH_PWRM_BASE_SIZE	0x10000

#define SPI_BASE_ADDRESS	0xfe010000

#define GPIO_BASE_SIZE		0x10000

#define HECI1_BASE_ADDRESS	0xfeda2000

#define VTD_BASE_ADDRESS	0xfed90000
#define VTD_BASE_SIZE		0x00004000

#define MCH_BASE_ADDRESS	0xfedc0000
#define MCH_BASE_SIZE		0x20000

#define EARLY_GSPI_BASE_ADDRESS 0xfe030000

#define EARLY_I2C_BASE_ADDRESS	0xfe020000
#define EARLY_I2C_BASE(x)	(EARLY_I2C_BASE_ADDRESS + (0x2000 * (x)))

#define IOM_BASE_ADDRESS	0xfbc10000
#define IOM_BASE_SIZE		0x1600

/*
 * If MAINBOARD_HAS_EARLY_LIBGFXINIT is set, the following memory space is used
 * at least temporarily in romstage and ramstage as the Intel Graphics Device
 * Base Address Range 0. */
#define IGD_BASE_ADDRESS	CONFIG_GFX_GMA_DEFAULT_MMIO
#define IGD_BASE_SIZE		0x1000000

/*
 * I/O port address space
 */
#define SMBUS_BASE_ADDRESS	0x0efa0
#define SMBUS_BASE_SIZE		0x20

#define ACPI_BASE_ADDRESS	0x1800
#define ACPI_BASE_SIZE		0x100

#define TCO_BASE_ADDRESS	0x400
#define TCO_BASE_SIZE		0x20

#define P2SB_BAR		CONFIG_PCR_BASE_ADDRESS
#define P2SB_SIZE		(16 * MiB)

#endif
