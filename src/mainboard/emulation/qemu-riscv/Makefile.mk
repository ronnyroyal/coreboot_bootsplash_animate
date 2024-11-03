## SPDX-License-Identifier: GPL-2.0-only

bootblock-y += mainboard.c
bootblock-y += uart.c
bootblock-y += rom_media.c
bootblock-y += clint.c

romstage-y += cbmem.c
romstage-y += romstage.c
romstage-y += uart.c
romstage-y += rom_media.c
romstage-y += clint.c

ramstage-y += mainboard.c
ramstage-y += uart.c
ramstage-y += rom_media.c
ramstage-y += clint.c
ramstage-y += cbmem.c
ramstage-y += chip.c

CPPFLAGS_common += -I$(src)/mainboard/$(MAINBOARDDIR)/include
