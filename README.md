# API Documentation

## MCAL Interface Guide for STM32F4

This guide provides documentation for the Microcontroller Abstraction Layer (MCAL) drivers, including RCC, GPIO, SysTick, EXTI, NVIC, and SYSCFG.

### RCC - Functions

The Reset and Clock Control (RCC) driver is responsible for configuring system clocks, enabling/disabling peripheral clocks, and setting bus prescalers.

#### `MRCC_vInit`

```c
void MRCC_vInit(void);
```

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

#### `MRCC_vEnableClk`

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

#### `MRCC_vDisableClk`

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

#### `MRCC_vSetAPB1Prescaler`

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

#### `MRCC_vSetAPB2Prescaler`

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

#### `MRCC_vSetAHBPrescaler`

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

#### `MRCC_vOutputClockOnHardwarePin`

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

### GPIO - Functions

The General Purpose Input/Output (GPIO) driver provides an abstraction layer for configuring and controlling GPIO pins.

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

#### `MGPIO_vSetPinValue`

Sets the logical state of an output pin to high or low.

```c
void MGPIO_vSetPinValue(u8 A_u8PortID, u8 A_u8PinID, u8 A_u8Value);
```

* **`A_u8PortID`**: The port ID (e.g., `GPIO_A`).
* **`A_u8PinID`**: The pin number (e.g., `GPIO_PIN_5`).
* **`A_u8Value`**: The desired logical level.
  * `GPIO_PIN_HIGH`
  * `GPIO_PIN_LOW`

##### `MGPIO_u8GetPinValue`

Reads the logical state of an input pin.

```c
u8 MGPIO_u8GetPinValue(u8 A_u8PortID, u8 A_u8PinID);
```

* **`A_u8PortID`**: The port ID (e.g., `GPIO_A`).
* **`A_u8PinID`**: The pin number (e.g., `GPIO_PIN_0`).
* **Returns**: `GPIO_PIN_HIGH` (1) or `GPIO_PIN_LOW` (0).

#### `MGPIO_vTogglePinValue`

Toggles the logical state of an output pin (HIGH to LOW or LOW to HIGH).

```c
void MGPIO_vTogglePinValue(u8 A_u8PortID, u8 A_u8PinID);
```

* **`A_u8PortID`**: The port ID (e.g., `GPIO_A`).
* **`A_u8PinID`**: The pin number (e.g., `GPIO_PIN_5`).

#### Other GPIO Functions

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

### SYSTICK - Functions

The SysTick driver provides a simple 24-bit down-counting timer for creating time bases, delays, and periodic interrupts.

#### `MSYSTICK_vChooseClockSource`

Selects the clock source for the SysTick timer.

```c
void MSYSTICK_vChooseClockSource(u8 A_u8ClockSource);
```

* **`A_u8ClockSource`**: The desired clock source.
  * `SYSTICK_CLK_SOURCE_AHB_DIV_8`
  * `SYSTICK_CLK_SOURCE_AHB_DIV_1`

#### `MSYSTICK_vStartTimer`

Starts the SysTick timer with a specific reload value.

```c
void MSYSTICK_vStartTimer(u32 A_u32ReloadValue);
```

* **`A_u32ReloadValue`**: The value to load into the timer (max `0x00FFFFFF`). The timer will count down from this value.

#### `MSYSTICK_vSetDelayMS`

Creates a blocking delay for a specified duration in milliseconds.

```c
void MSYSTICK_vSetDelayMS(f32 A_f32Delay);
```

* **`A_f32Delay`**: The delay duration in milliseconds.

#### `MSYSTICK_vSetIntervalSingle`

Sets the SysTick timer to trigger an interrupt once after a specified interval.

```c
void MSYSTICK_vSetIntervalSingle(u32 A_u32Interval, void (*A_pvCallBack)(void));
```

* **`A_u32Interval`**: The interval duration in milliseconds.
* **`A_pvCallBack`**: A pointer to the callback function to execute when the interval elapses.

#### `MSYSTICK_vSetIntervalMulti`

Sets the SysTick timer to trigger interrupts periodically.

```c
void MSYSTICK_vSetIntervalMulti(u32 A_u32Interval, void (*A_pvCallBack)(void));
```

* **`A_u32Interval`**: The interval duration in milliseconds.
* **`A_pvCallBack`**: A pointer to the callback function to execute at each interval.

#### `MSYSTICK_vSetIntervalMultiMicroseconds`

Sets the SysTick timer to trigger interrupts periodically with microsecond precision.

```c
void MSYSTICK_vSetIntervalMultiMicroseconds(u32 A_u32Interval, void (*A_pvCallBack)(void));
```

