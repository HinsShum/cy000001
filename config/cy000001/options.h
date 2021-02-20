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

/*---------- macro ----------*/
#define SYS_VERSION                             ("V1.00")
#ifndef SYS_HARD_VERSION
#define SYS_HARD_VERSION                        ("CY000001")
#endif

/* delay */
#define __delay_ms(ms)                          mdelay(ms)
#define __delay_us(us)                          udelay(us)

/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
#endif /* __RSTF103ZET6_OPTIONS_H */
