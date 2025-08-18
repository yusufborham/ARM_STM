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



#endif /* MCAL_RCC_RCC_INT_H_ */
