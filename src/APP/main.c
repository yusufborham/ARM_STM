
#include "../MCAL/RCC/RCC_int.h"
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/RCC/RCC_prv.h"
#include "../MCAL/RCC/RCC_cfg.h"
#include "../MCAL/GPIO/GPIO_int.h"
#include "../MCAL/GPIO/GPIO_prv.h"
#include "../HAL/SevenSegment/SevSeg_int.h"
#include "../HAL/SevenSegment/SevSeg_prv.h"
#include "../MCAL/NVIC/NVIC_int.h"
#include "../MCAL/NVIC/NVIC_prv.h"
#include "../MCAL/EXTI/EXTI_int.h"
#include "../MCAL/EXTI/EXTI_prv.h"
#include "../MCAL/SYSCFG/SYSCFG_int.h"
#include "../MCAL/SYSCFG/SYSCFG_prv.h"
#include "../MCAL/SYSTICK/SYSTICK_int.h"
#include "../MCAL/SYSTICK/SYSTICK_prv.h"
#include "../HAL/LedMatrix/ledmatrix_int.h"
#include "../HAL/LedMatrix/ledmatrix_prv.h"


#define DELAY_MS(d) for(unsigned long i = 0 ; i < (d * 4000) ; i++ ){asm("NOP");}

volatile u32 counter = 0;

int main (void){
	// enable clock for GPIOA, GPIOB and SYSCFG
	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, GPIOAEN);
	MRCC_vEnableClk(RCC_AHB1, GPIOBEN);
	MRCC_vEnableClk(RCC_APB2, SYSCFGEN);

	MRCC_vSetAHBPrescaler(AHB_PRESCALER_DIVIDE_1);

	LedMatrix_config_t led_matrix_cfg = {
		.Port1 = GPIO_A,
		.RowPins = {
			{ .Pin = GPIO_PIN_0 },
			{ .Pin = GPIO_PIN_1 },
			{ .Pin = GPIO_PIN_2 },
			{ .Pin = GPIO_PIN_3 },
			{ .Pin = GPIO_PIN_4 },
			{ .Pin = GPIO_PIN_5 },
			{ .Pin = GPIO_PIN_6 },
			{ .Pin = GPIO_PIN_7 }
		},
		.Port2 = GPIO_B,
		.ColPins = {
			{ .Pin = GPIO_PIN_0 },
			{ .Pin = GPIO_PIN_1 },
			{ .Pin = GPIO_PIN_2 },
			{ .Pin = GPIO_PIN_5 },
			{ .Pin = GPIO_PIN_6 },  
			{ .Pin = GPIO_PIN_7 },
			{ .Pin = GPIO_PIN_8 },
			{ .Pin = GPIO_PIN_9 }
		}
	};

	HLedMatrix_vInitPins(&led_matrix_cfg);

	// display character I  on 8*8 led matrix 
	u8 led_matrix_buffer[6][8] = {
		{0, 0, 231, 231, 231, 231, 0, 0},
		{0, 0, 231, 231, 231, 231, 231, 231},
		{0, 0, 231, 231, 231, 231, 0, 0},
		{255, 195, 153, 153, 129, 153, 153, 255},
		{126, 60, 24, 0, 36, 60, 60, 60},
		{0, 0, 231, 231, 231, 231, 231, 231}

	};



	MSYSTICK_vChooseClockSource(SYSTICK_CLK_SOURCE_AHB_DIV_8);
	

	while(1){
	
		

		// display the character I
		 
		HLedMatrix_vDisplayFrameFor(1000 , &led_matrix_cfg , led_matrix_buffer[0]);
		 
		HLedMatrix_vDisplayFrameFor(1000 , &led_matrix_cfg , led_matrix_buffer[1]);
		 
		HLedMatrix_vDisplayFrameFor(1000 , &led_matrix_cfg , led_matrix_buffer[2]);
		 
		HLedMatrix_vDisplayFrameFor(1000 , &led_matrix_cfg , led_matrix_buffer[3]);
		 
		HLedMatrix_vDisplayFrameFor(1000 , &led_matrix_cfg , led_matrix_buffer[4]);
		 
		HLedMatrix_vDisplayFrameFor(1000 , &led_matrix_cfg , led_matrix_buffer[5]);
		 
	}
	return 0;
}

