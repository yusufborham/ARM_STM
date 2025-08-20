#include "EXTI_int.h"
#include "EXTI_cfg.h"
#include "EXTI_prv.h"

// an array of pointers to functions 
static void (*g_apfHandler[16])(void) = {NULL};


void MEXTI_vEnableExternalInterruptLine(u8 A_u8PinID){
    if (A_u8PinID < 16)
        SET_BIT(EXTI->IMR , A_u8PinID ) ; 
}

void MEXTI_vDisableExternalInterruptLine(u8 A_u8PinID){
    if (A_u8PinID < 16)
        CLR_BIT(EXTI->IMR , A_u8PinID ) ;
}

void MEXTI_vSetTriggerCondition(u8 A_u8PinID, u8 A_u8TriggerCondition){
    if (A_u8PinID < 16) {
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
}

u8 MEXTI_u8GetPendingFlag(u8 A_u8PinID){
    if (A_u8PinID < 16){
        return GET_BIT(EXTI->PR , A_u8PinID);
    }
    return 0;
}

void MEXTI_vClearPendingFlag(u8 A_u8PinID){
    if (A_u8PinID < 16)
        SET_BIT(EXTI->PR , A_u8PinID);
}

void MEXTI_vSetCallBackFunction(u8 A_u8PinID , void(*A_fpHandler)(void)){
    if (A_u8PinID < 16)
        g_apfHandler[A_u8PinID] = A_fpHandler ;
}

void EXTI0_IRQHandler(void)
{
    if (MEXTI_u8GetPendingFlag(0)) {
        // Clear the pending flag
        MEXTI_vClearPendingFlag(0);
        
        // Call the handler if it is set
        if (g_apfHandler[0] != NULL) {
            g_apfHandler[0]();
        }
    }
}

void EXTI1_IRQHandler(void)
{
    if (MEXTI_u8GetPendingFlag(1)) {
        // Clear the pending flag
        MEXTI_vClearPendingFlag(1);

        // Call the handler if it is set
        if (g_apfHandler[1] != NULL) {
            g_apfHandler[1]();
        }
    }
}
void EXTI2_IRQHandler(void)
{
    if (MEXTI_u8GetPendingFlag(2)) {
        // Clear the pending flag
        MEXTI_vClearPendingFlag(2);

        // Call the handler if it is set
        if (g_apfHandler[2] != NULL) {
            g_apfHandler[2]();
        }
    }
}

void EXTI3_IRQHandler(void)
{
    if (MEXTI_u8GetPendingFlag(3)) {
        // Clear the pending flag
        MEXTI_vClearPendingFlag(3);

        // Call the handler if it is set
        if (g_apfHandler[3] != NULL) {
            g_apfHandler[3]();
        }
    }
}

void EXTI4_IRQHandler(void)
{
    if (MEXTI_u8GetPendingFlag(4)) {
        // Clear the pending flag
        MEXTI_vClearPendingFlag(4);

        // Call the handler if it is set
        if (g_apfHandler[4] != NULL) {
            g_apfHandler[4]();
        }
    }
}

void EXTI9_5_IRQHandler(void)
{
    if (MEXTI_u8GetPendingFlag(5)) {
        // Clear the pending flag
        MEXTI_vClearPendingFlag(5);

        // Call the handler if it is set
        if (g_apfHandler[5] != NULL) {
            g_apfHandler[5]();
        }
    }

    if (MEXTI_u8GetPendingFlag(6)) {
        // Clear the pending flag
        MEXTI_vClearPendingFlag(6);

        // Call the handler if it is set
        if (g_apfHandler[6] != NULL) {
            g_apfHandler[6]();
        }
    }

    if (MEXTI_u8GetPendingFlag(7)) {
        // Clear the pending flag
        MEXTI_vClearPendingFlag(7);

        // Call the handler if it is set
        if (g_apfHandler[7] != NULL) {
            g_apfHandler[7]();
        }
    }

    if (MEXTI_u8GetPendingFlag(8)) {
        // Clear the pending flag
        MEXTI_vClearPendingFlag(8);

        // Call the handler if it is set
        if (g_apfHandler[8] != NULL) {
            g_apfHandler[8]();
        }
    }

    if (MEXTI_u8GetPendingFlag(9)) {
        // Clear the pending flag
        MEXTI_vClearPendingFlag(9);

        // Call the handler if it is set
        if (g_apfHandler[9] != NULL) {
            g_apfHandler[9]();
        }
    }
}

void  EXTI15_10_IRQHandler(void)
{
    if (MEXTI_u8GetPendingFlag(10)) {
        // Clear the pending flag
        MEXTI_vClearPendingFlag(10);

        // Call the handler if it is set
        if (g_apfHandler[10] != NULL) {
            g_apfHandler[10]();
        }
    }

    if (MEXTI_u8GetPendingFlag(11)) {
        // Clear the pending flag
        MEXTI_vClearPendingFlag(11);

        // Call the handler if it is set
        if (g_apfHandler[11] != NULL) {
            g_apfHandler[11]();
        }
    }

    if (MEXTI_u8GetPendingFlag(12)) {
        // Clear the pending flag
        MEXTI_vClearPendingFlag(12);

        // Call the handler if it is set
        if (g_apfHandler[12] != NULL) {
            g_apfHandler[12]();
        }
    }

    if (MEXTI_u8GetPendingFlag(13)) {
        // Clear the pending flag
        MEXTI_vClearPendingFlag(13);

        // Call the handler if it is set
        if (g_apfHandler[13] != NULL) {
            g_apfHandler[13]();
        }
    }

    if (MEXTI_u8GetPendingFlag(14)) {
        // Clear the pending flag
        MEXTI_vClearPendingFlag(14);

        // Call the handler if it is set
        if (g_apfHandler[14] != NULL) {
            g_apfHandler[14]();
        }
    }

    if (MEXTI_u8GetPendingFlag(15)) {
        // Clear the pending flag
        MEXTI_vClearPendingFlag(15);

        // Call the handler if it is set
        if (g_apfHandler[15] != NULL) {
            g_apfHandler[15]();
        }
    }
}
