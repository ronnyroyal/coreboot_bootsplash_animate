## SPDX-License-Identifier: GPL-2.0-only

ifeq ($(CONFIG_MEMORY_MAPPED_TPM),y)
all-y += tis.c
endif
