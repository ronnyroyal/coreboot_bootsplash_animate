/* SPDX-License-Identifier: GPL-2.0-only */

/* DefinitionBlock Statement */
#include <acpi/acpi.h>
DefinitionBlock (
	"dsdt.aml",
	"DSDT",
	ACPI_DSDT_REV_2,
	OEM_ID,
	ACPI_TABLE_CREATOR,
	0x00010001	/* OEM Revision */
)
{	/* Start of ASL file */
	#include <globalnvs.asl>
} /* End of ASL file */
