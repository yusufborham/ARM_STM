#include "ledmatrix_int.h"
#include "ledmatrix_prv.h"


void HLedMatrix_vInitPins(LedMatrix_config_t* LedMatrix_cfg){
    switch (LedMatrix_cfg->Mode) {
        case LED_MATRIX_NORMAL_MODE:{
            u8 L_u8Port1Name = ((LedMatrix_cfg->Config.normalConfig.Port1 == GPIO_A) ? GPIOAEN :GPIOBEN) ;
            u8 L_u8Port2Name = ((LedMatrix_cfg->Config.normalConfig.Port2 == GPIO_A) ? GPIOAEN :GPIOBEN) ;

            MRCC_vEnableClk(RCC_AHB1, L_u8Port1Name);
            MRCC_vEnableClk(RCC_AHB1, L_u8Port2Name);

            for (u8 pin = 0; pin < 8; pin++) {
                GPIOx_PinConfig_t pinFunction[] = { 
                    {.Port = LedMatrix_cfg->Config.normalConfig.Port1, 
                     .Pin = LedMatrix_cfg->Config.normalConfig.RowPins[pin].Pin, 
                     .Mode = GPIO_MODE_OUTPUT, 
                     .OutputType = GPIO_OTYPE_PP , 
                     .PullType = GPIO_PUPD_NONE, 
                     .Speed = GPIO_SPEED_LOW , 
                     .AltFunc = GPIO_AF0 } 
                };

                MGPIO_vPinInit(pinFunction);
            }
            for (u8 pin = 0; pin < 8; pin++) {
                GPIOx_PinConfig_t pinFunction[] = { 
                    { .Port = LedMatrix_cfg->Config.normalConfig.Port2, 
                      .Pin = LedMatrix_cfg->Config.normalConfig.ColPins[pin].Pin, 
                      .Mode = GPIO_MODE_OUTPUT, 
                      .OutputType = GPIO_OTYPE_PP , 
                      .PullType = GPIO_PUPD_NONE, 
                      .Speed = GPIO_SPEED_LOW , 
                      .AltFunc = GPIO_AF0 } 
                };

                MGPIO_vPinInit(pinFunction);
            }
            break;}
        case LED_MATRIX_STP_MODE:
            HSTP_vInit(&LedMatrix_cfg->Config.stpConfig);
            break;
    }
    
}

void HLedMatrix_vDisplayRow(LedMatrix_config_t* LedMatrix_cfg, u8 row){
    switch (LedMatrix_cfg->Mode)
    {
    case LED_MATRIX_NORMAL_MODE:
        for (u8 pin = 0; pin < 8; pin++) {
            MGPIO_vSetPinValue(LedMatrix_cfg->Config.normalConfig.Port1, LedMatrix_cfg->Config.normalConfig.RowPins[pin].Pin, (row & (1<<pin)) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
        }
        break;
    default:
        break;
    }
    
}

void HLedMatrix_vDisplayColumn(LedMatrix_config_t* LedMatrix_cfg, u8 col){
    switch (LedMatrix_cfg->Mode)
    {
    case LED_MATRIX_NORMAL_MODE:
        for (u8 pin = 0; pin < 8; pin++) {
            MGPIO_vSetPinValue(LedMatrix_cfg->Config.normalConfig.Port2, LedMatrix_cfg->Config.normalConfig.ColPins[pin].Pin, (col & (1<<pin)) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
        }
        break;
    
    default:
        break;
    }
}
void HLedMatrix_vDisplayFrame(LedMatrix_config_t* LedMatrix_cfg , u8 A_au8FrameData[8])
{   switch (LedMatrix_cfg->Mode)
    {
    case LED_MATRIX_NORMAL_MODE:
        for (u8 col = 0; col < 8; col++)
        {
            // 1. Deactivate all columns to prevent ghosting
            HLedMatrix_vDisplayColumn(LedMatrix_cfg, 0x00);

            // 2. Set the row data for the current column
            HLedMatrix_vDisplayRow(LedMatrix_cfg, A_au8FrameData[col]);
            
            // 3. Activate only the current column
            HLedMatrix_vDisplayColumn(LedMatrix_cfg, (1 << col));
            
            // 4. Delay for a short period for persistence of vision
            MSYSTICK_vSetDelayMS(2.5); // e.g., 2.5ms delay. Total refresh time = 8*2.5 = 20ms (~50 Hz)
        }
        break;
    case LED_MATRIX_STP_MODE:
        for (u8 col = 0; col < 8; col++){
            // Clear previous data
            HSTP_vSendData(&LedMatrix_cfg->Config.stpConfig, 0);
            // Prepare new data
            u8 L_u8HighByte = (1 << col ) ;
            u8 l_u8LowByte = (A_au8FrameData[col] & 0xFF) ;
            u32 L_u32DataToSend = (L_u8HighByte << 8) | l_u8LowByte ;
            // send data 
            HSTP_vSendData(&LedMatrix_cfg->Config.stpConfig, L_u32DataToSend);
            DELAY_MS(2.5);
        }
        break;
    default:
        break;
    }
}

void HLedMatrix_vDisplayFrameFor(u32 A_u32DurationMs , LedMatrix_config_t* LedMatrix_cfg , u8 A_au8FrameData[8]){
    u32 L_u32CountTimes = A_u32DurationMs / 20 ; // each frame takes 20 ms to display
    for (u32 i = 0; i < L_u32CountTimes; i++) {
        HLedMatrix_vDisplayFrame(LedMatrix_cfg , A_au8FrameData);
    }
}

