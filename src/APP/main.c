
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


#define DELAY_MS(d) for(unsigned long i = 0 ; i < (d * 4000) ; i++ ){asm("NOP");}

void A_pvCallBack(void);

void A_pvStartPause(void);

void A_pvReset(void);

volatile u8 G_u8isPlaying = 0;
u32 sampleNumber = 0;

DAC_cfg_t dacConfig = {
		.Port = GPIO_A,
		.Pins = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, 
				 GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7}
};

int main (void){
	// enable clock for GPIOA, GPIOB and SYSCFG
	MRCC_vInit();

	MRCC_vSetAHBPrescaler(AHB_PRESCALER_DIVIDE_1);

	MRCC_vEnableClk(RCC_AHB1, GPIOAEN);
	MRCC_vEnableClk(RCC_AHB1, GPIOBEN);
	MRCC_vEnableClk(RCC_APB2, SYSCFGEN);

	GPIOx_PinConfig_t startPauseBut = {
		.Port = GPIO_B,
		.Pin = GPIO_PIN_0,
		.Mode = GPIO_MODE_INPUT,
		.OutputType = GPIO_OTYPE_PP,
		.PullType = GPIO_PUPD_PULL_UP,
		.Speed = GPIO_SPEED_MEDIUM,
		.AltFunc = GPIO_AF0
	};
	MGPIO_vPinInit(&startPauseBut);

	GPIOx_PinConfig_t resetButton = {
		.Port = GPIO_B,
		.Pin = GPIO_PIN_1,
		.Mode = GPIO_MODE_INPUT,
		.OutputType = GPIO_OTYPE_PP,
		.PullType = GPIO_PUPD_PULL_UP,
		.Speed = GPIO_SPEED_MEDIUM,
		.AltFunc = GPIO_AF0
	};

	MGPIO_vPinInit(&resetButton);

	// enable EXTI in the NVIC 
	MNVIC_vEnableInterrupt(EXTI1_IRQn);
	MNVIC_vEnableInterrupt(EXTI0_IRQn);



	// configure the NVIC priority
	MNVIC_vConfigGroupPriority(NVIC_PriorityGroup16_SubGroup0);

	// set the priority
	MNVIC_vSetPriority(EXTI0_IRQn, 0, 0);
	MNVIC_vSetPriority(EXTI1_IRQn, 0, 0);

	// enable the external interrupt line
	MEXTI_vEnableExternalInterruptLine(GPIO_PIN_0);
	MEXTI_vEnableExternalInterruptLine(GPIO_PIN_1);

	// trigger condition 
	MEXTI_vSetTriggerCondition(GPIO_PIN_0, FALLING_EDGE_INTERRUPT_TRIGGER);
	MEXTI_vSetTriggerCondition(GPIO_PIN_1, FALLING_EDGE_INTERRUPT_TRIGGER);

	// config the multiplexer 
	MSYSCFG_vSetExternalInterruptLine(GPIO_B, GPIO_PIN_0);
	MSYSCFG_vSetExternalInterruptLine(GPIO_B, GPIO_PIN_1);

	MEXTI_vSetCallBackFunction(GPIO_PIN_0, A_pvStartPause);
	MEXTI_vSetCallBackFunction(GPIO_PIN_1, A_pvReset);

	MSYSTICK_vEnableTimer();
    MSYSTICK_vChooseClockSource(SYSTICK_CLK_SOURCE_AHB_DIV_1);
	// init from A0 to A7 in port A 
	HDAC_vInit(&dacConfig);

	MSYSTICK_vSetIntervalMultiMicroseconds( 125 , A_pvCallBack );

	while(1){
		
		
	}
	return 0;
}

void A_pvCallBack(void){
	if (G_u8isPlaying == 0){
		return;
	}
	
	HDAC_vSetValue(&dacConfig, song[sampleNumber]);
	sampleNumber++;
	if (sampleNumber >= song_len){
		sampleNumber = 0;
	}
	
}

void A_pvStartPause(void){
	// toggle play/pause state
	G_u8isPlaying ^= 1;
	DELAY_MS(10) ;
}

void A_pvReset(void){
	sampleNumber = 0;
	DELAY_MS(10) ;
}