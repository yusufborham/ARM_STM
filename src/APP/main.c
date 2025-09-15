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
// #include "img.h"


int main(void) {
	// enable clock for GPIOA, GPIOB and SYSCFG
		// enable clock for GPIOA, GPIOB and SYSCFG
	MRCC_vInit();
	MRCC_vSetAHBPrescaler(AHB_PRESCALER_DIVIDE_1);
	

	MRCC_vEnableClk(RCC_AHB1, GPIOAEN);
	MRCC_vEnableClk(RCC_AHB1, GPIOBEN);
	MRCC_vEnableClk(RCC_APB2, SYSCFGEN);
	MRCC_vEnableClk(RCC_APB2, USART6EN);
	MRCC_vEnableClk(RCC_APB2, SPI1EN);

    // if not using the usart just comment this part un comment the next line 
    // MSYSTICK_vEnableBckgroundMillis();

    // enable tx pin for usart 1
    GPIOx_PinConfig_t USART6_TX_Pin = {
       .Port = GPIO_A,
       .Pin = GPIO_PIN_11,
       .Mode = GPIO_MODE_ALTERNATE,
       .Speed = GPIO_SPEED_VERY_HIGH,
       .AltFunc = GPIO_AF8  // AF7 for USART1
    };
    MGPIO_vPinInit(&USART6_TX_Pin);

    USART_Config_t myUsart = {
       .fclk = USART_CLK_25MHZ ,
       .peripheral = USART_PERIPH_6,
       .baudRate = USART_BAUDRATE_115200,
       .wordLength = USART_WORD_LENGTH_8BITS,
       .stopBits = USART_STOP_BITS_1,
       .parity = USART_PARITY_NONE,
       .sampleRate = USART_SAMPLE_16_TIMES,
       .sampleMethod = USART_SAMPLE_METHOD_THREE_BITS,
       .mode = USART_MODE_TX_ONLY
    };

    MUSART_Init(&myUsart);

    Ultrasonic_cfg_t myUltrasonic = {
        .Trig_port = GPIO_A ,
        .Trig_pin  = GPIO_PIN_2 ,
        .Echo_port = GPIO_A ,
        .Echo_pin  = GPIO_PIN_3 
    } ;
    HUltra_vInit(&myUltrasonic) ;

    // IR_LineFollowing_cfg_t myIR = {
    //     .IR_ports = {GPIO_B, GPIO_B, GPIO_B, GPIO_B, GPIO_B},
    //     .IR_pins  = {GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_10, GPIO_PIN_11},
    //     .sensorType = HIGH_WHEN_LINE_DETECTED
    // };

    // HIR_vInit(&myIR);

    u8 buffer[60] ;
    // const u8 welcome[50] = "Hello from the stm32 \n" ;
    f32 distance = 0.0 ;

    // MUSART_u8WriteString(USART_PERIPH_1 , welcome );

	while (1) {

        if (HUltra_u8ReadDisatnce(&myUltrasonic, &distance) == FINISHED){
            ftoa(distance , buffer ) ;
            MUSART_u8WriteString(USART_PERIPH_6 ,(const u8*) buffer );
            const u8 cm[5] = " cm \n" ;
            MUSART_u8WriteString(USART_PERIPH_6 , cm );
        }
        DELAY_MS(100) ;
	}
return 0;
}

