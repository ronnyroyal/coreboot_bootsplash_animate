/* SPDX-License-Identifier: GPL-2.0-only */

#include <bootblock_common.h>
#include <gpio.h>
#include <soc/spi.h>

#include "gpio.h"

static void usb3_hub_reset(void)
{
	gpio_output(GPIO_USB3_HUB_RST_L, 1);
}

void bootblock_mainboard_init(void)
{
	mtk_snfc_init();
	setup_chromeos_gpios();
	usb3_hub_reset();
}
