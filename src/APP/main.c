
#include "../MCAL/RCC/RCC_int.h"
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/RCC/RCC_prv.h"
#include "../MCAL/RCC/RCC_cfg.h"
#include "../MCAL/GPIO/GPIO_int.h"
#include "../MCAL/GPIO/GPIO_prv.h"



int main (void){

	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, GPIOAEN);

	GPIOx_PinConfig_t led = {.Port = GPIO_A , .Pin = GPIO_PIN_0 , .Mode = GPIO_MODE_OUTPUT , .OutputType = GPIO_OTYPE_PP , .PullType = GPIO_PUPD_NONE , .Speed = GPIO_SPEED_LOW , .AltFunc = 0};

	MGPIO_vPinInit(&led);
	MGPIO_vSetPinValue(GPIO_A, GPIO_PIN_0, GPIO_PIN_HIGH);

	while(1){
			MGPIO_vSetPinValue(GPIO_A, GPIO_PIN_0, GPIO_PIN_HIGH);
			for(long i = 0 ; i < 650000 ; i++ ){
				asm("NOP");
				asm("NOP");
				asm("NOP");
				asm("NOP");

			}

			MGPIO_vSetPinValue(GPIO_A, GPIO_PIN_0, GPIO_PIN_LOW);
			for(long i = 0 ; i < 650000 ; i++ ){
				asm("NOP");
				asm("NOP");
				asm("NOP");
				asm("NOP");

			}
	}
	return 0;
}
