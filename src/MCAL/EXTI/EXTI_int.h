#ifndef EXTI_INT_H
#define EXTI_INT_H

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../GPIO/GPIO_int.h"

#define RISING_EDGE_INTERRUPT_TRIGGER       0
#define FALLING_EDGE_INTERRUPT_TRIGGER      1
#define BOTH_EDGE_INTERRUPT_TRIGGER         2
#define NO_INTERRUPT_TRIGGER                3

void MEXTI_vEnableExternalInterruptLine(u8 A_u8PinID);
void MEXTI_vDisableExternalInterruptLine(u8 A_u8PinID);
void MEXTI_vSetTriggerCondition(u8 A_u8PinID, u8 A_u8TriggerCondition);
u8 MEXTI_u8GetPendingFlag(u8 A_u8PinID);
void MEXTI_vClearPendingFlag(u8 A_u8PinID);
void MEXTI_vSetCallBackFunction(u8 A_u8PinID , void(*A_fpHandler)(void));

#endif