* **`A_u32Interval`**: The interval duration in microseconds.
* **`A_pvCallBack`**: A pointer to the callback function to execute at each interval.

#### `MSYSTICK_millis`

Returns the number of milliseconds that have elapsed since the SysTick timer was enabled.

```c  
u32 MSYSTICK_millis();

```

#### `MSYSTICK_vEnableBackgroundMillis`

```c
void MSYSTICK_vEnableBackgroundMillis();
```

Enables a background millisecond counter using SysTick. This allows `MSYSTICK_millis()` to return the elapsed time since enabled.

#### Other SysTick Functions

* **`MSYSTICK_vEnableTimer()`**: Enables the SysTick timer counter.
* **`MSYSTICK_vDisableTimer()`**: Stops/disables the SysTick timer.
* **`MSYSTICK_vEnableOvfInterrupt()`**: Enables the count-to-zero interrupt.
* **`MSYSTICK_vDisableOvfInterrupt()`**: Disables the count-to-zero interrupt.
* **`u8 MSYSTICK_u8GetFlag()`**: Returns 1 if the timer has counted to 0 since the last read.
* **`u32 MSYSTICK_u32GetElapsedTimeTicks()`**: Returns the number of ticks that have elapsed since the last reload.
* **`u32 MSYSTICK_u32GetRemainingTimeTicks()`**: Returns the number of ticks remaining before the counter reaches zero.

### EXTI - Functions

The External Interrupt (EXTI) driver configures interrupts triggered by GPIO pin state changes.

#### `MEXTI_vEnableExternalInterruptLine`

Enables the interrupt for a specific EXTI line (0-15).

```c
void MEXTI_vEnableExternalInterruptLine(u8 A_u8PinID);
```

* **`A_u8PinID`**: The pin number corresponding to the EXTI line (e.g., `GPIO_PIN_0` for EXTI0).

#### `MEXTI_vDisableExternalInterruptLine`

Disables the interrupt for a specific EXTI line.

```c
void MEXTI_vDisableExternalInterruptLine(u8 A_u8PinID);
```

* **`A_u8PinID`**: The pin number corresponding to the EXTI line.

#### `MEXTI_vSetTriggerCondition`

Configures the trigger condition (e.g., rising or falling edge) for an EXTI line.

```c
void MEXTI_vSetTriggerCondition(u8 A_u8PinID, u8 A_u8TriggerCondition);
```

* **`A_u8PinID`**: The pin number corresponding to the EXTI line.
* **`A_u8TriggerCondition`**: The event that will trigger the interrupt.
  * `RISING_EDGE_INTERRUPT_TRIGGER`
  * `FALLING_EDGE_INTERRUPT_TRIGGER`
  * `BOTH_EDGE_INTERRUPT_TRIGGER`

#### `MEXTI_vSetCallBackFunction`

Registers a callback function to be executed when an EXTI interrupt occurs.

```c
void MEXTI_vSetCallBackFunction(u8 A_u8PinID, void (*A_fpHandler)(void));
```

* **`A_u8PinID`**: The pin number corresponding to the EXTI line.
* **`A_fpHandler`**: A pointer to the user-defined handler function.

#### Other EXTI Functions

* **`u8 MEXTI_u8GetPendingFlag(u8 A_u8PinID)`**: Checks if an interrupt is pending on a line.
* **`void MEXTI_vClearPendingFlag(u8 A_u8PinID)`**: Clears the pending interrupt flag for a line.

### SYSCFG - Functions

The System Configuration (SYSCFG) controller is primarily used to map a GPIO port to an EXTI line.

#### `MSYSCFG_vSetExternalInterruptLine`

Maps a GPIO port to a specific EXTI line. For example, you can select whether EXTI line 0 is connected to PA0, PB0, or PC0.

```c
void MSYSCFG_vSetExternalInterruptLine(u8 A_u8PortID, u8 A_u8PinID);
```

* **`A_u8PortID`**: The port to connect to the EXTI line (e.g., `GPIO_A`, `GPIO_B`).
* **`A_u8PinID`**: The pin number (0-15) which determines the EXTI line.

### NVIC - Functions

The Nested Vectored Interrupt Controller (NVIC) manages all hardware interrupts, including enabling/disabling them and setting their priorities.

#### `MNVIC_vEnableInterrupt`

Enables a specific peripheral or external interrupt.

```c
void MNVIC_vEnableInterrupt(u8 A_u8InterruptID);
```

* **`A_u8InterruptID`**: The ID of the interrupt to enable. See the `Interrupt_ID_t` enum for all options (e.g., `EXTI0_IRQn`, `TIM2_IRQn`, `USART1_IRQn`).

