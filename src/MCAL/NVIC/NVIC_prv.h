#ifndef NVIC_PRV_H
#define NVIC_PRV_H

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#define NVIC_BASE_ADDR 0xE000E100U
#define SCB_AIRCR_ADDR 0xE000ED0C

#define LockValueForAIRCR 0x5FA

typedef struct {
    volatile u32 NVIC_ISERx[8];     // Interrupt Set-Enable Registers
    volatile u32 Reserved0[24];     // Reserved
    volatile u32 NVIC_ICERx[8];     // Interrupt Clear-Enable Registers
    volatile u32 Reserved1[24];     // Reserved
    volatile u32 NVIC_ISPRx[8];     // Interrupt Set-Pending Registers
    volatile u32 Reserved2[24];     // Reserved
    volatile u32 NVIC_ICPRx[8];     // Interrupt Clear-Pending Registers
    volatile u32 Reserved3[24];     // Reserved
    volatile u32 NVIC_IABRx[8];     // Interrupt Active Bit Registers
    volatile u32 Reserved4[56];     // Reserved
    volatile u8  NVIC_IPRx[240];    // Interrupt Priority Registers
    volatile u32 Reserved5[580];    // Reserved
    volatile u32 NVIC_STIR;         // Software Trigger Interrupt Register

} NVIC_MemMap_t;


#define NVIC ((volatile NVIC_MemMap_t *)NVIC_BASE_ADDR) 
#define SCB_AIRCR *((volatile u32*)(SCB_AIRCR_ADDR))

#endif