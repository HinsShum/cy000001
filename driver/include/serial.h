/**
 * @file driver/include/serial.h
 *
 * Copyright (C) 2021
 *
 * serial.h is free software: you can redistribute it and/or modify
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
#ifndef __SERIAL_H
#define __SERIAL_H

/*---------- includes ----------*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <device.h>

/*---------- macro ----------*/
#define IOCTL_SERIAL_GET_COMPORT                    (IOCTL_USER_START + 0x00)
#define IOCTL_SERIAL_SET_IRQ_HANDLER                (IOCTL_USER_START + 0x01)

/*---------- type define ----------*/
typedef struct {
    uint8_t comport;
    bool (*init)(void);
    void (*deinit)(void);
    uint16_t (*write)(uint8_t *pbuf, uint16_t len);
    int32_t (*irq_handler)(uint32_t irq_handler, void *args, uint32_t len);
} serial_describe_t;

/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
#endif /* __SERIAL_H */