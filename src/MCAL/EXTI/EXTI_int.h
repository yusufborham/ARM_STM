/**
 * @file EXTI_int.h
 * @brief External Interrupt (EXTI) Driver Interface
 *
 * This module provides APIs to configure and control 
 * external interrupt lines for GPIO pins. 
 * It allows enabling/disabling interrupt lines, 
 * configuring trigger conditions, handling pending flags, 
 * and registering user-defined callback functions.
 *
 * @note Depends on GPIO driver and standard type definitions.
 */

#ifndef EXTI_INT_H
#define EXTI_INT_H

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../GPIO/GPIO_int.h"

/*-----------------------------------------------------------------------------------*/
/*                               Trigger Condition Macros                            */
/*-----------------------------------------------------------------------------------*/

/**
 * @brief Trigger interrupt on rising edge of the signal.
 */
#define RISING_EDGE_INTERRUPT_TRIGGER       0

/**
 * @brief Trigger interrupt on falling edge of the signal.
 */
#define FALLING_EDGE_INTERRUPT_TRIGGER      1

/**
 * @brief Trigger interrupt on both rising and falling edges.
 */
#define BOTH_EDGE_INTERRUPT_TRIGGER         2

/**
 * @brief Disable interrupt triggering on this line.
 */
#define NO_INTERRUPT_TRIGGER                3

/*-----------------------------------------------------------------------------------*/
/*                               Function Prototypes                                 */
/*-----------------------------------------------------------------------------------*/

/**
 * @brief Enable external interrupt for a given pin.
 *
 * @param A_u8PinID   GPIO pin ID (defined in GPIO driver).
 */
void MEXTI_vEnableExternalInterruptLine(u8 A_u8PinID);

/**
 * @brief Disable external interrupt for a given pin.
 *
 * @param A_u8PinID   GPIO pin ID (defined in GPIO driver).
 */
void MEXTI_vDisableExternalInterruptLine(u8 A_u8PinID);

/**
 * @brief Configure the trigger condition for the external interrupt.
 *
 * @param A_u8PinID             GPIO pin ID (defined in GPIO driver).
 * @param A_u8TriggerCondition  One of:
 *                              - RISING_EDGE_INTERRUPT_TRIGGER
 *                              - FALLING_EDGE_INTERRUPT_TRIGGER
 *                              - BOTH_EDGE_INTERRUPT_TRIGGER
 *                              - NO_INTERRUPT_TRIGGER
 */
void MEXTI_vSetTriggerCondition(u8 A_u8PinID, u8 A_u8TriggerCondition);

/**
 * @brief Get the pending interrupt flag status for a given pin.
 *
 * @param A_u8PinID   GPIO pin ID.
 * @return u8         1 if pending flag is set, 0 otherwise.
 */
u8 MEXTI_u8GetPendingFlag(u8 A_u8PinID);

/**
 * @brief Clear the pending interrupt flag for a given pin.
 *
 * @param A_u8PinID   GPIO pin ID.
 */
void MEXTI_vClearPendingFlag(u8 A_u8PinID);

/**
 * @brief Register a callback function to handle the interrupt.
 *
 * @param A_u8PinID    GPIO pin ID.
 * @param A_fpHandler  Pointer to user-defined handler function (void func(void)).
 */
void MEXTI_vSetCallBackFunction(u8 A_u8PinID, void(*A_fpHandler)(void));

#endif /* EXTI_INT_H */
