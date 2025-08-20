/*
 * RCC_int.h
 *
 *  Created on: Aug 17, 2025
 *      Author: yusuf
 *
 *  Description:
 *      This file contains the interface definitions for the Reset and Clock
 *      Control (RCC) driver for STM32 microcontrollers.
 *
 *      The RCC is responsible for configuring and controlling the system
 *      clocks, enabling/disabling peripheral clocks, and setting prescalers
 *      for AHB, APB1, and APB2 buses.
 */

#include "../../LIB/STD_TYPES.h"

#ifndef MCAL_RCC_RCC_INT_H_
#define MCAL_RCC_RCC_INT_H_

/*==============================================================================
 * Bus Identifiers
 *============================================================================*/
/**
 * @brief Available bus IDs in the STM32 clock tree.
 */
#define RCC_AHB1   0   /**< Advanced High-performance Bus 1 */
#define RCC_AHB2   1   /**< Advanced High-performance Bus 2 */
#define RCC_APB1   2   /**< Advanced Peripheral Bus 1 */
#define RCC_APB2   3   /**< Advanced Peripheral Bus 2 */

/*==============================================================================
 * Prescaler Enumerations
 *============================================================================*/
/**
 * @brief Prescaler options for APB1 bus.
 */
typedef enum {
    APB1_PRESCALER_DIVIDE_1   = 0, /**< HCLK not divided */
    APB1_PRESCALER_DIVIDE_2   = 4, /**< HCLK divided by 2 */
    APB1_PRESCALER_DIVIDE_4   = 5, /**< HCLK divided by 4 */
    APB1_PRESCALER_DIVIDE_8   = 6, /**< HCLK divided by 8 */
    APB1_PRESCALER_DIVIDE_16  = 7  /**< HCLK divided by 16 */
} APB1_Prescaler_t;

/**
 * @brief Prescaler options for APB2 bus.
 */
typedef enum {
    APB2_PRESCALER_DIVIDE_1   = 0, /**< HCLK not divided */
    APB2_PRESCALER_DIVIDE_2   = 4, /**< HCLK divided by 2 */
    APB2_PRESCALER_DIVIDE_4   = 5, /**< HCLK divided by 4 */
    APB2_PRESCALER_DIVIDE_8   = 6, /**< HCLK divided by 8 */
    APB2_PRESCALER_DIVIDE_16  = 7  /**< HCLK divided by 16 */
} APB2_Prescaler_t;

/**
 * @brief Prescaler options for AHB bus.
 */
typedef enum {
    AHB_PRESCALER_DIVIDE_1    = 0,  /**< SYSCLK not divided */
    AHB_PRESCALER_DIVIDE_2    = 8,  /**< SYSCLK divided by 2 */
    AHB_PRESCALER_DIVIDE_4    = 9,  /**< SYSCLK divided by 4 */
    AHB_PRESCALER_DIVIDE_8    = 10, /**< SYSCLK divided by 8 */
    AHB_PRESCALER_DIVIDE_16   = 11, /**< SYSCLK divided by 16 */
    AHB_PRESCALER_DIVIDE_64   = 12, /**< SYSCLK divided by 64 */
    AHB_PRESCALER_DIVIDE_128  = 13, /**< SYSCLK divided by 128 */
    AHB_PRESCALER_DIVIDE_256  = 14, /**< SYSCLK divided by 256 */
    AHB_PRESCALER_DIVIDE_512  = 15  /**< SYSCLK divided by 512 */
} AHB_Prescaler_t;

/*==============================================================================
 * Peripheral Identifiers
 *============================================================================*/
/*
 * Peripheral IDs must be defined in RCC_prv.h for each MCU.
 * Example:
 *   #define GPIOAEN 0
 *   #define GPIOBEN 1
 *   #define GPIOCEN 2
 *   #define GPIODEN 3
 *
 * Example aliases:
 */
#define RCC_GPIOA   0   /**< GPIOA clock enable */
#define RCC_GPIOB   1   /**< GPIOB clock enable */

/*==============================================================================
 * Function Prototypes
 *============================================================================*/

/**
 * @brief Initializes the RCC with default clock settings.
 *        Typically configures HSI/HSE, PLL, and system clock source.
 */
void MRCC_vInit(void);

/**
 * @brief Enables the clock for a specific peripheral.
 *
 * @param A_u8BusID         Bus ID (RCC_AHB1, RCC_AHB2, RCC_APB1, RCC_APB2)
 * @param A_u8PeripheralID  Peripheral ID defined in RCC_prv.h
 */
void MRCC_vEnableClk(u8 A_u8BusID, u8 A_u8PeripheralID);

/**
 * @brief Disables the clock for a specific peripheral.
 *
 * @param A_u8BusID         Bus ID (RCC_AHB1, RCC_AHB2, RCC_APB1, RCC_APB2)
 * @param A_u8PeripheralID  Peripheral ID defined in RCC_prv.h
 */
void MRCC_vDisableClk(u8 A_u8BusID, u8 A_u8PeripheralID);

/**
 * @brief Configures the APB1 prescaler.
 *
 * @param A_u8Prescaler  One of @ref APB1_Prescaler_t values
 */
void MRCC_vSetAPB1Prescaler(u8 A_u8Prescaler);

/**
 * @brief Configures the APB2 prescaler.
 *
 * @param A_u8Prescaler  One of @ref APB2_Prescaler_t values
 */
void MRCC_vSetAPB2Prescaler(u8 A_u8Prescaler);

/**
 * @brief Configures the AHB prescaler.
 *
 * @param A_u8Prescaler  One of @ref AHB_Prescaler_t values
 */
void MRCC_vSetAHBPrescaler(u8 A_u8Prescaler);

#endif /* MCAL_RCC_RCC_INT_H_ */
