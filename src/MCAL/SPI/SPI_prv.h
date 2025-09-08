#ifndef SPI_PRV_H
#define SPI_PRV_H

#include "../../LIB/STD_TYPES.h"


#define SP1_BASE_ADDR		0x40013000U
#define SP2_BASE_ADDR		0x40003800U
#define SP3_BASE_ADDR		0x40003C00U
#define SP4_BASE_ADDR		0x40013400U

typedef struct
{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 CRCPR;
	volatile u32 RXCRCR;
	volatile u32 TXCRCR;
	volatile u32 I2SCFGR;
	volatile u32 I2SPR;

}SPIx_MemMap_t;

#define SPI1	((volatile SPIx_MemMap_t*)(SP1_BASE_ADDR))
#define SPI2	((volatile SPIx_MemMap_t*)(SP2_BASE_ADDR))
#define SPI3	((volatile SPIx_MemMap_t*)(SP3_BASE_ADDR))
#define SPI4	((volatile SPIx_MemMap_t*)(SP4_BASE_ADDR))

// defines for the bit positions
#define CPHA	0
#define CPOL	1
#define MSTR	2
#define BR	3
#define SPE	6
#define LSBFIRST	7
#define LSBFIRST	5
#define SSI	8
#define SSM	9
#define RXONLY	10
#define DFF	11
#define CRCNEXT	12
#define CRCEN	13
#define BIDIOE	14
#define BIDIMODE	15

// SPI Status Register (SPI_CR2) bits
#define RXDMAEN 0
#define TXDMAEN 1
#define SSOE    2

#define FRF     4
#define ERRIE   5
#define RXNEIE  6
#define TXEIE   7


// SPI Control Register 1 (SPI_SR) bits
#define RXNE    0
#define TXE     1
#define CHSIDE  2
#define UDR     3
#define CRCERR  4
#define MODF    5
#define OVR     6
#define BSY     7
#define FRE     8



///////// helper stuff //////////

#define SPI_PERIPHERAL_NUMBER 4  

typedef struct {
	SPI_Operation_mode_t thisMode ;

}SPI_Control_status_t;


typedef struct {
    volatile u8 SPI_TX_BUFFER[SPI_MAX_TX_BUFFER_SIZE] ;
    volatile u8 SPI_RX_BUFFER[SPI_MAX_RX_BUFFER_SIZE] ;
    volatile u8 txPutPtr ;
    volatile u8 txGetPtr ;
    volatile u8 rxPutPtr ;
    volatile u8 rxGetPtr ;
}SPI_Buffer_t ;

//
#endif // SPI_PRV_H