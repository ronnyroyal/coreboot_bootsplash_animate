/* SPDX-License-Identifier: GPL-2.0-only */

#include <device/azalia_device.h>

const u32 cim_verb_data[] = {
	0x10ec0269,	/* Codec Vendor/Device ID: Realtek ALC269 */
	0x10ec0269,	/* Subsystem ID */
	16,		/* Number of entries */

	AZALIA_RESET(0x1),

	AZALIA_SUBVENDOR(0, 0x10ec0269),
	AZALIA_PIN_CFG(0, 0x12, 0x90a60130), /* DMIC */
	AZALIA_PIN_CFG(0, 0x14, 0x90170110), /* FRONT */
	AZALIA_PIN_CFG(0, 0x17, 0x40000000), /* N/C */
	AZALIA_PIN_CFG(0, 0x18, 0x04a11020), /* MIC1 */
	AZALIA_PIN_CFG(0, 0x19, 0x411111f0), /* N/C */
	AZALIA_PIN_CFG(0, 0x1a, 0x411111f0), /* N/C */
	AZALIA_PIN_CFG(0, 0x1b, 0x411111f0), /* N/C */
	AZALIA_PIN_CFG(0, 0x1d, 0x40e38105), /* BEEP */
	AZALIA_PIN_CFG(0, 0x1e, 0x411111f0), /* N/C */
	AZALIA_PIN_CFG(0, 0x21, 0x0421101f), /* HP-OUT */

	/* EQ */
	0x02050011,
	0x02040710,
	0x02050012,
	0x02041901,

	0x0205000D,
	0x02044440,
	0x02050007,
	0x02040040,

	0x02050002,
	0x0204AAB8,
	0x02050008,
	0x02040300,

	0x02050017,
	0x020400AF,
	0x02050005,
	0x020400C0,

	0x8086281a,	/* Codec Vendor/Device ID: Intel Jasper Lake HDMI */
	0x80860101,	/* Subsystem ID */
	6,		/* Number of entries */

	AZALIA_SUBVENDOR(2, 0x80860101),
	AZALIA_PIN_CFG(2, 0x04, 0x18560010),
	AZALIA_PIN_CFG(2, 0x06, 0x18560010),
	AZALIA_PIN_CFG(2, 0x08, 0x18560010),
	AZALIA_PIN_CFG(2, 0x0a, 0x18560010),
	AZALIA_PIN_CFG(2, 0x0b, 0x18560010),
};

const u32 pc_beep_verbs[] = {};

AZALIA_ARRAY_SIZES;
