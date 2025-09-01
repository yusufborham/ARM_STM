# MCAL Interface Guide for STM32F4

This guide provides documentation for the Microcontroller Abstraction Layer (MCAL) drivers, including RCC, GPIO, SysTick, EXTI, NVIC, and SYSCFG.

## RCC - Functions

The Reset and Clock Control (RCC) driver is responsible for configuring system clocks, enabling/disabling peripheral clocks, and setting bus prescalers.

### `MRCC_vInit`

Initializes the RCC with the default clock settings configured in `RCC_cfg.h`. This typically involves configuring HSI/HSE, the PLL, and selecting the system clock source.

```c
void MRCC_vInit(void);
```

**Configuration in `RCC_cfg.h`:**

  * To choose the system clock source, modify the `RCC_SYS_CLK` definition:
    ```c
    #define RCC_SYS_CLK   HSE_CLK // Options: HSE_CLK, HSI_CLK, PLL_CLK
    ```
  * To specify the external clock source type (crystal/oscillator or external clock):
    ```c
    #define HSE_BYPASS    MECHANICAL_CLK // Options: RC_CLK, MECHANICAL_CLK
    ```

### `MRCC_vEnableClk`

Enables the clock for a specific peripheral.

```c
void MRCC_vEnableClk(u8 A_u8BusID, u8 A_u8PeripheralID);
```

  * **`A_u8BusID`**: The bus the peripheral is connected to.
      * `RCC_AHB1`
      * `RCC_AHB2`
      * `RCC_APB1`
      * `RCC_APB2`
  * **`A_u8PeripheralID`**: The ID of the peripheral to enable (defined in `RCC_prv.h`). Examples include: `GPIOAEN`, `GPIOBEN`, `TIM2EN`, `SPI1EN`, `USART1EN`, `SYSCFGEN`, etc.

### `MRCC_vDisableClk`

Disables the clock for a specific peripheral to save power.

```c
void MRCC_vDisableClk(u8 A_u8BusID, u8 A_u8PeripheralID);
```

  * **`A_u8BusID`**: The bus the peripheral is connected to.
      * `RCC_AHB1`
      * `RCC_AHB2`
      * `RCC_APB1`
      * `RCC_APB2`
  * **`A_u8PeripheralID`**: The ID of the peripheral to disable.

### `MRCC_vSetAPB1Prescaler`

Configures the clock prescaler for the APB1 bus.

```c
void MRCC_vSetAPB1Prescaler(u8 A_u8Prescaler);
```

  * **`A_u8Prescaler`**: The division factor for the HCLK.
      * `APB1_PRESCALER_DIVIDE_1`
      * `APB1_PRESCALER_DIVIDE_2`
      * `APB1_PRESCALER_DIVIDE_4`
      * `APB1_PRESCALER_DIVIDE_8`
      * `APB1_PRESCALER_DIVIDE_16`

### `MRCC_vSetAPB2Prescaler`

Configures the clock prescaler for the APB2 bus.

```c
void MRCC_vSetAPB2Prescaler(u8 A_u8Prescaler);
```

  * **`A_u8Prescaler`**: The division factor for the HCLK.
      * `APB2_PRESCALER_DIVIDE_1`
      * `APB2_PRESCALER_DIVIDE_2`
      * `APB2_PRESCALER_DIVIDE_4`
      * `APB2_PRESCALER_DIVIDE_8`
      * `APB2_PRESCALER_DIVIDE_16`

### `MRCC_vSetAHBPrescaler`

Configures the clock prescaler for the AHB bus.

```c
void MRCC_vSetAHBPrescaler(u8 A_u8Prescaler);
```

  * **`A_u8Prescaler`**: The division factor for the SYSCLK.
      * `AHB_PRESCALER_DIVIDE_1`
      * `AHB_PRESCALER_DIVIDE_2`
      * `AHB_PRESCALER_DIVIDE_4`
      * `AHB_PRESCALER_DIVIDE_8`
      * `AHB_PRESCALER_DIVIDE_16`
      * `AHB_PRESCALER_DIVIDE_64`
      * `AHB_PRESCALER_DIVIDE_128`
      * `AHB_PRESCALER_DIVIDE_256`
      * `AHB_PRESCALER_DIVIDE_512`

### `MRCC_vOutputClockOnHardwarePin`

Configures the MCO1 pin to output a selected system clock for debugging or external use.

