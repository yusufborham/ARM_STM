#ifndef DAC_INT_H
#define DAC_INT_H

#include "../../LIB/STD_TYPES.h"


#include "../../MCAL/GPIO/GPIO_int.h"
#include "../../MCAL/RCC/RCC_int.h"
#include "../../MCAL/RCC/RCC_prv.h"

// Your code here
typedef struct {
    u8 Port ;
    u8 Pins[8];
} DAC_cfg_t;

/*
 * Initializes the DAC.
 */
void HDAC_vInit(DAC_cfg_t* cfg);

/*
 * Sets the DAC output value.
 * @param cfg Pointer to the DAC configuration structure.
 * @param value The value to set on the DAC output.
 */
void HDAC_vSetValue(DAC_cfg_t* cfg, u8 value);
#endif
