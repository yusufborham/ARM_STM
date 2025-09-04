#include "USART_int.h"
#include "USART_cfg.h"
#include "USART_prv.h"



static u8 S_u8USART1_TxINT_enabled = 0 ;
static u8 S_u8USART2_TxINT_enabled = 0 ;
static u8 S_u8USART6_TxINT_enabled = 0 ;

u8 G_au8StringBuffer[STRING_BUFFER_MAX_SIZE] ;

void MUSART_vBaudRateCalculations(u32 A_u32BaudRateValue ,u8 A_u8SampleRate ,u32 A_u32USART_Fclk,USART_BaudRate_cfg_t* A_sBaudRateCfg);
u8 MUSART_GetFlagStatus(USART_Peripheral_t peripheral ,USART_Flags_t flag) ;
USART_Status_t MUSART_DisableInterrupt(USART_Peripheral_t peripheral, USART_Interrupts_t interrupt);
USART_Status_t MUSART_EnableInterrupt(USART_Peripheral_t peripheral,USART_Interrupts_t interrupt);

// 
USART_Buffer_t G_sUSART1_Buffer_data = {.rxGetPtr = 0 , .rxPutPtr = 0 , .txGetPtr = 0 , .txPutPtr = 0 , .USART_RX_BUFFER={0} , .USART_TX_BUFFER={0}} ;
USART_Buffer_t G_sUSART2_Buffer_data = {.rxGetPtr = 0 , .rxPutPtr = 0 , .txGetPtr = 0 , .txPutPtr = 0 , .USART_RX_BUFFER={0} , .USART_TX_BUFFER={0}} ;
USART_Buffer_t G_sUSART6_Buffer_data = {.rxGetPtr = 0 , .rxPutPtr = 0 , .txGetPtr = 0 , .txPutPtr = 0 , .USART_RX_BUFFER={0} , .USART_TX_BUFFER={0}} ;

u8 MUSART_GetFlagStatus(USART_Peripheral_t peripheral, USART_Flags_t flag){
    switch (peripheral) {
        case USART_PERIPH_1:
            return (USART1->SR & (1 << flag)) ? 1 : 0;
        case USART_PERIPH_2:
            return (USART2->SR & (1 << flag)) ? 1 : 0;
        case USART_PERIPH_6:
            return (USART6->SR & (1 << flag)) ? 1 : 0;
        default:
            return 0;
    }
}

USART_Status_t MUSART_EnableInterrupt(USART_Peripheral_t peripheral , USART_Interrupts_t interrupt){
    switch ( peripheral) {
        case USART_PERIPH_1:
            SET_BIT(USART1->CR1, interrupt);
            break;
        case USART_PERIPH_2:
            SET_BIT(USART2->CR1, interrupt);
            break;
        case USART_PERIPH_6:
            SET_BIT(USART6->CR1, interrupt);
            break;
        default:
            return USART_ERR_BAD_PERIPH;
    }
    return USART_OK;
}

USART_Status_t MUSART_DisableInterrupt(USART_Peripheral_t peripheral, USART_Interrupts_t interrupt) {
    switch (peripheral) {
        case USART_PERIPH_1:
            CLR_BIT(USART1->CR1, interrupt);
            break;
        case USART_PERIPH_2:
            CLR_BIT(USART2->CR1, interrupt);
            break;
        case USART_PERIPH_6:
            CLR_BIT(USART6->CR1, interrupt);
            break;
        default:
            return USART_ERR_BAD_PERIPH;
    }
    return USART_OK;
}

void MUSART_vBaudRateCalculations(u32 A_u32BaudRateValue ,u8 A_u8SampleRate ,u32 A_u32USART_Fclk,USART_BaudRate_cfg_t* A_sBaudRateCfg){
    A_sBaudRateCfg->DIV_Mantissa = (A_u32USART_Fclk) / (A_u8SampleRate * A_u32BaudRateValue);
    u8 A_u8Fraction = (u8) (((A_u32USART_Fclk) % (A_u8SampleRate * A_u32BaudRateValue) * A_u8SampleRate) / (A_u8SampleRate * A_u32BaudRateValue));
    A_sBaudRateCfg->DIV_Fraction = (A_u8SampleRate == 8 ) ? (A_u8Fraction & 0x07) : A_u8Fraction;
}