```c
void MRCC_vOutputClockOnHardwarePin(u8 A_u8MCO1_PRESCALER, u8 A_u8MCO1_SOURCE);
```

  * **`A_u8MCO1_PRESCALER`**: The division factor for the selected clock source.
      * `MCO1_PRESCALER_DIVIDE_1`
      * `MCO1_PRESCALER_DIVIDE_2`
      * `MCO1_PRESCALER_DIVIDE_4`
      * `MCO1_PRESCALER_DIVIDE_8`
      * `MCO1_PRESCALER_DIVIDE_16`
  * **`A_u8MCO1_SOURCE`**: The clock source to output.
      * `MCO1_SOURCE_HSI`
      * `MCO1_SOURCE_LSE`
      * `MCO1_SOURCE_HSE`
      * `MCO1_SOURCE_PLL`

## GPIO - Functions

The General Purpose Input/Output (GPIO) driver provides an abstraction layer for configuring and controlling GPIO pins.

### `MGPIO_vPinInit`

Initializes a single GPIO pin with a comprehensive set of configurations using a structure.

```c
// Define a configuration structure
GPIOx_PinConfig_t pinLed = { 
    .Port = GPIO_A, 
    .Pin = GPIO_PIN_5, 
    .Mode = GPIO_MODE_OUTPUT, 
    .OutputType = GPIO_OTYPE_PP, 
    .PullType = GPIO_PUPD_NONE, 
    .Speed = GPIO_SPEED_LOW,
    .AltFunc = GPIO_AF0 // Not applicable for Input/Output mode
};

// Pass the structure address to the initialization function
MGPIO_vPinInit(&pinLed);
```

  * **`A_xPinCfg`**: A pointer to a `GPIOx_PinConfig_t` structure with the following fields:
      * **`.Port`**: `GPIO_A`, `GPIO_B`, `GPIO_C`, `GPIO_D`
      * **`.Pin`**: `GPIO_PIN_0` through `GPIO_PIN_15`
      * **`.Mode`**: `GPIO_MODE_INPUT`, `GPIO_MODE_OUTPUT`, `GPIO_MODE_ALTERNATE`, `GPIO_MODE_ANALOG`
      * **`.OutputType`**: `GPIO_OTYPE_PP` (Push-pull), `GPIO_OTYPE_OD` (Open-drain)
      * **`.PullType`**: `GPIO_PUPD_NONE`, `GPIO_PUPD_PULL_UP`, `GPIO_PUPD_PULL_DOWN`
      * **`.Speed`**: `GPIO_SPEED_LOW`, `GPIO_SPEED_MEDIUM`, `GPIO_SPEED_HIGH`, `GPIO_SPEED_VERY_HIGH`
      * **`.AltFunc`**: `GPIO_AF0` through `GPIO_AF15` (used when `.Mode` is `GPIO_MODE_ALTERNATE`)

### `MGPIO_vSetPinValue`

Sets the logical state of an output pin to high or low.

```c
void MGPIO_vSetPinValue(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8Value);
```

  * **`A_u8PortID`**: The port ID (e.g., `GPIO_A`).
  * **`A_u8PinID`**: The pin number (e.g., `GPIO_PIN_5`).
  * **`A_u8Value`**: The desired logical level.
      * `GPIO_PIN_HIGH`
      * `GPIO_PIN_LOW`

### `MGPIO_u8GetPinValue`

Reads the logical state of an input pin.

```c
u8 MGPIO_u8GetPinValue(u8 A_u8PortID, u8 A_u8PinID);
```

  * **`A_u8PortID`**: The port ID (e.g., `GPIO_A`).
  * **`A_u8PinID`**: The pin number (e.g., `GPIO_PIN_0`).
  * **Returns**: `GPIO_PIN_HIGH` (1) or `GPIO_PIN_LOW` (0).

### `MGPIO_vTogglePinValue`

Toggles the logical state of an output pin (HIGH to LOW or LOW to HIGH).

```c
void MGPIO_vTogglePinValue(u8 A_u8PortID, u8 A_u8PinID);
```

  * **`A_u8PortID`**: The port ID (e.g., `GPIO_A`).
  * **`A_u8PinID`**: The pin number (e.g., `GPIO_PIN_5`).

### Other GPIO Functions

The following functions provide direct control over pin configuration aspects, which are also handled by `MGPIO_vPinInit`.

  * **`MGPIO_vSetPinMode(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8Mode)`**: Sets the mode (Input, Output, etc.).
  * **`MGPIO_vSetPinOutputType(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8OutputType)`**: Sets the output type (Push-pull, Open-drain).
  * **`MGPIO_vSetPinSpeed(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8Speed)`**: Sets the pin speed.
  * **`MGPIO_vSetPinPullUpDown(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8PullUpDown)`**: Configures pull-up/pull-down resistors.
  * **`MGPIO_vSetPinAlternateFunction(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8AlternateFunction)`**: Sets the alternate function number for a pin.

