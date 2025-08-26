#include "ledmatrix_int.h"
#include "ledmatrix_prv.h"


void HLedMatrix_vInitPins(LedMatrix_config_t* LedMatrix_cfg){

    u8 L_u8Port1Name = (LedMatrix_cfg->Port1 == GPIO_A) ? GPIOAEN :GPIOBEN ;
    u8 L_u8Port2Name = (LedMatrix_cfg->Port2 == GPIO_A) ? GPIOAEN :GPIOBEN ;

    MRCC_vEnableClk(RCC_AHB1, L_u8Port1Name);
    MRCC_vEnableClk(RCC_AHB1, L_u8Port2Name);

    for (int pin = 0; pin < 8; pin++) {
        GPIOx_PinConfig_t pinFunction[] = { 
            { .Port = LedMatrix_cfg->Port1, .Pin = LedMatrix_cfg->RowPins[pin].Pin, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OTYPE_PP , .PullType = GPIO_PUPD_NONE, .Speed = GPIO_SPEED_LOW , .AltFunc = GPIO_AF0 } 
        };

        MGPIO_vPinInit(pinFunction);
    }
    for (int pin = 0; pin < 8; pin++) {
        GPIOx_PinConfig_t pinFunction[] = { 
            { .Port = LedMatrix_cfg->Port2, .Pin = LedMatrix_cfg->ColPins[pin].Pin, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OTYPE_PP , .PullType = GPIO_PUPD_NONE, .Speed = GPIO_SPEED_LOW , .AltFunc = GPIO_AF0 } 
        };

        MGPIO_vPinInit(pinFunction);
    }
}

void HLedMatrix_vDisplayRow(LedMatrix_config_t* LedMatrix_cfg, u8 row){
    for (int pin = 0; pin < 8; pin++) {
        MGPIO_vSetPinValue(LedMatrix_cfg->Port1, LedMatrix_cfg->RowPins[pin].Pin, (row & (1<<pin)) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
    }
}

void HLedMatrix_vDisplayColumn(LedMatrix_config_t* LedMatrix_cfg, u8 col){
    for (int pin = 0 ; pin < 8 ; pin++) {
        MGPIO_vSetPinValue(LedMatrix_cfg->Port2, LedMatrix_cfg->ColPins[pin].Pin, (col & (1<<pin)) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
    }
}
void HLedMatrix_vDisplayFrame(LedMatrix_config_t* LedMatrix_cfg , u8 A_au8FrameData[8])
{
    for (int col = 0; col < 8; col++)
    {
        // 1. Deactivate all columns to prevent ghosting
        HLedMatrix_vDisplayColumn(LedMatrix_cfg, 0x00);

        // 2. Set the row data for the current column
        HLedMatrix_vDisplayRow(LedMatrix_cfg, A_au8FrameData[col]);
        
        // 3. Activate only the current column
        HLedMatrix_vDisplayColumn(LedMatrix_cfg, (1 << col));
        
        // 4. Delay for a short period for persistence of vision
        MSYSTICK_vSetDelayMS(2); // e.g., 2ms delay. Total refresh time = 8*2 = 16ms (~62.5 Hz)
    }
}