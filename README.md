# MCAL interface Guide for STM32F4

## RCC - Functions 

### Enable clock 

``` c
MRCC_vInit()
```

- In RCC_cfg.h file

To choose the system clock source, modify the RCC_SYS_CLK definition: the options are HSE_CLK, HSI_CLK, PLL_CLK

``` c
#define RCC_SYS_CLK     HSE_CLK // Options: HSE_CLK, HSI_CLK, PLL_CLK
```

- In RCC_cfg.h 

To choose the outer clock source is a crystal or a clock 

``` c
#define HSE_BYPASS   MECHANICAL_CLK // Options: RC_CLK, MECHANICAL_CLK
```

### To enable a specific peripheral

``` c
MRCC_vEnableClk(u8 A_u8BusID, u8 A_u8PeripheralID);
```

- A_u8BusID: The bus ID (e.g., RCC_AHB1, RCC_APB1, RCC_APB2)
- A_u8PeripheralID: The peripheral ID (e.g. GPIOAEN , GPIOBEN, GPIOCEN , GPIODEN , GPIOEEN , GPIOHEN , TIM2EN , TIM3EN , TIM4EN , TIM5EN , WWDGEN , SPI2EN , SPI3EN , USART2EN , I2C1EN , I2C2EN , I2C3EN , PWREN , TIM1EN , USART1EN , USART6EN , ADC1EN , SDIOEN , SPI1EN , SPI4EN , SYSCFGEN , TIM9EN , TIM10EN , TIM11EN)

### To disable a specific peripheral 

``` c
MRCC_vDisableClk(u8 A_u8BusID, u8 A_u8PeripheralID);
```

- A_u8BusID: The bus ID (e.g., RCC_AHB1, RCC_APB1, RCC_APB2)
- A_u8PeripheralID: The peripheral ID (e.g. GPIOAEN , GPIOBEN, GPIOCEN , GPIODEN , GPIOEEN , GPIOHEN , TIM2EN , TIM3EN , TIM4EN , TIM5EN , WWDGEN , SPI2EN , SPI3EN , USART2EN , I2C1EN , I2C2EN , I2C3EN , PWREN , TIM1EN , USART1EN , USART6EN , ADC1EN , SDIOEN , SPI1EN , SPI4EN , SYSCFGEN , TIM9EN , TIM10EN , TIM11EN)

### To set APB1 prescaler 

``` c
MRCC_vSetAPB1Prescaler(u8 A_u8Prescaler)
```

- A_u8Prescaler: The prescaler value (e.g., APB1_PRESCALER_DIVIDE_1 , APB1_PRESCALER_DIVIDE_2 , APB1_PRESCALER_DIVIDE_4 , APB1_PRESCALER_DIVIDE_8 , APB1_PRESCALER_DIVIDE_16)

### To set APB2 prescaler 

``` c
MRCC_vSetAPB2Prescaler(u8 A_u8Prescaler)
```

- A_u8Prescaler: The prescaler value (e.g., APB2_PRESCALER_DIVIDE_1 , APB2_PRESCALER_DIVIDE_2 , APB2_PRESCALER_DIVIDE_4 , APB2_PRESCALER_DIVIDE_8 , APB2_PRESCALER_DIVIDE_16)

### To set AHB prescaler

``` c
MRCC_vSetAHBPrescaler(u8 A_u8Prescaler)
```

- A_u8Prescaler: The prescaler value (e.g., AHB_PRESCALER_DIVIDE_1 , AHB_PRESCALER_DIVIDE_2 , AHB_PRESCALER_DIVIDE_4 , AHB_PRESCALER_DIVIDE_8 , AHB_PRESCALER_DIVIDE_16 , AHB_PRESCALER_DIVIDE_64 , AHB_PRESCALER_DIVIDE_128 , AHB_PRESCALER_DIVIDE_256 , AHB_PRESCALER_DIVIDE_512)

### To output clock on a hardware pin 

``` c
MRCC_vOutputClockOnHardwarePin(u8 A_u8MCO1_PRESCALER , u8 A_u8MCO1_SOURCE);
```

- A_u8MCO1_PRESCALER: The prescaler value (e.g., MCO1_PRESCALER_DIVIDE_1 , MCO1_PRESCALER_DIVIDE_2 , MCO1_PRESCALER_DIVIDE_3 , MCO1_PRESCALER_DIVIDE_4 , MCO1_PRESCALER_DIVIDE_5)

