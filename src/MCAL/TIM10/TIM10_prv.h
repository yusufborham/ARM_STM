#ifndef TIM_PRV_H
#define TIM_PRV_H

#include "TIM10_int.h"

#define TIM10_BASE_ADDRESS 0x40014400UL

typedef struct {
    volatile u32 TIM10_CR1;    // 0x00
    volatile u32 RESERVED0;    // 0x04
    volatile u32 RESERVED1;    // 0x08  
    volatile u32 TIM10_DIER;   // 0x0C
    volatile u32 TIM10_SR;     // 0x10
    volatile u32 TIM10_EGR;    // 0x14
    volatile u32 TIM10_CCMR1;  // 0x18
    volatile u32 RESERVED2;    // 0x1C
    volatile u32 TIM10_CCER;   // 0x20
    volatile u32 TIM10_CNT;    // 0x24
    volatile u32 TIM10_PSC;    // 0x28
    volatile u32 TIM10_ARR;    // 0x2C
    volatile u32 RESERVED3;    // 0x30
    volatile u32 TIM10_CCR1;   // 0x34
} TIM10_RegDef_t;

#define TIM10 ((TIM10_RegDef_t *) TIM10_BASE_ADDRESS)


// bits in CR1 

#define CEN     0
#define UDIS    1
#define URS     2
#define OPM     3
#define ARPE    7
#define CKD0    8

// bits in DIER
#define UIE     0
#define CC1IE   1

// bits in SR
#define UIF     0
#define CC1IF   1
#define CC1OF   9

// Bits in EGR
#define UG      0
#define CC1G    1

// Bits in CCMR1
#define CC1S0   0
#define CC1S1   1
#define OC1FE   2
#define OC1PE   3
#define OC1M0   4
#define OC1M1   5
#define OC1M2   6

// Bits in CCER
#define CC1E    0
#define CC1P    1
#define CC1NP   3

// TIM1_UP_TIM10_IRQn --- > FOR THE NVIC  ENABLE/DISABLE



#endif


 