#### `MNVIC_vDisableInterrupt`

Disables a specific interrupt.

```c
void MNVIC_vDisableInterrupt(u8 A_u8InterruptID);
```

* **`A_u8InterruptID`**: The ID of the interrupt to disable (from `Interrupt_ID_t`).

#### `MNVIC_vConfigGroupPriority`

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

#### `MNVIC_vSetPriority`

Sets the group and sub-priority for a specific interrupt.

```c
void MNVIC_vSetPriority(u8 A_u8InterruptID, u8 A_u8GroupPriority, u8 A_u8SubGroupPriority);
```

* **`A_u8InterruptID`**: The ID of the interrupt.
* **`A_u8GroupPriority`**: The group priority value (determines preemption).
* **`A_u8SubGroupPriority`**: The sub-priority value (determines order among same-priority interrupts).

#### Other NVIC Functions

* **`void MNVIC_vSetPendingFlag(u8 A_u8InterruptID)`**: Manually sets the pending flag for an interrupt (for software-triggered interrupts).
* **`void MNVIC_vClearPendingFlag(u8 A_u8InterruptID)`**: Clears the pending flag for an interrupt.
* **`u8 MNVIC_u8GetActiveFlag(u8 A_u8InterruptID)`**: Returns 1 if the specified interrupt is currently being serviced.

---

### USART - Functions

The Universal Synchronous/Asynchronous Receiver/Transmitter (USART) driver provides APIs to configure and use USART peripherals for serial communication. It supports multiple baud rates, word lengths, stop bits, parity modes, and operational modes (TX, RX, TX/RX).

---

#### `MUSART_Init`

Initializes the USART peripheral with the specified configuration.

```c
USART_Status_t MUSART_Init(USART_Config_t* cfg);
```

* **`cfg`**: Pointer to a `USART_Config_t` structure containing:

  * Clock source (`USART_CLK_8MHZ`, `USART_CLK_16MHZ`, …)
  * Peripheral (`USART_PERIPH_1`, `USART_PERIPH_2`, `USART_PERIPH_6`)
  * Baud rate (`USART_BAUDRATE_9600`, `USART_BAUDRATE_115200`, etc.)
  * Word length (8 or 9 bits)
  * Stop bits (0.5, 1, 1.5, 2)
  * Parity (`NONE`, `EVEN`, `ODD`)
  * Oversampling (8 or 16)
  * Sampling method (1-bit or 3-bit majority)
  * Mode (TX only, RX only, TX/RX)

**Returns:**

* `USART_OK` if initialized successfully.
* Error codes: `USART_ERR_NULLCFG`, `USART_ERR_BAD_PERIPH`, `USART_ERR_TIMEOUT`.

**Notes:**

* GPIO pins for TX/RX must be configured before calling.
* NVIC interrupts must be enabled separately if used.

---

#### `MUSART_u8ReadByte`

Reads a single byte from the USART receive buffer.

```c
u8 MUSART_u8ReadByte(USART_Peripheral_t A_thisID);
```

* **`A_thisID`**: USART peripheral (`USART_PERIPH_1`, `USART_PERIPH_2`, `USART_PERIPH_6`).

**Returns:**

* The received byte, or `0` if no data is available.

---

#### `MUSART_u8BytesAvailable`

Checks how many bytes are available in the receive buffer.

```c
u8 MUSART_u8BytesAvailable(USART_Peripheral_t A_thisID);
```

* **`A_thisID`**: USART peripheral.

**Returns:**

* Number of bytes currently available in the RX buffer.

---

#### `MUSART_u8WriteByte`

Writes a single byte to the transmit buffer.

```c
USART_Status_t MUSART_u8WriteByte(USART_Peripheral_t A_thisID, u8 A_u8ByteToPush);
```

* **`A_thisID`**: USART peripheral.
* **`A_u8ByteToPush`**: The byte to transmit.

**Returns:**

* `USART_OK` on success.
* Error code if the TX buffer is full.

---

#### `MUSART_u8WriteString`

Writes a null-terminated string to the transmit buffer.

```c
USART_Status_t MUSART_u8WriteString(USART_Peripheral_t A_thisID, const u8* A_u8StringToPush);
```

* **`A_thisID`**: USART peripheral.
* **`A_u8StringToPush`**: Pointer to the null-terminated string.

**Returns:**

* `USART_OK` on success.
* Error code if buffer overflows.

---

#### `MUSART_u8ReadStringUntil`

Reads characters until a terminating character or buffer limit is reached.

```c
USART_Status_t MUSART_u8ReadStringUntil(USART_Peripheral_t A_thisID, 
                                        u8 *A_u8pStringBuffer,
                                        u32 A_u32BufferSize,
                                        u8 A_u8TerminatingChar);
```

