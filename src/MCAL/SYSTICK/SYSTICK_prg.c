#include "SYSTICK_int.h"
#include "SYSTICK_prv.h"

u8 MSYSTICK_u8GetFlag(){
    return (GET_BIT(SYSTICK->CTRL , COUNT_FLAG));  
}

void MSYSTICK_vChooseClockSource(u8 A_u8ClockSource){
    A_u8ClockSource ? SET_BIT(SYSTICK->CTRL , CLOCK_SRC) :  CLR_BIT(SYSTICK->CTRL , CLOCK_SRC) ;
}

void MSYSTICK_vEnableOvfInterrupt(){
    SET_BIT(SYSTICK->CTRL , TICK_INT ) ;
}

void MSYSTICK_vDisableOvfInterrupt(){
    CLR_BIT(SYSTICK->CTRL , TICK_INT ) ;
}

void MSYSTICK_vEnableTimer(){
    SET_BIT(SYSTICK->CTRL , ENABLE) ;
}

void MSYSTICK_vDisableTimer(){
    CLR_BIT(SYSTICK->CTRL , ENABLE) ;
}

void MSYSTICK_vSetReloadValue(u32 A_u32ReloadValue){
    SYSTICK->LOAD = A_u32ReloadValue & 0x0FFF;
}

u32 MSYSTICK_u32GetCurrentReloadValue(){
    return SYSTICK->LOAD & 0x0FFF;
}

u32 MSYSTICK_u32GetCurrentValue(){
    return SYSTICK->VAL & 0x0FFF;
}

void MSYSTICK_vSetCurrentValue(u32 A_u32CurrentValue){
    SYSTICK->VAL = A_u32CurrentValue & 0x0FFF;
}
