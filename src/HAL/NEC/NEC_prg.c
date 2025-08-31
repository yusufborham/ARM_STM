#include "NEC_int.h"
volatile u8 G_u8StartFrameDetected = 0 ;
volatile u32 G_au32FrameData[60] = {0} ;
volatile u8 G_u8DataByte = 0;
volatile u8 index = 0  ;

void HNEC_vInit(NEC_cfg_t* cfg){
  // Define a configuration structure
    GPIOx_PinConfig_t recPin = { 
        .Port = cfg->Port, 
        .Pin = cfg->Pin, 
        .Mode = GPIO_MODE_INPUT, 
        .OutputType = GPIO_OTYPE_PP, 
        .PullType = GPIO_PUPD_NONE, 
        .Speed = GPIO_SPEED_HIGH,
        .AltFunc = GPIO_AF0 // Not applicable for Input/Output mode
    };

    MGPIO_vPinInit(&recPin);

    MSYSTICK_vChooseClockSource(cfg->Timer_DIV);

    MEXTI_vEnableExternalInterruptLine(cfg->Pin);

    MEXTI_vSetTriggerCondition(cfg->Pin, FALLING_EDGE_INTERRUPT_TRIGGER);

    MSYSCFG_vSetExternalInterruptLine(cfg->Port, cfg->Pin);

   MNVIC_vConfigGroupPriority(NVIC_PriorityGroup16_SubGroup0);

   switch (cfg->Pin) {
       case GPIO_PIN_0: MNVIC_vEnableInterrupt(EXTI0_IRQn)     ; MNVIC_vSetPriority(EXTI0_IRQn, 0, 0)    ; break;
       case GPIO_PIN_1: MNVIC_vEnableInterrupt(EXTI1_IRQn)     ; MNVIC_vSetPriority(EXTI1_IRQn, 0, 0)    ; break;
       case GPIO_PIN_2: MNVIC_vEnableInterrupt(EXTI2_IRQn)     ; MNVIC_vSetPriority(EXTI2_IRQn, 0, 0)    ; break;
       case GPIO_PIN_3: MNVIC_vEnableInterrupt(EXTI3_IRQn)     ; MNVIC_vSetPriority(EXTI3_IRQn, 0, 0)    ; break;
       case GPIO_PIN_4: MNVIC_vEnableInterrupt(EXTI4_IRQn)     ; MNVIC_vSetPriority(EXTI4_IRQn, 0, 0)    ; break;
       case GPIO_PIN_5: MNVIC_vEnableInterrupt(EXTI9_5_IRQn)   ; MNVIC_vSetPriority(EXTI9_5_IRQn, 0, 0)  ; break;
       case GPIO_PIN_6: MNVIC_vEnableInterrupt(EXTI9_5_IRQn)   ; MNVIC_vSetPriority(EXTI9_5_IRQn, 0, 0)  ; break;
       case GPIO_PIN_7: MNVIC_vEnableInterrupt(EXTI9_5_IRQn)   ; MNVIC_vSetPriority(EXTI9_5_IRQn, 0, 0)  ; break;
       case GPIO_PIN_8: MNVIC_vEnableInterrupt(EXTI9_5_IRQn)   ; MNVIC_vSetPriority(EXTI9_5_IRQn, 0, 0)  ; break;
       case GPIO_PIN_9: MNVIC_vEnableInterrupt(EXTI9_5_IRQn)   ; MNVIC_vSetPriority(EXTI9_5_IRQn, 0, 0)  ; break;
       case GPIO_PIN_10: MNVIC_vEnableInterrupt(EXTI15_10_IRQn); MNVIC_vSetPriority(EXTI15_10_IRQn, 0, 0); break;
       case GPIO_PIN_11: MNVIC_vEnableInterrupt(EXTI15_10_IRQn); MNVIC_vSetPriority(EXTI15_10_IRQn, 0, 0); break;
       case GPIO_PIN_12: MNVIC_vEnableInterrupt(EXTI15_10_IRQn); MNVIC_vSetPriority(EXTI15_10_IRQn, 0, 0); break;
       case GPIO_PIN_13: MNVIC_vEnableInterrupt(EXTI15_10_IRQn); MNVIC_vSetPriority(EXTI15_10_IRQn, 0, 0); break;
       case GPIO_PIN_14: MNVIC_vEnableInterrupt(EXTI15_10_IRQn); MNVIC_vSetPriority(EXTI15_10_IRQn, 0, 0); break;
       case GPIO_PIN_15: MNVIC_vEnableInterrupt(EXTI15_10_IRQn); MNVIC_vSetPriority(EXTI15_10_IRQn, 0, 0); break;
       default: /* Handle invalid pin if necessary */ break;
   }
    MEXTI_vSetCallBackFunction(cfg->Pin, HNEC_vReadCode);

}

void HNEC_vReadCode(){
    if (!G_u8StartFrameDetected) {
    	G_u8StartFrameDetected = 1;
    	MSYSTICK_vStartTimerMs(15);
      //MSYSTICK_vSetIntervalSingle(15, HNEC_vDecodeFrame);

//      index = 0;
      
    }

    else {
      G_au32FrameData[index++] = MSYSTICK_u32GetElapsedTimeUs() ;
      //MSYSTICK_vStartTimerMs(500);
      MSYSTICK_vSetIntervalSingle(4, HNEC_vDecodeFrame);
    }
}

void HNEC_vDecodeFrame(){
  // Decode the NEC frame data
  MSYSTICK_vDisableTimer();
  G_u8DataByte = 0 ;
  for (u8 i = 0; i < 8; i++) {
    if (G_au32FrameData[i+17] > 1800 && G_au32FrameData[i+17] < 2500) {
        SET_BIT(G_u8DataByte, i);
    }

    else if (G_au32FrameData[i+17] > 900 && G_au32FrameData[i+17] < 1300) {
        CLR_BIT(G_u8DataByte, i);
    }

  }
  G_u8StartFrameDetected = 0 ;
  index = 0 ;
  //clear the array
  for (u8 i = 0; i < 60; i++) {
    G_au32FrameData[i] = 0;
  }
}
