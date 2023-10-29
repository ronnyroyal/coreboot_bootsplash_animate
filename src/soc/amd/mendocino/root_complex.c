/* SPDX-License-Identifier: GPL-2.0-only */

/* TODO: Check if this is still correct */

#include <acpi/acpigen.h>
#include <amdblocks/acpi.h>
#include <amdblocks/alib.h>
#include <amdblocks/data_fabric.h>
#include <amdblocks/ioapic.h>
#include <amdblocks/iomap.h>
#include <amdblocks/memmap.h>
#include <amdblocks/root_complex.h>
#include <arch/ioapic.h>
#include <arch/vga.h>
#include <cbmem.h>
#include <console/console.h>
#include <device/device.h>
#include <device/pci.h>
#include <fsp/amd_misc_data.h>
#include <soc/iomap.h>
#include <stdint.h>
#include "chip.h"

#define TDP_15W	15
#define DPTC_TOTAL_UPDATE_PARAMS	13

struct dptc_input {
	uint16_t size;
	struct alib_dptc_param params[DPTC_TOTAL_UPDATE_PARAMS];
} __packed;


#define DPTC_INPUTS(_thermctllmit, _spptTimeConst, _fast, _slow,	\
	_vrmCurrentLimit, _vrmMaxCurrentLimit, _vrmSocCurrentLimit,	\
	_sttMinLimit, _sttM1, _sttM2, _sttCApu, _sttAlphaApu, _sttSkinTempLimitApu)	\
	{									\
		.size = sizeof(struct dptc_input),				\
		.params = {							\
			{							\
				.id = ALIB_DPTC_THERMAL_CONTROL_LIMIT_ID,	\
				.value = _thermctllmit,				\
			},							\
			{							\
				.id = ALIB_DPTC_SLOW_PPT_TIME_CONSTANT_ID,	\
				.value = _spptTimeConst,			\
			},							\
			{							\
				.id = ALIB_DPTC_FAST_PPT_LIMIT_ID,		\
				.value = _fast,					\
			},							\
			{							\
				.id = ALIB_DPTC_SLOW_PPT_LIMIT_ID,		\
				.value = _slow,					\
			},							\
			{							\
				.id = ALIB_DPTC_VRM_CURRENT_LIMIT_ID,		\
				.value = _vrmCurrentLimit,			\
			},							\
			{							\
				.id = ALIB_DPTC_VRM_MAXIMUM_CURRENT_LIMIT,	\
				.value = _vrmMaxCurrentLimit,			\
			},							\
			{							\
				.id = ALIB_DPTC_VRM_SOC_CURRENT_LIMIT_ID,	\
				.value = _vrmSocCurrentLimit,			\
			},							\
			{							\
				.id = ALIB_DPTC_STT_MIN_LIMIT_ID,		\
				.value = _sttMinLimit,				\
			},							\
			{							\
				.id = ALIB_DPTC_STT_M1_ID,			\
				.value = _sttM1,				\
			},							\
			{							\
				.id = ALIB_DPTC_STT_M2_ID,			\
				.value = _sttM2,				\
			},							\
			{							\
				.id = ALIB_DPTC_STT_C_APU_ID,			\
				.value = _sttCApu,				\
			},							\
			{							\
				.id = ALIB_DPTC_STT_ALPHA_APU,			\
				.value = _sttAlphaApu,				\
			},							\
			{							\
				.id = ALIB_DPTC_STT_SKIN_TEMPERATURE_LIMIT_APU_ID,	\
				.value = _sttSkinTempLimitApu,			\
			},							\
		},								\
	}

