#ifndef USART_INT_H
#define USART_INT_H

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Delay.h"
#include "../../LIB/MATH_Fn.h" 

#define USART_BAUDRATE_9600     9600
#define USART_BAUDRATE_19200   19200
#define USART_BAUDRATE_115200 115200
#define USART_BAUDRATE_1M     1000000

typedef enum {
    USART_PERIPH_1  = 1,
    USART_PERIPH_2  = 2,
    USART_PERIPH_6  = 3
}USART_Peripheral_t;

typedef enum {
    USART_WORD_LENGTH_8BITS  = 1,
    USART_WORD_LENGTH_9BITS  = 2
}USART_WordLength_t;

typedef enum {
    USART_STOP_BITS_0_5= 1,
    USART_STOP_BITS_1  = 2,
    USART_STOP_BITS_1_5= 3,
    USART_STOP_BITS_2  = 4
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
    USART_CLK_8MHZ  = 8,
    USART_CLK_16MHZ = 16,
    USART_CLK_25MHZ = 25,
    USART_CLK_32MHZ = 32,
    USART_CLK_42MHZ = 42,
    USART_CLK_48MHZ = 48,
    USART_CLK_64MHZ = 64
}USART_clk_t;

typedef enum {
    USART_OK,
    USART_ERR_NULLCFG,
    USART_ERR_BAD_PERIPH,
    USART_ERR_TIMEOUT
} USART_Status_t;


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



USART_Status_t MUSART_Init(USART_Config_t* cfg);
USART_Status_t MUSART_SendData(USART_Peripheral_t A_peripheral , u8 data);
u8 MUSART_ReceiveData(USART_Peripheral_t A_peripheral);
void MUSART_SendString(USART_Peripheral_t A_peripheral , const char* str);

#endif /* USART_INT_H */