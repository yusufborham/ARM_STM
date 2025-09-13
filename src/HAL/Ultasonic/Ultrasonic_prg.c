#include "Ultrasonic_int.h"


volatile u32 pulseWidth = 0 ;
volatile u8 triggered = 0 ;
Ultrasonic_measuingState_t G_myUltaState ; 

///////////////////// prototypes ////////////////////
void handleUS(void);




/////////////////////////////////////////////////////
void handleUS(void){
    static u32 pulseStart = 0 ;
    if (MGPIO_u8GetPinValue(GPIO_A, GPIO_PIN_3) == 1){ // then we need to start timing 
        pulseStart = MSYSTICK_micros();         // registered a start for the pulse 
        G_myUltaState = MEASURING ;
    } 
    else {
        u32 *ptr = &pulseWidth ;
        *ptr =  MSYSTICK_micros() - pulseStart ;
        G_myUltaState = FINISHED ;
        pulseStart = 0;
    }
}



void HUltra_vInit(Ultrasonic_cfg_t* cfg){

    GPIOx_PinConfig_t echo = {
		.Port = cfg->Echo_port,
		.Pin = cfg->Echo_pin,
		.Mode = GPIO_MODE_INPUT,
		.AltFunc = GPIO_AF0,
		.Speed = GPIO_SPEED_HIGH,
		.PullType = GPIO_PUPD_NONE
	};
	MGPIO_vPinInit(&echo);

    GPIOx_PinConfig_t trig = {
        .Port = cfg->Trig_port,
        .Pin = cfg->Trig_pin,
        .Mode = GPIO_MODE_OUTPUT,
        .OutputType = GPIO_OTYPE_PP,
        .AltFunc = GPIO_AF0,
        .Speed = GPIO_SPEED_HIGH,
        .PullType = GPIO_PUPD_NONE
    };
    MGPIO_vPinInit(&trig);

    MEXTI_vEnableExternalInterruptLine(cfg->Echo_pin);

	MEXTI_vSetTriggerCondition(cfg->Echo_pin, BOTH_EDGE_INTERRUPT_TRIGGER);

	MEXTI_vSetCallBackFunction(cfg->Echo_pin, handleUS);

	MSYSCFG_vSetExternalInterruptLine(cfg->Echo_port, cfg->Echo_pin);

    MNVIC_vConfigGroupPriority(NVIC_PriorityGroup16_SubGroup0);

    switch (cfg->Echo_pin){
        case (GPIO_PIN_0) :
            MNVIC_vEnableInterrupt(EXTI0_IRQn);
            MNVIC_vSetPriority(EXTI0_IRQn, 6, 0);
            break ;
        case (GPIO_PIN_1) :
            MNVIC_vEnableInterrupt(EXTI1_IRQn);
            MNVIC_vSetPriority(EXTI1_IRQn, 6, 0);
            break ;
        case (GPIO_PIN_2) :
            MNVIC_vEnableInterrupt(EXTI2_IRQn);
            MNVIC_vSetPriority(EXTI2_IRQn, 6, 0);
            break ;
        case (GPIO_PIN_3) :
            MNVIC_vEnableInterrupt(EXTI3_IRQn);
            MNVIC_vSetPriority(EXTI3_IRQn, 6, 0);
            break ;
        case (GPIO_PIN_4) :
            MNVIC_vEnableInterrupt(EXTI4_IRQn);
            MNVIC_vSetPriority(EXTI4_IRQn, 6, 0);
            break ;
        case (GPIO_PIN_5) :
        case (GPIO_PIN_6) :
        case (GPIO_PIN_7) :
        case (GPIO_PIN_8) :
        case (GPIO_PIN_9) :
            MNVIC_vEnableInterrupt(EXTI9_5_IRQn);
            MNVIC_vSetPriority(EXTI9_5_IRQn, 6, 0);
            break ;
        case (GPIO_PIN_10) :
        case (GPIO_PIN_11) :
        case (GPIO_PIN_12) :
        case (GPIO_PIN_13) :
        case (GPIO_PIN_14) :
        case (GPIO_PIN_15) :
            MNVIC_vEnableInterrupt(EXTI15_10_IRQn);
            MNVIC_vSetPriority(EXTI15_10_IRQn, 6, 0);
            break ;
    }
	

    MSYSTICK_vEnableBckgroundMillis();
}

Ultrasonic_measuingState_t HUltra_u8ReadDisatnce(Ultrasonic_cfg_t* cfg , f32* ptr) {
    if (!triggered){
        MGPIO_vSetPinValue(GPIO_A ,GPIO_PIN_2 , GPIO_PIN_LOW);
        DELAY_US(2);
        MGPIO_vSetPinValue(GPIO_A ,GPIO_PIN_2 , GPIO_PIN_HIGH);
        DELAY_US(10);
        MGPIO_vSetPinValue(GPIO_A ,GPIO_PIN_2 , GPIO_PIN_LOW);
        triggered = 1 ;
    }
    if (triggered && G_myUltaState == FINISHED){
        f32 distance = (f32)pulseWidth * 0.017  ;
        *ptr = distance ;
        triggered = 0 ;
        G_myUltaState = MEASURING ;
        return FINISHED ;
    }
    return MEASURING ;

}
