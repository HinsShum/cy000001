/**
 * @file src/platform.c
 *
 * Copyright (C) 2020
 *
 * platform.c is free software: you can redistribute it and/or modify
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
#include "platform.h"
#include "bsp.h"
#include "bsp_led.h"
#include "led.h"
#include "config/errorno.h"
#include "config/options.h"

/*---------- macro ----------*/
/*---------- variable prototype ----------*/
extern struct st_device dev_led_ds0;
extern struct st_device dev_led_ds1;

/*---------- function prototype ----------*/
/*---------- type define ----------*/
typedef bool (*init_fnc_t)(void);
typedef void (*deinit_fnc_t)(void);

/*---------- variable ----------*/
static init_fnc_t init_fnc_sequence[] = {
    bsp_init,
    bsp_systick1ms_init,
    bsp_led_init,
    NULL
};

static deinit_fnc_t deinit_fnc_sequence[] = {
    bsp_deinit,
    bsp_led_deinit,
    NULL
};

/*---------- function ----------*/
static void platform_peripherals_init(void)
{
    init_fnc_t *init_fnc_ptr = NULL;

    __disable_irq();
    for(init_fnc_ptr = init_fnc_sequence; NULL != *init_fnc_ptr; ++init_fnc_ptr) {
        if(true != (*init_fnc_ptr)()) {
            while(true);    /*<< blocking here, wait watch dog to reset the device */
        }
    }
    __enable_irq();
}

static void platform_peripherals_deinit(void)
{
    deinit_fnc_t *deinit_fnc_ptr = NULL;

    for(deinit_fnc_ptr = deinit_fnc_sequence; NULL != deinit_fnc_ptr; ++deinit_fnc_ptr) {
        (*deinit_fnc_ptr)();
    }
}

static int32_t platform_misc_init(void)
{
    return CY_EOK;
}

static int32_t platform_driver_init(void)
{
    uint32_t led_blink = 500;

    /* set ds0 led blinking every 500ms */
    device_ioctl(&dev_led_ds0, DEVICE_IOCTL_LED_SET_BLINK_TIME, (void *)&led_blink);

    return CY_EOK;
}

void platform_hw_init(void)
{
    platform_peripherals_init();
}

void platform_hw_deinit(void)
{
    platform_peripherals_deinit();
}

int32_t platform_init(void)
{
    platform_driver_init();
    platform_misc_init();

    return CY_EOK;
}
