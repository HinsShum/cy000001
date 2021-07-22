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
#include "led.h"
#include "driver.h"
#include "printk.h"
#include "config/errorno.h"
#include "config/options.h"

/*---------- macro ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- type define ----------*/
/*---------- variable ----------*/
platform_describe_t g_platform;

/* logo and copyright
 */
static const char *copyright_notice[] =
{
    " ",
    "============================================================",
    "=  (C) COPYRIGHT 2021                                      =",
    "=                                                          =",
    "=  Program Information:                                    =",
    "=     cy000001 Application                                 =",
    "=                                              By HinsShum =",
    "============================================================",
    "\0"
};

/*---------- function ----------*/
static void platform_sayhello(void)
{
    /* print copyright */
    for(const char **pcopyright = copyright_notice; **pcopyright != 0; pcopyright++) {
        printk(KERN_INFO "%s\n", (const char *)*pcopyright);
    }
}

static int32_t platform_misc_init(void)
{
    led_cycle_t led = {0};

    platform_sayhello();
    led.cycle_count = LED_CYCLE_COUNT_MAX;
    led.cycle_time = 500;
    device_ioctl(g_platform.handler.dev_led0, IOCTL_LED_SET_CYCLE, &led);

    return CY_EOK;
}

static unsigned int platform_low_level_printk(const char *s, unsigned int len)
{
    return device_write(g_platform.handler.dev_printk, (void *)s, 0, len);
}

static int32_t platform_driver_init(void)
{
    driver_search_device();

    /* open devices */
    g_platform.handler.dev_led0 = device_open("led_ds0");
    g_platform.handler.dev_printk = device_open("print");
    /* assert device's handler */
    assert(g_platform.handler.dev_led0);
    assert(g_platform.handler.dev_printk);
    /* initialize console */
    console_driver_init(platform_low_level_printk);

    return CY_EOK;
}

int32_t platform_init(void)
{
    platform_driver_init();
    platform_misc_init();

    return CY_EOK;
}
