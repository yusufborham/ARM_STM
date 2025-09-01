#ifndef STP_INT_H
#define STP_INT_H

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO_int.h"
#include "../../LIB/Delay.h"



typedef enum {
    STP_8BIT_MODE ,
    STP_16BIT_MODE
} STP_Mode_t;

typedef struct {
    u8 Port ;
    u8 ShiftClkPin ;
    u8 SerialDataPin ;
    u8 LatchPin ;
    STP_Mode_t Mode ;
} STP_Config_t;

void HSTP_vInit(STP_Config_t* Config);
void HSTP_vShiftClockAdvance(STP_Config_t* Config);
void HSTP_vLatchClockAdvance(STP_Config_t* Config);
void HSTP_vSendData(STP_Config_t* Config, u32 Data);

#endif
