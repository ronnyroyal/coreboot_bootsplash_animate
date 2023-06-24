/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef AMD_PHOENIX_PCI_DEVS_H
#define AMD_PHOENIX_PCI_DEVS_H

#include <device/pci_def.h>
#include <amdblocks/pci_devs.h>

/* GNB Root Complex */
#define GNB_DEV			0x0
#define GNB_FUNC		0
#define GNB_DEVFN		PCI_DEVFN(GNB_DEV, GNB_FUNC)
#define SOC_GNB_DEV		_SOC_DEV(GNB_DEV, GNB_FUNC)

/* IOMMU */
#define IOMMU_DEV		0x0
#define IOMMU_FUNC		2
#define IOMMU_DEVFN		PCI_DEVFN(IOMMU_DEV, IOMMU_FUNC)
#define SOC_IOMMU_DEV		_SOC_DEV(IOMMU_DEV, IOMMU_FUNC)

/* PCIe GFX/GPP Bridge device 1 with 4 ports */
#define PCIE_GPP_BRIDGE_1_DEV	0x1

#define PCIE_GPP_1_1_FUNC	1
#define PCIE_GPP_1_1_DEVFN	PCI_DEVFN(PCIE_GPP_BRIDGE_1_DEV, PCIE_GPP_1_1_FUNC)
#define SOC_GPP_1_1_DEV		_SOC_DEV(PCIE_GPP_BRIDGE_1_DEV, PCIE_GPP_1_1_FUNC)

#define PCIE_GPP_1_2_FUNC	2
#define PCIE_GPP_1_2_DEVFN	PCI_DEVFN(PCIE_GPP_BRIDGE_1_DEV, PCIE_GPP_1_2_FUNC)
#define SOC_GPP_1_2_DEV		_SOC_DEV(PCIE_GPP_BRIDGE_1_DEV, PCIE_GPP_1_2_FUNC)

#define PCIE_GPP_1_3_FUNC	3
#define PCIE_GPP_1_3_DEVFN	PCI_DEVFN(PCIE_GPP_BRIDGE_1_DEV, PCIE_GPP_1_3_FUNC)
#define SOC_GPP_1_3_DEV		_SOC_DEV(PCIE_GPP_BRIDGE_1_DEV, PCIE_GPP_1_3_FUNC)

#define PCIE_GPP_1_4_FUNC	4
#define PCIE_GPP_1_4_DEVFN	PCI_DEVFN(PCIE_GPP_BRIDGE_1_DEV, PCIE_GPP_1_4_FUNC)
#define SOC_GPP_1_4_DEV		_SOC_DEV(PCIE_GPP_BRIDGE_1_DEV, PCIE_GPP_1_4_FUNC)

/* PCIe GPP Bridge device 2 with up to 6 ports */
#define PCIE_GPP_BRIDGE_2_DEV	0x2

#define PCIE_GPP_2_1_FUNC	1
#define PCIE_GPP_2_1_DEVFN	PCI_DEVFN(PCIE_GPP_BRIDGE_2_DEV, PCIE_GPP_2_1_FUNC)
#define SOC_GPP_2_1_DEV		_SOC_DEV(PCIE_GPP_BRIDGE_2_DEV, PCIE_GPP_2_1_FUNC)

#define PCIE_GPP_2_2_FUNC	2
#define PCIE_GPP_2_2_DEVFN	PCI_DEVFN(PCIE_GPP_BRIDGE_2_DEV, PCIE_GPP_2_2_FUNC)
#define SOC_GPP_2_2_DEV		_SOC_DEV(PCIE_GPP_BRIDGE_2_DEV, PCIE_GPP_2_2_FUNC)

#define PCIE_GPP_2_3_FUNC	3
#define PCIE_GPP_2_3_DEVFN	PCI_DEVFN(PCIE_GPP_BRIDGE_2_DEV, PCIE_GPP_2_3_FUNC)
#define SOC_GPP_2_3_DEV		_SOC_DEV(PCIE_GPP_BRIDGE_2_DEV, PCIE_GPP_2_3_FUNC)

#define PCIE_GPP_2_4_FUNC	4
#define PCIE_GPP_2_4_DEVFN	PCI_DEVFN(PCIE_GPP_BRIDGE_2_DEV, PCIE_GPP_2_4_FUNC)
#define SOC_GPP_2_4_DEV		_SOC_DEV(PCIE_GPP_BRIDGE_2_DEV, PCIE_GPP_2_4_FUNC)

#define PCIE_GPP_2_5_FUNC	5
#define PCIE_GPP_2_5_DEVFN	PCI_DEVFN(PCIE_GPP_BRIDGE_2_DEV, PCIE_GPP_2_5_FUNC)
#define SOC_GPP_2_5_DEV		_SOC_DEV(PCIE_GPP_BRIDGE_2_DEV, PCIE_GPP_2_5_FUNC)

#define PCIE_GPP_2_6_FUNC	6
#define PCIE_GPP_2_6_DEVFN	PCI_DEVFN(PCIE_GPP_BRIDGE_2_DEV, PCIE_GPP_2_6_FUNC)
#define SOC_GPP_2_6_DEV		_SOC_DEV(PCIE_GPP_BRIDGE_2_DEV, PCIE_GPP_2_6_FUNC)

/* PCIe Bridges to Bus A, Bus B and Bus C devices */
#define PCIE_ABC_BRIDGE_DEV	0x8

#define PCIE_ABC_A_FUNC		1
#define PCIE_ABC_A_DEVFN	PCI_DEVFN(PCIE_ABC_BRIDGE_DEV, PCIE_ABC_A_FUNC)
#define SOC_PCIE_ABC_A_DEV	_SOC_DEV(PCIE_ABC_BRIDGE_DEV, PCIE_ABC_A_FUNC)

