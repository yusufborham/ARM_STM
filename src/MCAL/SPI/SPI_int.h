#ifndef SPI_INT_H
#define SPI_INT_H

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Delay.h"
#include "../../LIB/MATH_Fn.h" 

typedef enum {
    NSS_SW ,
    NSS_OE ,
    NSS_OD
}SPI_NSS_mode_t ;

typedef enum {
    CLK_PHA_POL_MODE_0 ,    // Clock is low when idle; data is sampled on the rising edge and shifted on the falling edge. (CPOL=0, CPHA=0)
    CLK_PHA_POL_MODE_1 ,    // Clock is low when idle; data is sampled on the falling edge and shifted on the rising edge. (CPOL=0, CPHA=1)
    CLK_PHA_POL_MODE_2 ,    // Clock is high when idle; data is sampled on the falling edge and shifted on the rising edge.(CPOL=1, CPHA=0)
    CLK_PHA_POL_MODE_3      // Clock is high when idle; data is sampled on the rising edge and shifted on the falling edge.(CPOL=1, CPHA=1
}SPI_Clock_phase_polarity_t ;

typedef enum {
    DATA_FRAME_8BIT ,
    DATA_FRAME_16BIT 
}SPI_Data_frame_t ;

typedef enum {
    LSB_FIRST ,
    MSB_FIRST 
}SPI_Data_shift_t ;

typedef enum {
    FULL_DUPLEX ,
    HALF_DUPLEX ,
    SIMPLEX_TRANSMIT ,
    SIMPLEX_RECIEVE 
}SPI_Operation_mode_t ;

typedef enum {
    MASTER , 
    SLAVE 
}SPI_mode_t;

typedef enum {
    SPI_PERIPH_1 ,
    SPI_PERIPH_2 ,
    SPI_PERIPH_3 ,
    SPI_PERIPH_4
}SPI_peripheralID_t ;

typedef enum {
    CLK_DIV_2 ,
    CLK_DIV_4 ,
    CLK_DIV_8 ,
    CLK_DIV_16 ,
    CLK_DIV_32 ,
    CLK_DIV_64 ,
    CLK_DIV_128 ,
    CLK_DIV_256 
}SPI_Baud_rate_t ;

typedef enum {
    MOTOROLA_FORMAT ,
    TI_FORMAT
}SPI_frameFormat_t ;

typedef struct {
    SPI_peripheralID_t myPeripheral ;
    SPI_mode_t mySPIMode ;
    SPI_Baud_rate_t myBaudRate ; 
    SPI_Operation_mode_t myOperationMode ;
    SPI_Data_shift_t dataShift ;
    SPI_Data_frame_t dataFrameLn ;
    SPI_Clock_phase_polarity_t ClockPhasePol ;
    SPI_NSS_mode_t NSSMode ;
    SPI_frameFormat_t myformat ;
}SPI_Config_t ;

typedef enum {
    SPI_OK ,
    SPI_BAD_PERIPH ,
    BUFF_OVF
}SPI_status ;
// SPI initialization function
SPI_status MSPI_vInit(SPI_Config_t* cfg);

// SPI send data function
void MSPI_vSendData(u8 A_u8Data);

// SPI receive data function
u8 MSPI_u8ReceiveData(void);

#endif // SPI_INT_H