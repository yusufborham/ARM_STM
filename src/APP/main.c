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
//#include "song.h"
#include "../HAL/DAC/DAC_int.h"
#include "../LIB/Delay.h"
#include "../HAL/STP/STP_int.h"
#include "../MCAL/USART/USART_int.h"
#include "../MCAL/SPI/SPI_int.h"
#include "../MCAL/SPI/SPI_cfg.h"
#include "../HAL/TFT/TFT_int.h"
#include "../HAL/TFT/TFT_prv.h"
// #include "img.h"

void switchText(void);

volatile u8 changed = 1 ;
volatile u8 toggle = 0 ;

// const tImage Image = { image_data_Image, 128, 160, 16 };

u8 Mytext2[50] = "Hello my Friend How are you" ;
u8 Mytext1[50] = "I am fine thank you ";



int main(void) {
	// enable clock for GPIOA, GPIOB and SYSCFG
	MRCC_vInit();
	MRCC_vSetAHBPrescaler(AHB_PRESCALER_DIVIDE_1);
	

	MRCC_vEnableClk(RCC_AHB1, GPIOAEN);
	MRCC_vEnableClk(RCC_AHB1, GPIOBEN);
	MRCC_vEnableClk(RCC_APB2, SYSCFGEN);
	MRCC_vEnableClk(RCC_APB2, USART1EN);
	MRCC_vEnableClk(RCC_APB2, SPI1EN);

	MEXTI_vEnableExternalInterruptLine(GPIO_PIN_3);

	MEXTI_vSetTriggerCondition(GPIO_PIN_3, FALLING_EDGE_INTERRUPT_TRIGGER);

	MEXTI_vSetCallBackFunction(GPIO_PIN_3, switchText);

	MSYSCFG_vSetExternalInterruptLine(GPIO_A, GPIO_PIN_3);

	MNVIC_vEnableInterrupt(EXTI3_IRQn);

	MNVIC_vConfigGroupPriority(NVIC_PriorityGroup16_SubGroup0);
    MNVIC_vSetPriority(EXTI3_IRQn, 6, 0);

	GPIOx_PinConfig_t button = {
		.Port = GPIO_A,
		.Pin = GPIO_PIN_3,
		.Mode = GPIO_MODE_INPUT,
		.AltFunc = GPIO_AF0,
		.Speed = GPIO_SPEED_HIGH,
		.PullType = GPIO_PUPD_PULL_UP
	};
	MGPIO_vPinInit(&button);

	HTFT_cfg_t myHTFT = {
	.mySPI = SPI_PERIPH_1,
	.myPixelFormat = PIXEL_FORMAT_16BIT,
	.myScreenSize = SCREEN_SIZE_128X160,
	.myRSTport = GPIO_A,
	.myRSTpin = GPIO_PIN_1,
	.myA0port = GPIO_A,
	.myA0pin = GPIO_PIN_2
	};

	HTFT_vInit(&myHTFT);
	DELAY_MS(100);
	HTFT_vFillBackground(0); // Fill background with black color
	// HTFT_vDrawImage(&Image, 0, 0);
	
	while (1) {
		if (changed) {
		HTFT_vFillBackground(0); // Fill background with black color
		HTFT_vWriteString(5, 5 , toggle ? Mytext1 : Mytext2 ,TFT_WHITE, TFT_BLACK ) ;
		changed = 0 ;
		}

	}
return 0;
}


void switchText(void){
	changed = 1 ;
	toggle = 1 - toggle ;
	DELAY_MS(100);
}

