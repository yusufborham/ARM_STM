#include "STP_int.h"

u8 G_u8CounterBitMode = 0 ;

void HSTP_vInit(STP_Config_t* Config) {
    GPIOx_PinConfig_t pinFunction = { 
        .Port = Config->Port, 
        .Pin = Config->ShiftClkPin, 
        .Mode = GPIO_MODE_OUTPUT, 
        .OutputType = GPIO_OTYPE_PP, 
        .PullType = GPIO_PUPD_NONE, 
        .Speed = GPIO_SPEED_HIGH, 
        .AltFunc = GPIO_AF0 
    };
    MGPIO_vPinInit(&pinFunction);
    pinFunction.Pin = Config->SerialDataPin;
    MGPIO_vPinInit(&pinFunction);
    pinFunction.Pin = Config->LatchPin;
    MGPIO_vPinInit(&pinFunction);
    G_u8CounterBitMode = (Config->Mode == STP_8BIT_MODE) ? 8 : 16;
}

void HSTP_vShiftClockAdvance(STP_Config_t* Config) {
    MGPIO_vSetPinValue(Config->Port, Config->ShiftClkPin, GPIO_PIN_HIGH);
    DELAY_MS(1);
    MGPIO_vSetPinValue(Config->Port, Config->ShiftClkPin, GPIO_PIN_LOW);
}


void HSTP_vLatchClockAdvance(STP_Config_t* Config) {
    MGPIO_vSetPinValue(Config->Port, Config->LatchPin, GPIO_PIN_HIGH);
    DELAY_MS(1);
    MGPIO_vSetPinValue(Config->Port, Config->LatchPin, GPIO_PIN_LOW);
}

void HSTP_vSendData(STP_Config_t* Config, u32 Data) {
    for (u8 i = 0; i < G_u8CounterBitMode; i++) {
        MGPIO_vSetPinValue(Config->Port, Config->SerialDataPin, (Data & (1 << i)) ? GPIO_PIN_HIGH : GPIO_PIN_LOW);
        HSTP_vShiftClockAdvance(Config);
    }
    HSTP_vLatchClockAdvance(Config);
}