The following functions provide control over an entire port or a byte within a port.

  * **`MGPIO_vSetAllPort(u8 A_u8PortID, u16 A_u16Value)`**: Sets the output value of all 16 pins of a port at once.
  * **`MGPIO_vSetLeastByteInPort(u8 A_u8PortID, u8 A_u8Value)`**: Sets the value of the lower 8 pins (0-7) of a port.
  * **`MGPIO_vSetMostByteInPort(u8 A_u8PortID, u8 A_u8Value)`**: Sets the value of the higher 8 pins (8-15) of a port.

## SYSTICK - Functions

The SysTick driver provides a simple 24-bit down-counting timer for creating time bases, delays, and periodic interrupts.

### `MSYSTICK_vChooseClockSource`

Selects the clock source for the SysTick timer.

```c
void MSYSTICK_vChooseClockSource(u8 A_u8ClockSource);
```

  * **`A_u8ClockSource`**: The desired clock source.
      * `SYSTICK_CLK_SOURCE_AHB_DIV_8`
      * `SYSTICK_CLK_SOURCE_AHB_DIV_1`

### `MSYSTICK_vStartTimer`

Starts the SysTick timer with a specific reload value.

```c
void MSYSTICK_vStartTimer(u32 A_u32ReloadValue);
```

  * **`A_u32ReloadValue`**: The value to load into the timer (max `0x00FFFFFF`). The timer will count down from this value.

### `MSYSTICK_vSetDelayMS`

Creates a blocking delay for a specified duration in milliseconds.

```c
void MSYSTICK_vSetDelayMS(f32 A_f32Delay);
```

  * **`A_f32Delay`**: The delay duration in milliseconds.

### `MSYSTICK_vSetIntervalSingle`

Sets the SysTick timer to trigger an interrupt once after a specified interval.

```c
void MSYSTICK_vSetIntervalSingle(u32 A_u32Interval, void (*A_pvCallBack)(void));
```

  * **`A_u32Interval`**: The interval duration in milliseconds.
  * **`A_pvCallBack`**: A pointer to the callback function to execute when the interval elapses.

### `MSYSTICK_vSetIntervalMulti`

Sets the SysTick timer to trigger interrupts periodically.

```c
void MSYSTICK_vSetIntervalMulti(u32 A_u32Interval, void (*A_pvCallBack)(void));
```

  * **`A_u32Interval`**: The interval duration in milliseconds.
  * **`A_pvCallBack`**: A pointer to the callback function to execute at each interval.

### `MSYSTICK_vSetIntervalMultiMicroseconds`

Sets the SysTick timer to trigger interrupts periodically with microsecond precision.

```c
void MSYSTICK_vSetIntervalMultiMicroseconds(u32 A_u32Interval, void (*A_pvCallBack)(void));
```

  * **`A_u32Interval`**: The interval duration in microseconds.
  * **`A_pvCallBack`**: A pointer to the callback function to execute at each interval.

### Other SysTick Functions

  * **`MSYSTICK_vEnableTimer()`**: Enables the SysTick timer counter.
  * **`MSYSTICK_vDisableTimer()`**: Stops/disables the SysTick timer.
  * **`MSYSTICK_vEnableOvfInterrupt()`**: Enables the count-to-zero interrupt.
  * **`MSYSTICK_vDisableOvfInterrupt()`**: Disables the count-to-zero interrupt.
  * **`u8 MSYSTICK_u8GetFlag()`**: Returns 1 if the timer has counted to 0 since the last read.
  * **`u32 MSYSTICK_u32GetElapsedTimeTicks()`**: Returns the number of ticks that have elapsed since the last reload.
  * **`u32 MSYSTICK_u32GetRemainingTimeTicks()`**: Returns the number of ticks remaining before the counter reaches zero.

## EXTI - Functions

The External Interrupt (EXTI) driver configures interrupts triggered by GPIO pin state changes.

### `MEXTI_vEnableExternalInterruptLine`

Enables the interrupt for a specific EXTI line (0-15).

```c
void MEXTI_vEnableExternalInterruptLine(u8 A_u8PinID);
```

  * **`A_u8PinID`**: The pin number corresponding to the EXTI line (e.g., `GPIO_PIN_0` for EXTI0).

### `MEXTI_vDisableExternalInterruptLine`

Disables the interrupt for a specific EXTI line.

```c
void MEXTI_vDisableExternalInterruptLine(u8 A_u8PinID);
```

  * **`A_u8PinID`**: The pin number corresponding to the EXTI line.

### `MEXTI_vSetTriggerCondition`

