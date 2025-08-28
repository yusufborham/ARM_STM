#include "SYSTICK_int.h"
#include "SYSTICK_prv.h"

u32 G_u32ClockSource = 0;

volatile u8 G_u8Flag = 0;

void (*G_pvCallBack)(void) = NULL;

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
    SYSTICK->LOAD = A_u32ReloadValue & SYSTICK_MAX_VALUE;
}

u32 MSYSTICK_u32GetCurrentReloadValue(){
    return SYSTICK->LOAD & SYSTICK_MAX_VALUE;
}

u32 MSYSTICK_u32GetCurrentValue(){
    return SYSTICK->VAL & SYSTICK_MAX_VALUE;
}

void MSYSTICK_vSetCurrentValue(u32 A_u32CurrentValue){
    SYSTICK->VAL = A_u32CurrentValue & SYSTICK_MAX_VALUE;
}

u32 MSYSTICK_u32GetElapsedTime(){
    switch (G_u32ClockSource)
    {
    case SYSTICK_CLK_SOURCE_AHB_DIV_8:
        return ((SYSTICK->LOAD - SYSTICK->VAL) & SYSTICK_MAX_VALUE)/SYSTICK_TICKS_1MS_DIV_8;
    case SYSTICK_CLK_SOURCE_AHB_DIV_1:
        return ((SYSTICK->LOAD - SYSTICK->VAL) & SYSTICK_MAX_VALUE)/SYSTICK_TICKS_1MS_DIV_1;
    default:
        return 0;
    }
}

u32 MSYSTICK_u32GetRemainingTime(){
    return (SYSTICK->VAL) & SYSTICK_MAX_VALUE;
}

void MSYSTICK_vSetDelayMS(f32 A_f32Delay){
     u32 L_u32NumberTicks = 0 ;
    // IF using AHB/8
    // and an external clock of 25MHz then 3125 tick means 1 ms has passed thus
    switch (G_u32ClockSource) {
        case SYSTICK_CLK_SOURCE_AHB_DIV_8:
            L_u32NumberTicks = (A_f32Delay * SYSTICK_TICKS_1MS_DIV_8);
            if ((L_u32NumberTicks < SYSTICK_MAX_VALUE) && (L_u32NumberTicks > 0)) {
                MSYSTICK_vSetReloadValue((u32)L_u32NumberTicks);
            }
            else {
                MSYSTICK_vSetReloadValue(SYSTICK_MAX_VALUE);
            }
            break;

        case SYSTICK_CLK_SOURCE_AHB_DIV_1:
            L_u32NumberTicks = (A_f32Delay * SYSTICK_TICKS_1MS_DIV_1);
            if ((L_u32NumberTicks < SYSTICK_MAX_VALUE) && (L_u32NumberTicks > 0)) {
                MSYSTICK_vSetReloadValue((u32)L_u32NumberTicks);
            }

            else {
                MSYSTICK_vSetReloadValue(SYSTICK_MAX_VALUE);
            }
            break;
        }
    MSYSTICK_vEnableTimer();
    while (!MSYSTICK_u8GetFlag());
    // stop the timer
    MSYSTICK_vDisableTimer();
}


void MSYSTICK_vSetIntervalMulti( u32 A_u32Interval , void (*A_pvCallBack)(void)){
    MSYSTICK_vEnableOvfInterrupt();
    // SET THE FLAG TO SYSTICK_RUNNING_MULTI
    G_u8Flag = SYSTICK_RUNNING_MULTI;
    // asign the call back function 
    G_pvCallBack = A_pvCallBack;
    u32 L_u32TicksNumber = 0 ;
    
    switch (G_u32ClockSource){
        case SYSTICK_CLK_SOURCE_AHB_DIV_8:
            L_u32TicksNumber = SYSTICK_TICKS_1MS_DIV_8 * A_u32Interval;
            break;
        case SYSTICK_CLK_SOURCE_AHB_DIV_1:
            L_u32TicksNumber = SYSTICK_TICKS_1MS_DIV_1 * A_u32Interval;
            break;
    }
    
    if (L_u32TicksNumber < SYSTICK_MAX_VALUE){
        MSYSTICK_vStartTimer(L_u32TicksNumber);
    }

    else {
        L_u32TicksNumber = SYSTICK_MAX_VALUE;
    }

}

void MSYSTICK_vSetIntervalMultiMicroseconds( u32 A_u32Interval , void (*A_pvCallBack)(void)){
    MSYSTICK_vEnableOvfInterrupt();
    // SET THE FLAG TO SYSTICK_RUNNING_MULTI
    G_u8Flag = SYSTICK_RUNNING_MULTI_MICRO;
    // asign the call back function 
    G_pvCallBack = A_pvCallBack;
    u32 L_u32TicksNumber = 0 ;
    
    switch (G_u32ClockSource){
        case SYSTICK_CLK_SOURCE_AHB_DIV_8:
            L_u32TicksNumber = SYSTICK_TICKS_1US_DIV_8 * A_u32Interval;
            break;
        case SYSTICK_CLK_SOURCE_AHB_DIV_1:
            L_u32TicksNumber = SYSTICK_TICKS_1US_DIV_1 * A_u32Interval;
            break;
    }
    
    if (L_u32TicksNumber < SYSTICK_MAX_VALUE){
        MSYSTICK_vStartTimer(L_u32TicksNumber);
    }

    else {
        L_u32TicksNumber = SYSTICK_MAX_VALUE;
    }

}

void MSYSTICK_vSetIntervalSingle(u32 A_u32Interval, void (*A_pvCallBack)(void)){
    MSYSTICK_vEnableOvfInterrupt();
    // SET THE FLAG TO SYSTICK_RUNNING_SINGLE
    G_u8Flag = SYSTICK_RUNNING_SINGLE;
    // asign the call back function 
    G_pvCallBack = A_pvCallBack;
    u32 L_u32TicksNumber = 0 ;
    
    switch (G_u32ClockSource){
        case SYSTICK_CLK_SOURCE_AHB_DIV_8:
            L_u32TicksNumber = SYSTICK_TICKS_1MS_DIV_8 * A_u32Interval;
            break;
        case SYSTICK_CLK_SOURCE_AHB_DIV_1:
            L_u32TicksNumber = SYSTICK_TICKS_1MS_DIV_1 * A_u32Interval;
            break;
    }

    if (L_u32TicksNumber < SYSTICK_MAX_VALUE){
        MSYSTICK_vStartTimer(L_u32TicksNumber);
    }

    else {
        L_u32TicksNumber = SYSTICK_MAX_VALUE;
    }

}

void SysTick_Handler(void){
    // Clear the interrupt flag
    if (G_pvCallBack != NULL){
        switch (G_u8Flag) {
            case SYSTICK_RUNNING_MULTI:
                G_pvCallBack();
                MSYSTICK_vSetCurrentValue(0); // Reset the counter
                break;

            case SYSTICK_RUNNING_SINGLE:
                G_pvCallBack();
                MSYSTICK_vDisableTimer();
                break;
            case SYSTICK_RUNNING_MULTI_MICRO:
                G_pvCallBack();
                MSYSTICK_vSetCurrentValue(0); // Reset the counter
                break;
        }
    }
}