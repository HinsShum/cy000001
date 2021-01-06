/**
 * @file driver/driver.c
 *
 * Copyright (C) 2021
 *
 * driver.c is free software: you can redistribute it and/or modify
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
#include "driver.h"
#include "device.h"
#include "config/errorno.h"
#include <string.h>

/*---------- macro ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- type define ----------*/
/*---------- variable ----------*/
/*---------- function ----------*/
int32_t driver_search_device(void)
{
    extern driver_t _sdrv;
    extern driver_t _edrv;
    extern device_t _sdev;
    extern device_t _edev;

    driver_t *drv = NULL;
    device_t *dev = NULL;

    for(dev = &_sdev; dev < &_edev; ++dev) {
        for(drv = &_sdrv; drv < &_edrv; ++drv) {
            if(!strncmp(dev->drv_name, drv->drv_name, sizeof(drv->drv_name))) {
                dev->pdrv = drv;
            }
        }
    }

    return CY_EOK;
}
