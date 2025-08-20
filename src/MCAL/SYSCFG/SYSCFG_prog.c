#include "SYSCFG_int.h"
#include "SYSCFG_prv.h"
#include "SYSCFG_cfg.h"


void MSYSCFG_vSetExternalInterruptLine(u8 A_u8PortID ,u8 A_u8PinID){
    u8 L_u8RegisterIndex = A_u8PinID / 4;                                       // choose EXTICR1–4
    u8 L_u8ShiftAmount = (A_u8PinID % 4) * 4;                                   // choose the nibble in the register
    SYSCFG->EXTICRx[L_u8RegisterIndex] &= ~(0xF << L_u8ShiftAmount);            // clear the nibble
    SYSCFG->EXTICRx[L_u8RegisterIndex] |=  (A_u8PortID << L_u8ShiftAmount);     // set new port
}
