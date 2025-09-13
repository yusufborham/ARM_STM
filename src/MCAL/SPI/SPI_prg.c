#include "SPI_int.h"
#include "SPI_cfg.h"
#include "SPI_prv.h"

#include "../NVIC/NVIC_int.h"
#include "../SYSTICK/SYSTICK_int.h"

/////////////////////// Global variables / structs ///////////////////////////
SPI_Control_status_t G_sSPI_control_status[SPI_PERIPHERAL_NUMBER] = {{0}};


// circular buffer 
SPI_BufferTx_t G_sSPI_TX_Buffer[SPI_PERIPHERAL_NUMBER] = {0} ;
SPI_BufferRx_t G_sSPI_RX_Buffer[SPI_PERIPHERAL_NUMBER] = {0} ;

///////////////////////// function prototypes /////////////////////////////////
static inline volatile SPIx_MemMap_t* MSPI_pGetRegDef(SPI_peripheralID_t peripheral) ;
static inline u8 MSPI_u8GetFlagStatus(SPI_peripheralID_t peripheral , SPI_flag_t flag );
static inline SPI_status MSPI_DisableInterrupt(SPI_peripheralID_t peripheral , SPI_Interrupt_t interrupt);
static inline SPI_status MSPI_EnableInterrupt(SPI_peripheralID_t peripheral , SPI_Interrupt_t interrupt);




//////////////////////// function definition ///////////////////////////////////
static inline volatile SPIx_MemMap_t* MSPI_pGetRegDef(SPI_peripheralID_t peripheral) {
    if (peripheral == SPI_PERIPH_1) return SPI1;
    if (peripheral == SPI_PERIPH_2) return SPI2;
    if (peripheral == SPI_PERIPH_3) return SPI3;
    if (peripheral == SPI_PERIPH_4) return SPI4;
    return NULL;
}

static inline u8 MSPI_u8GetFlagStatus(SPI_peripheralID_t peripheral , SPI_flag_t flag ){
    volatile SPIx_MemMap_t* SPIx = MSPI_pGetRegDef(peripheral);

    return (SPIx->SR & (1 << flag)) ? 1 : 0;
}

static inline SPI_status MSPI_EnableInterrupt(SPI_peripheralID_t peripheral , SPI_Interrupt_t interrupt){
    volatile SPIx_MemMap_t* SPIx = MSPI_pGetRegDef(peripheral);

    if (SPIx == NULL )   return SPI_BAD_PERIPH ; 

    SET_BIT(SPIx->CR2 , interrupt);
    return SPI_OK ;
} 

static inline SPI_status MSPI_DisableInterrupt(SPI_peripheralID_t peripheral , SPI_Interrupt_t interrupt){
    volatile SPIx_MemMap_t* SPIx = MSPI_pGetRegDef(peripheral);

    if (SPIx == NULL )   return SPI_BAD_PERIPH ; 

    CLR_BIT(SPIx->CR2 , interrupt);
    return SPI_OK ;
} 



//////////////////////////////////// NVIC functions /////////////////////////////////////////

static inline void MSPI_vEnableNVIC(SPI_peripheralID_t peripheral){
    switch (peripheral) {
        case SPI_PERIPH_1:
            MNVIC_vEnableInterrupt(SPI1_IRQn);
            break;
        case SPI_PERIPH_2:
            MNVIC_vEnableInterrupt(SPI2_IRQn);
            break;
        case SPI_PERIPH_3:
            MNVIC_vEnableInterrupt(SPI3_IRQn);
            break;
        case SPI_PERIPH_4:
            MNVIC_vEnableInterrupt(SPI4_IRQn);
            break;
        default:
            // Invalid peripheral, do nothing or handle error
            break;
    }
}

static inline void MUSART_vDisableNVIC(SPI_peripheralID_t peripheral){
    switch (peripheral) {
        case SPI_PERIPH_1:
            MNVIC_vDisableInterrupt(SPI1_IRQn);
            break;
        case SPI_PERIPH_2:
            MNVIC_vDisableInterrupt(SPI2_IRQn);
            break;
        case SPI_PERIPH_3:
            MNVIC_vDisableInterrupt(SPI3_IRQn);
            break;
        case SPI_PERIPH_4:
            MNVIC_vDisableInterrupt(SPI4_IRQn);
            break;
        default:
            // Invalid peripheral, do nothing or handle error
            break;
    }
}

 
/////////////////////////////////////// API functions /////////////////////////////////////////
 

