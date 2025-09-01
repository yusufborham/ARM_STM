#ifndef EXTI_PRV_H
#define EXTI_PRV_H

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#define EXTI_BASE_ADDRESS 0x40013C00

/*
0000  A
0001  B 
0010  C 
*/
typedef struct {
    volatile u32 IMR;   // Interrupt Mask Register
    volatile u32 EMR;   // Event Mask Register
    volatile u32 RTSR;  // Rising Trigger Selection Register
    volatile u32 FTSR;  // Falling Trigger Selection Register
    volatile u32 SWIER; // Software Interrupt Event Register
    volatile u32 PR;    // Pending Register
} EXTI_MemMap_t;


#define EXTI    (( volatile EXTI_MemMap_t *)EXTI_BASE_ADDRESS)


#endif