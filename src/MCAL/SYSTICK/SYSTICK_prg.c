#include "SYSTICK_int.h"
#include "SYSTICK_prv.h"

u32 G_u32ClockSource = 0;

u8 MSYSTICK_u8GetFlag(){
    return (GET_BIT(SYSTICK->CTRL , COUNT_FLAG));  
}

void MSYSTICK_vChooseClockSource(u8 A_u8ClockSource){
    A_u8ClockSource ? SET_BIT(SYSTICK->CTRL , CLOCK_SRC) :  CLR_BIT(SYSTICK->CTRL , CLOCK_SRC) ;
    G_u32ClockSource = A_u8ClockSource;
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

void MSYSTICK_vStartTimer( u32 A_u32ReloadValue){
    MSYSTICK_vSetReloadValue(A_u32ReloadValue);
    MSYSTICK_vEnableTimer();
}

void MSYSTICK_vSetReloadValue(u32 A_u32ReloadValue){
    SYSTICK->LOAD = A_u32ReloadValue & 0x00FFFFFF;
}

u32 MSYSTICK_u32GetCurrentReloadValue(){
    return SYSTICK->LOAD & 0x00FFFFFF;
}

u32 MSYSTICK_u32GetCurrentValue(){
    return SYSTICK->VAL & 0x00FFFFFF;
}

void MSYSTICK_vSetCurrentValue(u32 A_u32CurrentValue){
    SYSTICK->VAL = A_u32CurrentValue & 0x00FFFFFF;
}

u32 MSYSTICK_u32GetElapsedTime(){
    return (SYSTICK->LOAD - SYSTICK->VAL) & 0x00FFFFFF;
}

u32 MSYSTICK_u32GetRemainingTime(){
    return (SYSTICK->VAL) & 0x00FFFFFF;
}

void MSYSTICK_vSetDelayMS(u32 A_u32Delay){

    // IF using AHB/8
    // and an external clock of 25MHz then 3125 tick means 1 ms has passed thus
    if (G_u32ClockSource == 0) {

        u32 L_u32NumberTicks = (A_u32Delay * 3125);

        if ((L_u32NumberTicks < 0x00FFFFFF) && (L_u32NumberTicks > 0)) {
            MSYSTICK_vSetReloadValue(L_u32NumberTicks);
            MSYSTICK_vStartTimer(L_u32NumberTicks);
        }

        while (!MSYSTICK_u8GetFlag());

        // stop the timer
        MSYSTICK_vDisableTimer();
    }
}