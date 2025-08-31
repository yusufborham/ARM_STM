
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
#include "../OS/os_prv.h"
#include "../OS/os_int.h"
#include "song.h"
#include "../HAL/DAC/DAC_int.h"
#include "../LIB/Delay.h"
#include "../HAL/STP/STP_int.h"


static LedMatrix_config_t LedMatrix_cfg = {
	.Mode = LED_MATRIX_STP_MODE,
	.Config = {
		.stpConfig = {
			.Port = GPIO_A,
			.ShiftClkPin = GPIO_PIN_0,
			.SerialDataPin = GPIO_PIN_1,
			.LatchPin = GPIO_PIN_2,
			.Mode = STP_16BIT_MODE
		}
	}
};

int main (void){
	// enable clock for GPIOA, GPIOB and SYSCFG
	MRCC_vInit();

	MRCC_vSetAHBPrescaler(AHB_PRESCALER_DIVIDE_1);

	MRCC_vEnableClk(RCC_AHB1, GPIOAEN);
	MRCC_vEnableClk(RCC_AHB1, GPIOBEN);
	MRCC_vEnableClk(RCC_APB2, SYSCFGEN);

	HLedMatrix_vInitPins(&LedMatrix_cfg);

	// display character I  on 8*8 led matrix 
	u8 led_matrix_buffer[6][8] = {
		{0, 0, 231, 231, 231, 231, 0, 0},
		{0, 0, 231, 231, 231, 231, 231, 231},
		{0, 0, 231, 231, 231, 231, 0, 0},
		{255, 195, 153, 153, 129, 153, 153, 255},
		{126, 60, 24, 0, 36, 60, 60, 60},
		{0, 0, 231, 231, 231, 231, 231, 231}

	};

	while(1){

			HLedMatrix_vDisplayFrame(&LedMatrix_cfg , led_matrix_buffer[0]);

		}

	return 0;
}

