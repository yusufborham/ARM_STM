#ifndef SEVSEG_INT_H_
#define SEVSEG_INT_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"


#include  "../../MCAL/GPIO/GPIO_int.h"
#include "../../MCAL/GPIO/GPIO_prv.h"

#include "../../MCAL/RCC/RCC_int.h"
#include "../../MCAL/RCC/RCC_prv.h"



typedef struct {
    u8 Port ;
    u8 Pin_A ;
    u8 Pin_B ;
    u8 Pin_C ;
    u8 Pin_D ;
    u8 Pin_E ;
    u8 Pin_F ;
    u8 Pin_G ;
} Seven_Segment_config_t;


void HSevenSeg_vInitPins(Seven_Segment_config_t* Sev_seg_cfg);
void HSevenSeg_vDisplayNumber(Seven_Segment_config_t* Sev_seg_cfg, u8 number);

#endif