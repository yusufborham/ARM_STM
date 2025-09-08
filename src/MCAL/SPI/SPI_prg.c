#include "SPI_int.h"
#include "SPI_cfg.h"
#include "SPI_prv.h"

/////////////////////// Global variables / structs ///////////////////////////
SPI_Control_status_t G_sSPI_control_status[SPI_PERIPHERAL_NUMBER] = {{0}};




///////////////////////// function prototypes /////////////////////////////////
static inline SPIx_MemMap_t* MSPI_pGetRegDef(SPI_peripheralID_t peripheral) ;






//////////////////////// function definition ///////////////////////////////////
static inline SPIx_MemMap_t* MSPI_pGetRegDef(SPI_peripheralID_t peripheral) {
    if (peripheral == SPI_PERIPH_1) return SPI1;
    if (peripheral == SPI_PERIPH_2) return SPI2;
    if (peripheral == SPI_PERIPH_3) return SPI3;
    if (peripheral == SPI_PERIPH_4) return SPI4;
    return NULL;
}

//---------------> inline functions for enabling the interrupts 

//---------------> inline functions for returning the flag status 

SPI_status MSPI_vInit(SPI_Config_t* cfg){
    // assign the base address of the selected SPI peripheral to a pointer
    SPIx_MemMap_t* SPIx = MSPI_pGetRegDef(cfg->myPeripheral);
    if (SPIx == NULL) return SPI_BAD_PERIPH ;

    // control and status 
    SPI_Control_status_t* L_thisSPI_control_status = &G_sSPI_control_status[cfg->myPeripheral];
    L_thisSPI_control_status->thisMode = cfg->myOperationMode ;

//---------> enable the interrupt from the NVIC  

    switch(cfg->NSSMode){
        case NSS_SW :
            SET_BIT(SPIx->CR1 , SSM);
//---------> // check if master 
            SET_BIT(SPIx->CR1 , SSI );
        case NSS_OE :
            CLR_BIT(SPIx->CR1 , SSM);
            SET_BIT(SPIx->CR2 , SSOE);
        case NSS_OD :
            CLR_BIT(SPIx->CR1 , SSM);
            CLR_BIT(SPIx->CR2 , SSOE);
    }

    // clcok configs 
    switch (cfg->ClockPhasePol){
        case CLK_PHA_POL_MODE_0 :
            CLR_BIT(SPIx->CR1 , CPHA);
            CLR_BIT(SPIx->CR1 , CPOL);
            break ;
        case  CLK_PHA_POL_MODE_1 :
            SET_BIT(SPIx->CR1 , CPHA);
            CLR_BIT(SPIx->CR1 , CPOL);
            break ;
        case CLK_PHA_POL_MODE_2 :
            CLR_BIT(SPIx->CR1 , CPHA);
            SET_BIT(SPIx->CR1 , CPOL);
            break ;
        case CLK_PHA_POL_MODE_3 : 
            SET_BIT(SPIx->CR1 , CPHA);
            SET_BIT(SPIx->CR1 , CPOL);
            break ;
        default :
//---------> handle error 
            break ;
    }

    // data frame length 
    switch (cfg->dataFrameLn){
        case DATA_FRAME_8BIT :
            CLR_BIT(SPIx->CR1 , DFF);
            break ; 
        case DATA_FRAME_16BIT:
            SET_BIT(SPIx->CR1 , DFF);
            break ;
        default :
//---------> handle error 
            break ;
    }

    // set the datashift
    switch (cfg->dataShift){
        case LSB_FIRST :
            SET_BIT(SPIx->CR1 , LSBFIRST) ;
            break ;
        case MSB_FIRST :
            CLR_BIT(SPIx->CR1 , LSBFIRST) ;
            break ;
        default :
//---------> handle error 
            break ;
    }

    switch (cfg->myOperationMode){
        case FULL_DUPLEX :
            CLR_BIT(SPIx->CR1 , BIDIMODE);
            CLR_BIT(SPIx->CR1 , RXONLY);
//---------> enable both interupts 
            break ; 
        case HALF_DUPLEX :      // to send or receive will have ot won function 
            SET_BIT(SPIx->CR1 , BIDIMODE);
//--------> depending on wheteher sending or recieving we enable the corresponding interrupt 
            break ;
        case SIMPLEX_TRANSMIT:  // same as full duplex but we wont read from the rx buffer and we disable the interrupt for rx  
            CLR_BIT(SPIx->CR1 , BIDIMODE);
            CLR_BIT(SPIx->CR1 , RXONLY);

//---------> then only enable the tx interrupt no need for the rx (dont connect the miso)
            break ;
        case SIMPLEX_RECIEVE : 
            CLR_BIT(SPIx->CR1 , BIDIMODE);
            SET_BIT(SPIx->CR1 , RXONLY);

// --------> enable the rx interrupt only             
            break ;
    }

    // frame format config 
    switch (cfg->myformat){
        case MOTOROLA_FORMAT :
            CLR_BIT(SPIx->CR2 , FRF);
            break ;
        case TI_FORMAT :
            SET_BIT(SPIx->CR2 , FRF);
    }

// ----------> I do prefare to rap it in a switch case 
    // set the baud rate for the clock 
    SPIx->CR1 &= ~(0b111 << BR);            // clear the 4 bits 
    SPIx->CR1 |= (cfg->myBaudRate << BR);   // Write the value 

    switch (cfg->mySPIMode){ // make it last step beside the enabling of sp 
        case MASTER :
            SET_BIT(SPIx->CR1 , MSTR);
            break ;
        case SLAVE :
            CLR_BIT(SPIx->CR1 , MSTR);
            break ;
        default :
//---------> handle error 
            break ;
    }

    // finally enable the SPI 

    SET_BIT(SPIx->CR1 , SPE) ;




}

void MSPI_vSendData(u8 A_u8Data) {
    // Send data over SPI
}

u8 MSPI_u8ReceiveData(void) {
    // Receive data over SPI
    return 0;
}
