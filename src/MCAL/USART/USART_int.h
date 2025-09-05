#ifndef USART_INT_H
#define USART_INT_H

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Delay.h"
#include "../../LIB/MATH_Fn.h" 
#include "USART_prv.h"
#include "USART_cfg.h"

#define USART_BAUDRATE_9600     9600
#define USART_BAUDRATE_19200   19200
#define USART_BAUDRATE_115200 115200
#define USART_BAUDRATE_1M     1000000


typedef enum {
    USART_WORD_LENGTH_8BITS  = 1,
    USART_WORD_LENGTH_9BITS  = 2
}USART_WordLength_t;

typedef enum {
    USART_STOP_BITS_0_5 = 1,
    USART_STOP_BITS_1   = 2,
    USART_STOP_BITS_1_5 = 3,
    USART_STOP_BITS_2   = 4
}USART_StopBits_t;

typedef enum {
    USART_PARITY_NONE = 1,
    USART_PARITY_EVEN = 2,
    USART_PARITY_ODD  = 3
}USART_Parity_t;

typedef enum {
    USART_SAMPLE_8_TIMES    = 1,
    USART_SAMPLE_16_TIMES   = 2
}USART_SampleRate_t;

typedef enum {
    USART_SAMPLE_METHOD_ONE_BIT   = 1,
    USART_SAMPLE_METHOD_THREE_BITS= 2
}USART_SampleMethod_t;

typedef enum {
    USART_MODE_TX_ONLY   = 1,
    USART_MODE_RX_ONLY   = 2,
    USART_MODE_TX_RX     = 3
}USART_Mode_t;


typedef enum {
    USART_OK,
    USART_ERR_NULLCFG,
    USART_ERR_BAD_PERIPH,
    USART_ERR_TIMEOUT , 
    USART_STRING_BUFFER_OVF,
    USART_ERR_BUFFER_FULL
} USART_Status_t;

typedef enum {
    STILL_PARSING ,
    DONE_PARSING ,
    INVALID_ARGUMENT ,
    TIMEOUT_OCCURRED 
} USART_ParsingStatus_t ;


/*
    * Initialzing structure for USART

    *fclk is the clock of the USART peripheral
        ** USART_CLK_8MHZ
        ** USART_CLK_16MHZ
        ** USART_CLK_25MHZ
        ** USART_CLK_32MHZ
        ** USART_CLK_42MHZ
        ** USART_CLK_48MHZ
        ** USART_CLK_64MHZ
    *peripheral is the USART peripheral to be used
        ** USART_PERIPH_1
        ** USART_PERIPH_2
        ** USART_PERIPH_6
    *baudRate is the desired baud rate for communication
        ** USART_BAUDRATE_9600
        ** USART_BAUDRATE_19200
        ** USART_BAUDRATE_115200
        ** USART_BAUDRATE_1M
    *wordLength is the number of data bits (8 or 9)
        ** USART_WORD_LENGTH_8BITS
        ** USART_WORD_LENGTH_9BITS
    *stopBits is the number of stop bits (0.5, 1, 1.5, or 2)
        ** USART_STOP_BITS_0_5
        ** USART_STOP_BITS_1
        ** USART_STOP_BITS_1_5
        ** USART_STOP_BITS_2
    *parity is the parity configuration (none, even, or odd)
        ** USART_PARITY_NONE
        ** USART_PARITY_EVEN
        ** USART_PARITY_ODD
    *sampleRate is the oversampling rate (8 or 16)
        ** USART_SAMPLE_8_TIMES
        ** USART_SAMPLE_16_TIMES
    *sampleMethod is the sampling method (1-bit or 3-bit majority)
        ** USART_SAMPLE_METHOD_ONE_BIT
        ** USART_SAMPLE_METHOD_THREE_BITS
    *mode is the operation mode (TX only, RX only, or TX/RX)
        ** USART_MODE_TX_ONLY
        ** USART_MODE_RX_ONLY
        ** USART_MODE_TX_RX 
*/

typedef struct {
    USART_clk_t fclk ;
    USART_Peripheral_t peripheral;
    u32 baudRate;
    USART_WordLength_t wordLength;
    USART_StopBits_t stopBits;
    USART_Parity_t parity;
    USART_SampleRate_t sampleRate;
    USART_SampleMethod_t sampleMethod;
    USART_Mode_t mode;
}USART_Config_t;


// ###############################################################################

/* Function descriptions */

