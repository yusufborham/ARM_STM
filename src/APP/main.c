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


int main(void) {
	// enable clock for GPIOA, GPIOB and SYSCFG
	MRCC_vInit();
	MRCC_vSetAHBPrescaler(AHB_PRESCALER_DIVIDE_1);
	

	MRCC_vEnableClk(RCC_AHB1, GPIOAEN);
	MRCC_vEnableClk(RCC_AHB1, GPIOBEN);
	MRCC_vEnableClk(RCC_APB2, SYSCFGEN);
	MRCC_vEnableClk(RCC_APB2, USART1EN);
	MRCC_vEnableClk(RCC_APB2, SPI1EN);

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

	GPIOx_PinConfig_t mosiPin = {
		.Port = GPIO_A,
		.Pin = GPIO_PIN_7,
		.Mode = GPIO_MODE_ALTERNATE,	
		.AltFunc = GPIO_AF5
	};

	MGPIO_vPinInit(&mosiPin);

	GPIOx_PinConfig_t sck = {
		.Port = GPIO_A,
		.Pin = GPIO_PIN_5,
		.Mode = GPIO_MODE_ALTERNATE,
		.AltFunc = GPIO_AF5
	};

	MGPIO_vPinInit(&sck);

	SPI_Config_t spi1_cfg = {
		.myPeripheral = SPI_PERIPH_1,
		.mySPIMode = MASTER,
		.myBaudRate = CLK_DIV_8,
		.myOperationMode = SIMPLEX_TRANSMIT,
		.dataFrameLn = DATA_FRAME_16BIT,
		.dataShift = MSB_FIRST,
		.ClockPhasePol = CLK_PHA_POL_MODE_0,
		.NSSMode = NSS_SW
	};

	MSPI_vInit(&spi1_cfg);

	while (1) {
		for (u16 i = 0; i < 65000; i++) {
			MSPI_vSendData(SPI_PERIPH_1, i);
			DELAY_US(10);
		}
	}
return 0;
}

