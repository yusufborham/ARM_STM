#ifndef USART_PRV_H
#define USART_PRV_H

#include "../../LIB/STD_TYPES.h"
#include "USART_cfg.h"

#define MEGA(x)   ((x) * 1000000UL)

#define USART1_BASE_ADDRESS 0x40011000
#define USART2_BASE_ADDRESS 0x40004400
#define USART6_BASE_ADDRESS 0x40011400

#define USART_NUMBER 3
typedef enum {
    USART_FLAG_PARITY_ERROR                 = 0,
    USART_FLAG_FRAME_ERROR                  = 1,
    USART_FLAG_NOISE_DETECTED               = 2,
    USART_FLAG_OVER_RUN                     = 3,
    USART_FLAG_IDLE_DETECTED                = 4,
    USART_FLAG_READ_DATA_READY              = 5,
    USART_FLAG_TRANSMISSION_COMPLETE        = 6,
    USART_FLAG_TRANSMIT_DATA_REG_EMPTY = 7
}USART_Flags_t;

typedef enum {
    USART_IDLE_DETECTED_INT             = 4,
    USART_READ_DATA_READY_INT           = 5,
    USART_TRANSMISION_COMPLETE_INT      = 6,
    USART_TRANSMIT_DATA_REG_EMPTY_INT   = 7,
    USART_PARITY_ERROR_INT              = 8
}USART_Interrupts_t;

typedef struct {
    u32 DIV_Mantissa ;
    u8 DIV_Fraction ;
} USART_BaudRate_cfg_t;

typedef struct {
    volatile u8 USART_TX_BUFFER[MAX_TX_BUFFER_SIZE] ;
    volatile u8 USART_RX_BUFFER[MAX_RX_BUFFER_SIZE] ;
    volatile u8 txPutPtr ;
    volatile u8 txGetPtr ;
    volatile u8 rxPutPtr ;
    volatile u8 rxGetPtr ;
}USART_Buffer_t ;

typedef struct {
    s32 result ;
    u8 isFirstByte ;
    u8 sign ;
    u8 isParsing ;
    u32 entryTime ;
} USART_parsingIntStatus_t ;

typedef struct {
    u8 Tx_enabled ;
    u8 Rx_enabled ;
} USART_InterruptStatus_t;

typedef struct {
    u32 idx ;
    u32 jdx  ;
    u8  entered  ;
    u32 startIdx  ;
    u8  exit  ;
}USART_StringFunctionStatus_t ;

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
    USART_PERIPH_1  = 0,
    USART_PERIPH_2  = 1,
    USART_PERIPH_6  = 2
}USART_Peripheral_t;



typedef struct {
    volatile u32 SR ;
    volatile u32 DR ;
    volatile u32 BRR ;
    volatile u32 CR1 ;
    volatile u32 CR2 ;
    volatile u32 CR3 ;
    u32 GTPR ;
} USART_RegDef_t;


#define USART1 ((USART_RegDef_t *)USART1_BASE_ADDRESS)
#define USART2 ((USART_RegDef_t *)USART2_BASE_ADDRESS)
#define USART6 ((USART_RegDef_t *)USART6_BASE_ADDRESS)

// SR Bits 

#define PE      0
#define FE      1
#define NE      2
#define ORE     3
#define IDLE    4
#define RXNE    5
#define TC      6
#define TXE     7
#define LBD     8
#define CTS     9

// CR1 Bits

#define SBK     0
#define RWU     1
#define RE      2
#define TE      3
#define IDLEIE  4
#define RXNEIE  5
#define TCIE    6
#define TXEIE   7
#define PEIE    8
#define PS      9
#define PCE     10
#define WAKE    11
#define M       12
#define UE      13
#define OVER8   15

// CR2 bits 

#define LBDL    5
#define LBDIE   6
#define LBCL    8
#define CPHA    9
#define CPOL    10
#define CLKEN   11
#define STOP    12
#define LINEN   14

// CR3 bits 
#define EIE     0
#define IREN    1
#define IRLP    2
#define HDSEL   3
#define NACK    4
#define SCEN    5
#define DMAR    6
#define DMAT    7
#define RTSE    8
#define CTSE    9
#define CTSIE   10
#define ONEBIT  11


// stop bits macros 

#define USART_CR2_STOP_Msk  0b11
#define USART_0_5_STOP_BIT   0b01
#define USART_1_STOP_BIT     0b00
#define USART_1_5_STOP_BIT   0b11
#define USART_2_STOP_BIT     0b10


#endif /* USART_PRV_H */