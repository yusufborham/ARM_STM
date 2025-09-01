#include "SevSeg_int.h"
#include "SevSeg_prv.h"

GPIOx_PinConfig_t seven_seg[7];

 u8 seven_seg_v[10] = { // binary values to put in portA directly to dispplay digits
	  	0b0111111, // 0
		0b0000110, // 1
		0b1011011, // 2
		0b1001111, // 3
		0b1100110, // 4
		0b1101101, // 5
		0b1111101, // 6
		0b0000111, // 7
		0b1111111, // 8
		0b1101111  // 9
};

void HSevenSeg_vInitPins(Seven_Segment_config_t* Sev_seg_cfg) {
        seven_seg[0] = (GPIOx_PinConfig_t){.Port = Sev_seg_cfg->Port, .Pin = Sev_seg_cfg->Pin_A, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OTYPE_PP, .PullType = GPIO_PUPD_NONE, .Speed = GPIO_SPEED_LOW, .AltFunc = 0};
        seven_seg[1] = (GPIOx_PinConfig_t){.Port = Sev_seg_cfg->Port, .Pin = Sev_seg_cfg->Pin_B, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OTYPE_PP, .PullType = GPIO_PUPD_NONE, .Speed = GPIO_SPEED_LOW, .AltFunc = 0};
        seven_seg[2] = (GPIOx_PinConfig_t){.Port = Sev_seg_cfg->Port, .Pin = Sev_seg_cfg->Pin_C, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OTYPE_PP, .PullType = GPIO_PUPD_NONE, .Speed = GPIO_SPEED_LOW, .AltFunc = 0};
        seven_seg[3] = (GPIOx_PinConfig_t){.Port = Sev_seg_cfg->Port, .Pin = Sev_seg_cfg->Pin_D, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OTYPE_PP, .PullType = GPIO_PUPD_NONE, .Speed = GPIO_SPEED_LOW, .AltFunc = 0};
        seven_seg[4] = (GPIOx_PinConfig_t){.Port = Sev_seg_cfg->Port, .Pin = Sev_seg_cfg->Pin_E, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OTYPE_PP, .PullType = GPIO_PUPD_NONE, .Speed = GPIO_SPEED_LOW, .AltFunc = 0};
        seven_seg[5] = (GPIOx_PinConfig_t){.Port = Sev_seg_cfg->Port, .Pin = Sev_seg_cfg->Pin_F, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OTYPE_PP, .PullType = GPIO_PUPD_NONE, .Speed = GPIO_SPEED_LOW, .AltFunc = 0};
        seven_seg[6] = (GPIOx_PinConfig_t){.Port = Sev_seg_cfg->Port, .Pin = Sev_seg_cfg->Pin_G, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OTYPE_PP, .PullType = GPIO_PUPD_NONE, .Speed = GPIO_SPEED_LOW, .AltFunc = 0};

        switch (Sev_seg_cfg->Port){
            case GPIO_A :
                MRCC_vEnableClk(RCC_AHB1, GPIOAEN);
                break ;
            case GPIO_B :
                MRCC_vEnableClk(RCC_AHB1, GPIOBEN);
                break;
            default:
                break;
        }
        MGPIO_vPinInit(&seven_seg[0]);
        MGPIO_vPinInit(&seven_seg[1]);
        MGPIO_vPinInit(&seven_seg[2]);
        MGPIO_vPinInit(&seven_seg[3]);
        MGPIO_vPinInit(&seven_seg[4]);
        MGPIO_vPinInit(&seven_seg[5]);
        MGPIO_vPinInit(&seven_seg[6]);
}
   

void HSevenSeg_vDisplayNumber(Seven_Segment_config_t* Sev_seg_cfg , u8 number){
    MGPIO_vSetPinValue(Sev_seg_cfg->Port, Sev_seg_cfg->Pin_A, ((seven_seg_v[number] >> 0) & 1) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
    MGPIO_vSetPinValue(Sev_seg_cfg->Port, Sev_seg_cfg->Pin_B, ((seven_seg_v[number] >> 1) & 1) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
    MGPIO_vSetPinValue(Sev_seg_cfg->Port, Sev_seg_cfg->Pin_C, ((seven_seg_v[number] >> 2) & 1) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
    MGPIO_vSetPinValue(Sev_seg_cfg->Port, Sev_seg_cfg->Pin_D, ((seven_seg_v[number] >> 3) & 1) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
    MGPIO_vSetPinValue(Sev_seg_cfg->Port, Sev_seg_cfg->Pin_E, ((seven_seg_v[number] >> 4) & 1) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
    MGPIO_vSetPinValue(Sev_seg_cfg->Port, Sev_seg_cfg->Pin_F, ((seven_seg_v[number] >> 5) & 1) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
    MGPIO_vSetPinValue(Sev_seg_cfg->Port, Sev_seg_cfg->Pin_G, ((seven_seg_v[number] >> 6) & 1) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
}