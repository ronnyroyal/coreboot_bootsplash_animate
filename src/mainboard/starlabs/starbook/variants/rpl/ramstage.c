/* SPDX-License-Identifier: GPL-2.0-only */

#include <option.h>
#include <soc/ramstage.h>


void mainboard_silicon_init_params(FSP_S_CONFIG *supd)
{
	if (get_uint_option("thunderbolt", 1) == 0)
		supd->UsbTcPortEn = 0;
}