- A_u8MCO1_SOURCE: The clock source (e.g., MCO1_SOURCE_HSI ,MCO1_SOURCE_LSE, MCO1_SOURCE_HSE , MCO1_SOURCE_PLL)

## GPIO - Functions

### Initialzing a Pin 

``` c
GPIOx_PinConfig_t pinFunction = { .Port = GPIOx, .Pin = GPIO_PIN_x, .Mode = GPIO_MODE_x, .OutputType = GPIO_OTYPE_X , .PullType = GPIO_PUPD_x, .Speed = GPIO_SPEED_x , .AltFunc = GPIO_AFx };

MGPIO_vPinInit(&pinFunction);
```

This structure can be used to configure any GPIO pin by changing the values of the fields.

- .Port options: GPIO_A, GPIO_B, GPIO_C, GPIO_D, GPIO_E, GPIO_F, GPIO_G, GPIO_H

- .Mode options: GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, GPIO_MODE_ALTERNATE, GPIO_MODE_ANALOG

- .OutputType options: GPIO_OTYPE_PP, GPIO_OTYPE_OD

- .PullType options: GPIO_PUPD_NONE, GPIO_PUPD_PULL_UP, GPIO_PUPD_PULL_DOWN

- .Speed options: GPIO_SPEED_LOW, GPIO_SPEED_MEDIUM, GPIO_SPEED_HIGH, GPIO_SPEED_VERY_HIGH

- .AltFunc options: GPIO_AF0, GPIO_AF1, GPIO_AF2, GPIO_AF3, GPIO_AF4, GPIO_AF5, GPIO_AF6, GPIO_AF7, GPIO_AF8, GPIO_AF9, GPIO_AF10, GPIO_AF11, GPIO_AF12, GPIO_AF13, GPIO_AF14, GPIO_AF15

### Set Pin Value 

``` c
MGPIO_vSetPinValue(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8Value);
```

- A_u8PortID: The port ID (e.g., GPIO_A, GPIO_B, GPIO_C, GPIO_D, GPIO_E, GPIO_F, GPIO_G, GPIO_H)

- A_u8PinID: The pin ID (e.g., GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, ..., GPIO_PIN_15)

- A_u8Value: The value to set (e.g., GPIO_PIN_HIGH, GPIO_PIN_LOW)

### Toggle Pin Value

``` c
MGPIO_vTogglePinValue(u8 A_u8PortID, u8 A_u8PinID);
```

- A_u8PortID: The port ID (e.g., GPIO_A, GPIO_B, GPIO_C, GPIO_D, GPIO_E, GPIO_F, GPIO_G, GPIO_H)

- A_u8PinID: The pin ID (e.g., GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, ..., GPIO_PIN_15)

### To read a Pin

``` c
MGPIO_u8GetPinValue(u8 A_u8PortID, u8 A_u8PinID);
```

- A_u8PortID: The port ID (e.g., GPIO_A, GPIO_B, GPIO_C, GPIO_D, GPIO_E, GPIO_F, GPIO_G, GPIO_H)

- A_u8PinID: The pin ID (e.g., GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, ..., GPIO_PIN_15)

## NVIC - Functions 

### To Enable an Interrupt

``` c
MNVIC_vEnableInterrupt(u8 A_u8InterruptID);
```

- A_u8InterruptID: The interrupt ID (e.g.,WWDG_IRQn , EXTI16_IRQn , EXTI21_IRQn , EXTI22_IRQn , EXTI0_IRQn , EXTI1_IRQn , EXTI2_IRQn , EXTI3_IRQn , EXTI4_IRQn , DMA1_Stream0_IRQn , DMA1_Stream1_IRQn , DMA1_Stream2_IRQn , DMA1_Stream3_IRQn , DMA1_Stream4_IRQn , DMA1_Stream5_IRQn , DMA1_Stream6_IRQn , ADC_IRQn , CAN1_TX_IRQn , CAN1_RX0_IRQn , CAN1_RX1_IRQn , CAN1_SCE_IRQn , EXTI9_5_IRQn , TIM1_BRK_TIM9_IRQn , TIM1_UP_TIM10_IRQn , TIM1_TRG_COM_TIM11_IRQn , TIM1_CC_IRQn , TIM2_IRQn , TIM3_IRQn , TIM4_IRQn , I2C1_EV_IRQn , I2C1_ER_IRQn , I2C2_EV_IRQn , I2C2_ER_IRQn , SPI1_IRQn , SPI2_IRQn , USART1_IRQn , USART2_IRQn)

