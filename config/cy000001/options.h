/**
 * @file /config/CY000001/options.h
 *
 * Copyright (C) 2020
 *
 * options.h is free software: you can redistribute it and/or modify
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
#ifndef __RSTF103ZET6_OPTIONS_H
#define __RSTF103ZET6_OPTIONS_H

/*---------- includes ----------*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "stm32f1xx_ll_conf.h"
#include "cpu.h"
#include "version.h"

/*---------- macro ----------*/
#undef assert
#ifdef NDEBUG
#define assert(expr)                            ((void)0U)
#else
#define assert(expr)                            do { if(!(expr)) { for(;;); }} while(0)
#endif

/* format to string
 */
#define _STRING(x)                              #x              /*<< only format alphabet as string */
#define STRING(x)                               _STRING(x)      /*<< format alphabet or digit as string */

/* system variables defined
 */
#define SYS_VERSION                             ((VERSION_MAJOR << 24) | (VERSION_MINOR << 16) | (VERSION_FIX << 8) | VERSION_BUILD)
#define SYS_VERSION_STRING                      (STRING(VERSION_MAJOR)"."STRING(VERSION_MINOR)"."STRING(VERSION_FIX)"."STRING(VERSION_BUILD))
#define SYS_MODEL_NAME                          ("CY000001")
#define SYS_HW_VERSION                          ((HW_VERSION_MAJOR << 8) | HW_VERSION_MINOR)
#define SYS_PRODUCT_TIME                        (__DATE__)

/* delay */
#define __delay_ms(ms)                          mdelay(ms)
#define __delay_us(us)                          udelay(us)
#define __get_ticks()                           tick_get()
#define MS2TICKS(ms)                            (ms)

/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
extern void mdelay(uint32_t delay);
extern void udelay(uint32_t us);

#endif /* __RSTF103ZET6_OPTIONS_H */
