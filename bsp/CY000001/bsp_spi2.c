/**
 * @file bsp/CY000001/bsp_spi2.c
 *
 * Copyright (C) 2020
 *
 * bsp_spi2.c is free software: you can redistribute it and/or modify
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
#include "bsp_spi2.h"
#include "stm32f1xx_ll_conf.h"
// #include "enc28j60.h"

/*---------- macro ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- type define ----------*/
/*---------- variable ----------*/
// static struct st_enc28j60_describe m_enc28j60;

/*---------- function ----------*/
static void bsp_spi2_io_init(void)
{
    LL_GPIO_InitTypeDef gpio_init_structure = {0};

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
    while(LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_GPIOB));
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOD);
    while(LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_GPIOD));

    /* GPIO configure
     * CS   ---> PD8
     * SCK  ---> PB13
     * MISO ---> PB14
     * MOSI ---> PB15
     */
    LL_GPIO_StructInit(&gpio_init_structure);
    gpio_init_structure.Pin = LL_GPIO_PIN_14;
    LL_GPIO_Init(GPIOB, &gpio_init_structure);

    gpio_init_structure.Pin = LL_GPIO_PIN_8;
    gpio_init_structure.Mode = LL_GPIO_MODE_OUTPUT;
    gpio_init_structure.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    gpio_init_structure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOD, &gpio_init_structure);
    LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_8);

    gpio_init_structure.Pin = LL_GPIO_PIN_13 | LL_GPIO_PIN_15;
    gpio_init_structure.Mode = LL_GPIO_MODE_ALTERNATE;
    gpio_init_structure.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    gpio_init_structure.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    LL_GPIO_Init(GPIOB, &gpio_init_structure);
}

static void bsp_spi2_reg_init(void)
{
    LL_SPI_InitTypeDef spi_init_structure;

    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);
    while(true != LL_APB1_GRP1_IsEnabledClock(LL_APB1_GRP1_PERIPH_SPI2));
    /* spi clock = 72M / 64 = 1.125M */
    LL_SPI_StructInit(&spi_init_structure);
    spi_init_structure.Mode = LL_SPI_MODE_MASTER;
    spi_init_structure.ClockPolarity = LL_SPI_POLARITY_LOW;
    spi_init_structure.ClockPhase = LL_SPI_PHASE_1EDGE;
    spi_init_structure.NSS = LL_SPI_NSS_SOFT;
    spi_init_structure.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV64;
    LL_SPI_Init(SPI2, &spi_init_structure);
    LL_SPI_Enable(SPI2);
}

// static uint8_t bsp_spi2_xfer(uint8_t ch)
// {
//     while(true != LL_SPI_IsActiveFlag_TXE(SPI2));
//     LL_SPI_TransmitData8(SPI2, ch);
//     while(true != LL_SPI_IsActiveFlag_RXNE(SPI2));
//     return LL_SPI_ReceiveData8(SPI2);
// }

// static bool bsp_spi2_cs_ctl(bool on)
// {
//     if(on) {
//         LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_8);
//     } else {
//         LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_8);
//     }

//     return true;
// }

bool bsp_spi2_init(void)
{
    bsp_spi2_io_init();
    bsp_spi2_reg_init();

    // m_enc28j60.xfer = bsp_spi2_xfer;
    // m_enc28j60.cs_ctrl = bsp_spi2_cs_ctl;
    // enc28j60_register(&m_enc28j60);

    return true;
}

void bsp_spi2_deinit(void)
{
    LL_SPI_Disable(SPI2);
    LL_SPI_DeInit(SPI2);
}
