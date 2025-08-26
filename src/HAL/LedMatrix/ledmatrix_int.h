#ifndef LEDMATRIX_INT_H
#define LEDMATRIX_INT_H

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/GPIO/gpio_int.h"
#include "../../MCAL/GPIO/gpio_prv.h"

#include "../../MCAL/RCC/rcc_int.h"
#include "../../MCAL/RCC/rcc_prv.h"

#include "../../MCAL/SYSTICK/systick_int.h"
#include "../../MCAL/SYSTICK/systick_prv.h"
// Your code here

typedef struct {
    u8 Pin ;
}Pin_cfg_t;

typedef struct {
    u8 Port1;
    Pin_cfg_t RowPins[8];
    u8 Port2;
    Pin_cfg_t ColPins[8];
} LedMatrix_config_t;


void HLedMatrix_vInitPins(LedMatrix_config_t* LedMatrix_cfg);

void HLedMatrix_vDisplayRow(LedMatrix_config_t* LedMatrix_cfg, u8 row);

void HLedMatrix_vDisplayColumn(LedMatrix_config_t* LedMatrix_cfg, u8 col);

void HLedMatrix_vDisplayFrame(LedMatrix_config_t* LedMatrix_cfg , u8 A_au8FrameData[8]);

#endif // LEDMATRIX_INT_H