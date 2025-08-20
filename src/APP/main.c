
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

void handler(void) ; 

#define DELAY_MS(d) for(unsigned long i = 0 ; i < (d * 4000) ; i++ ){asm("NOP");}

volatile u8 flag = 0;

int main (void){
	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, GPIOAEN);
	MRCC_vEnableClk(RCC_AHB1, GPIOBEN);
	MRCC_vEnableClk(RCC_APB2, SYSCFGEN);
 
	// Seven_Segment_config_t seven_seg_cfg = {.Port = GPIO_A, .Pin_A = GPIO_PIN_0, .Pin_B = GPIO_PIN_1, .Pin_C = GPIO_PIN_2, .Pin_D = GPIO_PIN_3, .Pin_E = GPIO_PIN_4, .Pin_F = GPIO_PIN_5, .Pin_G = GPIO_PIN_6};

	// HSevenSeg_vInitPins(&seven_seg_cfg);

	GPIOx_PinConfig_t led = {.Port = GPIO_A , .Pin = GPIO_PIN_0 , .Mode = GPIO_MODE_OUTPUT , .OutputType = GPIO_OTYPE_PP , .PullType = GPIO_PUPD_NONE , .Speed = GPIO_SPEED_LOW , .AltFunc = 0};
	MGPIO_vPinInit(&led);

	GPIOx_PinConfig_t button = {.Port = GPIO_B , .Pin = GPIO_PIN_0 , .Mode = GPIO_MODE_INPUT  ,  .PullType = GPIO_PUPD_PULL_UP , .Speed = GPIO_SPEED_LOW };
	MGPIO_vPinInit(&button);

	MEXTI_vSetCallBackFunction(GPIO_PIN_0, handler);

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

	DELAY_MS(1000);

	MNVIC_vSetPendingFlag(EXTI0_IRQn);

	while(1){
		// MGPIO_vSetPinValue(GPIO_A, GPIO_PIN_0, GPIO_PIN_HIGH);
		// DELAY_MS(1000);
		// MGPIO_vSetPinValue(GPIO_A, GPIO_PIN_0, GPIO_PIN_LOW);
		// MNVIC_vSetPendingFlag(EXTI0_IRQn);
		// DELAY_MS(2000);
	}
	return 0;
}

void handler(void){
	MGPIO_vTogglePinValue(GPIO_A, GPIO_PIN_0);
	DELAY_MS(200);
}