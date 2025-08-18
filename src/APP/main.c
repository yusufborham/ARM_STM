
#include "../MCAL/RCC/RCC_int.h"
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/RCC/RCC_prv.h"
#include "../MCAL/RCC/RCC_cfg.h"
#include "../MCAL/GPIO/GPIO_int.h"
#include "../MCAL/GPIO/GPIO_prv.h"
#include "../HAL/SevenSegment/SevSeg_int.h"
#include "../HAL/SevenSegment/SevSeg_prv.h"

#define DELAY_MS(d) for(long i = 0 ; i < (d * 4000) ; i++ ){asm("NOP");}


int main (void){

	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, GPIOAEN);
	MRCC_vEnableClk(RCC_AHB1, GPIOBEN);

	//GPIOx_PinConfig_t button = {.Port = GPIO_A , .Pin = GPIO_PIN_1 , .Mode = GPIO_MODE_INPUT  , .OutputType = GPIO_OTYPE_PP , .PullType = GPIO_PUPD_PULL_UP , .Speed = GPIO_SPEED_LOW , .AltFunc = 0};

	// 7 segment display leds init from A0 to A6
	// GPIOx_PinConfig_t led = {.Port = GPIO_A , .Pin = GPIO_PIN_0 , .Mode = GPIO_MODE_OUTPUT , .OutputType = GPIO_OTYPE_PP , .PullType = GPIO_PUPD_NONE , .Speed = GPIO_SPEED_LOW , .AltFunc = 0};
	// GPIOx_PinConfig_t button = {.Port = GPIO_A , .Pin = GPIO_PIN_1 , .Mode = GPIO_MODE_INPUT  , .OutputType = GPIO_OTYPE_PP , .PullType = GPIO_PUPD_PULL_UP , .Speed = GPIO_SPEED_LOW , .AltFunc = 0};
	
	Seven_Segment_config_t seven_seg_cfg = {.Port = GPIO_A, .Pin_A = GPIO_PIN_0, .Pin_B = GPIO_PIN_1, .Pin_C = GPIO_PIN_2, .Pin_D = GPIO_PIN_3, .Pin_E = GPIO_PIN_4, .Pin_F = GPIO_PIN_5, .Pin_G = GPIO_PIN_6};

	HSevenSeg_vInitPins(&seven_seg_cfg);


	GPIOx_PinConfig_t button = {.Port = GPIO_B , .Pin = GPIO_PIN_0 , .Mode = GPIO_MODE_INPUT  , .OutputType = GPIO_OTYPE_PP , .PullType = GPIO_PUPD_PULL_UP , .Speed = GPIO_SPEED_LOW , .AltFunc = 0};

	MGPIO_vPinInit(&button);
	
	
	u8 counter = 0 ;
	while(1){
		
		if (MGPIO_u8GetPinValue(GPIO_B, GPIO_PIN_0) == GPIO_PIN_LOW) { // button pressed
			counter = (counter+1)%10 ; 
			DELAY_MS(200);
		}

		HSevenSeg_vDisplayNumber(&seven_seg_cfg, counter);


	}
	return 0;
}
