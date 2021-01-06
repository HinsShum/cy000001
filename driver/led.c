/**
 * @file /driver/led.c
 *
 * Copyright (C) 2020
 *
 * led.c is free software: you can redistribute it and/or modify
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
 */

/*---------- includes ----------*/
#include "led.h"
#include "config/errorno.h"
#include "config/assert.h"
#include "driver.h"
#include "device.h"

/*---------- macro ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- type define ----------*/
/*---------- variable ----------*/
/*---------- function ----------*/
static int32_t led_open(driver_t **pdrv)
{
    struct st_led_describe *pdesc = NULL;
    int32_t retval = CY_EOK;

    assert(pdrv);
    pdesc = container_of(pdrv, device_t, pdrv)->pdesc;
    if(pdesc && pdesc->init) {
        pdesc->init();
    }

    return retval;
}

static void led_close(driver_t **pdrv)
{
    struct st_led_describe *pdesc = NULL;

    assert(pdrv);
    pdesc = container_of(pdrv, device_t, pdrv)->pdesc;
    if(pdesc && pdesc->deinit) {
        pdesc->deinit();
    }
}

static int32_t led_ioctl(driver_t **pdrv, uint32_t cmd, void *arg)
{
    struct st_led_describe *pdesc = NULL;
    int32_t retval = CY_EOK;

    assert(pdrv);

    pdesc = container_of(pdrv, device_t, pdrv)->pdesc;
    switch(cmd) {
        case DEVICE_IOCTL_LED_ON:
            if(pdesc->ctrl) {
                pdesc->ctrl(true);
            }
            break;
        case DEVICE_IOCTL_LED_OFF:
            if(pdesc->ctrl) {
                pdesc->ctrl(false);
            }
            break;
        case DEVICE_IOCTL_LED_TOGGLE:
            if(pdesc->toggle) {
                pdesc->toggle();
            }
            break;
        case DEVICE_IOCTL_LED_SET_BLINK_TIME:
            if(arg) {
                pdesc->blink_time = *(uint32_t *)arg;
            }
            break;
        case DEVICE_IOCTL_LED_GET_BLINK_TIME:
            if(arg) {
                *(uint32_t *)arg = pdesc->blink_time;
            }
            break;
        default:
            retval = CY_E_WRONG_ARGS;
            break;
    }

    return retval;
}

DRIVER_DEFINED(led, led_open, led_close, NULL, NULL, led_ioctl, NULL);
