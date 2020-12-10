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

/*---------- macro ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- type define ----------*/
/*---------- variable ----------*/
/*---------- function ----------*/
static int32_t led_ioctl(struct st_device *pdev, uint32_t cmd, void *arg)
{
    struct st_led_describe *pled = NULL;
    int32_t retval = CY_EOK;

    assert(pdev);
    assert(pdev->user);

    pled = (struct st_led_describe *)pdev->user;

    switch(cmd) {
        case DEVICE_IOCTL_LED_ON:
            if(pled->ctrl) {
                pled->ctrl(true);
            }
            break;
        case DEVICE_IOCTL_LED_OFF:
            if(pled->ctrl) {
                pled->ctrl(false);
            }
            break;
        case DEVICE_IOCTL_LED_TOGGLE:
            if(pled->toggle) {
                pled->toggle();
            }
            break;
        case DEVICE_IOCTL_LED_SET_BLINK_TIME:
            if(arg) {
                pled->blink_time = *(uint32_t *)arg;
            }
            break;
        case DEVICE_IOCTL_LED_GET_BLINK_TIME:
            if(arg) {
                *(uint32_t *)arg = pled->blink_time;
            }
            break;
        default:
            retval = CY_E_WRONG_ARGS;
            break;
    }

    return retval;
}

int32_t led_register(struct st_device *pdev, struct st_led_describe *pled)
{
    assert(pdev);
    assert(pled);

    pdev->attrib = 0;
    pdev->init = NULL;
    pdev->write = NULL;
    pdev->read = NULL;
    pdev->ioctl = led_ioctl;
    pdev->user = (void *)pled;

    return CY_EOK;
}
