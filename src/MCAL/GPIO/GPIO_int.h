/*
 * GPIO_int.h
 *
 *  Created on: Aug 17, 2025
 *      Author: yusuf
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#ifndef MCAL_GPIO_GPIO_INT_H_
#define MCAL_GPIO_GPIO_INT_H_

typedef struct 
{
    u8 Port ;
    u8 Pin ;
    u8 Mode ;
    u8 OutputType ;
    u8 PullType ;
    u8 Speed ;
    u8 AltFunc ;
} GPIOx_PinConfig_t ;


// Don't change the values here //

////////////////////////////////////////////////////////////////////////////////////////////
// GPIO Pin IDs
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

// GPIO Mode options
#define GPIO_MODE_INPUT         0x00U
#define GPIO_MODE_OUTPUT        0x01U
#define GPIO_MODE_ALTERNATE     0x02U
#define GPIO_MODE_ANALOG        0x03U

// GPIO Output Type options
#define GPIO_OTYPE_PP           0x00U  // Push-Pull
#define GPIO_OTYPE_OD           0x01U  // Open-Drain

// GPIO Speed options
#define GPIO_SPEED_LOW          0x00U
#define GPIO_SPEED_MEDIUM       0x01U
#define GPIO_SPEED_HIGH         0x02U
#define GPIO_SPEED_VERY_HIGH    0x03U

// GPIO Pull-Up/Pull-Down options
#define GPIO_PUPD_NONE          0x00U
#define GPIO_PUPD_PULL_UP       0x01U
#define GPIO_PUPD_PULL_DOWN     0x02U

// GPIO Alternate Function options
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

#define GPIO_PIN_HIGH          1U
#define GPIO_PIN_LOW           0U

///////////////////////////////////////////////////////////////////////////////////////////

// PORT IDs
#define GPIO_A 0
#define GPIO_B 1
#define GPIO_C 2
#define GPIO_D 3


void MGPIO_vSetPinMode(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8Mode);                           // analog mode, input mode, output mode, alternate function mode

void MGPIO_vSetPinOutputType(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8OutputType);               // push-pull, open-drain

void MGPIO_vSetPinSpeed(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8Speed);                         // low speed, medium speed, high speed, very high speed

void MGPIO_vSetPinPullUpDown(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8PullUpDown);               // no pull-up/pull-down, pull-up, pull-down

void MGPIO_vSetPinAlternateFunction(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8AlternateFunction); // set alternate function for the pin

void MGPIO_vSetPinValue(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8Value);                         // set pin high or low
u8 MGPIO_u8GetPinValue(u8 A_u8PortID, u8 A_u8PinID);                                        // get pin value (high or low)

void MGPIO_vPinInit(GPIOx_PinConfig_t* A_xPinCfg);

void MGPIO_vSetAllPort(u8 A_u8PortID, u16 A_u16Value);
void MGPIO_vSetLeastByteInPort( u8 A_u8PortID , u8 A_u8Value);                              // set least significant byte of the port
void MGPIO_vSetMostByteInPort(u8 A_u8PortID , u8 A_u8Value);

#endif /* MCAL_GPIO_GPIO_INT_H_ */
