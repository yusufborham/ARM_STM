#ifndef TIM10_INT_H
#define TIM10_INT_H

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Delay.h"
#include "../../LIB/MATH_Fn.h" 
#include "../NVIC/NVIC_int.h"
#include "../RCC/RCC_int.h"
#include "../RCC/RCC_prv.h"


void MTIM10_vInit(void) ;
u32 MTIM10_vGetMillis() ;
u32 MTIM10_vGetMicros() ; 





#endif