/**
 * @file components/lwip/src/portable/arch/cc.h
 *
 * Copyright (C) 2020
 *
 * cc.h is free software: you can redistribute it and/or modify
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
#ifndef __LWIP_CC_H
#define __LWIP_CC_H

/*---------- includes ----------*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "printk.h"

/*---------- macro ----------*/
/* define macro about structure package
 */
#define PACK_STRUCT_FIELD(x)            x
#define PACK_STRUCT_STRUCT
#define PACK_STRUCT_BEGIN               __packed
#define PACK_STRUCT_END

/* define macro about lwip debug
 */
#define LWIP_DEBUG
#define LWIP_PLATFORM_DIAG(x)           {printk x;}
#define LWIP_PLATFORM_ASSERT(x)         {printk(x); while(true);}
#define LWIP_ERROR(message,                                     \
                   expression, handler) do {                    \
                                            if(!(expression)) { \
                                                printk(message);\
                                                handler;        \
                                            }                   \
                                        } while(0)

#define U16_F                           "u"
#define S16_F                           "d"
#define X16_F                           "x"
#define U32_F                           "u"
#define S32_F                           "d"
#define X32_F                           "x"

/* define lwip internal errno
 */
#define LWIP_PROVIDE_ERRNO

/* define machine byte order
 */
#define BYTE_ORDER                      LITTLE_ENDIANLITTLE_ENDIAN

/*---------- type define ----------*/
/* lwip private data type typedef
 */
typedef unsigned char u8_t;
typedef signed char s8_t;
typedef unsigned short u16_t;
typedef signed short s16_t;
typedef unsigned int u32_t;
typedef signed int s32_t;
typedef unsigned int sys_prot_t;
typedef unsigned int mem_ptr_t;

/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
static inline u32_t sys_now(void)
{
    extern uint32_t HAL_GetTick(void);
    return (u32_t)HAL_GetTick();
}

#endif /* __LWIP_CC_H */