USART_Status_t MUSART_Init(USART_Config_t* cfg){
    // ############# Future Note ###############
    // I must enable the interrupt from the NVIC driver also // 
    // maybe set a priorty also ///
    if (cfg == NULL) return USART_ERR_NULLCFG;

    u8 L_u8USART_SampleRate = DEFAULT_SAMPLE_RATE ;
    // set default values if the user has not provided them
    if (cfg->sampleRate == 0) cfg->sampleRate = USART_SAMPLE_16_TIMES;
    if (cfg->sampleMethod == 0) cfg->sampleMethod = USART_SAMPLE_METHOD_THREE_BITS;
    if (cfg->mode == 0) cfg->mode = USART_MODE_TX_RX;
    if (cfg->parity == 0) cfg->parity = USART_PARITY_NONE;
    if (cfg->wordLength == 0) cfg->wordLength = USART_WORD_LENGTH_8BITS;
    if (cfg->stopBits == 0) cfg->stopBits = USART_STOP_BITS_1;

    u32 L_u32USART_Fclk = MEGA(cfg->fclk);

    USART_RegDef_t* USARTx = NULL;

    switch (cfg->peripheral) {
        case USART_PERIPH_1:
            USARTx = USART1;
            break;
        case USART_PERIPH_2:
            USARTx = USART2;
            break;
        case USART_PERIPH_6:
            USARTx = USART6;
            break;
        default:
            return USART_ERR_BAD_PERIPH;
    }

    SET_BIT(USARTx->CR1 , UE);
    switch (cfg->wordLength){
        case USART_WORD_LENGTH_8BITS:
            CLR_BIT(USARTx->CR1 , M);
            break;
        case USART_WORD_LENGTH_9BITS:
            SET_BIT(USARTx->CR1 , M);
            break;
    }
    switch (cfg->stopBits){
        case USART_STOP_BITS_1:
            USARTx->CR2 &= ~(USART_CR2_STOP_Msk << STOP);
            USARTx->CR2 |= (USART_1_STOP_BIT << STOP);
            break;
        case USART_STOP_BITS_1_5:
            USARTx->CR2 &= ~(USART_CR2_STOP_Msk << STOP);
            USARTx->CR2 |= (USART_1_5_STOP_BIT << STOP);
            break;
        case USART_STOP_BITS_2:
            USARTx->CR2 &= ~(USART_CR2_STOP_Msk << STOP);
            USARTx->CR2 |= (USART_2_STOP_BIT << STOP);
            break;
        case USART_STOP_BITS_0_5:
            USARTx->CR2 &= ~(USART_CR2_STOP_Msk << STOP);
            USARTx->CR2 |= (USART_0_5_STOP_BIT << STOP);
            break;
    }
    switch (cfg->parity){
        case USART_PARITY_NONE:
            CLR_BIT(USARTx->CR1 , PCE);
            break;
        case USART_PARITY_EVEN:
            SET_BIT(USARTx->CR1 , PCE);
            CLR_BIT(USARTx->CR1 , PS);
            break;
        case USART_PARITY_ODD:
            SET_BIT(USARTx->CR1 , PCE);
            SET_BIT(USARTx->CR1 , PS);
            break;
    }
    switch (cfg->sampleRate){
        case USART_SAMPLE_16_TIMES:
            CLR_BIT(USARTx->CR1 , OVER8);
            L_u8USART_SampleRate = 16 ;
            break;
        case USART_SAMPLE_8_TIMES:
            SET_BIT(USARTx->CR1 , OVER8);
            L_u8USART_SampleRate = 8 ;
            break;
    }
    switch (cfg->sampleMethod){
        case USART_SAMPLE_METHOD_ONE_BIT:
            SET_BIT(USARTx->CR3 , ONEBIT);
            break;
        case USART_SAMPLE_METHOD_THREE_BITS:
            CLR_BIT(USARTx->CR3 , ONEBIT);
            break;
    }
    switch (cfg->mode){
        case USART_MODE_TX_ONLY:
            SET_BIT(USARTx->CR1 , TE);
            CLR_BIT(USARTx->CR1 , RE);
            break;
        case USART_MODE_RX_ONLY:
            SET_BIT(USARTx->CR1 , RE);
            CLR_BIT(USARTx->CR1 , TE);
            break;
        case USART_MODE_TX_RX:
            SET_BIT(USARTx->CR1 , TE);
            SET_BIT(USARTx->CR1 , RE);
            break;
    }
    MUSART_EnableInterrupt(cfg->peripheral , USART_READ_DATA_READY_INT);
    USART_BaudRate_cfg_t L_sU1BaudRateCfg;
    MUSART_vBaudRateCalculations(cfg->baudRate , L_u8USART_SampleRate , L_u32USART_Fclk, &L_sU1BaudRateCfg);
    USARTx->BRR = (L_sU1BaudRateCfg.DIV_Mantissa << 4) | (L_sU1BaudRateCfg.DIV_Fraction & 0x0F);

    return USART_OK;
}


