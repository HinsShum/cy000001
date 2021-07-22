/**
 * @file /arch/stm32f103xx/CY000001/include/cpu.h
 *
 * Copyright (C) 2020
 *
 * cpu_fre.h is free software: you can redistribute it and/or modify
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
#ifndef __CPU_H
#define __CPU_H

/*---------- includes ----------*/
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/*---------- macro ----------*/
#define tick_increase()                 HAL_IncTick()
#define tick_get()                      HAL_GetTick()

/*---------- type define ----------*/
/*---------- variable prototype ----------*/
/*---------- function prototype ----------*/
/**
 * @brief initialize cpu register
 * 
 * @retval None
 */
extern void cpu_config(void);

/**
 * @brief restore cpu register
 * 
 * @retval None
 */
extern void cpu_restore(void);

/**
 * udelay() - This function provides accurate delay (in microsecond) based on SysTick counter flag
 * @note: Blocking delay
 * @note: Based on the system HCLK.
 * @note: The delay time length can not exceed the SysTick LOAD, otherwise, use LL_mDelay().
 * @us: Delay specifies the delay time length, in microsecond.
 *
 * retval: None
 */
extern void udelay(volatile uint32_t us);

/**
 * mdelay() - This function provides accurate delay (in
 * milliseconds) based on SysTick counter flag
 * @note: When a RTOS is used, it is recommended to avoid using
 *      blocking delay and use rather osDelay service.
 * @note: To respect 1ms timebase, user should call @ref
 *      LL_Init1msTick function which will configure Systick to
 *      1ms.
 * @delay: Delay specifies the delay time length, in
 *       milliseconds.
 *
 * retval: None
 */
extern void mdelay(uint32_t delay);

/**
 * @brief This function is called to increment a global
 *        variable "tick" used as application time base.
 * @note: In the default implementation, this variable is
 *      incremented each 1ms in Systick ISR.
 *
 * retval: None
 */
extern void HAL_IncTick(void);

/**
 * @brief Provides a tick value in millisecond
 *
 * @retval tick value
 */
extern uint32_t HAL_GetTick(void);

#endif /* __CPU_H */
