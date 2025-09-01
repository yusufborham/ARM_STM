/**
 * @file SYSCFG_int.h
 * @brief System Configuration (SYSCFG) Interface for External Interrupt Line Mapping
 *
 * This header file provides the interface for configuring the mapping of GPIO pins
 * to external interrupt lines through the SYSCFG peripheral.
 *
 * The SYSCFG module is typically used in microcontrollers (like STM32 series) to:
 *   - Remap external interrupt (EXTI) lines to specific GPIO ports.
 *   - Allow multiple GPIO ports to share interrupt lines flexibly.
 *
 * Example use case:
 *   - If EXTI line 0 is connected to PA0 by default, this function allows
 *     remapping it to PB0 or PC0 instead.
 */

#ifndef SYSCFG_INT_H_
#define SYSCFG_INT_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../GPIO/GPIO_int.h"

/**
 * @brief Maps a GPIO pin from a given port to an external interrupt line.
 *
 * This function configures which GPIO port is connected to a specific EXTI line.
 * Each EXTI line can be connected to one pin from one port at a time.
 *
 * @param A_u8PortID   The GPIO port ID (e.g., GPIO_PORTA, GPIO_PORTB, etc.).
 * @param A_u8PinID    The GPIO pin number (0 to 15) to be mapped to the EXTI line.
 *
 * @note This only configures the SYSCFG mapping. To fully enable the interrupt:
 *       - Configure the EXTI line trigger condition (rising, falling, or both).
 *       - Enable the interrupt line in EXTI.
 *       - Enable the NVIC interrupt for the EXTI line.
 *
 * @see MEXTI_vEnableExternalInterruptLine()
 * @see MEXTI_vSetTriggerCondition()
 */
void MSYSCFG_vSetExternalInterruptLine(u8 A_u8PortID, u8 A_u8PinID);

#endif /* SYSCFG_INT_H_ */
