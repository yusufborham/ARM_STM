#ifndef USART_PRV_H
#define USART_PRV_H

#include "../../LIB/STD_TYPES.h"

#define USART1_BASE_ADDRESS 0x40011000
#define USART2_BASE_ADDRESS 0x40004400
#define USART6_BASE_ADDRESS 0x40011400

typedef struct {
    u32 SR ;
    u32 DR ;
    u32 BRR ;
    u32 CR1 ;
    u32 CR2 ;
    u32 CR3 ;
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



#endif /* USART_PRV_H */