SPI_status MSPI_vInit(SPI_Config_t* cfg){
    // assign the base address of the selected SPI peripheral to a pointer
    volatile SPIx_MemMap_t* SPIx = MSPI_pGetRegDef(cfg->myPeripheral);
    if (SPIx == NULL) return SPI_BAD_PERIPH ;

    // control and status 
    SPI_Control_status_t* L_thisSPI_control_status = &G_sSPI_control_status[cfg->myPeripheral];
    L_thisSPI_control_status->thisMode = cfg->myOperationMode ;

    MSPI_vEnableNVIC(cfg->myPeripheral);

    switch(cfg->NSSMode){
        case NSS_SW :
            SET_BIT(SPIx->CR1 , SSM);
//---------> // check if master 
            SET_BIT(SPIx->CR1 , SSI );
            break ;
        case NSS_OE :
            CLR_BIT(SPIx->CR1 , SSM);
            SET_BIT(SPIx->CR2 , SSOE);
            break ;
        case NSS_OD :
            CLR_BIT(SPIx->CR1 , SSM);
            CLR_BIT(SPIx->CR2 , SSOE);
            break ;
        default :
//---------> handle error 
            break ;
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
    SPI_BufferTx_t* L_sTBuff = &G_sSPI_TX_Buffer[cfg->myPeripheral]; 
    SPI_BufferRx_t* L_sRBuff = &G_sSPI_RX_Buffer[cfg->myPeripheral];

    switch (cfg->dataFrameLn){
        case DATA_FRAME_8BIT :
            CLR_BIT(SPIx->CR1 , DFF);
            L_sTBuff->dataFrame = DATA_FRAME_8BIT ;
            L_sRBuff->dataFrame = DATA_FRAME_8BIT ;
            break ; 
        case DATA_FRAME_16BIT:
            SET_BIT(SPIx->CR1 , DFF);
            L_sTBuff->dataFrame = DATA_FRAME_16BIT ;
            L_sRBuff->dataFrame = DATA_FRAME_16BIT ;
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
    return SPI_OK ;
}

// ---------> for now hasht8l 3la 8 bits but we lazem  handle el 16 bit kman ha3mlha b casting 
SPI_status MSPI_vSendData(SPI_peripheralID_t peripheral , u16 A_u16Data) {
    // check the peripheral is valid 
    if (peripheral >= SPI_PERIPHERAL_NUMBER) return SPI_BAD_PERIPH ;
    //To use this function the thisMode must be FULL_DUPLEX ,HALF_DUPLEX , SIMPLEX_TRANSMIT 
    SPI_Control_status_t* L_thisSPI_control_status = &G_sSPI_control_status[peripheral];

    volatile SPIx_MemMap_t* SPIx = MSPI_pGetRegDef(peripheral);

    if (L_thisSPI_control_status->thisMode == SIMPLEX_RECIEVE)  return SPI_WRONG_CONFIG ;

    // if half duplex set the BIDIOE bit in the CR1 register 

    if (L_thisSPI_control_status->thisMode == HALF_DUPLEX)  SET_BIT(SPIx->CR1 , BIDIOE);

     SPI_BufferTx_t* L_sTBuff = &G_sSPI_TX_Buffer[peripheral]; 
    
    #ifdef OVERWRITE_TX_BUFFER 
        u8 L_nextPointer = (L_sTBuff->txPutPtr+1)%SPI_MAX_TX_BUFFER_SIZE ;
        if (L_nextPointer == L_sTBuff->txGetPtr) return SPI_BUFF_OVF ;
    #endif
    // Send data over SPI

     // critical section disable the interrupt 
     MSPI_DisableInterrupt(peripheral , TRANSMIT_BUFFER_EMPTY_INT);
//----------------> maybe it is better to disable the global intterupt or the NVIC controller 
     
     if (L_sTBuff->dataFrame == DATA_FRAME_8BIT ){
        L_sTBuff->buffer.Mode8BIT.SPI_TX_BUFFER[L_sTBuff->txPutPtr++] = (u8)(A_u16Data & 0XFF) ;
     }
     // handle 16 bit mode 
     else if (L_sTBuff->dataFrame == DATA_FRAME_16BIT){
        L_sTBuff->buffer.Mode16BIT.SPI_TX_BUFFER[L_sTBuff->txPutPtr++] = (A_u16Data & 0XFFFF) ;
     }
     
     L_sTBuff->txPutPtr = (L_sTBuff->txPutPtr)%SPI_MAX_TX_BUFFER_SIZE ;

     // end of critical section 
     MSPI_EnableInterrupt(peripheral , TRANSMIT_BUFFER_EMPTY_INT );
     L_thisSPI_control_status->txInterruptStatus = 1 ;

     return SPI_OK ;

}

u8 MSPI_u8ReceiveData(void) {
    // Receive data over SPI
    return 0;
}
void SPI_HandlerRoutine(SPI_peripheralID_t peripheral ){
    SPI_Control_status_t* L_thisSPI_control_status = &G_sSPI_control_status[peripheral];
    volatile SPIx_MemMap_t* SPIx = MSPI_pGetRegDef(peripheral);

    if (MSPI_u8GetFlagStatus(peripheral ,TRANSMIT_BUFFER_EMPTY_FLAG) ){
        SPI_BufferTx_t* L_sTBuff = &G_sSPI_TX_Buffer[peripheral]; 
    
        if (L_sTBuff->txGetPtr == L_sTBuff->txPutPtr){
            MSPI_DisableInterrupt(peripheral , TRANSMIT_BUFFER_EMPTY_INT);
            L_thisSPI_control_status->txInterruptStatus = 0 ;
        }
        else { // el mafrood hena a handle el modes ya2ema 8bits ya2ema 16 bit ha switch 3la el frame mode el gowa el struct
            if (L_sTBuff->dataFrame == DATA_FRAME_8BIT )
                SPIx->DR = L_sTBuff->buffer.Mode8BIT.SPI_TX_BUFFER[L_sTBuff->txGetPtr++];
            else if (L_sTBuff->dataFrame == DATA_FRAME_16BIT)
                SPIx->DR = L_sTBuff->buffer.Mode16BIT.SPI_TX_BUFFER[L_sTBuff->txGetPtr++];
            L_sTBuff->txGetPtr = (L_sTBuff->txGetPtr)%SPI_MAX_TX_BUFFER_SIZE ;
        }
    }
}
void SPI1_IRQHandler(void){
    // Handle SPI1 interrupt
    SPI_HandlerRoutine(SPI_PERIPH_1) ;
}

void SPI2_IRQHandler(void){
    // Handle SPI2 interrupt
    SPI_HandlerRoutine(SPI_PERIPH_2) ;
}

void SPI3_IRQHandler(void){
    // Handle SPI3 interrupt
    SPI_HandlerRoutine(SPI_PERIPH_3) ;
}

void SPI4_IRQHandler(void){
    // Handle SPI4 interrupt
    SPI_HandlerRoutine(SPI_PERIPH_4) ;
}



