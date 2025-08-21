#ifndef SYSTICK_PRV_H_
#define SYSTICK_PRV_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#define SYSTICK_BASE_ADDRESS  0xE000E010

// BITS FOR CTRL 
#define COUNT_FLAG      16 
#define CLOCK_SRC       2
#define TICK_INT        1
#define ENABLE          0

typedef struct {
    volatile u32 CTRL ;
    volatile u32 LOAD ; 
    volatile u32 VAL ;
    volatile u32 CALIB ;   
}SYSTICK_MemMap_t ;

#define SYSTICK         ((volatile SYSTICK_MemMap_t*)(SYSTICK_BASE_ADDRESS))

#endif /* SYSTICK_PRV_H_ */