* **`A_thisID`**: USART peripheral.
* **`A_u8pStringBuffer`**: Pointer to buffer to store the string.
* **`A_u32BufferSize`**: Size of the buffer.
* **`A_u8TerminatingChar`**: Character indicating end of string.

**Returns:**

* `USART_OK` if successful.
* `USART_STRING_BUFFER_OVF` if buffer overflows.

**Notes:**

* The string is null-terminated.

---

#### `MUSART_vFlush`

Flushes both transmit and receive buffers.

```c
USART_Status_t MUSART_vFlush(USART_Peripheral_t A_thisID);
```

* **`A_thisID`**: USART peripheral.

**Returns:**

* `USART_OK` on success.

---

#### `MUSART_u32ParseIntBlocking`

Parses an integer from incoming data with a timeout.

```c
USART_Status_t MUSART_u32ParseIntBlocking(USART_Peripheral_t A_thisID, 
                                          s32* A_ps32Result,  
                                          u32 timeout_ms);
```

* **`A_thisID`**: USART peripheral.
* **`A_ps32Result`**: Pointer to store parsed integer.
* **`timeout_ms`**: Timeout in milliseconds.

**Returns:**

* `USART_OK` if successful.
* `USART_ERR_TIMEOUT` if timeout occurred.

---

#### `MUSART_u8ParseInt`

Non-blocking integer parser for incoming data.

```c
USART_ParsingStatus_t MUSART_u8ParseInt(USART_Peripheral_t A_thisID, s32* A_ps32Result);
```

* **`A_thisID`**: USART peripheral.
* **`A_ps32Result`**: Pointer to store parsed integer.

**Returns (Parsing status):**

* `STILL_PARSING`
* `DONE_PARSING`
* `INVALID_ARGUMENT`
* `TIMEOUT_OCCURRED`

#### `MUSART_u8ReadStringUntilBufferPatern`

Reads a string from the USART receive buffer until a specified terminating pattern is encountered or the buffer limit is reached.

**Notes**:

* The function reads characters from the receive buffer and stores them in A_u8pStringBuffer until the terminating pattern is encountered or the buffer limit (STRING_BUFFER_MAX_SIZE) is reached. The resulting string in A_u8pStringBuffer is null-terminated. If the buffer limit is reached before encountering the terminating pattern, it returns USART_STRING_BUFFER_OVF. Ensure that A_u8pStringBuffer has enough space to hold the incoming string and the null terminator.

* The function is non-blocking Synchronous function and can be called repeatedly to continue parsing until the terminating pattern is found in order to use the input buffer you must be sure that the function returned  `DONE_PARSING` if not then you cant use the buffer as it is still being filled.

for example

``` c
if (MUSART_u8ReadStringUntilBufferPatern(USART_PERIPH_1 , buffer , 50 , buffer2) == DONE_PARSING) {
   MUSART_u8WriteString(USART_PERIPH_1 , buffer);
   if (buffer[0] == 'o' && buffer[1] == 'n') {
    MGPIO_vSetPinValue(GPIO_A , GPIO_PIN_0 , GPIO_PIN_HIGH); 
   }
   else if (buffer[0] == 'o' && buffer[1] == 'f' && buffer[2] == 'f') {
    MGPIO_vSetPinValue(GPIO_A , GPIO_PIN_0 , GPIO_PIN_LOW);
   }
   else {
    // Ignore unknown commands
   }
}
```

``` c
USART_Status_t MUSART_u8ReadStringUntilBufferPatern(USART_Peripheral_t A_thisID, u8 *A_u8pStringBuffer, u32 A_u32BufferSize ,const u8 *A_u8pTerminatingBuffer);
```

* **`A_thisID`**: USART peripheral.
* **`A_u8pStringBuffer`**: Pointer to buffer to store the string
* **`A_u32BufferSize`**: Size of the buffer.
* **`A_u8pTerminatingBuffer`**: Pointer to the terminating string pattern
**Returns:**
* `DONE_PARSING` if successful.
* `USART_STRING_BUFFER_OVF` if buffer overflows.
* `STILL_PARSING` if the terminating pattern is not yet found.
* `INVALID_ARGUMENT` if the provided arguments are invalid.
* `TIMEOUT_OCCURRED` if a timeout occurs during parsing.
* `INVALID_BUFFER_SIZE` if the provided buffer size is invalid.
* `USART_ERR_BAD_PERIPH` if the specified peripheral is invalid.

---

#### Configuration Example