/*
 *
 *                     +--------------------------------+
 *                     |                                |
 *                     |                                |
 *                     |                                |
 *                     |                                |
 *                     |                                |
 *                     |                                |
 *                     |                                |
 *   reserved_dram_end +--------------------------------+
 *                     |                                |
 *                     |       verstage (if reqd)       |
 *                     |          (VERSTAGE_SIZE)       |
 *                     +--------------------------------+ VERSTAGE_ADDR
 *                     |                                |
 *                     |            FSP-M               |
 *                     |         (FSP_M_SIZE)           |
 *                     +--------------------------------+ FSP_M_ADDR
 *                     |           romstage             |
 *                     |        (ROMSTAGE_SIZE)         |
 *                     +--------------------------------+ ROMSTAGE_ADDR = BOOTBLOCK_END
 *                     |                                | X86_RESET_VECTOR = BOOTBLOCK_END  - 0x10
 *                     |           bootblock            |
 *                     |     (C_ENV_BOOTBLOCK_SIZE)     |
 *                     +--------------------------------+ BOOTBLOCK_ADDR = BOOTBLOCK_END - C_ENV_BOOTBLOCK_SIZE
 *                     |          Unused hole           |
 *                     |            (30KiB)             |
 *                     +--------------------------------+
 *                     |     FMAP cache (FMAP_SIZE)     |
 *                     +--------------------------------+ PSP_SHAREDMEM_BASE + PSP_SHAREDMEM_SIZE + PRERAM_CBMEM_CONSOLE_SIZE + 0x200
 *                     |  Early Timestamp region (512B) |
 *                     +--------------------------------+ PSP_SHAREDMEM_BASE + PSP_SHAREDMEM_SIZE + PRERAM_CBMEM_CONSOLE_SIZE
 *                     |      Preram CBMEM console      |
 *                     |   (PRERAM_CBMEM_CONSOLE_SIZE)  |
 *                     +--------------------------------+ PSP_SHAREDMEM_BASE + PSP_SHAREDMEM_SIZE
 *                     |   PSP shared (vboot workbuf)   |
 *                     |      (PSP_SHAREDMEM_SIZE)      |
 *                     +--------------------------------+ PSP_SHAREDMEM_BASE
 *                     |          APOB (120KiB)         |
 *                     +--------------------------------+ PSP_APOB_DRAM_ADDRESS
 *                     |        Early BSP stack         |
 *                     |   (EARLYRAM_BSP_STACK_SIZE)    |
 * reserved_dram_start +--------------------------------+ EARLY_RESERVED_DRAM_BASE
 *                     |              DRAM              |
 *                     +--------------------------------+ 0x100000
 *                     |           Option ROM           |
 *                     +--------------------------------+ 0xc0000
 *                     |           Legacy VGA           |
 *                     +--------------------------------+ 0xa0000
 *                     |              DRAM              |
 *                     +--------------------------------+ 0x0
 */
static void read_resources(struct device *dev)
{
	uint32_t mem_usable = (uintptr_t)cbmem_top();
	unsigned int idx = 0;

	uintptr_t early_reserved_dram_start, early_reserved_dram_end;
	const struct memmap_early_dram *e = memmap_get_early_dram_usage();

	early_reserved_dram_start = e->base;
	early_reserved_dram_end = e->base + e->size;

	/* The root complex has no PCI BARs implemented, so there's no need to call
	   pci_dev_read_resources for it */

	fixed_io_range_reserved(dev, idx++, PCI_IO_CONFIG_INDEX, PCI_IO_CONFIG_PORT_COUNT);

	/* 0x0 - 0x9ffff */
	ram_range(dev, idx++, 0, 0xa0000);

	/* 0xa0000 - 0xbffff: legacy VGA */
	mmio_range(dev, idx++, VGA_MMIO_BASE, VGA_MMIO_SIZE);

	/* 0xc0000 - 0xfffff: Option ROM */
	reserved_ram_from_to(dev, idx++, 0xc0000, 1 * MiB);

	/* 1MiB - bottom of DRAM reserved for early coreboot usage */
	ram_from_to(dev, idx++, 1 * MiB, early_reserved_dram_start);

	/* DRAM reserved for early coreboot usage */
	reserved_ram_from_to(dev, idx++, early_reserved_dram_start, early_reserved_dram_end);

	/*
	 * top of DRAM consumed early - low top usable RAM
	 * cbmem_top() accounts for low UMA and TSEG if they are used.
	 */
	ram_from_to(dev, idx++, early_reserved_dram_end, mem_usable);

	mmconf_resource(dev, idx++);

	/* Reserve fixed IOMMU MMIO region */
	mmio_range(dev, idx++, IOMMU_RESERVED_MMIO_BASE, IOMMU_RESERVED_MMIO_SIZE);

	read_fsp_resources(dev, &idx);
}

static void root_complex_init(struct device *dev)
{
	register_new_ioapic((u8 *)GNB_IO_APIC_ADDR);
}

