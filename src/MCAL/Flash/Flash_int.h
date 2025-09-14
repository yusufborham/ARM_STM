#ifndef FLASH_INT_H_
#define FLASH_INT_H_

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Delay.h"
#include "../../LIB/MATH_Fn.h" 

typedef enum {
    SECTOR_0 = 0 ,
    SECTOR_1 ,
    SECTOR_2 ,
    SECTOR_3 ,
    SECTOR_4 ,
    SECTOR_5 ,
}Flash_sector_t ;

void MFMI_vMassErase(void);
void MFMI_vSectorErase(Flash_sector_t A_xSectorNo);
void MFMI_vProgramFlash(u32 A_u32Address, u16* A_PtrData, u16 Datalength);

#endif