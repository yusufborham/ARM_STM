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

/*
Structure for SPI configuration

*myPeripheral: Specifies the SPI peripheral to be used (SPI_PERIPH_1, SPI_PERIPH_2, etc.).
*mySPIMode: Specifies the SPI mode (MASTER or SLAVE).
*myBaudRate: Specifies the baud rate for the SPI clock.
  ** The baud rate is determined by dividing the peripheral clock by a factor (e.g., CLK_DIV_2, CLK_DIV_4, etc.).
*myOperationMode: Specifies the operation mode (FULL_DUPLEX, HALF_DUPLEX, SIMPLEX_TRANSMIT, SIMPLEX_RECIEVE).
*dataShift: Specifies the data shift order (LSB_FIRST or MSB_FIRST).
*dataFrameLn: Specifies the data frame length (DATA_FRAME_8BIT or DATA_FRAME_16BIT).
*ClockPhasePol: Specifies the clock phase and polarity (CLK_PHA_POL_MODE_0, CLK_PHA_POL_MODE_1, etc.).
*NSSMode: Specifies the NSS (Slave Select) mode (NSS_SW, NSS_OE, NSS_OD).
*myformat: Specifies the frame format (MOTOROLA_FORMAT or TI_FORMAT).

*/
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
    SPI_BUFF_OVF ,
    SPI_WRONG_CONFIG 
}SPI_status ;
// SPI initialization function


/*
@brief Initializes the SPI peripheral based on the provided configuration.
@param cfg Pointer to a SPI_Config_t structure containing the configuration settings.
@return SPI_status indicating the success or failure of the initialization.
*/
SPI_status MSPI_vInit(SPI_Config_t* cfg);

// SPI send data function

/*
@brief Sends data over the specified SPI peripheral.
@param peripheral The SPI peripheral ID to use for sending data (SPI_PERIPH_1, SPI_PERIPH_2, etc.).
@param A_u16Data The data to be sent (8-bit or 16-bit based on configuration).
@return SPI_status indicating the success or failure of the data transmission.
*/
SPI_status MSPI_vSendData(SPI_peripheralID_t peripheral , u16 A_u16Data);

// SPI receive data function
u8 MSPI_u8ReceiveData(void);

#endif // SPI_INT_H