### To disable an Interrupt

``` c
MNVIC_vDisableInterrupt(u8 A_u8InterruptID);
```

- A_u8InterruptID: The interrupt ID (e.g.,WWDG_IRQn , EXTI16_IRQn , EXTI21_IRQn , EXTI22_IRQn , EXTI0_IRQn , EXTI1_IRQn , EXTI2_IRQn , EXTI3_IRQn , EXTI4_IRQn , DMA1_Stream0_IRQn , DMA1_Stream1_IRQn , DMA1_Stream2_IRQn , DMA1_Stream3_IRQn , DMA1_Stream4_IRQn , DMA1_Stream5_IRQn , DMA1_Stream6_IRQn , ADC_IRQn , CAN1_TX_IRQn , CAN1_RX0_IRQn , CAN1_RX1_IRQn , CAN1_SCE_IRQn , EXTI9_5_IRQn , TIM1_BRK_TIM9_IRQn , TIM1_UP_TIM10_IRQn , TIM1_TRG_COM_TIM11_IRQn , TIM1_CC_IRQn , TIM2_IRQn , TIM3_IRQn , TIM4_IRQn , I2C1_EV_IRQn , I2C1_ER_IRQn , I2C2_EV_IRQn , I2C2_ER_IRQn , SPI1_IRQn , SPI2_IRQn , USART1_IRQn , USART2_IRQn)

### Set the pending flag for an Interrupt

``` c
MNVIC_vSetPendingFlag(u8 A_u8InterruptID);
```

- Setting a pending flag to 1 will cause the interrupt to be triggered as soon as the current instruction completes.

### Clear the pending flag for an Interrupt

``` c
MNVIC_vClearPendingFlag(u8 A_u8InterruptID);
```

- As soon as the interrupt is serviced, the pending flag will be cleared. clearing this flag only won't be enough to prevent the interrupt from being triggered again you must clear the peripheral's interrupt flag as well and the hardware clears the NVIC pending flag.


### Get the active flag for an Interrupt

``` c
MNVIC_u8GetActiveFlag(u8 A_u8InterruptID);
```

### Configure the Group sub Group Priority

``` c
MNVIC_vConfigGroupPriority(NVIC_PriorityGroup_t A_u8GroupPriority);
```

- A_u8GroupPriority: The group priority configuration ( eg NVIC_PriorityGroup16_SubGroup0 , NVIC_PriorityGroup8_SubGroup2 , NVIC_PriorityGroup4_SubGroup4 , NVIC_PriorityGroup2_SubGroup8 , NVIC_PriorityGroup0_SubGroup16 
)

### To set the priority of an Interrupt

``` c
MNVIC_vSetPriority(u8 A_u8InterruptID, u8 A_u8GroupPriority , u8 A_u8SubGroupPriority);
```

- A_u8InterruptID: The interrupt ID (e.g., WWDG_IRQn, EXTI16_IRQn, etc.)
- A_u8GroupPriority: The group priority according to the configuration check `MNVIC_vConfigGroupPriority(NVIC_PriorityGroup_t A_u8GroupPriority)`
- A_u8SubGroupPriority: The sub-group priority according to the configuration check `MNVIC_vConfigGroupPriority(NVIC_PriorityGroup_t A_u8GroupPriority)`

## EXTI - Functions 
    
### To Enable an EXTI Line

``` c
MEXTI_vEnableExternalInterruptLine(u8 A_u8PinID);
```

- A_u8PinID: The EXTI line ID (e.g., GPIO_PIN_0, GPIO_PIN_1, etc.)

### To Disable an EXTI Line

``` c
MEXTI_vDisableExternalInterruptLine(u8 A_u8PinID);
```

- A_u8PinID: The EXTI line ID (e.g., GPIO_PIN_0, GPIO_PIN_1, etc.)

### To Set the Triggering Edge for an EXTI Line

``` c
MEXTI_vSetTriggerCondition(u8 A_u8PinID, u8 A_u8TriggerCondition);
```

- A_u8PinID: The EXTI line ID (e.g., GPIO_PIN_0, GPIO_PIN_1, etc.)
- A_u8TriggerCondition: The triggering condition (e.g., RISING_EDGE_INTERRUPT_TRIGGER, FALLING_EDGE_INTERRUPT_TRIGGER,BOTH_EDGE_INTERRUPT_TRIGGER ,  NO_INTERRUPT_TRIGGER)

