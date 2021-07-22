/**
 * @file /arch/stm32f103xx/CY000001/cpu.c
 *
 * Copyright (C) 2020
 *
 * cpu_freq.c is free software: you can redistribute it and/or modify
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
#include "cpu.h"
#include "stm32f1xx_ll_conf.h"

/*---------- macro ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/*---------- type define ----------*/
/*---------- variable ----------*/
static __IO uint32_t tick = 0;
static uint32_t clk_cycle = 0;

/*---------- function ----------*/
static void cpu_freq_config(void)
{
    LL_UTILS_PLLInitTypeDef pll_init_structure = {0};
    LL_UTILS_ClkInitTypeDef clk_init_structure = {0};

    /* Restore RCC */
    LL_RCC_DeInit();
    /* Enable Prefetch Buffer */
    LL_FLASH_EnablePrefetch();
    /* After a system reset, the HSI oscollator will be selected as system clock.
     * If config System clock from HSE failed, automatic switch to HSI(MAX: 64MHz)
     * HSI will keep enable, it will be used when operate embedded flash memory
     * AHB_CLK = PLL_CLK/1
     * APB1_CLK = AHB_CLK/2
     * APB2_CLK = AHB_CLK/1
     * APB1_PERIPHERAL = APB1_CLK
     * APB1_TIMER = APB1_CLK * 2
     * APB2_PERIPHERAL = APB2_CLK
     * APB2_TIMER = APB2_CLK
     */
#if HSE_VALUE > 8000000
    pll_init_structure.Prediv =LL_RCC_PREDIV_DIV_2;
#else
    pll_init_structure.Prediv = LL_RCC_PREDIV_DIV_1;
#endif
    pll_init_structure.PLLMul = LL_RCC_PLL_MUL_9;
    clk_init_structure.AHBCLKDivider = LL_RCC_SYSCLK_DIV_1;
    clk_init_structure.APB1CLKDivider = LL_RCC_APB1_DIV_2;
    clk_init_structure.APB2CLKDivider = LL_RCC_APB2_DIV_1;
    if(SUCCESS != LL_PLL_ConfigSystemClock_HSE(HSE_VALUE, LL_UTILS_HSEBYPASS_OFF,
                                               &pll_init_structure, &clk_init_structure)) {
        pll_init_structure.PLLMul = LL_RCC_PLL_MUL_16;
        if(SUCCESS != LL_PLL_ConfigSystemClock_HSI(&pll_init_structure, &clk_init_structure)) {
            while(true);
        }
    }
    /* close other no use oscollator */
    LL_RCC_LSI_Disable();
    LL_RCC_LSE_Disable();
}

static void systick_config(void)
{
    LL_RCC_ClocksTypeDef RCC_ClocksStructure = {0};

    /* Configures the Cortex-M SysTick source to have 1ms time base. */
    LL_RCC_GetSystemClocksFreq(&RCC_ClocksStructure);
    LL_Init1msTick(RCC_ClocksStructure.HCLK_Frequency);
    LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
    LL_SYSTICK_EnableIT();
    /* SysTick_IRQn interrupt configuration */
    NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));

    /* calc clock cycle
     * @note: clk_cycle is used for bsp_udelay()
     */
    clk_cycle = RCC_ClocksStructure.HCLK_Frequency / 1000000;
}

void cpu_config()
{
#if defined(__ARMCC_VERSION)
    extern uint32_t Image$$ER_IROM1$$Base[];
    uint32_t base = (uint32_t)Image$$ER_IROM1$$Base;
#elif defined(__GNUC__)
    extern uint32_t _svector;
    uint32_t base = (uint32_t)&_svector;
#else
    #error "not support this compiler for relocate the vector table"
#endif
    /* config RCC */
    cpu_freq_config();
    /* relocate vector table */
#ifdef VECT_TAB_SRAM
    SCB->VTOR = SRAM_BASE | (base - SRAM_BASE);  /* Vector Table Relocation in Internal SRAM */
#else
    SCB->VTOR = FLASH_BASE | (base - FLASH_BASE); /* Vector Table Relocation in Internal FLASH */
#endif
    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
    while(true != LL_APB2_GRP1_IsEnabledClock(LL_APB2_GRP1_PERIPH_AFIO));
    /* initialize systick */
    systick_config();
}

void cpu_restore(void)
{
    /* deinit RCC */
    LL_RCC_DeInit();
    LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_AFIO);
    /* close systick */
    SysTick->CTRL &= (~(SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk));
}

void udelay(volatile uint32_t us)
{
    uint32_t tmp1, tmp2, delta;

    tmp1 = SysTick->VAL;
    while(true) {
        tmp2 = SysTick->VAL;
        delta = tmp2 < tmp1 ? (tmp1 - tmp2) : (SysTick->LOAD - tmp2 + tmp1);
        if(delta >= (us * clk_cycle)) {
            break;
        }
    }
}

void mdelay(uint32_t delay)
{
    LL_mDelay(delay);
}

void HAL_IncTick(void)
{
    tick++;
}

uint32_t HAL_GetTick(void)
{
    return tick;
}
