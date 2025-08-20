/*
 * RCC_prog.c
 *
 *  Created on: Aug 17, 2025
 *      Author: yusuf
 */


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "RCC_int.h"
#include "RCC_prv.h"
#include "RCC_cfg.h"

void MRCC_vInit(void){

#if RCC_SYS_CLK == HSE_CLK
		//choose bypass
#if	HSE_BYPASS == RC_CLK
	SET_BIT(RCC->CR , 18);
#elif HSE_BYPASS == MECHANICAL_CLK
	CLR_BIT(RCC->CR , 18);
#endif
// HSE on
SET_BIT(RCC->CR , 16);

// wait till flag
while (GET_BIT(RCC->CR ,17) == 0)
	;

// Switch to HSE
	SET_BIT(RCC->CFGR , 0);
	CLR_BIT(RCC->CFGR , 1);

#elif RCC_SYS_CLK == HSI_CLK

	SET_BIT(RCC->CR , 0);

	while(GET_BIT(RCC->CR, 1) == 0)
		;

	CLR_BIT(RCC->CFGR , 1);
	CLR_BIT(RCC->CFGR , 0);

#elif RCC_SYS_CLK == PLL_CLK

#else
#warning "Invalid option "
#endif

}
void MRCC_vEnableClk(u8 A_u8BusID , u8 A_u8PeripheralID){

	switch(A_u8BusID){
	case RCC_AHB1:
		SET_BIT(RCC->AHB1ENR , A_u8PeripheralID);
		break;
	case RCC_AHB2:
		SET_BIT(RCC->AHB2ENR , A_u8PeripheralID);
		break;
	case RCC_APB1:
		SET_BIT(RCC->APB1ENR , A_u8PeripheralID);
		break;
	case RCC_APB2:
		SET_BIT(RCC->APB2ENR , A_u8PeripheralID);
		break;
	default:
		// Handle error
		break;
	}

}
void MRCC_vDisableClk(u8 A_u8BusID, u8 A_u8PeripheralID){

	switch(A_u8BusID){
	case RCC_AHB1:
		CLR_BIT(RCC->AHB1ENR , A_u8PeripheralID);
		break;
	case RCC_AHB2:
		CLR_BIT(RCC->AHB2ENR , A_u8PeripheralID);
		break;
	case RCC_APB1:
		CLR_BIT(RCC->APB1ENR , A_u8PeripheralID);
		break;
	case RCC_APB2:
		CLR_BIT(RCC->APB2ENR , A_u8PeripheralID);
		break;
	default:
		// Handle error
		break;
	}
}
void MRCC_vSetAPB1Prescaler(u8 A_u8Prescaler){
	RCC->CFGR &= ~(0b111 << 10);			// clear the 3 bit field
	RCC->CFGR |= (A_u8Prescaler << 10);		// set the new prescaler value
}

void MRCC_vSetAPB2Prescaler(u8 A_u8Prescaler){
	RCC->CFGR &= ~(0b111 << 13);			// clear the 3 bit field
	RCC->CFGR |= (A_u8Prescaler << 13);		// set the new prescaler value
}

void MRCC_vSetAHBPrescaler(u8 A_u8Prescaler){
	RCC->CFGR &= ~(0b1111 << 4);			// clear the 4 bit field
	RCC->CFGR |= (A_u8Prescaler << 4);		// set the new prescaler value
}