### To Get the Pending Status of an EXTI Line

``` c
u8 MEXTI_u8GetPendingFlag(u8 A_u8PinID);
```

- A_u8PinID: The EXTI line ID (e.g., GPIO_PIN_0, GPIO_PIN_1, etc.)

### To Clear the Pending Status of an EXTI Line

``` c
MEXTI_vClearPendingFlag(u8 A_u8PinID);
```

### To set the call back functions 

``` c 
MEXTI_vSetCallBackFunction(u8 A_u8PinID, void(*A_fpHandler)(void));
```

- A_fpHandler: Pointer to the callback function to be executed when the EXTI line is triggered.

- A_u8PinID: The EXTI line ID (e.g., GPIO_PIN_0, GPIO_PIN_1, etc.)

#### Notes

- You must configure the EXTI line before using it. 
- you must enable the clock to the GPIO port that the EXTI line is connected to.
- you must enable the clock to the SYSCFG peripheral. using this function: `MRCC_vEnableClk(RCC_APB2, SYSCFGEN);`
- Then use this function `MSYSCFG_vSetExternalInterruptLine(u8 A_u8PortID, u8 A_u8PinID);`
- A_u8PortID: The port ID (e.g., GPIO_A, GPIO_B, GPIO_C, GPIO_D, GPIO_E, GPIO_F, GPIO_G, GPIO_H)
- A_u8PinID: The EXTI line ID (e.g., GPIO_PIN_0, GPIO_PIN_1, etc.)

## SYSCFG - Functions

### To Configure the EXTI Line

``` c
MSYSCFG_vSetExternalInterruptLine(u8 A_u8PortID, u8 A_u8PinID);
```

- A_u8PortID: The port ID (e.g., GPIO_A, GPIO_B, GPIO_C, GPIO_D, GPIO_E, GPIO_F, GPIO_G, GPIO_H)
- A_u8PinID: The EXTI line ID (e.g., GPIO_PIN_0, GPIO_PIN_1, etc.)

## SYSTICK - Functions 

The SYSTICK timer is a countdown timer that can be used to generate interrupts at regular intervals.

### To choose the clock source for the SYSTICK 

``` c 
void MSYSTICK_vChooseClockSource(u8 A_u8ClockSource);
```

- A_u8ClockSource: The clock source (e.g., SYSTICK_CLK_SOURCE_AHB_DIV_8, SYSTICK_CLK_SOURCE_AHB_DIV_1)

### To start the timer in a normal mode

``` c 
MSYSTICK_vEnableTimer();
```

### To set the reload value for the SYSTICK timer

``` c
void MSYSTICK_vSetReloadValue(u32 A_u32ReloadValue);
```

- A_u32ReloadValue: The reload value for the SYSTICK timer must be a 24 bit number or less 

### To set the reload value and start the timer at the same time 

``` c
void MSYSTICK_vStartTimer(u32 A_u32ReloadValue);
```

### To set the current value in the timer register 

``` c 
MSYSTICK_vSetCurrentValue(u32 A_u32CurrentValue);
```

- Take care when calling this function no matter what value is written the counter just reloads from the reload register 

### To get the cuurent value 

``` c 
u32 MSYSTICK_u32GetCurrentValue();
```

### To get the reload value 

``` c 
MSYSTICK_u32GetCurrentReloadValue();
```

### To disable the timer 

``` c
MSYSTICK_vDisableTimer();
```

### To perform a delay which blocks the execution 

``` c 
MSYSTICK_vSetDelayMS(u32 A_u32Delay);
```

- A_u32Delay: The delay duration in milliseconds.


### To Set a Repeating Timer To perform an action at regular intervals

``` c
MSYSTICK_vSetIntervalMulti( u32 A_u32Interval , void (*A_pvCallBack)(void));
 ```

- A_u32Interval: The interval duration in milliseconds.
- A_pvCallBack: Pointer to the callback function to be executed at each interval.


### To Set a Single-Execution Timer To perform an action once after a delay

``` c
MSYSTICK_vSetIntervalSingle(u32 A_u32Interval, void (*A_pvCallBack)(void));
```

### Get the flag value 

``` c
u8 MSYSTICK_u8GetFlag();
```