```c
// USART_cfg.h

#ifndef USART_CFG_H
#define USART_CFG_H

// Baudrate configuration
#define USART_BAUDRATE 9600

// Word length configuration
#define USART_WORD_LENGTH 8

// Stop bits configuration
#define USART_STOP_BITS 1

// Parity configuration
#define USART_PARITY NONE

#endif // USART_CFG_H
```

### SPI - Functions

The Serial Peripheral Interface (SPI) driver provides APIs to configure and use SPI peripherals for synchronous serial communication. It supports multiple modes, baud rates, data frame formats, and operational modes (full-duplex, half-duplex, simplex).

#### SPI - Struct Configuration

```c
typedef struct {
    SPI_Peripheral_t myPeripheral;
    SPI_Mode_t mySPIMode;
    u32 myBaudRate;
    SPI_OperationMode_t myOperationMode;
    SPI_DataShift_t dataShift;
    SPI_DataFrameLength_t dataFrameLn;
    SPI_ClockPhasePolarity_t ClockPhasePol;
    SPI_NSSMode_t NSSMode;
    SPI_FrameFormat_t myformat;
} SPI_Config_t;
```

* myPeripheral: Specifies the SPI peripheral to be used (SPI_PERIPH_1, SPI_PERIPH_2, etc.).
* mySPIMode: Specifies the SPI mode (MASTER or SLAVE).
* myBaudRate: Specifies the baud rate for the SPI clock.
  * The baud rate is determined by dividing the peripheral clock by a factor (e.g., CLK_DIV_2, CLK_DIV_4, etc.).
* myOperationMode: Specifies the operation mode (FULL_DUPLEX, HALF_DUPLEX, SIMPLEX_TRANSMIT, SIMPLEX_RECIEVE).
* dataShift: Specifies the data shift order (LSB_FIRST or MSB_FIRST).
* dataFrameLn: Specifies the data frame length (DATA_FRAME_8BIT or DATA_FRAME
_16BIT).
* ClockPhasePol: Specifies the clock phase and polarity (CLK_PHA_POL_MODE_0, CLK_PHA_POL_MODE_1, etc.).
* NSSMode: Specifies the NSS (Slave Select) mode (NSS_SW, NSS_OE, NSS_OD).
* myformat: Specifies the frame format (MOTOROLA_FORMAT or TI_FORMAT).

#### `MSPI_vInit`

Initializes the SPI peripheral with the specified configuration.

```c
void MSPI_vInit(SPI_Config_t* cfg);
```

* **`cfg`**: Pointer to a `SPI_Config_t` structure containing the configuration parameters.
**Returns:**
* `SPI_OK` if initialized successfully.
* Error codes: `SPI_ERR_NULLCFG`, `SPI_ERR_BAD_PERIPH`.
**Notes:**
* GPIO pins for SPI (SCK, MISO, MOSI, NSS) must be configured before calling.

#### `MSPI_vSendData`

```c
SPI_status MSPI_vSendData(SPI_peripheralID_t peripheral , u16 A_u16Data);
```

* **`peripheral`**: The SPI peripheral ID to use for sending data (SPI_PERIPH_1, SPI_PERIPH_2, etc.).
* **`A_u16Data`**: The data to be sent (8-bit or 16-bit based on configuration).
**Returns:**
* `SPI_OK` if data is sent successfully.
* Error codes: `SPI_ERR_NULLDATA`, `SPI_ERR_BAD_PERIPH`.
**Notes:**
* Ensure the SPI peripheral is initialized before calling this function.

#### `MSPI_u16RecieveData`

```c
SPI_status MSPI_u16RecieveData(SPI_peripheralID_t peripheral , u16* A_u16Data); // Not fully implemented
```

* **`peripheral`**: The SPI peripheral ID to use for receiving data (SPI_PERIPH_1, SPI_PERIPH_2, etc.).
* **`A_u16Data`**: Pointer to the variable where the received data will be stored (8-bit or 16-bit based on configuration).
**Returns:**
* `SPI_OK` if data is received successfully.
* Error codes: `SPI_ERR_NULLDATA`, `SPI_ERR_BAD_PERIPH`.
**Notes:**
* Ensure the SPI peripheral is initialized before calling this function.
**Example Usage:**

```c
u16 receivedData;
SPI_status status = MSPI_u16RecieveData(SPI_PERIPH_1, &receivedData);
if (status == SPI_OK) {
    // Data received successfully
} else {
    // Handle error
}
```

## HAL Interface Guide for STM32F4

This guide provides documentation for the Hardware Abstraction Layer (HAL) drivers, TFT , DAC , LedMatrix , S2P , NEC , Seven Segment ESP8266 , MPU6050 .

### TFT - Functions

