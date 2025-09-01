#ifndef NEC_INT_H
#define NEC_INT_H

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/GPIO/gpio_int.h"
#include "../../MCAL/GPIO/gpio_prv.h"

#include "../../MCAL/RCC/rcc_int.h"
#include "../../MCAL/RCC/rcc_prv.h"

#include "../../MCAL/SYSTICK/systick_int.h"
#include "../../MCAL/SYSTICK/systick_prv.h"

#include "../../MCAL/EXTI/EXTI_int.h"
#include "../../MCAL/EXTI/EXTI_prv.h"

#include "../../MCAL/NVIC/NVIC_int.h"
#include "../../MCAL/NVIC/NVIC_prv.h"

#include "../../HAL/STP/STP_int.h"
#include "../../LIB/Delay.h"
#include "../../MCAL/SYSCFG/SYSCFG_int.h"
// Your code here
typedef struct {
    u8 Port ;
    u8 Pin ;
    u8 Timer_DIV ;
} NEC_cfg_t;

/*
 * Initializes the NEC.
 */
void HNEC_vInit(NEC_cfg_t* cfg);

void HNEC_vReadCode();

void HNEC_vDecodeFrame();
#endif
