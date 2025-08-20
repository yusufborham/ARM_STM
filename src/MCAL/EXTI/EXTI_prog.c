#include "EXTI_int.h"
#include "EXTI_cfg.h"
#include "EXTI_prv.h"

void MEXTI_vEnableExternalInterruptLine(u8 A_u8PinID){
    SET_BIT(EXTI->IMR , A_u8PinID ) ; 
}

void MEXTI_vDisableExternalInterruptLine(u8 A_u8PinID){
    CLR_BIT(EXTI->IMR , A_u8PinID ) ;
}

void MEXTI_vSetTriggerCondition(u8 A_u8PinID, u8 A_u8TriggerCondition){
    switch (A_u8TriggerCondition) {
        case RISING_EDGE_INTERRUPT_TRIGGER :
            SET_BIT(EXTI->RTSR , A_u8PinID ) ;
            CLR_BIT(EXTI->FTSR , A_u8PinID ) ;
            break ;
        
        case FALLING_EDGE_INTERRUPT_TRIGGER :
            SET_BIT(EXTI->FTSR , A_u8PinID ) ;
            CLR_BIT(EXTI->RTSR , A_u8PinID ) ;
            break ;

        case BOTH_EDGE_INTERRUPT_TRIGGER :
            SET_BIT(EXTI->RTSR , A_u8PinID ) ;
            SET_BIT(EXTI->FTSR , A_u8PinID ) ;
            break ;

        case NO_INTERRUPT_TRIGGER :
            CLR_BIT(EXTI->RTSR , A_u8PinID ) ;
            CLR_BIT(EXTI->FTSR , A_u8PinID ) ;
            break ;
    }
}

u8 MEXTI_u8GetPendingFlag(u8 A_u8PinID){
    return GET_BIT(EXTI->PR , A_u8PinID);
}

void MEXTI_vClearPendingFlag(u8 A_u8PinID){
    SET_BIT(EXTI->PR , A_u8PinID);
}