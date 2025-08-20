#ifndef SYSCFG_PRV_H
#define SYSCFG_PRV_H

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#define SYSCFG_BASE_ADDRESS 0x40013800

#define SYSCFG_REG_INDEX(pin)   ((pin) / 4)
#define SYSCFG_NIBBLE_POS(pin)  (((pin) % 4) * 4)
#define SYSCFG_CLEAR_MASK(pin)  (0xF << SYSCFG_NIBBLE_POS(pin))



typedef struct {
    volatile u32 MEMRMP ;
    volatile u32 PMC ;
    volatile u32 EXTICRx[4];
    volatile u32 reserved[2];
    volatile u32 CMPCR;
} SYSCFG_MemMap_t ;

#define SYSCFG  (( volatile SYSCFG_MemMap_t*)SYSCFG_BASE_ADDRESS)

#endif