void HTFT_vInit(HTFT_cfg_t*cfg);
void HTFT_vSet_Xposition(u8 X_start , u8 X_end );
void HTFT_vSet_Yposition(u8 Y_start , u8 Y_end );
void HTFT_vDrawImage(const tImage* image, u8 x, u8 y);
void HTFT_vDrawRect(u8 x, u8 y, u8 width, u8 height, u16 color);
void HTFT_vFillBackground(u16 color);
void HTFT_vDrawAsciiChar(u8 x_start, u8 y_start , u8 character, u16 color, u16 bgColor) ;
void HTFT_vWriteString(u8 x_start, u8 y_start , u8* str ,u16 color, u16 bgColor );

#### `HTFT_vInit`

Initializes the TFT display with the specified configuration.

```c
void HTFT_vInit(HTFT_cfg_t* cfg);
```

* **`cfg`**: Pointer to a `HTFT_cfg_t` structure containing the configuration parameters.

* mySPI: Specifies the SPI peripheral to be used (SPI_PERIPH_1, SPI_PERIPH_2, etc.).
* myPixelFormat: Specifies the pixel format (PIXEL_FORMAT_16BIT or PIXEL_FORMAT_18BIT).
* myScreenSize: Specifies the screen size (SCREEN_SIZE_128x128, SCREEN_SIZE_128x160, SCREEN_SIZE_240x320).
* myRSTport: Specifies the GPIO port for the reset pin (e.g., GPIO_A, GPIO_B, etc.).
* myRSTpin: Specifies the GPIO pin number for the reset pin (e.g., GPIO_PIN_0, GPIO_PIN_1, etc.).
* myA0port: Specifies the GPIO port for the A0 (data/command) pin.
* myA0pin: Specifies the GPIO pin number for the A0 pin.

#### `HTFT_vSet_Xposition`

Sets the X position range for subsequent drawing operations.

```c
void HTFT_vSet_Xposition(u8 X_start , u8 X_end );
```

* **`X_start`**: The starting X position (0 to screen width - 1).
* **`X_end`**: The ending X position (0 to screen width - 1).

#### `HTFT_vSet_Yposition`

Sets the Y position range for subsequent drawing operations.

```c
void HTFT_vSet_Yposition(u8 Y_start , u8 Y_end );
```

* **`Y_start`**: The starting Y position (0 to screen height - 1).
* **`Y_end`**: The ending Y position (0 to screen height - 1).

#### `HTFT_vDrawImage`

Draws an image at the specified position on the TFT display.

```c  
void HTFT_vDrawImage(const tImage* image, u8 x, u8 y);
```

* **`image`**: Pointer to a `tImage` structure containing the image data.
* **`x`**: The X position to draw the image (0 to screen width - 1).
* **`y`**: The Y position to draw the image (0 to screen height - 1).

#### `HTFT_vDrawRect`

Draws a rectangle at the specified position with the given dimensions and color.

```c
void HTFT_vDrawRect(u8 x, u8 y, u8 width, u8 height, u16 color);
```

* **`x`**: The X position of the top-left corner of the rectangle (0 to screen width - 1).
* **`y`**: The Y position of the top-left corner of the rectangle (0 to screen height - 1).
* **`width`**: The width of the rectangle (1 to screen width - x).
* **`height`**: The height of the rectangle (1 to screen height - y).
* **`color`**: The color of the rectangle in 16-bit RGB565 format.

#### `HTFT_vFillBackground`

Fills the entire TFT display with the specified background color.

```c
void HTFT_vFillBackground(u16 color);
```

* **`color`**: The background color in 16-bit RGB565 format.

```c
void HTFT_vFillBackground(u16 color);
```

* **`color`**: The background color in 16-bit RGB565 format.

#### `HTFT_vDrawAsciiChar`

Draws a single ASCII character at the specified position with the given foreground and background colors.

```c
void HTFT_vDrawAsciiChar(u8 x_start, u8 y_start , u8 character, u16 color, u16 bgColor);
```

* **`x_start`**: The X position to draw the character (0 to screen width - 1).
* **`y_start`**: The Y position to draw the character (0 to screen height - 1).
* **`character`**: The ASCII character to draw (0x20 to 0x7E).
* **`color`**: The foreground color of the character in 16-bit RGB565 format.
* **`bgColor`**: The background color behind the character in 16-bit RGB565 format.

#### `HTFT_vWriteString`

Writes a null-terminated string at the specified position with the given foreground and background colors.

```c  
void HTFT_vWriteString(u8 x_start, u8 y_start , u8* str ,u16 color, u16 bgColor );
```

