/*
 * RCC_int.h
 *
 *  Created on: Aug 17, 2025
 *      Author: yusuf
 */

#include "../../LIB/STD_TYPES.h"
#ifndef MCAL_RCC_RCC_INT_H_
#define MCAL_RCC_RCC_INT_H_



// Bus IDs
#define RCC_AHB1 0
#define RCC_AHB2 1
#define RCC_APB1 2
#define RCC_APB2 3

typedef enum {
    APB1_PRESCALER_DIVIDE_1 = 0 ,
    APB1_PRESCALER_DIVIDE_2 = 4 ,
    APB1_PRESCALER_DIVIDE_4 = 5 ,
    APB1_PRESCALER_DIVIDE_8 = 6 ,
    APB1_PRESCALER_DIVIDE_16 = 7
}APB1_Prescaler_t;

typedef enum {
    APB2_PRESCALER_DIVIDE_1 = 0 ,
    APB2_PRESCALER_DIVIDE_2 = 4 ,
    APB2_PRESCALER_DIVIDE_4 = 5 ,
    APB2_PRESCALER_DIVIDE_8 = 6 ,
    APB2_PRESCALER_DIVIDE_16 = 7
}APB2_Prescaler_t;

typedef enum {
    AHB_PRESCALER_DIVIDE_1 = 0 ,
    AHB_PRESCALER_DIVIDE_2 = 8 ,
    AHB_PRESCALER_DIVIDE_4 = 9 ,
    AHB_PRESCALER_DIVIDE_8 = 10 ,
    AHB_PRESCALER_DIVIDE_16 = 11 ,
    AHB_PRESCALER_DIVIDE_64 = 12 ,
    AHB_PRESCALER_DIVIDE_128 = 13 ,
    AHB_PRESCALER_DIVIDE_256 = 14 ,
    AHB_PRESCALER_DIVIDE_512 = 15
}AHB_Prescaler_t;

// Peripheral IDs
/*
    * Peripheral IDs are defined in RCC_prv.h
    * Example:
    * #define GPIOAEN 0
    * #define GPIOBEN 1
    * #define GPIOCEN 2
    * #define GPIODEN 3
*/ 

// #define RCC_GPIO GPIOAEN
#define RCC_GPIOA   0
#define RCC_GPIOB   1


// Function prototypes
void MRCC_vInit(void);
void MRCC_vEnableClk(u8 A_u8BusID, u8 A_u8PeripheralID);
void MRCC_vDisableClk(u8 A_u8BusID, u8 A_u8PeripheralID);
void MRCC_vSetAPB1Prescaler(u8 A_u8Prescaler);
void MRCC_vSetAPB2Prescaler(u8 A_u8Prescaler);
void MRCC_vSetAHBPrescaler(u8 A_u8Prescaler);


#endif /* MCAL_RCC_RCC_INT_H_ */
