/**
 * @file bsp/CY000001/bsp_print.c
 *
 * Copyright (C) 2020
 *
 * bsp_print.c is free software: you can redistribute it and/or modify
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
#include "bsp_print.h"
#include "stm32f1xx_ll_conf.h"
#include "printk.h"

/*---------- macro ----------*/
#define _BSP_TX_PORT                (GPIOA)
#define _BSP_TX_PIN                 (LL_GPIO_PIN_9)
#define _BSP_RX_PORT                (GPIOA)
#define _BSP_RX_PIN                 (LL_GPIO_PIN_10)
#define _BSP_UART                   (USART1)

/*---------- variable prototype ----------*/
extern struct con console_driver;

/*---------- function prototype ----------*/
/*---------- type define ----------*/
/*---------- variable ----------*/
/*---------- function ----------*/
static void bsp_print_io_init(void)
{
    LL_GPIO_InitTypeDef gpio_init_structure;

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
    while(true != LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_GPIOA));

    LL_GPIO_StructInit(&gpio_init_structure);
    gpio_init_structure.Pin = _BSP_RX_PIN;
    LL_GPIO_Init(_BSP_RX_PORT, &gpio_init_structure);

    gpio_init_structure.Pin = _BSP_TX_PIN;
    gpio_init_structure.Mode = LL_GPIO_MODE_ALTERNATE;
    gpio_init_structure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(_BSP_TX_PORT, &gpio_init_structure);
}

static void bsp_print_reg_init(void)
{
    LL_USART_InitTypeDef uart_init_structure;

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
    while(true != LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_USART1));

    LL_USART_StructInit(&uart_init_structure);
    uart_init_structure.BaudRate = 115200;
    LL_USART_Init(_BSP_UART, &uart_init_structure);
    LL_USART_ConfigAsyncMode(_BSP_UART);

    LL_USART_Enable(_BSP_UART);
}

static void bsp_print_putc(char ch)
{
    if('\n' == ch) {
        LL_USART_TransmitData8(_BSP_UART, '\r');
        while(SET != LL_USART_IsActiveFlag_TC(_BSP_UART));
    }
    LL_USART_TransmitData8(_BSP_UART, ch);
    while(SET != LL_USART_IsActiveFlag_TC(_BSP_UART));
}

static unsigned int bsp_print_puts(const char *s, unsigned int len)
{
    uint32_t i = 0;

    for(; (i < len) && ('\0' != s[i]); ++i) {
        bsp_print_putc(s[i]);
    }

    return i;
}

static void bsp_print_register(void)
{
    console_driver.getc = NULL;
    console_driver.write = bsp_print_puts;
}

bool bsp_print_init(void)
{
    bsp_print_io_init();
    bsp_print_reg_init();
    bsp_print_register();

    return true;
}

void bsp_print_deinit(void)
{
    console_driver.getc = NULL;
    console_driver.write = NULL;
    LL_USART_DeInit(_BSP_UART);
}