* **`x_start`**: The X position to start writing the string (0 to screen width - 1).
* **`y_start`**: The Y position to start writing the string (0 to screen height - 1).
* **`str`**: Pointer to the null-terminated string to write.
* **`color`**: The foreground color of the text in 16-bit RGB565 format.
* **`bgColor`**: The background color behind the text in 16-bit RGB565 format.

### Ultasonic - Functions

The Ultrasonic driver provides APIs to interface with ultrasonic distance sensors, allowing for distance measurement in various applications.

#### `HUltra_vInit`

Initializes the ultrasonic sensor with the specified configuration.

```c
void HUltra_vInit(Ultrasonic_cfg_t* cfg);
```

* **`cfg`**: Pointer to a `Ultrasonic_cfg_t` structure containing the configuration parameters.
  * Trig_port: Specifies the GPIO port for the trigger pin (e.g., GPIO_A, GPIO_B, etc.).
  * Trig_pin: Specifies the GPIO pin number for the trigger pin (e.g., GPIO_PIN_0, GPIO_PIN_1, etc.).
  * Echo_port: Specifies the GPIO port for the echo pin (e.g., GPIO_A, GPIO_B, etc.).
  * Echo_pin: Specifies the GPIO pin number for the echo pin (e.g., GPIO_PIN_0, GPIO_PIN_1, etc.).

#### `HUltra_u8ReadDisatnce`

Reads the distance measured by the ultrasonic sensor.

```c
Ultrasonic_measuingState_t HUltra_u8ReadDisatnce(Ultrasonic_cfg_t* cfg , f32* ptr) ;
```

* **`cfg`**: Pointer to a `Ultrasonic_cfg_t` structure containing the configuration parameters.
* **`ptr`**: Pointer to a float variable where the measured distance will be stored

* **Returns**: An `Ultrasonic_measuingState_t` enum indicating the measurement state:
  * `MEASURING`: The measurement is still in progress.
  * `FINISHED`: The measurement is complete, and the distance value is available in the variable pointed to by `ptr`.

```c
if (HUltra_u8ReadDisatnce(&myUltrasonic, &distance) == FINISHED){
            ftoa(distance , buffer ) ;
            MUSART_u8WriteString(USART_PERIPH_1 , buffer );
            const u8 cm[5] = " cm \n" ;
            MUSART_u8WriteString(USART_PERIPH_1 , cm );
}
```

### IR - Functions

The IR line-following sensor array driver provides APIs to interface with an array of infrared sensors for line detection and position calculation.

#### HIR_vInit

initializes the GPIO pins for the IR sensor array.

```c
void HIR_vInit(IR_LineFollowing_cfg_t* cfg);
```

* **`cfg`**: Pointer to a user-defined configuration structure for the sensor array.
* **Returns**: IR_Status_t
  * IR_STATUS_OK on success.
  * IR_STATUS_ERROR_NULL_PTR if cfg is NULL.

#### HIR_f32ReadSensors

Reads all sensors, calculates the line position, and provides status.

```c
IR_Status_t HIR_f32ReadSensors(IR_LineFollowing_cfg_t* cfg, f32* position_out);
```

* **`cfg`**: Pointer to the initialized configuration structure.
* **`position_out`**: Pointer to a float where the calculated line position will be stored. The range is from -2.0 (far left) to +2.0 (far right), with 0.0 being centered.

* **Returns**: IR_Status_t
  * IR_STATUS_LINE_AQUIRED if the line is detected normally.
  * IR_STATUS_LINE_LOST if no sensors detect the line.
  * IR_STATUS_INTERSECTION if all sensors detect the line.
  * IR_STATUS_ERROR_NULL_PTR if a null pointer argument is provided.

```c
f32 position;
if (HIR_f32ReadSensors(&myIRArray, &position) == IR_STATUS_LINE_AQUIRED) {
    // Use the position value for control
    ftoa(position, buffer);
    MUSART_u8WriteString(USART_PERIPH_1, buffer);
    const u8 newline[2] = "\n";
    MUSART_u8WriteString(USART_PERIPH_1, newline);
}
```

* Note : In the configuartion file you define the number of sesnors in Ultra_cfg.h

### DAC - Functions

The Digital-to-Analog Converter (DAC) driver provides APIs to configure and use a DAC peripheral for converting digital values to analog voltages.

#### `HDAC_vInit`

Initializes the DAC with the specified configuration.

```c
void HDAC_vInit(DAC_cfg_t* cfg) {
}
```

* **`cfg`**: Pointer to a `DAC_cfg_t` structure containing the configuration parameters.
  * Port: Specifies the GPIO port for the DAC pins (e.g., GPIO_A, GPIO_B, etc.).
  * Pins: An array of 8 GPIO pin numbers for the DAC output (e.g., GPIO_PIN_0, GPIO_PIN_1, etc.).