u8 MUSART_u8ReadByte(USART_Config_t* cfg){
    USART_Buffer_t* L_spUSART_buffData = NULL ;
    u8 L_u8readData = 0 ;
    switch (cfg->peripheral)
    {
    case USART_PERIPH_1:
        L_spUSART_buffData = &G_sUSART1_Buffer_data ;
        break;
    case USART_PERIPH_2:
        L_spUSART_buffData = &G_sUSART2_Buffer_data ;
        break;
    case USART_PERIPH_6:
        L_spUSART_buffData = &G_sUSART6_Buffer_data ;
        break;
    default:
        return USART_ERR_BAD_PERIPH;
    }

    if (L_spUSART_buffData->rxGetPtr == L_spUSART_buffData->rxPutPtr )
        return 0 ;
    
    else {
        L_u8readData = L_spUSART_buffData->USART_RX_BUFFER[L_spUSART_buffData->rxGetPtr++];
        L_spUSART_buffData->rxGetPtr =(L_spUSART_buffData->rxGetPtr ) % MAX_RX_BUFFER_SIZE ;
        return L_u8readData ;
    }           
}

u8 MUSART_u8BytesAvailable(USART_Config_t* cfg){
    USART_Buffer_t* L_spUSART_buffData = NULL ;

    switch (cfg->peripheral)
    {
    case USART_PERIPH_1:
        L_spUSART_buffData = &G_sUSART1_Buffer_data ;
        break;
    case USART_PERIPH_2:
        L_spUSART_buffData = &G_sUSART2_Buffer_data ;
        break;
    case USART_PERIPH_6:
        L_spUSART_buffData = &G_sUSART6_Buffer_data ;
        break;
    default:
        return USART_ERR_BAD_PERIPH;
    }

    return (L_spUSART_buffData->rxPutPtr - L_spUSART_buffData->rxGetPtr + MAX_RX_BUFFER_SIZE) % MAX_RX_BUFFER_SIZE;
}

USART_Status_t MUSART_u8WriteByte(USART_Config_t* cfg , u8 A_u8ByteToPush){
    USART_Buffer_t* L_spUSART_buffData = NULL ;
    switch (cfg->peripheral)
    {
    case USART_PERIPH_1:
        L_spUSART_buffData = &G_sUSART1_Buffer_data ;
        break;
    case USART_PERIPH_2:
        L_spUSART_buffData = &G_sUSART2_Buffer_data ;
        break;
    case USART_PERIPH_6:
        L_spUSART_buffData = &G_sUSART6_Buffer_data ;
        break;
    default:
        return USART_ERR_BAD_PERIPH;
    }

    // push data into the buffer 
    L_spUSART_buffData->USART_TX_BUFFER[L_spUSART_buffData->txPutPtr++] = A_u8ByteToPush;
    L_spUSART_buffData->txPutPtr = (L_spUSART_buffData->txPutPtr) % MAX_TX_BUFFER_SIZE;
    
    if (!S_u8USART1_TxINT_enabled && cfg->peripheral == USART_PERIPH_1){
        MUSART_EnableInterrupt(cfg->peripheral , USART_TRANSMIT_DATA_REG_EMPTY_INT) ;
        S_u8USART1_TxINT_enabled = 1 ;
    }

    if (!S_u8USART2_TxINT_enabled && cfg->peripheral == USART_PERIPH_2){
        MUSART_EnableInterrupt(cfg->peripheral , USART_TRANSMIT_DATA_REG_EMPTY_INT) ;
        S_u8USART2_TxINT_enabled = 1 ;
    }

    if (!S_u8USART6_TxINT_enabled && cfg->peripheral == USART_PERIPH_6){
        MUSART_EnableInterrupt(cfg->peripheral , USART_TRANSMIT_DATA_REG_EMPTY_INT) ;
        S_u8USART6_TxINT_enabled = 1 ;
    }

    return  USART_OK;
             
}

USART_Status_t MUSART_u8WriteString(USART_Config_t* cfg , u8* A_u8StringToPush){
    while (*A_u8StringToPush != '\0'){
    	MUSART_u8WriteByte(cfg , *(A_u8StringToPush++)) ;
    }
    return USART_OK ;
}

u8* MUSART_u8ReadStringUntil(USART_Config_t* cfg , u8 A_u8TerminatingChar){
    u32 idx = 0 ;
    while (MUSART_u8BytesAvailable(cfg)){
       G_au8StringBuffer[idx] = MUSART_u8ReadByte(cfg) ;
       if ( (G_au8StringBuffer[idx] == A_u8TerminatingChar) || idx >= STRING_BUFFER_MAX_SIZE - 1 ){
            G_au8StringBuffer[idx] = '\0' ;
            break ;
       }
       idx++;
    }
    return G_au8StringBuffer ;
}

