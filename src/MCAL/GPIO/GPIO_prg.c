/*
 * GPIO_prg.c
 *
 *  Created on: Aug 17, 2025
 *      Author: yusuf
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "GPIO_int.h"
#include "GPIO_prv.h"


void MGPIO_vSetPinMode(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8Mode)
{
    switch (A_u8PortID) {
        case GPIO_A:
            GPIOA->MODER &= ~(0x03U << (A_u8PinID * 2)); // Clear mode bits for the pin
            GPIOA->MODER |= (A_u8Mode << (A_u8PinID * 2)); // Set new mode
            break;
        case GPIO_B:
            GPIOB->MODER &= ~(0x03U << (A_u8PinID * 2));
            GPIOB->MODER |= (A_u8Mode << (A_u8PinID * 2));
            break;
        case GPIO_C:
            GPIOC->MODER &= ~(0x03U << (A_u8PinID * 2));
            GPIOC->MODER |= (A_u8Mode << (A_u8PinID * 2));
            break;
        default:
            // Handle error
            break;
    }
}

void MGPIO_vSetPinOutputType(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8OutputType)
{
    switch (A_u8PortID) {
        case GPIO_A:
            if (A_u8OutputType == GPIO_OTYPE_PP) {
                CLR_BIT(GPIOA->OTYPER, A_u8PinID);
            } else if (A_u8OutputType == GPIO_OTYPE_OD) {
                SET_BIT(GPIOA->OTYPER, A_u8PinID);
            }
            break;
        case GPIO_B:
            if (A_u8OutputType == GPIO_OTYPE_PP) {
                CLR_BIT(GPIOB->OTYPER, A_u8PinID);
            } else if (A_u8OutputType == GPIO_OTYPE_OD) {
                SET_BIT(GPIOB->OTYPER, A_u8PinID);
            }
            break;
        case GPIO_C:
            if (A_u8OutputType == GPIO_OTYPE_PP) {
                CLR_BIT(GPIOC->OTYPER, A_u8PinID);
            } else if (A_u8OutputType == GPIO_OTYPE_OD) {
                SET_BIT(GPIOC->OTYPER, A_u8PinID);
            }
            break;
        default:
            // Handle error
            break;
    }
}

void MGPIO_vSetPinSpeed(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8Speed)
{
    switch (A_u8PortID) {
        case GPIO_A:
            GPIOA->OSPEEDR &= ~(0x03U << (A_u8PinID * 2)); // Clear speed bits for the pin
            GPIOA->OSPEEDR |= (A_u8Speed << (A_u8PinID * 2)); // Set new speed
            break;
        case GPIO_B:
            GPIOB->OSPEEDR &= ~(0x03U << (A_u8PinID * 2));
            GPIOB->OSPEEDR |= (A_u8Speed << (A_u8PinID * 2));
            break;
        case GPIO_C:
            GPIOC->OSPEEDR &= ~(0x03U << (A_u8PinID * 2));
            GPIOC->OSPEEDR |= (A_u8Speed << (A_u8PinID * 2));
            break;
        default:
            // Handle error
            break;
    }
}

void MGPIO_vSetPinPullUpDown(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8PullUpDown)
{
    switch (A_u8PortID) {
        case GPIO_A:
            GPIOA->PUPDR &= ~(0x03U << (A_u8PinID * 2)); // Clear pull-up/pull-down bits for the pin
            GPIOA->PUPDR |= (A_u8PullUpDown << (A_u8PinID * 2)); // Set new pull-up/pull-down
            break;
        case GPIO_B:
            GPIOB->PUPDR &= ~(0x03U << (A_u8PinID * 2));
            GPIOB->PUPDR |= (A_u8PullUpDown << (A_u8PinID * 2));
            break;
        case GPIO_C:
            GPIOC->PUPDR &= ~(0x03U << (A_u8PinID * 2));
            GPIOC->PUPDR |= (A_u8PullUpDown << (A_u8PinID * 2));
            break;
        default:
            // Handle error
            break;
    }
}

void MGPIO_vSetPinAlternateFunction(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8AlternateFunction)
{
    switch (A_u8PortID) {
        case GPIO_A:
            GPIOA->AFR[A_u8PinID / 8] &= ~(0x0FU << ((A_u8PinID % 8) * 4));                // Clear alternate function bits for the pin
            GPIOA->AFR[A_u8PinID / 8] |= (A_u8AlternateFunction << ((A_u8PinID % 8) * 4)); // Set new alternate function
            break;
        case GPIO_B:
            GPIOB->AFR[A_u8PinID / 8] &= ~(0x0FU << ((A_u8PinID % 8) * 4));
            GPIOB->AFR[A_u8PinID / 8] |= (A_u8AlternateFunction << ((A_u8PinID % 8) * 4));
            break;
        case GPIO_C:
            GPIOC->AFR[A_u8PinID / 8] &= ~(0x0FU << ((A_u8PinID % 8) * 4));
            GPIOC->AFR[A_u8PinID / 8] |= (A_u8AlternateFunction << ((A_u8PinID % 8) * 4));
            break;
        default:
            // Handle error
            break;
    }
}

void MGPIO_vSetPinValue(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8Value)
{
    switch (A_u8PortID) {
        case GPIO_A:
            if (A_u8Value == GPIO_PIN_HIGH) {
                SET_BIT(GPIOA->ODR, A_u8PinID);
            } else {
                CLR_BIT(GPIOA->ODR, A_u8PinID);
            }
            break;
        case GPIO_B:
            if (A_u8Value == GPIO_PIN_HIGH) {
                SET_BIT(GPIOB->ODR, A_u8PinID);
            } else {
                CLR_BIT(GPIOB->ODR, A_u8PinID);
            }
            break;
        case GPIO_C:
            if (A_u8Value == GPIO_PIN_HIGH) {
                SET_BIT(GPIOC->ODR, A_u8PinID);
            } else {
                CLR_BIT(GPIOC->ODR, A_u8PinID);
            }
            break;
        default:
            // Handle error
            break;
    }
}

void MGPIO_vTogglePinValue(u8 A_u8PortID, u8 A_u8PinID)
{
    switch (A_u8PortID) {
        case GPIO_A:
            TOG_BIT(GPIOA->ODR, A_u8PinID);
            break;
        case GPIO_B:
            TOG_BIT(GPIOB->ODR, A_u8PinID);
            break;
        case GPIO_C:
            TOG_BIT(GPIOC->ODR, A_u8PinID);
            break;
        default:
            // Handle error
            break;
    }
}

u8 MGPIO_u8GetPinValue(u8 A_u8PortID, u8 A_u8PinID)
{
    switch (A_u8PortID) {
        case GPIO_A:
            return (GET_BIT(GPIOA->IDR, A_u8PinID));
        case GPIO_B:
            return (GET_BIT(GPIOB->IDR, A_u8PinID));
        case GPIO_C:
            return (GET_BIT(GPIOC->IDR, A_u8PinID));
        default:
            // Handle error
            return 0xFF;
    }
}

void MGPIO_vSetAllPort(u8 A_u8PortID, u16 A_u16Value){
    switch (A_u8PortID) {
        case GPIO_A:
            GPIOA->ODR = A_u16Value;
            break;
        case GPIO_B:
            GPIOB->ODR = A_u16Value;
            break;
        case GPIO_C:
            GPIOC->ODR = A_u16Value;
            break;
        default:
            // Handle error
            break;
    }
}

void MGPIO_vSetLeastByteInPort( u8 A_u8PortID , u8 A_u8Value){
    switch (A_u8PortID) {
        case GPIO_A:
            GPIOA->ODR &= ~(0x00FF);          // clear first byte only
            GPIOA->ODR |= A_u8Value;
            break;
        case GPIO_B:
            GPIOB->ODR &= ~(0x00FF);          // clear first byte only
            GPIOB->ODR |= A_u8Value;
            break;
        case GPIO_C:
            GPIOC->ODR &= ~(0x00FF);          // clear first byte only
            GPIOC->ODR |= A_u8Value;
            break;
        default:
            // Handle error
    
            break;
    }
}

void MGPIO_vSetMostByteInPort(u8 A_u8PortID , u8 A_u8Value){
    switch (A_u8PortID) {
        u16 highValue;
        case GPIO_A:
            GPIOA->ODR &= ~(0xFF00);          // clear second byte only
            highValue = ( A_u8Value << 8 ) & 0xFF00;
            GPIOA->ODR |= highValue;
            break;
        case GPIO_B:
            GPIOB->ODR &= ~(0xFF00);          // clear second byte only
            highValue = ( A_u8Value << 8 ) & 0xFF00;
            GPIOB->ODR |= highValue;
            break;
        case GPIO_C:
            GPIOC->ODR &= ~(0xFF00);          // clear second byte only
            highValue = ( A_u8Value << 8 ) & 0xFF00;
            GPIOC->ODR |= highValue;
            break;
        default:
            // Handle error
    
            break;
    }
}


void MGPIO_vPinInit(GPIOx_PinConfig_t* A_xPinCfg){
    MGPIO_vSetPinMode(A_xPinCfg->Port , A_xPinCfg->Pin , A_xPinCfg->Mode);
    MGPIO_vSetPinOutputType(A_xPinCfg->Port , A_xPinCfg->Pin , A_xPinCfg->OutputType);
    MGPIO_vSetPinSpeed(A_xPinCfg->Port , A_xPinCfg->Pin , A_xPinCfg->Speed);
    MGPIO_vSetPinPullUpDown(A_xPinCfg->Port , A_xPinCfg->Pin , A_xPinCfg->PullType);
    MGPIO_vSetPinAlternateFunction(A_xPinCfg->Port , A_xPinCfg->Pin , A_xPinCfg->AltFunc);
}