#define   GFX_DEV		0x0
#define   GFX_FUNC		0
#define   GFX_DEVFN		PCI_DEVFN(GFX_DEV, GFX_FUNC)

#define   GFX_HDA_DEV		0x0
#define   GFX_HDA_FUNC		1
#define   GFX_HDA_DEVFN		PCI_DEVFN(GFX_HDA_DEV, GFX_HDA_FUNC)

#define   XHCI0_DEV		0x0
#define   XHCI0_FUNC		3
#define   XHCI0_DEVFN		PCI_DEVFN(XHCI0_DEV, XHCI0_FUNC)

#define   XHCI1_DEV		0x0
#define   XHCI1_FUNC		4
#define   XHCI1_DEVFN		PCI_DEVFN(XHCI1_DEV, XHCI1_FUNC)

#define   AUDIO_DEV		0x0
#define   AUDIO_FUNC		5
#define   AUDIO_DEVFN		PCI_DEVFN(AUDIO_DEV, AUDIO_FUNC)

#define   HD_AUDIO_DEV		0x0
#define   HD_AUDIO_FUNC		6
#define   HD_AUDIO_DEVFN	PCI_DEVFN(HD_AUDIO_DEV, HD_AUDIO_FUNC)

#define PCIE_ABC_B_FUNC		2
#define PCIE_GPP_B_DEVFN	PCI_DEVFN(PCIE_ABC_BRIDGE_DEV, PCIE_ABC_B_FUNC)
#define SOC_PCIE_GPP_B_DEV	_SOC_DEV(PCIE_ABC_BRIDGE_DEV, PCIE_ABC_B_FUNC)

#define   GFX_IPU_DEV		0x0
#define   GFX_IPU_FUNC		1
#define   GFX_IPU_DEVFN		PCI_DEVFN(GFX_IPU_DEV, GFX_IPU_FUNC)

#define PCIE_ABC_C_FUNC		3
#define PCIE_ABC_C_DEVFN	PCI_DEVFN(PCIE_ABC_BRIDGE_DEV, PCIE_ABC_C_FUNC)
#define SOC_PCIE_GPP_C_DEV	_SOC_DEV(PCIE_ABC_BRIDGE_DEV, PCIE_ABC_C_FUNC)

#define   USB4_XHCI0_DEV	0x0
#define   USB4_XHCI0_FUNC	3
#define   USB4_XHCI0_DEVFN	PCI_DEVFN(USB4_XHCI0_DEV, USB4_XHCI0_FUNC)

#define   USB4_XHCI1_DEV	0x0
#define   USB4_XHCI1_FUNC	4
#define   USB4_XHCI1_DEVFN	PCI_DEVFN(USB4_XHCI1_DEV, USB4_XHCI1_FUNC)

#define   USB4_ROUTER0_DEV	0x0
#define   USB4_ROUTER0_FUNC	5
#define   USB4_ROUTER0_DEVFN	PCI_DEVFN(USB4_ROUTER0_DEV, USB4_ROUTER0_FUNC)

#define   USB4_ROUTER1_DEV	0x0
#define   USB4_ROUTER1_FUNC	6
#define   USB4_ROUTER1_DEVFN	PCI_DEVFN(USB4_ROUTER1_DEV, USB4_ROUTER1_FUNC)

/* SMBUS */
#define SMBUS_DEV		0x14
#define SMBUS_FUNC		0
#define SMBUS_DEVFN		PCI_DEVFN(SMBUS_DEV, SMBUS_FUNC)
#define SOC_SMBUS_DEV		_SOC_DEV(SMBUS_DEV, SMBUS_FUNC)

/* LPC BUS */
#define PCU_DEV			0x14
#define LPC_FUNC		3
#define LPC_DEVFN		PCI_DEVFN(PCU_DEV, LPC_FUNC)
#define SOC_LPC_DEV		_SOC_DEV(PCU_DEV, LPC_FUNC)

/* Data Fabric functions */
#define DF_DEV			0x18

#define DF_F0_DEVFN		PCI_DEVFN(DF_DEV, 0)
#define SOC_DF_F0_DEV		_SOC_DEV(DF_DEV, 0)

#define DF_F1_DEVFN		PCI_DEVFN(DF_DEV, 1)
#define SOC_DF_F1_DEV		_SOC_DEV(DF_DEV, 1)

#define DF_F2_DEVFN		PCI_DEVFN(DF_DEV, 2)
#define SOC_DF_F2_DEV		_SOC_DEV(DF_DEV, 2)

#define DF_F3_DEVFN		PCI_DEVFN(DF_DEV, 3)
#define SOC_DF_F3_DEV		_SOC_DEV(DF_DEV, 3)

#define DF_F4_DEVFN		PCI_DEVFN(DF_DEV, 4)
#define SOC_DF_F4_DEV		_SOC_DEV(DF_DEV, 4)

#define DF_F5_DEVFN		PCI_DEVFN(DF_DEV, 5)
#define SOC_DF_F5_DEV		_SOC_DEV(DF_DEV, 5)

#define DF_F6_DEVFN		PCI_DEVFN(DF_DEV, 6)
#define SOC_DF_F6_DEV		_SOC_DEV(DF_DEV, 6)

#define DF_F7_DEVFN		PCI_DEVFN(DF_DEV, 7)
#define SOC_DF_F7_DEV		_SOC_DEV(DF_DEV, 7)

#endif /* AMD_PHOENIX_PCI_DEVS_H */