s32 MUSART_u32ParseIntBlocking(USART_Config_t* cfg, u32 timeout_ms) {
    s32 result = 0;
    u8 isFirstByte = 1;
    s8 sign = 1;

    // Scale timeout to something based on your system tick
    u32 countdown = timeout_ms * 1000; // if you treat loop ~1µs

    while (countdown--) {
        if (!MUSART_u8BytesAvailable(cfg))
            continue; // wait until data arrives

        u8 byte = MUSART_u8ReadByte(cfg);

        if (isFirstByte) {
            if (byte == '-') {
                sign = -1;
                isFirstByte = 0;
                continue;
            } else if (byte >= '0' && byte <= '9') {
                result = (byte - '0');
                isFirstByte = 0;
                continue;
            } else {
                // Ignore other leading chars
                continue;
            }
        }

        if (byte >= '0' && byte <= '9') {
            result = result * 10 + (byte - '0');
        } else {
            break; // stop on non-digit
        }
    }

    return result * sign;
}

s32 MUSART_u32ParseInt(USART_Config_t* cfg) {
    s32 result = 0;
    u8 isParsing = 0;
    s8 sign = 1;
    u8 isFirstByte = 1;

    while (MUSART_u8BytesAvailable(cfg)) {
        u8 byte = MUSART_u8ReadByte(cfg);

        // Handle first byte (sign or digit)
        if (isFirstByte) {
            isParsing = 1;
            if (byte == '-') {
                sign = -1;
                isFirstByte = 0;
                continue;
            } else if (byte >= '0' && byte <= '9') {
                result = (byte - '0');
                isFirstByte = 0;
                continue;
            } else {
                // Ignore garbage until valid number starts
                continue;
            }
        }

        // Handle digits
        if (byte >= '0' && byte <= '9') {
            result = result * 10 + (byte - '0');
        } else {
            // End of number detected
            s32 finalValue = result * sign;

            // Reset state for next call
            result = 0;
            isFirstByte = 1;
            sign = 1;
            isParsing = 0;

            return finalValue;
        }
    }

    // No full number yet
    return (isParsing ? 0 : -1); 
}

f32 MUSART_f32ParseFloatBlocking(USART_Config_t* cfg, u32 timeout_ms) {
    f32 result = 0.0;
    u8 isFirstByte = 1;
    s8 sign = 1;
    f32 decimalFactor = 0.1;
    u8 inDecimalPart = 0;

    // Scale timeout to something based on your system tick
    u32 countdown = timeout_ms * 1000; // if you treat loop ~1µs

    while (countdown--) {
        if (!MUSART_u8BytesAvailable(cfg))
            continue; // wait until data arrives

        u8 byte = MUSART_u8ReadByte(cfg);

        if (isFirstByte) {
            if (byte == '-') {
                sign = -1;
                isFirstByte = 0;
                continue;
            } else if (byte >= '0' && byte <= '9') {
                result = (byte - '0');
                isFirstByte = 0;
                continue;
            } else {
                // Ignore other leading chars
                continue;
            }
        }

        if (byte >= '0' && byte <= '9') {
            if (inDecimalPart) {
                result += (byte - '0') * decimalFactor;
                decimalFactor *= 0.1;
            } else {
                result = result * 10 + (byte - '0');
            }
        } else if (byte == '.' && !inDecimalPart) {
            inDecimalPart = 1; // start processing decimal part
        } else {
            break; // stop on non-digit/non-decimal point
        }
    }

    return result * sign;
}

