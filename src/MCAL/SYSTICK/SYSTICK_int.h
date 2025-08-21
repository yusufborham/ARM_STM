#ifndef SYSTICK_INT_H
#define SYSTICK_INT_H 

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"


typedef enum {
    SYSTICK_CLK_SOURCE_AHB_DIV_8 = 0 ,
    SYSTICK_CLK_SOURCE_AHB_DIV_1 = 1
} SYSTICK_clkSource_t ;

u8 MSYSTICK_u8GetFlag();
void MSYSTICK_vChooseClockSource(u8 A_u8ClockSource);
void MSYSTICK_vEnableOvfInterrupt();
void MSYSTICK_vDisableOvfInterrupt();
void MSYSTICK_vEnableTimer();
void MSYSTICK_vDisableTimer();
void MSYSTICK_vSetReloadValue(u32 A_u32ReloadValue);
void MSYSTICK_vSetCurrentValue(u32 A_u32CurrentValue);
u32 MSYSTICK_u32GetCurrentReloadValue();
u32 MSYSTICK_u32GetCurrentValue();

#endif