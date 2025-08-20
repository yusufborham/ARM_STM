/*
 * RCC_prv.h
 *
 *  Created on: Aug 17, 2025
 *      Author: yusuf
 */

#ifndef MCAL_RCC_RCC_PRV_H_
#define MCAL_RCC_RCC_PRV_H_


#define RCC_BASE_ADDR			0x40023800U


typedef struct {
    volatile u32 CR;          // 0x00: Clock control register
    volatile u32 PLLCFGR;     // 0x04: PLL configuration register
    volatile u32 CFGR;        // 0x08: Clock configuration register
    volatile u32 CIR;         // 0x0C: Clock interrupt register
    volatile u32 AHB1RSTR;    // 0x10: AHB1 peripheral reset register
    volatile u32 AHB2RSTR;    // 0x14: AHB2 peripheral reset register
    volatile u32 RESERVED0;   // 0x18: Reserved
    volatile u32 RESERVED1;   // 0x1C: Reserved
    volatile u32 APB1RSTR;    // 0x20: APB1 peripheral reset register
    volatile u32 APB2RSTR;    // 0x24: APB2 peripheral reset register
    volatile u32 RESERVED2;   // 0x28: Reserved
    volatile u32 RESERVED3;   // 0x2C: Reserved
    volatile u32 AHB1ENR;     // 0x30: AHB1 peripheral clock enable register
    volatile u32 AHB2ENR;     // 0x34: AHB2 peripheral clock enable register
    volatile u32 RESERVED4;   // 0x38: Reserved
    volatile u32 RESERVED5;   // 0x3C: Reserved
    volatile u32 APB1ENR;     // 0x40: APB1 peripheral clock enable register
    volatile u32 APB2ENR;     // 0x44: APB2 peripheral clock enable register
    volatile u32 RESERVED6;   // 0x48: Reserved
    volatile u32 RESERVED7;   // 0x4C: Reserved
    volatile u32 AHB1LPENR;   // 0x50: AHB1 peripheral clock enable in low power mode
    volatile u32 AHB2LPENR;   // 0x54: AHB2 peripheral clock enable in low power mode
    volatile u32 RESERVED8;   // 0x58: Reserved
    volatile u32 RESERVED9;   // 0x5C: Reserved
    volatile u32 APB1LPENR;   // 0x60: APB1 peripheral clock enable in low power mode
    volatile u32 APB2LPENR;   // 0x64: APB2 peripheral clock enable in low power mode
    volatile u32 RESERVED10;  // 0x68: Reserved
    volatile u32 RESERVED11;  // 0x6C: Reserved
    volatile u32 BDCR;        // 0x70: Backup domain control register
    volatile u32 CSR;         // 0x74: Clock control & status register
    volatile u32 RESERVED12;  // 0x78: Reserved
    volatile u32 RESERVED13;  // 0x7C: Reserved
    volatile u32 SSCGR;       // 0x80: Spread spectrum clock generation register
    volatile u32 PLLI2SCFGR;  // 0x84: PLLI2S configuration register
    volatile u32 Reserved14 ;
    volatile u32 DCKCFGR ;
} RCC_MemMap_t;


#define RCC			((volatile RCC_MemMap_t*)(RCC_BASE_ADDR))

#define HSE_CLK 	    0
#define HSI_CLK 	    1
#define PLL_CLK 	    2

#define RC_CLK 	        0
#define MECHANICAL_CLK 	1

#define GPIOAEN         0
#define GPIOBEN         1
#define GPIOCEN         2
#define GPIODEN         3
#define GPIOEEN         4
#define GPIOHEN         7

#define TIM2EN          0
#define TIM3EN          1   
#define TIM4EN          2
#define TIM5EN          3
#define WWDGEN         11
#define SPI2EN         14
#define SPI3EN         15
#define USART2EN       17
#define I2C1EN         21
#define I2C2EN         22
#define I2C3EN         23 
#define PWREN          28

#define TIM1EN         0
#define USART1EN       4
#define USART6EN       5
#define ADC1EN         8
#define SDIOEN         11
#define SPI1EN         12
#define SPI4EN         13
#define SYSCFGEN       14
#define TIM9EN         16
#define TIM10EN        17
#define TIM11EN        18


#endif /* MCAL_RCC_RCC_PRV_H_ */
