
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

#define DELAY_MS(d) for(long i = 0 ; i < (d * 4000) ; i++ ){asm("NOP");}


int main (void){

	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, GPIOAEN);
	MRCC_vEnableClk(RCC_AHB1, GPIOBEN);
 
	// Seven_Segment_config_t seven_seg_cfg = {.Port = GPIO_A, .Pin_A = GPIO_PIN_0, .Pin_B = GPIO_PIN_1, .Pin_C = GPIO_PIN_2, .Pin_D = GPIO_PIN_3, .Pin_E = GPIO_PIN_4, .Pin_F = GPIO_PIN_5, .Pin_G = GPIO_PIN_6};

	// HSevenSeg_vInitPins(&seven_seg_cfg);

	GPIOx_PinConfig_t led = {.Port = GPIO_A , .Pin = GPIO_PIN_0 , .Mode = GPIO_MODE_OUTPUT , .OutputType = GPIO_OTYPE_PP , .PullType = GPIO_PUPD_NONE , .Speed = GPIO_SPEED_LOW , .AltFunc = 0};
	MGPIO_vPinInit(&led);

	// GPIOx_PinConfig_t button = {.Port = GPIO_B , .Pin = GPIO_PIN_0 , .Mode = GPIO_MODE_INPUT  , .OutputType = GPIO_OTYPE_PP , .PullType = GPIO_PUPD_PULL_UP , .Speed = GPIO_SPEED_LOW , .AltFunc = 0};

	// MGPIO_vPinInit(&button);

	MNVIC_vEnableInterrupt(EXTI0_IRQ);
	MNVIC_vConfigGroupPriority(NVIC_PriorityGroup16_SubGroup0);
    MNVIC_vSetPriority(EXTI0_IRQ, 6, 0);
	MGPIO_vSetPinValue(GPIO_A, GPIO_PIN_0, GPIO_PIN_LOW);
	
	DELAY_MS(3000);

	MNVIC_vSetPendingFlag(EXTI0_IRQ);
 
	while(1){
	}
	return 0;
}

void EXTI0_IRQHandler(void)
{
	MGPIO_vSetPinValue(GPIO_A, GPIO_PIN_0, GPIO_PIN_HIGH);
}