USART_Status_t MUSART_vFlush(USART_Config_t* cfg){
    USART_Buffer_t* L_spUSART_buffData = NULL ;
    switch (cfg->peripheral)
    {
    case USART_PERIPH_1:
        L_spUSART_buffData = &G_sUSART1_Buffer_data ;
        break;
    case USART_PERIPH_2:
        L_spUSART_buffData = &G_sUSART2_Buffer_data ;
        break;
    case USART_PERIPH_6:
        L_spUSART_buffData = &G_sUSART6_Buffer_data ;
        break;
    default:
        return USART_ERR_BAD_PERIPH;
    }

    MUSART_DisableInterrupt(cfg->peripheral ,  USART_READ_DATA_READY_INT);
    L_spUSART_buffData->rxGetPtr = L_spUSART_buffData->rxPutPtr ;
    MUSART_EnableInterrupt(cfg->peripheral ,  USART_READ_DATA_READY_INT);
    return USART_OK ;

}
void USART1_IRQHandler(void){

    if (MUSART_GetFlagStatus(USART_PERIPH_1 , USART_FLAG_READ_DATA_READY)){                   // if there is data to read 
        G_sUSART1_Buffer_data.USART_RX_BUFFER[G_sUSART1_Buffer_data.rxPutPtr] = USART1->DR  ;       // reading from the data register clears the flag
        G_sUSART1_Buffer_data.rxPutPtr++ ; 
        G_sUSART1_Buffer_data.rxPutPtr = G_sUSART1_Buffer_data.rxPutPtr % MAX_RX_BUFFER_SIZE ;       // constrain to the range of the buffer 
    }

    if (MUSART_GetFlagStatus(USART_PERIPH_1 , USART_FLAG_TRANSMIT_DATA_REG_EMPTY)){
        if (G_sUSART1_Buffer_data.txPutPtr == G_sUSART1_Buffer_data.txGetPtr )
        {
            // if no new data to send disable the interrupt 
            MUSART_DisableInterrupt(USART_PERIPH_1 , USART_TRANSMIT_DATA_REG_EMPTY_INT) ;
            S_u8USART1_TxINT_enabled = 0 ;
        }

        else {
            USART1->DR = G_sUSART1_Buffer_data.USART_TX_BUFFER[G_sUSART1_Buffer_data.txGetPtr++] ;
            G_sUSART1_Buffer_data.txGetPtr = (G_sUSART1_Buffer_data.txGetPtr) % MAX_TX_BUFFER_SIZE ;
        }
    }
}

void USART2_IRQHandler(void){

    if (MUSART_GetFlagStatus(USART_PERIPH_2 , USART_FLAG_READ_DATA_READY)){                   // if there is data to read
        G_sUSART2_Buffer_data.USART_RX_BUFFER[G_sUSART2_Buffer_data.rxPutPtr] = USART2->DR;       // reading from the data register clears the flag
        G_sUSART2_Buffer_data.rxPutPtr++;
        G_sUSART2_Buffer_data.rxPutPtr = G_sUSART2_Buffer_data.rxPutPtr % MAX_RX_BUFFER_SIZE;       // constrain to the range of the buffer
    }

    if (MUSART_GetFlagStatus(USART_PERIPH_2 , USART_FLAG_TRANSMIT_DATA_REG_EMPTY)){
        if (G_sUSART2_Buffer_data.txPutPtr == G_sUSART2_Buffer_data.txGetPtr )
        {
            // if no new data to send disable the interrupt
            MUSART_DisableInterrupt(USART_PERIPH_2 , USART_TRANSMIT_DATA_REG_EMPTY_INT);
            S_u8USART2_TxINT_enabled = 0;
        }

        else {
            USART2->DR = G_sUSART2_Buffer_data.USART_TX_BUFFER[G_sUSART2_Buffer_data.txGetPtr++];
            G_sUSART2_Buffer_data.txGetPtr = (G_sUSART2_Buffer_data.txGetPtr) % MAX_TX_BUFFER_SIZE;
        }
    }
}


void USART6_IRQHandler(void){

        if (MUSART_GetFlagStatus(USART_PERIPH_6 , USART_FLAG_READ_DATA_READY)){                   // if there is data to read
            G_sUSART6_Buffer_data.USART_RX_BUFFER[G_sUSART6_Buffer_data.rxPutPtr] = USART6->DR;       // reading from the data register clears the flag
            G_sUSART6_Buffer_data.rxPutPtr++;
            G_sUSART6_Buffer_data.rxPutPtr = G_sUSART6_Buffer_data.rxPutPtr % MAX_RX_BUFFER_SIZE;       // constrain to the range of the buffer
        }

        if (MUSART_GetFlagStatus(USART_PERIPH_6 , USART_FLAG_TRANSMIT_DATA_REG_EMPTY)){
            if (G_sUSART6_Buffer_data.txPutPtr == G_sUSART6_Buffer_data.txGetPtr )
            {
                // if no new data to send disable the interrupt
                MUSART_DisableInterrupt(USART_PERIPH_6 , USART_TRANSMIT_DATA_REG_EMPTY_INT);
                S_u8USART6_TxINT_enabled = 0;
            }

            else {
                USART6->DR = G_sUSART6_Buffer_data.USART_TX_BUFFER[G_sUSART6_Buffer_data.txGetPtr++];
                G_sUSART6_Buffer_data.txGetPtr = (G_sUSART6_Buffer_data.txGetPtr) % MAX_TX_BUFFER_SIZE;
            }
        }

    }
