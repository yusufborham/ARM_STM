#include "TIM10_int.h"
#include "TIM10_prv.h"

volatile u32 G_u32TMillis = 0 ;

void MTIM10_vInit(void){
    // enable clock for TIM10
    MRCC_vEnableClk(RCC_APB2, TIM10EN);

    // set prescalar 
    // prescalar to have 1Mhz timer clock
    // assuming 25Mhz APB2 clock
    TIM10->TIM10_PSC = 25 ; 

    // set auto-reload value for 1ms overflow
    TIM10->TIM10_ARR = 1000 ;

    // enable update interrupt
    SET_BIT(TIM10->TIM10_DIER, UIE);

    // enable counter
    SET_BIT(TIM10->TIM10_CR1, CEN);

    // enable NVIC interrupt for TIM10
    MNVIC_vEnableInterrupt(TIM1_UP_TIM10_IRQn);
}

u32 MTIM10_vGetMillis(){
    return G_u32TMillis ;
}

u32 MTIM10_vGetMicros(){
    u32 L_u32CurrentMillis = G_u32TMillis ;
    u32 L_u32PassedMicros = TIM10->TIM10_CNT;
    return (L_u32CurrentMillis * 1000) + L_u32PassedMicros ;
}


void TIM1_UP_TIM10_IRQHandler(void){
    // check if update interrupt flag is set
    if (TIM10->TIM10_SR & (1 << UIF)) {
        // clear interrupt flag
        CLR_BIT(TIM10->TIM10_SR, UIF);
        G_u32TMillis += 1 ;

    }
}
