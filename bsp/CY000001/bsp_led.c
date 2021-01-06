/**
 * @file bsp/CY000001/bsp_led.c
 *
 * Copyright (C) 2020
 *
 * bsp_led.c is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author HinsShum hinsshum@qq.com
 *
 * @encoding utf-8
 */

/*---------- includes ----------*/
#include "bsp_led.h"
#include "stm32f1xx_ll_conf.h"
#include "led.h"
#include "device.h"

/*---------- macro ----------*/
#define _BSP_LED_DS0_PORT           (GPIOB)
#define _BSP_LED_DS0_PIN            (LL_GPIO_PIN_5)
#define _BSP_LED_DS1_PORT           (GPIOE)
#define _BSP_LED_DS1_PIN            (LL_GPIO_PIN_5)

/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
static void bsp_led_ds0_io_init(void);
static void bsp_led_ds0_ctrl(bool on);
static void bsp_led_ds0_toggle(void);
static void bsp_led_ds0_deinit(void);
static void bsp_led_ds1_io_init(void);
static void bsp_led_ds1_ctrl(bool on);
static void bsp_led_ds1_toggle(void);
static void bsp_led_ds1_deinit(void);

/*---------- type define ----------*/
/*---------- variable ----------*/
static struct st_led_describe m_led_ds0 = {
    .blink_time = 0,
    .init = bsp_led_ds0_io_init,
    .deinit = bsp_led_ds0_deinit,
    .ctrl = bsp_led_ds0_ctrl,
    .toggle = bsp_led_ds0_toggle
};

static struct st_led_describe m_led_ds1 = {
    .blink_time = 0,
    .init = bsp_led_ds1_io_init,
    .deinit = bsp_led_ds1_deinit,
    .ctrl = bsp_led_ds1_ctrl,
    .toggle = bsp_led_ds1_toggle
};

/*---------- function ----------*/
static void bsp_led_ds0_io_init(void)
{
    LL_GPIO_InitTypeDef gpio_init_structure = {0};

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
    while(true != LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_GPIOB));

    gpio_init_structure.Pin = _BSP_LED_DS0_PIN;
    gpio_init_structure.Mode = LL_GPIO_MODE_OUTPUT;
    gpio_init_structure.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    gpio_init_structure.Speed = LL_GPIO_SPEED_FREQ_LOW;
    LL_GPIO_Init(_BSP_LED_DS0_PORT, &gpio_init_structure);
    LL_GPIO_SetOutputPin(_BSP_LED_DS0_PORT, _BSP_LED_DS0_PIN);
}

static void bsp_led_ds1_io_init(void)
{
    LL_GPIO_InitTypeDef gpio_init_structure = {0};

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOE);
    while(true != LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_GPIOE));

    gpio_init_structure.Pin = _BSP_LED_DS1_PIN;
    gpio_init_structure.Mode = LL_GPIO_MODE_OUTPUT;
    gpio_init_structure.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    gpio_init_structure.Speed = LL_GPIO_SPEED_FREQ_LOW;
    LL_GPIO_Init(_BSP_LED_DS1_PORT, &gpio_init_structure);
    LL_GPIO_SetOutputPin(_BSP_LED_DS1_PORT, _BSP_LED_DS1_PIN);
}

static void bsp_led_ds0_ctrl(bool on)
{
    if(on) {
        LL_GPIO_ResetOutputPin(_BSP_LED_DS0_PORT, _BSP_LED_DS0_PIN);
    } else {
        LL_GPIO_SetOutputPin(_BSP_LED_DS0_PORT, _BSP_LED_DS0_PIN);
    }
}

static void bsp_led_ds1_ctrl(bool on)
{
    if(on) {
        LL_GPIO_ResetOutputPin(_BSP_LED_DS1_PORT, _BSP_LED_DS1_PIN);
    } else {
        LL_GPIO_SetOutputPin(_BSP_LED_DS1_PORT, _BSP_LED_DS1_PIN);
    }
}

static void bsp_led_ds0_toggle(void)
{
    LL_GPIO_TogglePin(_BSP_LED_DS0_PORT, _BSP_LED_DS0_PIN);
}

static void bsp_led_ds1_toggle(void)
{
    LL_GPIO_TogglePin(_BSP_LED_DS1_PORT, _BSP_LED_DS1_PIN);
}

static void bsp_led_ds0_deinit(void)
{
    LL_GPIO_SetOutputPin(_BSP_LED_DS0_PORT, _BSP_LED_DS0_PIN);
}

static void bsp_led_ds1_deinit(void)
{
    LL_GPIO_SetOutputPin(_BSP_LED_DS1_PORT, _BSP_LED_DS1_PIN);
}

DEVICE_DEFINED(led_ds0, led, &m_led_ds0);
DEVICE_DEFINED(led_ds1, led, &m_led_ds1);