static void acipgen_dptci(void)
{
	const struct soc_amd_mendocino_config *config = config_of_soc();

	/* Normal mode DPTC values. */
	struct dptc_input default_input = DPTC_INPUTS(
		config->thermctl_limit_degreeC,
		config->slow_ppt_time_constant_s,
		config->fast_ppt_limit_mW,
		config->slow_ppt_limit_mW,
		config->vrm_current_limit_mA,
		config->vrm_maximum_current_limit_mA,
		config->vrm_soc_current_limit_mA,
		config->stt_min_limit,
		config->stt_m1,
		config->stt_m2,
		config->stt_c_apu,
		config->stt_alpha_apu,
		config->stt_skin_temp_apu);
	acpigen_write_alib_dptc_default((uint8_t *)&default_input, sizeof(default_input));

	/* Low/No Battery */
	struct dptc_input no_battery_input = DPTC_INPUTS(
		config->thermctl_limit_degreeC,
		config->slow_ppt_time_constant_s,
		config->fast_ppt_limit_mW,
		config->slow_ppt_limit_mW,
		config->vrm_current_limit_throttle_mA,
		config->vrm_maximum_current_limit_throttle_mA,
		config->vrm_soc_current_limit_throttle_mA,
		config->stt_min_limit,
		config->stt_m1,
		config->stt_m2,
		config->stt_c_apu,
		config->stt_alpha_apu,
		config->stt_skin_temp_apu);
	acpigen_write_alib_dptc_no_battery((uint8_t *)&no_battery_input,
		sizeof(no_battery_input));

#if (CONFIG(FEATURE_TABLET_MODE_DPTC))
	struct dptc_input tablet_input = DPTC_INPUTS(
		config->thermctl_limit_degreeC,
		config->slow_ppt_time_constant_s,
		config->fast_ppt_limit_mW,
		config->slow_ppt_limit_mW,
		config->vrm_current_limit_mA,
		config->vrm_maximum_current_limit_mA,
		config->vrm_soc_current_limit_mA,
		config->stt_min_limit,
		config->stt_m1_tablet,
		config->stt_m2_tablet,
		config->stt_c_apu_tablet,
		config->stt_alpha_apu_tablet,
		config->stt_skin_temp_apu);
	acpigen_write_alib_dptc_tablet((uint8_t *)&tablet_input, sizeof(tablet_input));
#endif

#if (CONFIG(FEATURE_DYNAMIC_DPTC))
	/* Profile B */
	struct dptc_input thermal_B_input = DPTC_INPUTS(
		config->thermctl_limit_degreeC,
		config->slow_ppt_time_constant_s_B,
		config->fast_ppt_limit_mW_B,
		config->slow_ppt_limit_mW_B,
		config->vrm_current_limit_throttle_mA,
		config->vrm_maximum_current_limit_mA,
		config->vrm_soc_current_limit_mA,
		config->stt_min_limit_B,
		config->stt_m1_B,
		config->stt_m2_B,
		config->stt_c_apu_B,
		config->stt_alpha_apu,
		config->stt_skin_temp_apu_B);
	acpigen_write_alib_dptc_thermal_B((uint8_t *)&thermal_B_input,
		sizeof(thermal_B_input));

	/* Profile C */
	struct dptc_input thermal_C_input = DPTC_INPUTS(
		config->thermctl_limit_degreeC,
		config->slow_ppt_time_constant_s_C,
		config->fast_ppt_limit_mW_C,
		config->slow_ppt_limit_mW_C,
		config->vrm_current_limit_mA,
		config->vrm_maximum_current_limit_mA,
		config->vrm_soc_current_limit_mA,
		config->stt_min_limit_C,
		config->stt_m1_C,
		config->stt_m2_C,
		config->stt_c_apu_C,
		config->stt_alpha_apu,
		config->stt_skin_temp_apu_C);
	acpigen_write_alib_dptc_thermal_C((uint8_t *)&thermal_C_input,
		sizeof(thermal_C_input));

	/* Profile D */
	struct dptc_input thermal_D_input = DPTC_INPUTS(
		config->thermctl_limit_degreeC,
		config->slow_ppt_time_constant_s_D,
		config->fast_ppt_limit_mW_D,
		config->slow_ppt_limit_mW_D,
		config->vrm_current_limit_mA,
		config->vrm_maximum_current_limit_mA,
		config->vrm_soc_current_limit_mA,
		config->stt_min_limit_D,
		config->stt_m1_D,
		config->stt_m2_D,
		config->stt_c_apu_D,
		config->stt_alpha_apu,
		config->stt_skin_temp_apu_D);
	acpigen_write_alib_dptc_thermal_D((uint8_t *)&thermal_D_input,
		sizeof(thermal_D_input));

	/* Profile E */
	struct dptc_input thermal_E_input = DPTC_INPUTS(
		config->thermctl_limit_degreeC,
		config->slow_ppt_time_constant_s_E,
		config->fast_ppt_limit_mW_E,
		config->slow_ppt_limit_mW_E,
		config->vrm_current_limit_mA,
		config->vrm_maximum_current_limit_mA,
		config->vrm_soc_current_limit_mA,
		config->stt_min_limit_E,
		config->stt_m1_E,
		config->stt_m2_E,
		config->stt_c_apu_E,
		config->stt_alpha_apu,
		config->stt_skin_temp_apu_E);
	acpigen_write_alib_dptc_thermal_E((uint8_t *)&thermal_E_input,
		sizeof(thermal_E_input));

	/* Profile F */
	struct dptc_input thermal_F_input = DPTC_INPUTS(
		config->thermctl_limit_degreeC,
		config->slow_ppt_time_constant_s_F,
		config->fast_ppt_limit_mW_F,
		config->slow_ppt_limit_mW_F,
		config->vrm_current_limit_mA,
		config->vrm_maximum_current_limit_mA,
		config->vrm_soc_current_limit_mA,
		config->stt_min_limit_F,
		config->stt_m1_F,
		config->stt_m2_F,
		config->stt_c_apu_F,
		config->stt_alpha_apu,
		config->stt_skin_temp_apu_F);
	acpigen_write_alib_dptc_thermal_F((uint8_t *)&thermal_F_input,
		sizeof(thermal_F_input));
#endif
}

