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
#include "../HAL/Ultasonic/Ultrasonic_int.h"
#include "../HAL/IR_LineFollowing/IR_LineFollowing_int.h"
#include "../MCAL/Flash/Flash_int.h"
// #include "img.h"





int main(void) {
	// enable clock for GPIOA, GPIOB and SYSCFG
		// enable clock for GPIOA, GPIOB and SYSCFG
	MRCC_vInit();
	MRCC_vSetAHBPrescaler(AHB_PRESCALER_DIVIDE_1);
	

	MRCC_vEnableClk(RCC_AHB1, GPIOAEN);
	MRCC_vEnableClk(RCC_AHB1, GPIOBEN);
	MRCC_vEnableClk(RCC_APB2, SYSCFGEN);
	MRCC_vEnableClk(RCC_APB2, USART1EN);
	MRCC_vEnableClk(RCC_APB2, SPI1EN);

    // erase sector 1 , 2 ,3,4,5
//    MFMI_vSectorErase(SECTOR_0);
    MFMI_vSectorErase(SECTOR_2);
    
    // program flash at sector 2 address 0x08008000
    // 16 kb = 16384 BYTES = 8192 half words
    u16 data[8192] ;
    for (u16 i = 0 ; i < 8192 ; i++){
        data[i] = i ;
    }   
    MFMI_vProgramFlash(0x08008000 , data , 8192) ;

	while (1) {


	}
return 0;
}

