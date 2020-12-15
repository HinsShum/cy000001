/**
 * @file components/lwip/src/portable/arch/lwipopts.h
 *
 * Copyright (C) 2020
 *
 * lwipopts.h is free software: you can redistribute it and/or modify
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
#ifndef __LWIPOPTS_H
#define __LWIPOPTS_H

/*---------- includes ----------*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*---------- macro ----------*/
/* no sys arch
 */
#define NO_SYS                  1

/* define whether compile sockt API and sequential API
 */
#define LWIP_SOCKET             0
#define LWIP_NETCONN            0

/* define align bytes
 */
#define MEM_ALIGNMENT           4

/* define lwip internal heap size
 */ 
#define MEM_SIZE                1024 * 30

/* define lwip tcp send buffer maximum size
 */
#define TCP_SND_BUF             4000

/* define TCP message maximum size
 */
#define TCP_MSS                 1000

/* define whether allow lwip print arp debug information
 */
#define ETHARP_DEBUG            LWIP_DBG_ON

/* define whether allow lwip print icmp debug information
 */
#define ICMP_DEBUG              LWIP_DBG_ON

/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
#endif /* __LWIPOPTS_H */