/*
@brief: Initializes the USART peripheral with the specified configuration.
@param: cfg - Pointer to a USART_Config_t structure containing the configuration parameters.
@return: USART_Status_t indicating success or error code.
@note: This function must be called before any other USART functions.
         It configures the USART peripheral based on the provided settings.
         If cfg is NULL, it returns USART_ERR_NULLCFG.
         If an invalid peripheral is specified, it returns USART_ERR_BAD_PERIPH.
         Default values are set for any configuration parameters not explicitly provided.
@Note 
    - This function does not enable the NVIC interrupt for USART; it must be done separately if needed.
    - Ensure that the GPIO pins for TX and RX are configured appropriately before calling this function.

    - MNVIC_vEnableInterrupt(peripheral_IRQn); // Enable the USART interrupt in NVIC
        ** USART1_IRQn
        ** USART2_IRQn
        ** USART6_IRQn

    - Gpio pins for USART alternate function must be configured before calling this function.

    -GPIOx_PinConfig_t _xPin = {
		.Port = GPIO_p,
		.Pin = GPIO_PIN_y,
		.Mode = GPIO_MODE_ALTERNATE,	
		.AltFunc = GPIO_AF7             check the datasheet for the correct AF number
	};

    - Then initialize the pin using the GPIO driver
        ** MGPIO_vPinInit(&_xPin);
*/
USART_Status_t MUSART_Init(USART_Config_t* cfg);

/*
@brief: Reads a single byte from the USART receive buffer.
@param: A_thisID - The USART peripheral identifier (USART_PERIPH_1, USART_PERIPH_2, or USART_PERIPH_6).
@return: The byte read from the buffer, or 0 if no data is available.
*/
u8 MUSART_u8ReadByte(USART_Peripheral_t A_thisID) ;


/*
@brief: Checks if there are any bytes available in the USART receive buffer.
@param: A_thisID - The USART peripheral identifier (USART_PERIPH_1, USART_PERIPH_2, or USART_PERIPH_6).
@return: The number of bytes available in the buffer.
*/
u8 MUSART_u8BytesAvailable(USART_Peripheral_t A_thisID);

/*
@brief: Writes a single byte to the USART transmit buffer.
@param: A_thisID - The USART peripheral identifier (USART_PERIPH_1, USART_PERIPH_2, or USART_PERIPH_6).
@param: A_u8ByteToPush - The byte to be transmitted.
@return: USART_Status_t indicating success or error code.
*/
USART_Status_t MUSART_u8WriteByte(USART_Peripheral_t A_thisID, u8 A_u8ByteToPush);

/*
@brief: Writes a null-terminated string to the USART transmit buffer.
@param: A_thisID - The USART peripheral identifier (USART_PERIPH_1, USART_PERIPH_2, or USART_PERIPH_6).
@param: A_u8StringToPush - Pointer to the null-terminated string to be transmitted.
@return: USART_Status_t indicating success or error code.
@note: The function sends characters one by one until it encounters the null terminator.
*/
USART_Status_t MUSART_u8WriteString(USART_Peripheral_t A_thisID, const u8* A_u8StringToPush);

/*
@brief: Reads a string from the USART receive buffer until a specified terminating character is encountered or the buffer limit is reached.
@param: A_thisID - The USART peripheral identifier (USART_PERIPH_1, USART_PERIPH_2, or USART_PERIPH_6).
@param: A_u8pStringBuffer - Pointer to the buffer where the received string will be stored.
@param: A_u32BufferSize - The size of the buffer pointed to by A_u8pStringBuffer.
@param: A_u8TerminatingChar - The character that indicates the end of the string.
@return: USART_Status_t indicating success or error code.
@note: The function reads characters from the receive buffer and stores them in A_u8pStringBuffer until A_u8TerminatingChar is encountered or the buffer limit (STRING_BUFFER_MAX_SIZE) is reached.
       The resulting string in A_u8pStringBuffer is null-terminated.
       If the buffer limit is reached before encountering the terminating character, it returns USART_STRING_BUFFER_OVF.
       Ensure that A_u8pStringBuffer has enough space to hold the incoming string and the null terminator.
*/
USART_Status_t MUSART_u8ReadStringUntil(USART_Peripheral_t A_thisID, u8 *A_u8pStringBuffer,u32 A_u32BufferSize ,u8 A_u8TerminatingChar);

/*
@brief: Flushes the USART transmit and receive buffers.
@param: A_thisID - The USART peripheral identifier (USART_PERIPH_1, USART_PERIPH_2, or USART_PERIPH_6).
@return: USART_Status_t indicating success or error code.
*/
USART_Status_t MUSART_vFlush(USART_Peripheral_t A_thisID);

USART_Status_t MUSART_u32ParseIntBlocking(USART_Peripheral_t A_thisID,  s32* A_ps32Result,  u32 timeout_ms);
USART_ParsingStatus_t MUSART_u8ParseInt(USART_Peripheral_t A_thisID , s32* A_ps32Result) ;
// f32 MUSART_f32ParseFloatBlocking(USART_Peripheral_t A_thisID, u32 timeout_ms);

#endif /* USART_INT_H */
