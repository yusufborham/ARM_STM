#ifndef ULTRASONIC_INT_H
#define ULTRASONIC_INT_H


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Delay.h"

#include "../../MCAL/GPIO/GPIO_int.h"
#include "../../MCAL/GPIO/GPIO_prv.h"

#include "../../MCAL/TIM10/TIM10_int.h"

#include "../../MCAL/EXTI/EXTI_int.h"
#include "../../MCAL/EXTI/EXTI_prv.h"

#include "../../MCAL/NVIC/NVIC_int.h"
#include "../../MCAL/NVIC/NVIC_prv.h"


#include "../../MCAL/SYSCFG/SYSCFG_int.h"

typedef struct {
    u8 Trig_port ; 
    u8 Trig_pin ;
    u8 Echo_port ;
    u8 Echo_pin ;
}Ultrasonic_cfg_t ;

typedef enum {
    MEASURING , 
    FINISHED
}Ultrasonic_measuingState_t ;

void HUltra_vInit(Ultrasonic_cfg_t* cfg);

Ultrasonic_measuingState_t HUltra_u8ReadDisatnce(Ultrasonic_cfg_t* cfg , f32* ptr) ;

#endif
