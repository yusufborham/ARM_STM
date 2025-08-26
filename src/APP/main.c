
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

#define DELAY_MS(d) for(unsigned long i = 0 ; i < (d * 4000) ; i++ ){asm("NOP");}


void O_vTak1 (void );

void O_vTask2 (void );


int main (void){
	// enable clock for GPIOA, GPIOB and SYSCFG
	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, GPIOAEN);
	MRCC_vEnableClk(RCC_AHB1, GPIOBEN);
	MRCC_vEnableClk(RCC_APB2, SYSCFGEN);

	MRCC_vSetAHBPrescaler(AHB_PRESCALER_DIVIDE_1);

    
	GPIOx_PinConfig_t led1 = { .Port = GPIO_A, .Pin = GPIO_PIN_0, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OTYPE_PP , .PullType = GPIO_PUPD_NONE, .Speed = GPIO_SPEED_MEDIUM , .AltFunc = GPIO_AF0 };

	MGPIO_vPinInit(&led1);

	GPIOx_PinConfig_t led2 = { .Port = GPIO_A, .Pin = GPIO_PIN_1, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OTYPE_PP , .PullType = GPIO_PUPD_NONE, .Speed = GPIO_SPEED_MEDIUM , .AltFunc = GPIO_AF0 };

	MGPIO_vPinInit(&led2);

	OS_u8CreateTask(0,O_vTak1 ,1000, 0);

	OS_u8CreateTask(1,O_vTask2 ,500, 1);

	OS_vinit();
	OS_vStart();
	while(1){
		 
	}
	return 0;
}

void O_vTak1 (void ){
	MGPIO_vTogglePinValue(GPIO_A ,GPIO_PIN_0) ;
}

void O_vTask2 (void ){
	MGPIO_vTogglePinValue(GPIO_A ,GPIO_PIN_1) ;
}