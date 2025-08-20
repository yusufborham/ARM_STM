/*
 * NVIC_prg.c
 *
 *  Created on: Aug 19, 2025
 *      Author: Yusuf Borham 
 *      Version: 0.0
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "NVIC_int.h"
#include "NVIC_prv.h"
#include "NVIC_cfg.h"

u8 G_u8GroupPriority = 0;

void MNVIC_vEnableInterrupt(u8 A_u8InterruptID) {
    SET_BIT(NVIC->NVIC_ISERx[A_u8InterruptID / 32], A_u8InterruptID % 32);
}
void MNVIC_vDisableInterrupt(u8 A_u8InterruptID) {
    CLR_BIT(NVIC->NVIC_ICERx[A_u8InterruptID / 32], A_u8InterruptID % 32);
}

void MNVIC_vSetPendingFlag(u8 A_u8InterruptID) {
    SET_BIT(NVIC->NVIC_ISPRx[A_u8InterruptID / 32], A_u8InterruptID % 32);
}

void MNVIC_vClearPendingFlag(u8 A_u8InterruptID) {
    CLR_BIT(NVIC->NVIC_ICPRx[A_u8InterruptID / 32], A_u8InterruptID % 32);
}



u8 MNVIC_u8GetActiveFlag(u8 A_u8InterruptID) {
    return GET_BIT(NVIC->NVIC_IABRx[A_u8InterruptID / 32], A_u8InterruptID % 32);
}

void MNVIC_vSetPriority(u8 A_u8InterruptID, u8 A_u8GroupPriority , u8 A_u8SubGroupPriority) {
    switch (G_u8GroupPriority) {
        case NVIC_PriorityGroup16_SubGroup0:
            NVIC->NVIC_IPRx[A_u8InterruptID] = (A_u8GroupPriority << 4)  ;
            break;
        case NVIC_PriorityGroup8_SubGroup2:
            NVIC->NVIC_IPRx[A_u8InterruptID] = (A_u8GroupPriority << 5) | (A_u8SubGroupPriority << 4);
            break;
        case NVIC_PriorityGroup4_SubGroup4:
            NVIC->NVIC_IPRx[A_u8InterruptID] = (A_u8GroupPriority << 6) | (A_u8SubGroupPriority << 4);
            break;
        case NVIC_PriorityGroup2_SubGroup8:
            NVIC->NVIC_IPRx[A_u8InterruptID] = (A_u8GroupPriority << 7) | (A_u8SubGroupPriority << 4);
            break;
        case NVIC_PriorityGroup0_SubGroup16:
            NVIC->NVIC_IPRx[A_u8InterruptID] = (A_u8SubGroupPriority << 4);
            break;
    }
}

void MNVIC_vConfigGroupPriority(NVIC_PriorityGroup_t A_u8GroupPriority){
    G_u8GroupPriority = A_u8GroupPriority ; 
    SCB_AIRCR = LockValueForAIRCR | (A_u8GroupPriority << 8 ) ;
}
