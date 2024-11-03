/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef __SOC_MEDIATEK_COMMON_DISPLAY_H__
#define __SOC_MEDIATEK_COMMON_DISPLAY_H__

#include <commonlib/coreboot_tables.h>
#include <mipi/panel.h>

enum disp_path_sel {
	DISP_PATH_NONE = 0,
	DISP_PATH_EDP,
	DISP_PATH_MIPI,
};

struct panel_description {
	const char *name;
	void (*configure_backlight)(void);
	void (*power_on)(void);
	int (*get_edid)(struct edid *edid);
	int (*post_power_on)(const struct edid *edid);
	enum lb_fb_orientation orientation;
	enum disp_path_sel disp_path;
	bool pwm_ctrl_gpio;
};

int mtk_display_init(void);
struct panel_description *get_active_panel(void);

void mtk_ddp_init(void);
void mtk_ddp_mode_set(const struct edid *edid, enum disp_path_sel path);

#endif
