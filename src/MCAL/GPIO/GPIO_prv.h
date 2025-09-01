/*
 * GPIO_prv.h
 *
 *  Created on: Aug 17, 2025
 *      Author: yusuf
 */

#ifndef MCAL_GPIO_GPIO_PRV_H_
#define MCAL_GPIO_GPIO_PRV_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#define GPIOA_BASE_ADDR		0x40020000U
#define GPIOB_BASE_ADDR		0x40020400U
#define GPIOC_BASE_ADDR		0x40020800U

typedef struct {
    volatile u32 MODER;    // 0x00: GPIO port mode register
    volatile u32 OTYPER;   // 0x04: GPIO port output type register
    volatile u32 OSPEEDR;  // 0x08: GPIO port output speed register
    volatile u32 PUPDR;    // 0x0C: GPIO port pull-up/pull-down register
    volatile u32 IDR;      // 0x10: GPIO port input data register
    volatile u32 ODR;      // 0x14: GPIO port output data register
    volatile u32 BSRR;     // 0x18: GPIO port bit set/reset register
    volatile u32 LCKR;     // 0x1C: GPIO port configuration lock register
    volatile u32 AFR[2];   // 0x20-0x24: GPIO alternate function registers
} GPIO_MemMap_t;

#define GPIOA		((volatile GPIO_MemMap_t*)(GPIOA_BASE_ADDR))
#define GPIOB		((volatile GPIO_MemMap_t*)(GPIOB_BASE_ADDR))
#define GPIOC		((volatile GPIO_MemMap_t*)(GPIOC_BASE_ADDR))




#endif /* MCAL_GPIO_GPIO_PRV_H_ */
