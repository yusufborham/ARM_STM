/**
 * @file SYSTICK_int.h
 * @brief SysTick Timer Driver - Interface Layer
 *
 * This file provides the public API for configuring and controlling the ARM Cortex-M SysTick timer.
 * The SysTick is a 24-bit down counter commonly used for timebase generation (e.g., delays, periodic interrupts).
 *
 * @note The implementation of these functions is provided in SYSTICK_prog.c
 */

#ifndef SYSTICK_INT_H
#define SYSTICK_INT_H 

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/**
 * @enum SYSTICK_clkSource_t
 * @brief Clock source options for SysTick timer
 */
typedef enum {
    SYSTICK_CLK_SOURCE_AHB_DIV_8 = 0, /**< SysTick clock source = AHB/8 */
    SYSTICK_CLK_SOURCE_AHB_DIV_1 = 1  /**< SysTick clock source = AHB */
} SYSTICK_clkSource_t ;

/**
 * @brief Get the status of the SysTick COUNTFLAG.
 * @return u8 - Returns 1 if the timer counted to 0 since last read, else 0.
 */
u8 MSYSTICK_u8GetFlag();

/**
 * @brief Select the clock source for SysTick.
 * @param A_u8ClockSource One of @ref SYSTICK_clkSource_t
 */
void MSYSTICK_vChooseClockSource(u8 A_u8ClockSource);

/**
 * @brief Enable SysTick overflow (count-to-zero) interrupt.
 */
void MSYSTICK_vEnableOvfInterrupt();

/**
 * @brief Disable SysTick overflow (count-to-zero) interrupt.
 */
void MSYSTICK_vDisableOvfInterrupt();

/**
 * @brief Enable the SysTick timer.
 */
void MSYSTICK_vEnableTimer();

/**
 * @brief Start SysTick with a given reload value.
 * @param A_u32ReloadValue Reload value (max 0xFFFFFF)
 * @note This automatically enables the timer.
 */
void MSYSTICK_vStartTimer(u32 A_u32ReloadValue);

/**
 * @brief Stop/disable the SysTick timer.
 */
void MSYSTICK_vDisableTimer();

/**
 * @brief Set the reload value of SysTick.
 * @param A_u32ReloadValue Value loaded when counter resets (max 0xFFFFFF).
 */
void MSYSTICK_vSetReloadValue(u32 A_u32ReloadValue);

/**
 * @brief Manually set the current value of the SysTick counter.
 * @param A_u32CurrentValue The value to load into the counter.
 */
void MSYSTICK_vSetCurrentValue(u32 A_u32CurrentValue);

/**
 * @brief Get the reload value currently set in SysTick.
 * @return u32 - Reload value.
 */
u32 MSYSTICK_u32GetCurrentReloadValue();

/**
 * @brief Get the current counter value of SysTick.
 * @return u32 - Current down-count value.
 */
u32 MSYSTICK_u32GetCurrentValue();

/**
 * @brief Calculate elapsed time since the last reload.
 * @return u32 - Elapsed ticks.
 */
u32 MSYSTICK_u32GetElapsedTime();

/**
 * @brief Calculate remaining time before the timer expires.
 * @return u32 - Remaining ticks.
 */
u32 MSYSTICK_u32GetRemainingTime();

#endif /* SYSTICK_INT_H */
