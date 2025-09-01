/**
 * @file GPIO_int.h
 * @brief General Purpose Input/Output (GPIO) Driver Interface
 *
 * This module provides an abstraction layer for configuring 
 * and controlling GPIO pins and ports on ARM Cortex-M MCUs.
 * It allows users to set pin modes, output types, speeds, 
 * pull-up/pull-down resistors, alternate functions, and 
 * perform basic read/write/toggle operations.
 *
 * @date Aug 17, 2025
 * @author Yusuf
 */

#ifndef MCAL_GPIO_GPIO_INT_H_
#define MCAL_GPIO_GPIO_INT_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/*-----------------------------------------------------------------------------------*/
/*                               Data Structures                                     */
/*-----------------------------------------------------------------------------------*/

/**
 * @brief GPIO Pin Configuration structure.
 *
 * Used with @ref MGPIO_vPinInit to configure a single GPIO pin.
 */
typedef struct 
{
    u8 Port;        /**< GPIO port ID (e.g., GPIO_A, GPIO_B) */
    u8 Pin;         /**< GPIO pin number (0–15) */
    u8 Mode;        /**< Pin mode: input, output, alternate, analog */
    u8 OutputType;  /**< Output type: push-pull or open-drain */
    u8 PullType;    /**< Pull-up/pull-down configuration */
    u8 Speed;       /**< Output speed: low, medium, high, very high */
    u8 AltFunc;     /**< Alternate function number (AF0–AF15) */
} GPIOx_PinConfig_t;

/*-----------------------------------------------------------------------------------*/
/*                               GPIO Pin IDs                                        */
/*-----------------------------------------------------------------------------------*/

#define GPIO_PIN_0   0
#define GPIO_PIN_1   1
#define GPIO_PIN_2   2
#define GPIO_PIN_3   3
#define GPIO_PIN_4   4
#define GPIO_PIN_5   5
#define GPIO_PIN_6   6
#define GPIO_PIN_7   7
#define GPIO_PIN_8   8
#define GPIO_PIN_9   9
#define GPIO_PIN_10  10
#define GPIO_PIN_11  11
#define GPIO_PIN_12  12
#define GPIO_PIN_13  13
#define GPIO_PIN_14  14
#define GPIO_PIN_15  15

/*-----------------------------------------------------------------------------------*/
/*                               GPIO Modes                                          */
/*-----------------------------------------------------------------------------------*/

#define GPIO_MODE_INPUT         0x00U  /**< Input mode */
#define GPIO_MODE_OUTPUT        0x01U  /**< General purpose output mode */
#define GPIO_MODE_ALTERNATE     0x02U  /**< Alternate function mode */
#define GPIO_MODE_ANALOG        0x03U  /**< Analog mode */

/*-----------------------------------------------------------------------------------*/
/*                               Output Type                                         */
/*-----------------------------------------------------------------------------------*/

#define GPIO_OTYPE_PP           0x00U  /**< Push-pull output */
#define GPIO_OTYPE_OD           0x01U  /**< Open-drain output */

/*-----------------------------------------------------------------------------------*/
/*                               Output Speed                                        */
/*-----------------------------------------------------------------------------------*/

#define GPIO_SPEED_LOW          0x00U
#define GPIO_SPEED_MEDIUM       0x01U
#define GPIO_SPEED_HIGH         0x02U
#define GPIO_SPEED_VERY_HIGH    0x03U

/*-----------------------------------------------------------------------------------*/
/*                               Pull-Up / Pull-Down                                 */
/*-----------------------------------------------------------------------------------*/

#define GPIO_PUPD_NONE          0x00U  /**< No pull-up or pull-down */
#define GPIO_PUPD_PULL_UP       0x01U  /**< Enable pull-up resistor */
#define GPIO_PUPD_PULL_DOWN     0x02U  /**< Enable pull-down resistor */

/*-----------------------------------------------------------------------------------*/
/*                               Alternate Function IDs                              */
/*-----------------------------------------------------------------------------------*/

#define GPIO_AF0                0x00U
#define GPIO_AF1                0x01U
#define GPIO_AF2                0x02U
#define GPIO_AF3                0x03U
#define GPIO_AF4                0x04U
#define GPIO_AF5                0x05U
#define GPIO_AF6                0x06U
#define GPIO_AF7                0x07U
#define GPIO_AF8                0x08U
#define GPIO_AF9                0x09U
#define GPIO_AF10               0x0AU
#define GPIO_AF11               0x0BU
#define GPIO_AF12               0x0CU
#define GPIO_AF13               0x0DU
#define GPIO_AF14               0x0EU
#define GPIO_AF15               0x0FU

/*-----------------------------------------------------------------------------------*/
/*                               Pin Logic Levels                                    */
/*-----------------------------------------------------------------------------------*/

#define GPIO_PIN_HIGH           1U
#define GPIO_PIN_LOW            0U

/*-----------------------------------------------------------------------------------*/
/*                               Port IDs                                            */
/*-----------------------------------------------------------------------------------*/

#define GPIO_A 0
#define GPIO_B 1
#define GPIO_C 2
#define GPIO_D 3

/*-----------------------------------------------------------------------------------*/
/*                               Function Prototypes                                 */
/*-----------------------------------------------------------------------------------*/

/**
 * @brief Set the mode of a specific pin.
 */
void MGPIO_vSetPinMode(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8Mode);

/**
 * @brief Set the output type of a specific pin (Push-pull / Open-drain).
 */
void MGPIO_vSetPinOutputType(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8OutputType);

/**
 * @brief Set the speed of a specific pin.
 */
void MGPIO_vSetPinSpeed(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8Speed);

/**
 * @brief Configure pull-up or pull-down resistor for a pin.
 */
void MGPIO_vSetPinPullUpDown(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8PullUpDown);

/**
 * @brief Set alternate function number for a pin.
 */
void MGPIO_vSetPinAlternateFunction(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8AlternateFunction);

/**
 * @brief Set the logical value (HIGH/LOW) of a pin.
 */
void MGPIO_vSetPinValue(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8Value);

/**
 * @brief Get the logical value of a pin.
 * @return 1 if HIGH, 0 if LOW.
 */
u8 MGPIO_u8GetPinValue(u8 A_u8PortID, u8 A_u8PinID);

/**
 * @brief Toggle the logical value of a pin.
 */
void MGPIO_vTogglePinValue(u8 A_u8PortID, u8 A_u8PinID);

/**
 * @brief Initialize a GPIO pin using a configuration structure.
 */
void MGPIO_vPinInit(GPIOx_PinConfig_t* A_xPinCfg);

/**
 * @brief Set the output value of an entire port.
 */
void MGPIO_vSetAllPort(u8 A_u8PortID, u16 A_u16Value);

/**
 * @brief Set the least significant byte (LSB) of a port.
 */
void MGPIO_vSetLeastByteInPort(u8 A_u8PortID, u8 A_u8Value);

/**
 * @brief Set the most significant byte (MSB) of a port.
 */
void MGPIO_vSetMostByteInPort(u8 A_u8PortID, u8 A_u8Value);

#endif /* MCAL_GPIO_GPIO_INT_H_ */
