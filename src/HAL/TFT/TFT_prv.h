#ifndef TFT_PRV_H
#define TFT_PRV_H

#include "TFT_int.h"

//  Macros for TFT commands

#define TFT_NOP     0x00
#define TFT_SWRESET 0x01
#define TFT_RDDID   0x04
#define TFT_RDDST   0x09

#define TFT_SLPIN   0x10
#define TFT_SLPOUT  0x11
#define TFT_PTLON   0x12
#define TFT_NORON   0x13

#define TFT_INVOFF  0x20
#define TFT_INVON   0x21
#define TFT_DISPOFF 0x28
#define TFT_DISPON  0x29
#define TFT_CASET   0x2A
#define TFT_RASET   0x2B
#define TFT_RAMWR   0x2C
#define TFT_RAMRD   0x2E

#define TFT_PTLAR   0x30
#define TFT_COLMOD  0x3A
#define TFT_MADCTL  0x36

#define TFT_FRMCTR1 0xB1
#define TFT_FRMCTR2 0xB2
#define TFT_FRMCTR3 0xB3
#define TFT_INVCTR  0xB4
#define TFT_DISSET5 0xB6

#define TFT_PWCTR1  0xC0
#define TFT_PWCTR2  0xC1
#define TFT_PWCTR3  0xC2
#define TFT_PWCTR4  0xC3
#define TFT_PWCTR5  0xC4
#define TFT_VMCTR1  0xC5

#define TFT_RDID1   0xDA
#define TFT_RDID2   0xDB
#define TFT_RDID3   0xDC
#define TFT_RDID4   0xDD

#define TFT_PWCTR6  0xFC

#define TFT_GMCTRP1 0xE0
#define TFT_GMCTRN1 0xE1


#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_RGB 0x00
#define MADCTL_BGR 0x08
#define MADCTL_MH  0x04

#define COLMOD_12BIT 0x03
#define COLMOD_16BIT 0x05
#define COLMOD_18BIT 0x06

#define DATA_MAX_LENGTH 10

#define TERMINATING_WORD 0xF2F2

typedef struct {
    SPI_peripheralID_t mySPI ;
    HTFT_pixelFormat_t myPixelFormat ;
    HTFT_screenSize_t myScreenSize ;
    u8 myRSTport ;
    u8 myRSTpin  ;
    u8 myA0port  ;
    u8 myA0pin   ;
} HTFT_cfg_t;

typedef struct {
    u8 cmd ; 
    u16 data[DATA_MAX_LENGTH] ;
}HTFT_Frame_t ;


#endif