static void root_complex_fill_ssdt(const struct device *device)
{
	uint32_t tdp = 0;

	if (get_amd_smu_reported_tdp(&tdp) != CB_SUCCESS) {
		/* Unknown TDP, so return rather than setting invalid values. */
		return;
	}
	/* TODO(b/249359574): Add support for 6W DPTC values. */
	if (tdp != TDP_15W)
		return;

	if (CONFIG(SOC_AMD_COMMON_BLOCK_ACPI_DPTC))
		acipgen_dptci();
}

static const char *gnb_acpi_name(const struct device *dev)
{
	return "GNB";
}

struct device_operations mendocino_root_complex_operations = {
	.read_resources		= read_resources,
	.set_resources		= noop_set_resources,
	.enable_resources	= pci_dev_enable_resources,
	.init			= root_complex_init,
	.acpi_name		= gnb_acpi_name,
	.acpi_fill_ssdt		= root_complex_fill_ssdt,
};

uint32_t get_iohc_misc_smn_base(struct device *domain)
{
	return SMN_IOHC_MISC_BASE_13B1;
}

static const struct non_pci_mmio_reg non_pci_mmio[] = {
	{ 0x2d8, 0xfffffff00000ull,   1 * MiB, NON_PCI_RES_IDX_AUTO },
	{ 0x2e0, 0xfffffff00000ull,   1 * MiB, NON_PCI_RES_IDX_AUTO },
	{ 0x2e8, 0xfffffff00000ull,   1 * MiB, NON_PCI_RES_IDX_AUTO },
	/* The hardware has a 256 byte alignment requirement for the IOAPIC MMIO base, but we
	   tell the FSP to configure a 4k-aligned base address and this is reported as 4 KiB
	   resource. */
	{ 0x2f0, 0xffffffffff00ull,   4 * KiB, IOMMU_IOAPIC_IDX },
	{ 0x2f8, 0xfffffff00000ull,   1 * MiB, NON_PCI_RES_IDX_AUTO },
	{ 0x300, 0xfffffff00000ull,   1 * MiB, NON_PCI_RES_IDX_AUTO },
	{ 0x308, 0xfffffffff000ull,   4 * KiB, NON_PCI_RES_IDX_AUTO },
	{ 0x318, 0xfffffff80000ull, 512 * KiB, NON_PCI_RES_IDX_AUTO },
};

const struct non_pci_mmio_reg *get_iohc_non_pci_mmio_regs(size_t *count)
{
	*count = ARRAY_SIZE(non_pci_mmio);
	return non_pci_mmio;
}

signed int get_iohc_fabric_id(struct device *domain)
{
	switch (domain->path.domain.domain) {
	case 0:
		return IOMS0_FABRIC_ID;
	default:
		return -1;
	}
}