Configures the trigger condition (e.g., rising or falling edge) for an EXTI line.

```c
void MEXTI_vSetTriggerCondition(u8 A_u8PinID, u8 A_u8TriggerCondition);
```

  * **`A_u8PinID`**: The pin number corresponding to the EXTI line.
  * **`A_u8TriggerCondition`**: The event that will trigger the interrupt.
      * `RISING_EDGE_INTERRUPT_TRIGGER`
      * `FALLING_EDGE_INTERRUPT_TRIGGER`
      * `BOTH_EDGE_INTERRUPT_TRIGGER`

### `MEXTI_vSetCallBackFunction`

Registers a callback function to be executed when an EXTI interrupt occurs.

```c
void MEXTI_vSetCallBackFunction(u8 A_u8PinID, void (*A_fpHandler)(void));
```

  * **`A_u8PinID`**: The pin number corresponding to the EXTI line.
  * **`A_fpHandler`**: A pointer to the user-defined handler function.

### Other EXTI Functions

  * **`u8 MEXTI_u8GetPendingFlag(u8 A_u8PinID)`**: Checks if an interrupt is pending on a line.
  * **`void MEXTI_vClearPendingFlag(u8 A_u8PinID)`**: Clears the pending interrupt flag for a line.

## SYSCFG - Functions

The System Configuration (SYSCFG) controller is primarily used to map a GPIO port to an EXTI line.

### `MSYSCFG_vSetExternalInterruptLine`

Maps a GPIO port to a specific EXTI line. For example, you can select whether EXTI line 0 is connected to PA0, PB0, or PC0.

```c
void MSYSCFG_vSetExternalInterruptLine(u8 A_u8PortID, u8 A_u8PinID);
```

  * **`A_u8PortID`**: The port to connect to the EXTI line (e.g., `GPIO_A`, `GPIO_B`).
  * **`A_u8PinID`**: The pin number (0-15) which determines the EXTI line.

## NVIC - Functions

The Nested Vectored Interrupt Controller (NVIC) manages all hardware interrupts, including enabling/disabling them and setting their priorities.

### `MNVIC_vEnableInterrupt`

Enables a specific peripheral or external interrupt.

```c
void MNVIC_vEnableInterrupt(u8 A_u8InterruptID);
```

  * **`A_u8InterruptID`**: The ID of the interrupt to enable. See the `Interrupt_ID_t` enum for all options (e.g., `EXTI0_IRQn`, `TIM2_IRQn`, `USART1_IRQn`).

### `MNVIC_vDisableInterrupt`

Disables a specific interrupt.

```c
void MNVIC_vDisableInterrupt(u8 A_u8InterruptID);
```

  * **`A_u8InterruptID`**: The ID of the interrupt to disable (from `Interrupt_ID_t`).

### `MNVIC_vConfigGroupPriority`

Configures the global priority grouping scheme, which defines how the 4 priority bits are split between group priority (preemption) and sub-priority.

```c
void MNVIC_vConfigGroupPriority(NVIC_PriorityGroup_t A_u8GroupPriority);
```

  * **`A_u8GroupPriority`**: The desired grouping scheme.
      * `NVIC_PriorityGroup16_SubGroup0` (4 bits for group, 0 for sub)
      * `NVIC_PriorityGroup8_SubGroup2` (3 bits for group, 1 for sub)
      * `NVIC_PriorityGroup4_SubGroup4` (2 bits for group, 2 for sub)
      * `NVIC_PriorityGroup2_SubGroup8` (1 bit for group, 3 for sub)
      * `NVIC_PriorityGroup0_SubGroup16` (0 bits for group, 4 for sub)

### `MNVIC_vSetPriority`

Sets the group and sub-priority for a specific interrupt.

```c
void MNVIC_vSetPriority(u8 A_u8InterruptID, u8 A_u8GroupPriority, u8 A_u8SubGroupPriority);
```

  * **`A_u8InterruptID`**: The ID of the interrupt.
  * **`A_u8GroupPriority`**: The group priority value (determines preemption).
  * **`A_u8SubGroupPriority`**: The sub-priority value (determines order among same-priority interrupts).

### Other NVIC Functions

  * **`void MNVIC_vSetPendingFlag(u8 A_u8InterruptID)`**: Manually sets the pending flag for an interrupt (for software-triggered interrupts).
  * **`void MNVIC_vClearPendingFlag(u8 A_u8InterruptID)`**: Clears the pending flag for an interrupt.
  * **`u8 MNVIC_u8GetActiveFlag(u8 A_u8InterruptID)`**: Returns 1 if the specified interrupt is currently being serviced.