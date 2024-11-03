/* SPDX-License-Identifier: GPL-2.0-only */

#include <acpi/acpigen.h>
#include <arch/smp/mpspec.h>
#include <arch/vga.h>
#include <assert.h>
#include <cpu/intel/turbo.h>
#include <device/mmio.h>
#include <device/pci.h>
#include <intelblocks/acpi.h>
#include <soc/acpi.h>
#include <soc/iomap.h>
#include <soc/msr.h>
#include <soc/pci_devs.h>
#include <soc/pm.h>
#include <soc/soc_util.h>
#include <soc/util.h>

int soc_madt_sci_irq_polarity(int sci)
{
	if (sci >= 20)
		return MP_IRQ_POLARITY_LOW;
	else
		return MP_IRQ_POLARITY_HIGH;
}

uint32_t soc_read_sci_irq_select(void)
{
	struct device *dev = PCH_DEV_PMC;

	if (!dev)
		return 0;

	return pci_read_config32(dev, PMC_ACPI_CNT);
}

void soc_fill_fadt(acpi_fadt_t *fadt)
{
	const uint16_t pmbase = ACPI_BASE_ADDRESS;

	/* Fix flags set by common/block/acpi/acpi.c acpi_fill_fadt() */
	fadt->flags &=  ~(ACPI_FADT_SEALED_CASE);
	fadt->flags |= ACPI_FADT_SLEEP_TYPE;

	fadt->pm2_cnt_blk = pmbase + PM2_CNT;
	fadt->pm_tmr_blk = pmbase + PM1_TMR;

	fadt->pm2_cnt_len = 1;
	fadt->pm_tmr_len = 4;

	fadt->iapc_boot_arch = ACPI_FADT_LEGACY_DEVICES | ACPI_FADT_8042;

	/* PM Extended Registers */
	fill_fadt_extended_pm_io(fadt);
}

void uncore_fill_ssdt(const struct device *device)
{
	const IIO_UDS *hob = get_iio_uds();

	/* Only add RTxx entries once. */
	if (device->upstream->secondary != 0)
		return;

	for (int socket = 0, iio = 0; iio < hob->PlatformData.numofIIO; ++socket) {
		if (!soc_cpu_is_enabled(socket))
			continue;
		iio++;
		IIO_RESOURCE_INSTANCE iio_resource =
			hob->PlatformData.IIO_resource[socket];
		for (int stack = 0; stack <= PSTACK2; ++stack) {
			const STACK_RES *ri = &iio_resource.StackRes[stack];
			char rtname[16];

			snprintf(rtname, sizeof(rtname), "\\_SB.PC%02x", socket * MAX_IIO_STACK + stack);
			acpigen_write_scope(rtname);

			acpigen_write_name("_CRS");

			printk(BIOS_DEBUG, "\tCreating ResourceTemplate %s for socket: %d, stack: %d\n",
				rtname, socket, stack);

			acpigen_write_resourcetemplate_header();

			/* bus resource */
			acpigen_resource_word(2, 0xc, 0, 0, ri->BusBase, ri->BusLimit,
				0x0, (ri->BusLimit - ri->BusBase + 1));

			// additional io resources on socket 0 bus 0
			if (socket == 0 && stack == 0) {
				/* ACPI 6.4.2.5 I/O Port Descriptor */
				acpigen_write_io16(0xCF8, 0xCFF, 0x1, 0x8, 1);

				/* IO decode  CF8-CFF */
				acpigen_resource_word(1, 0xc, 0x3, 0, 0x0000, 0x03AF,
					0, 0x03B0);
				acpigen_resource_word(1, 0xc, 0x3, 0, 0x03E0, 0x0CF7,
					0, 0x0918);
				acpigen_resource_word(1, 0xc, 0x3, 0, 0x03B0, 0x03BB,
					0, 0x000C);
				acpigen_resource_word(1, 0xc, 0x3, 0, 0x03C0, 0x03DF,
					0, 0x0020);
			}

			/* IO resource */
			acpigen_resource_word(1, 0xc, 0x3, 0, ri->PciResourceIoBase,
				ri->PciResourceIoLimit, 0x0,
				(ri->PciResourceIoLimit - ri->PciResourceIoBase + 1));

			// additional mem32 resources on socket 0 bus 0
			if (socket == 0 && stack == 0) {
				acpigen_resource_dword(0, 0xc, 3, 0, VGA_MMIO_BASE,
					VGA_MMIO_LIMIT, 0x0, VGA_MMIO_SIZE);
				acpigen_resource_dword(0, 0xc, 1, 0, SPI_BASE_ADDRESS,
					(SPI_BASE_ADDRESS + SPI_BASE_SIZE - 1), 0x0,
					SPI_BASE_SIZE);
			}

			/* Mem32 resource */
			acpigen_resource_dword(0, 0xc, 1, 0, ri->PciResourceMem32Base,
				ri->PciResourceMem32Limit, 0x0,
				(ri->PciResourceMem32Limit - ri->PciResourceMem32Base + 1));

			/* Mem64 resource */
			acpigen_resource_qword(0, 0xc, 1, 0, ri->PciResourceMem64Base,
				ri->PciResourceMem64Limit, 0x0,
				(ri->PciResourceMem64Limit - ri->PciResourceMem64Base + 1));

			acpigen_write_resourcetemplate_footer();

			/* Scope */
			acpigen_pop_len();
		}
	}
}

void soc_power_states_generation(int core, int cores_per_package)
{
}
