#include "DAC_int.h"


void HDAC_vInit(DAC_cfg_t* cfg){
    switch (cfg->Port) {
        case GPIO_A:
            MRCC_vEnableClk(RCC_AHB1, GPIOAEN);
            for (u8 pin = 0 ; pin < 8 ; pin++){
                GPIOx_PinConfig_t pinCFG = {
                    .Port = GPIO_A , 
                    .Pin = cfg->Pins[pin] , 
                    .Mode = GPIO_MODE_OUTPUT , 
                    .OutputType = GPIO_OTYPE_PP ,
                    .PullType = GPIO_PUPD_NONE ,
                    .Speed = GPIO_SPEED_MEDIUM
                 };
                MGPIO_vPinInit(&pinCFG);
            }
            break;
        case GPIO_B:
            MRCC_vEnableClk(RCC_AHB1, GPIOBEN);
            for (u8 pin = 0 ; pin < 8 ; pin++){
                GPIOx_PinConfig_t pinCFG = {
                    .Port = GPIO_B , 
                    .Pin = cfg->Pins[pin] , 
                    .Mode = GPIO_MODE_OUTPUT , 
                    .OutputType = GPIO_OTYPE_PP ,
                    .PullType = GPIO_PUPD_NONE ,
                    .Speed = GPIO_SPEED_MEDIUM
                 };
                MGPIO_vPinInit(&pinCFG);
            }
            break;
        // Add more cases for other ports as needed
        default:
            // Handle invalid port
            break;
    }
}
void HDAC_vSetValue(DAC_cfg_t* cfg, u8 value){
    for (u8 i = 0; i < 8; i++){
			MGPIO_vSetPinValue(cfg->Port, cfg->Pins[i], (value & (1<<i)) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
		}
}