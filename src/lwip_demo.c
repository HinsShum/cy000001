/**
 * @file src/lwip_demo.c
 *
 * Copyright (C) 2020
 *
 * lwip_demo.c is free software: you can redistribute it and/or modify
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
#include "lwip/netif.h"
#include "lwip/ip.h"
#include "lwip/tcp.h"
#include "lwip/init.h"
#include "lwip/timers.h"
#include "netif/etharp.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*---------- macro ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
extern err_t ethernetif_init(struct netif *netif);
extern void process_mac(void);

/*---------- type define ----------*/
/*---------- variable ----------*/
struct netif enc28j60_netif;

/*---------- function ----------*/
static void lwip_demo_task_init(void)
{
    struct ip_addr ip, netmask, gateway;

    lwip_init();
    IP4_ADDR(&gateway, 192, 168, 1, 1);
    IP4_ADDR(&ip, 192, 168, 1, 2);
    IP4_ADDR(&netmask, 255, 255, 255, 0);
    netif_add(&enc28j60_netif, &ip, &netmask, &gateway, NULL,
              ethernetif_init, ethernet_input);
    netif_set_default(&enc28j60_netif);
    netif_set_up(&enc28j60_netif);
}

void lwip_demo_task(void)
{
    lwip_demo_task_init();

    while(true) {
        process_mac();
        sys_check_timeouts();
    }
}
