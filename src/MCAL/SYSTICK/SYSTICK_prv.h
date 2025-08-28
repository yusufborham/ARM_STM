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

#define SYSTICK_TICKS_1MS_DIV_8 3125
#define SYSTICK_TICKS_1MS_DIV_1  25000

#define SYSTICK_TICKS_1US_DIV_8  3.125
#define SYSTICK_TICKS_1US_DIV_1  25

#define SYSTICK_MAX_VALUE  0x00FFFFFF

typedef struct {
    volatile u32 CTRL ;
    volatile u32 LOAD ; 
    volatile u32 VAL ;
    volatile u32 CALIB ;   
}SYSTICK_MemMap_t ;

typedef enum {
    SYSTICK_RUNNING_MULTI = 0 ,
    SYSTICK_RUNNING_SINGLE =1 ,
    SYSTICK_RUNNING_MULTI_MICRO = 2
}SYSTICK_Mode_t;

#define SYSTICK         ((volatile SYSTICK_MemMap_t*)(SYSTICK_BASE_ADDRESS))

#endif /* SYSTICK_PRV_H_ */