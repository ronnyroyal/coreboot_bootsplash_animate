/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <commonlib/helpers.h>
#include <soc/gpio.h>

/* Pad configuration in ramstage */
static const struct pad_config override_gpio_table[] = {
	/* A21 : GPP_A21 ==> NC */
	PAD_NC(GPP_A21, NONE),
	/* A21 : GPP_A22 ==> NC */
	PAD_NC(GPP_A22, NONE),
	/* B5  : GPP_B5 ==> NC */
	PAD_NC_LOCK(GPP_B5, NONE, LOCK_CONFIG),
	/* B6  : GPP_B6 ==> NC */
	PAD_NC_LOCK(GPP_B6, NONE, LOCK_CONFIG),
	/* D3  : ISH_GP3 ==> NC */
	PAD_NC_LOCK(GPP_D3, NONE, LOCK_CONFIG),
	/* D8  : SRCCLKREQ3# ==> NC */
	PAD_NC(GPP_D8, NONE),
	/* D15 : ISH_UART0_RTS# ==> NC */
	PAD_NC_LOCK(GPP_D15, NONE, LOCK_CONFIG),
	/* D16 : ISH_UART0_CTS# ==> NC */
	PAD_NC_LOCK(GPP_D16, NONE, LOCK_CONFIG),
	/* F6  : CNV_PA_BLANKING ==> NC */
	PAD_NC(GPP_F6, NONE),
	/* F13 : SOC_PEN_DETECT_R_ODL ==> NC */
	PAD_NC(GPP_F13, NONE),
	/* F15 : SOC_PEN_DETECT_ODL ==> NC */
	PAD_NC_LOCK(GPP_F15, NONE, LOCK_CONFIG),
	/* H8  : CNV_MFUART2_RXD ==> NC */
	PAD_NC(GPP_H8, NONE),
	/* H9  : CNV_MFUART2_TXD ==> NC */
	PAD_NC(GPP_H9, NONE),
	/* H12 : UART0_RTS# ==> NC */
	PAD_NC_LOCK(GPP_H12, NONE, LOCK_CONFIG),
	/* H13 : UART0_CTS# ==> NC */
	PAD_NC_LOCK(GPP_H13, NONE, LOCK_CONFIG),
	/* H22 : IMGCLKOUT3 ==> NC */
	PAD_NC(GPP_H22, NONE),
	/* R6  : DMIC_CLK_A_1A ==> NC */
	PAD_NC(GPP_R6, NONE),
	/* R7  : DMIC_DATA_1A ==> NC */
	PAD_NC(GPP_R7, NONE),
};

/* Early pad configuration in bootblock */
static const struct pad_config early_gpio_table[] = {
	/* A13 : GPP_A13 ==> GSC_SOC_INT_ODL */
	PAD_CFG_GPI_APIC(GPP_A13, NONE, PLTRST, LEVEL, INVERT),
	/* E12 : THC0_SPI1_IO1 ==> SOC_WP_OD */
	PAD_CFG_GPI_GPIO_DRIVER(GPP_E12, NONE, DEEP),
	/* F18 : THC1_SPI2_INT# ==> EC_IN_RW_OD */
	PAD_CFG_GPI(GPP_F18, NONE, DEEP),
	/* H4  : I2C0_SDA ==> SOC_I2C_GSC_SDA */
	PAD_CFG_NF(GPP_H4, NONE, DEEP, NF1),
	/* H5  : I2C0_SCL ==> SOC_I2C_GSC_SCL */
	PAD_CFG_NF(GPP_H5, NONE, DEEP, NF1),
	/* H10 : UART0_RXD ==> UART_SOC_RX_DBG_TX */
	PAD_CFG_NF(GPP_H10, NONE, DEEP, NF2),
	/* H11 : UART0_TXD ==> UART_SOC_TX_DBG_RX */
	PAD_CFG_NF(GPP_H11, NONE, DEEP, NF2),
};

const struct pad_config *variant_gpio_override_table(size_t *num)
{
	*num = ARRAY_SIZE(override_gpio_table);
	return override_gpio_table;
}

const struct pad_config *variant_early_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(early_gpio_table);
	return early_gpio_table;
}