#### `HDAC_vSetValue`

Sets the DAC output value.

```c
void HDAC_vSetValue(DAC_cfg_t* cfg, u8 value) {
}
```

* **`cfg`**: Pointer to a `DAC_cfg_t` structure containing the configuration parameters.
* **`value`**: The value to set on the DAC output (0 to 255 for 8-bit resolution).

### LedMatrix - Functions

The LED Matrix driver provides APIs to control an 8x8 LED matrix display, allowing for the display of patterns, characters, and animations.

#### `HLedMatrix_vInitPins`

Initializes the GPIO pins for the LED matrix.

```c
void HLedMatrix_vInitPins(LedMatrix_config_t* LedMatrix_cfg);
```

* **`LedMatrix_cfg`**: Pointer to a `LedMatrix_config_t` structure containing the configuration parameters.
  * Mode: Specifies the operation mode (LED_MATRIX_NORMAL_MODE or LED_MATRIX_STP_MODE).
  * Config: Union containing configuration details for normal mode (GPIO ports and pins) or STP mode (shift register configuration).  

  * Example code for normal mode:
    * Port1: GPIO port for rows.
    * RowPins: Array of 8 GPIO pin numbers for the rows.
    * Port2: GPIO port for columns.
    * ColPins: Array of 8 GPIO pin numbers for the columns.

``` c
LedMatrix_config_t led_matrix_cfg = {
    .Mode = LED_MATRIX_NORMAL_MODE,
    .Config.normalConfig = {
        .Port1 = GPIO_A,
        .RowPins = {
            { .Pin = GPIO_PIN_0 },
            { .Pin = GPIO_PIN_1 },
            { .Pin = GPIO_PIN_2 },
            { .Pin = GPIO_PIN_3 },
            { .Pin = GPIO_PIN_4 },
            { .Pin = GPIO_PIN_5 },
            { .Pin = GPIO_PIN_6 },
            { .Pin = GPIO_PIN_7 }
        },
        .Port2 = GPIO_B,
        .ColPins = {
            { .Pin = GPIO_PIN_0 },
            { .Pin = GPIO_PIN_1 },
            { .Pin = GPIO_PIN_2 },
            { .Pin = GPIO_PIN_5 },
            { .Pin = GPIO_PIN_6 },  
            { .Pin = GPIO_PIN_7 },
            { .Pin = GPIO_PIN_8 },
            { .Pin = GPIO_PIN_9 }
        }
      }
};

  HLedMatrix_vInitPins(&led_matrix_cfg);
```

* Example code for STP mode:

``` c
STP_Config_t stp_config = {
    .DataPin = GPIO_PIN_0,
    .ClockPin = GPIO_PIN_1,
    .LatchPin = GPIO_PIN_2
};

LedMatrix_config_t led_matrix_cfg = {
    .Mode = LED_MATRIX_STP_MODE,
    .Config.stpConfig = stp_config
};

HLedMatrix_vInitPins(&led_matrix_cfg);
```

#### `HLedMatrix_vDisplayFrame`

Displays a specific frame on the LED matrix.

```c
void HLedMatrix_vDisplayFrame(LedMatrix_config_t* LedMatrix_cfg , u8 A_au8FrameData[8]);
```

* **`LedMatrix_cfg`**: Pointer to a `LedMatrix_config_t` structure containing the configuration parameters.
* **`A_au8FrameData`**: Array containing the frame data (8 rows).

``` c
u8 frame_data[8] = {
    0b11111111,
    0b10000001,
    0b10000001,
    0b10000001,
    0b10000001,
    0b10000001,
    0b11111111,
    0b00000000
};

HLedMatrix_vDisplayFrame(&led_matrix_cfg, frame_data);
```

#### `HLedMatrix_vDisplayFrameFor`

Displays a specific frame on the LED matrix for a given duration.

```c
void HLedMatrix_vDisplayFrameFor(u32 A_u32DurationMs , LedMatrix_config_t* LedMatrix_cfg , u8 A_au8FrameData[8]);
```

* **`A_u32DurationMs`**: Duration to display the frame (in milliseconds).
* **`LedMatrix_cfg`**: Pointer to a `LedMatrix_config_t` structure
* **`A_au8FrameData`**: Array containing the frame data (8 rows).

``` c
u8 frame_data[8] = {
    0b11111111,
    0b10000001,
    0b10000001,
    0b10000001,
    0b10000001,
    0b10000001,
    0b11111111,
    0b00000000
};

HLedMatrix_vDisplayFrameFor(1000, &led_matrix_cfg, frame_data);
```   