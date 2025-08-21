
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


void handler(void) ; 

#define DELAY_MS(d) for(unsigned long i = 0 ; i < (d * 4000) ; i++ ){asm("NOP");}

volatile u32 counter = 0;

int main (void){
	// enable clock for GPIOA, GPIOB and SYSCFG
	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, GPIOAEN);
	MRCC_vEnableClk(RCC_AHB1, GPIOBEN);
	MRCC_vEnableClk(RCC_APB2, SYSCFGEN);

	MRCC_vSetAHBPrescaler(AHB_PRESCALER_DIVIDE_1);

	Seven_Segment_config_t seven_seg_cfg = {.Port = GPIO_A, .Pin_A = GPIO_PIN_0, .Pin_B = GPIO_PIN_1, .Pin_C = GPIO_PIN_2, .Pin_D = GPIO_PIN_3, .Pin_E = GPIO_PIN_4, .Pin_F = GPIO_PIN_5, .Pin_G = GPIO_PIN_6};
	HSevenSeg_vInitPins(&seven_seg_cfg);

	GPIOx_PinConfig_t button = {.Port = GPIO_B , .Pin = GPIO_PIN_0 , .Mode = GPIO_MODE_INPUT  ,  .PullType = GPIO_PUPD_PULL_UP , .Speed = GPIO_SPEED_LOW };
	MGPIO_vPinInit(&button);

	GPIOx_PinConfig_t led = {.Port = GPIO_A , .Pin = GPIO_PIN_7 , .Mode = GPIO_MODE_OUTPUT , .OutputType = GPIO_OTYPE_PP , .PullType = GPIO_PUPD_NONE , .Speed = GPIO_SPEED_LOW };
	MGPIO_vPinInit(&led);

	// let pin A8 alternate function pin for the MCO1
	GPIOx_PinConfig_t mco1 = {.Port = GPIO_A, .Pin = GPIO_PIN_8, .Mode = GPIO_MODE_ALTERNATE, .PullType = GPIO_PUPD_NONE, .Speed = GPIO_SPEED_VERY_HIGH , .AltFunc = 0};
	MGPIO_vPinInit(&mco1);

	MRCC_vOutputClockOnHardwarePin( MCO1_PRESCALER_DIVIDE_1 , MCO1_SOURCE_HSE);

	MSYSTICK_vChooseClockSource(SYSTICK_CLK_SOURCE_AHB_DIV_8);
	// MSYSTICK_vSetReloadValue(3125000);

	// MEXTI_vSetCallBackFunction(GPIO_PIN_0, handler);

	// CONFIGURE NVIC
	MNVIC_vEnableInterrupt(EXTI0_IRQn);
	MNVIC_vConfigGroupPriority(NVIC_PriorityGroup16_SubGroup0);
    MNVIC_vSetPriority(EXTI0_IRQn, 6, 0);

	// Configure the correct Line 
	MSYSCFG_vSetExternalInterruptLine(GPIO_B , GPIO_PIN_0);

	// Set the trigger condition
	MEXTI_vSetTriggerCondition(GPIO_PIN_0 , FALLING_EDGE_INTERRUPT_TRIGGER);

	MEXTI_vEnableExternalInterruptLine(GPIO_PIN_0);

	MGPIO_vSetPinValue(GPIO_A, GPIO_PIN_0, GPIO_PIN_LOW);

	MSYSTICK_vSetCurrentValue(0);
	MSYSTICK_vEnableTimer();

	MSYSTICK_vSetIntervalMulti( 2000 , handler);

	while(1){
	
		HSevenSeg_vDisplayNumber(&seven_seg_cfg , counter) ;
		
	}
	return 0;
}

void handler(void){
	counter = (counter+1)%10;
}
