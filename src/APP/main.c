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


int main(void) {
	// enable clock for GPIOA, GPIOB and SYSCFG
	MRCC_vInit();
	MRCC_vSetAHBPrescaler(AHB_PRESCALER_DIVIDE_1);
	

	MRCC_vEnableClk(RCC_AHB1, GPIOAEN);
	MRCC_vEnableClk(RCC_AHB1, GPIOBEN);
	MRCC_vEnableClk(RCC_APB2, SYSCFGEN);
	MRCC_vEnableClk(RCC_APB2, USART1EN);

	GPIOx_PinConfig_t ledPin = {
		.Port = GPIO_A,
		.Pin = GPIO_PIN_0,
		.Mode = GPIO_MODE_OUTPUT,
		.OutputType = GPIO_OTYPE_PP,
		.AltFunc = GPIO_AF0,
		.Speed = GPIO_SPEED_HIGH,
		.PullType = GPIO_PUPD_NONE
	};
	MGPIO_vPinInit(&ledPin);

	// set GPIO A9 to be used as a TX for the USART1 

	GPIOx_PinConfig_t txPin = {
		.Port = GPIO_A,
		.Pin = GPIO_PIN_9,
		.Mode = GPIO_MODE_ALTERNATE,	
		.AltFunc = GPIO_AF7
	};

	MGPIO_vPinInit(&txPin);

		GPIOx_PinConfig_t rxPin = {
		.Port = GPIO_A,
		.Pin = GPIO_PIN_10,
		.Mode = GPIO_MODE_ALTERNATE,	
		.AltFunc = GPIO_AF7
	};

	MGPIO_vPinInit(&rxPin);

	USART_Config_t usart1_cfg = {
		.peripheral = USART_PERIPH_1,
		.baudRate = USART_BAUDRATE_115200,
		.wordLength = USART_WORD_LENGTH_8BITS,
		.stopBits = USART_STOP_BITS_1,
		.parity = USART_PARITY_NONE,
		.sampleRate = USART_SAMPLE_16_TIMES,
		.sampleMethod = USART_SAMPLE_METHOD_THREE_BITS,
		.mode = USART_MODE_TX_RX,
		.fclk = USART_CLK_25MHZ
	};

	MUSART_Init(&usart1_cfg);

	u8 buffer[50];  // Buffer to hold the string representation of the integer
	const u8 buffer2[] = "Hello Borham how are you \r\n";
	u8 str[] = "Hello from USART1\r\n";
	MUSART_u8WriteString(USART_PERIPH_1 , str);

	while (1) {
		
		if (MUSART_u8BytesAvailable(USART_PERIPH_1)){
			MUSART_u8ReadStringUntil(USART_PERIPH_1 , buffer , 50 , '\n') ;

			if (buffer[2] == 'a')	{
				MGPIO_vSetPinValue(GPIO_A , GPIO_PIN_0 , GPIO_PIN_HIGH);
				MUSART_u8WriteString(USART_PERIPH_1 , buffer);
			}
			else if (buffer[0] == 'b')
				MGPIO_vSetPinValue(GPIO_A , GPIO_PIN_0 , GPIO_PIN_LOW);
		}
	}
return 0;
}

