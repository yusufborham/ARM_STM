#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#ifndef NVIC_INT_H
#define NVIC_INT_H

typedef enum {
    NVIC_PriorityGroup16_SubGroup0  = 3 ,
    NVIC_PriorityGroup8_SubGroup2   = 4 ,
    NVIC_PriorityGroup4_SubGroup4   = 5 ,
    NVIC_PriorityGroup2_SubGroup8   = 6 ,
    NVIC_PriorityGroup0_SubGroup16  = 7
} NVIC_PriorityGroup_t;

typedef enum 
{
    WWDG_IRQn                = 0,   // Window Watchdog interrupt
    EXTI16_IRQn              = 1,   // PVD through EXTI Line 16
    EXTI21_IRQn              = 2,   // Tamper/TimeStamp via EXTI Line 21
    EXTI22_IRQn              = 3,   // RTC Wakeup via EXTI Line 22
    FLASH_IRQn               = 4,   // Flash global
    RCC_IRQn                 = 5,   // RCC global
    EXTI0_IRQ               = 6,   // EXTI Line 0
    EXTI1_IRQn               = 7,   // EXTI Line 1
    EXTI2_IRQn               = 8,   // EXTI Line 2
    EXTI3_IRQn               = 9,   // EXTI Line 3
    EXTI4_IRQn               = 10,  // EXTI Line 4
    DMA1_Stream0_IRQn        = 11,  // DMA1 Stream0
    DMA1_Stream1_IRQn        = 12,  // DMA1 Stream1
    DMA1_Stream2_IRQn        = 13,  // DMA1 Stream2
    DMA1_Stream3_IRQn        = 14,  // DMA1 Stream3
    DMA1_Stream4_IRQn        = 15,  // DMA1 Stream4
    DMA1_Stream5_IRQn        = 16,  // DMA1 Stream5
    DMA1_Stream6_IRQn        = 17,  // DMA1 Stream6
    ADC_IRQn                 = 18,  // ADC1
    EXTI9_5_IRQn             = 23,  // EXTI Lines 5–9
    TIM1_BRK_TIM9_IRQn       = 24,  // TIM1 Break, TIM9
    TIM1_UP_TIM10_IRQn       = 25,  // TIM1 Update, TIM10
    TIM1_TRG_COM_TIM11_IRQn  = 26,  // TIM1 Trigger/Commutation, TIM11
    TIM1_CC_IRQn             = 27,  // TIM1 Capture Compare
    TIM2_IRQn                = 28,  // TIM2 global
    TIM3_IRQn                = 29,  // TIM3 global
    TIM4_IRQn                = 30,  // TIM4 global
    I2C1_EV_IRQn             = 31,  // I2C1 event
    I2C1_ER_IRQn             = 32,  // I2C1 error
    I2C2_EV_IRQn             = 33,  // I2C2 event
    I2C2_ER_IRQn             = 34,  // I2C2 error
    SPI1_IRQn                = 35,  // SPI1 global
    SPI2_IRQn                = 36,  // SPI2 global
    USART1_IRQn              = 37,  // USART1 global
    USART2_IRQn              = 38,  // USART2 global
    EXTI15_10_IRQn           = 40,  // EXTI Lines 10–15
    EXTI17_RTC_Alarm_IRQn    = 41,  // RTC Alarm via EXTI17
    EXTI18_OTG_FS_WKUP_IRQn  = 42,  // USB OTG FS Wakeup via EXTI18
    DMA1_Stream7_IRQn        = 47,  // DMA1 Stream7
    SDIO_IRQn                = 49,  // SDIO global
    TIM5_IRQn                = 50,  // TIM5 global
    SPI3_IRQn                = 51,  // SPI3 global
    DMA2_Stream0_IRQn        = 56,  // DMA2 Stream0
    DMA2_Stream1_IRQn        = 57,  // DMA2 Stream1
    DMA2_Stream2_IRQn        = 58,  // DMA2 Stream2
    DMA2_Stream3_IRQn        = 59,  // DMA2 Stream3
    DMA2_Stream4_IRQn        = 60,  // DMA2 Stream4
    OTG_FS_IRQn              = 67,  // USB OTG FS global
    DMA2_Stream5_IRQn        = 68,  // DMA2 Stream5
    DMA2_Stream6_IRQn        = 69,  // DMA2 Stream6
    DMA2_Stream7_IRQn        = 70,  // DMA2 Stream7
    USART6_IRQn              = 71,  // USART6 global
    I2C3_EV_IRQn             = 72,  // I2C3 event
    I2C3_ER_IRQn             = 73,  // I2C3 error
    FPU_IRQn                 = 81,  // Floating Point Unit global
    SPI4_IRQn                = 84   // SPI4 global
} Interrupt_ID_t;


void MNVIC_vEnableInterrupt(u8 A_u8InterruptID);
void MNVIC_vDisableInterrupt(u8 A_u8InterruptID);
void MNVIC_vSetPendingFlag(u8 A_u8InterruptID);
void MNVIC_vClearPendingFlag(u8 A_u8InterruptID);
void MNVIC_vSetPriority(u8 A_u8InterruptID, u8 A_u8GroupPriority , u8 A_u8SubGroupPriority);
u8 MNVIC_u8GetActiveFlag(u8 A_u8InterruptID);
void MNVIC_vConfigGroupPriority(NVIC_PriorityGroup_t A_u8GroupPriority);

#endif
