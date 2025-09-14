#include "USART_prv.h"
#include "USART_int.h"
#include "USART_cfg.h"

#include "../NVIC/NVIC_int.h"
#include "../SYSTICK/SYSTICK_int.h"


static USART_parsingIntStatus_t G_aUSART_parsingStates[USART_NUMBER] = {0};
static USART_Buffer_t G_aUSART_Buffer_data[USART_NUMBER] = {0};
static USART_InterruptStatus_t G_aUSART_InterruptStatus[USART_NUMBER] = {0};
static USART_StringFunctionStatus_t G_aUSART_StringFunStatus[USART_NUMBER] = {0} ;

// ... Other static variables and functions from your driver ...
static USART_StringParseStatus_t G_aUSART_StringParseStatus[USART_NUMBER] = {{0}};

USART_Status_t USART_vHandlerRoutine(USART_Peripheral_t thisID);
void MUSART_vBaudRateCalculations(u32 A_u32BaudRateValue ,u8 A_u8SampleRate ,u32 A_u32USART_Fclk,USART_BaudRate_cfg_t* A_sBaudRateCfg);
static inline USART_RegDef_t* MUSART_pGetRegDef(USART_Peripheral_t peripheral) ;
static inline u8 MUSART_GetFlagStatus(USART_Peripheral_t peripheral ,USART_Flags_t flag) ;
static inline USART_Status_t MUSART_DisableInterrupt(USART_Peripheral_t peripheral, USART_Interrupts_t interrupt);
static inline USART_Status_t MUSART_EnableInterrupt(USART_Peripheral_t peripheral,USART_Interrupts_t interrupt);
static inline void MUSART_vEnableNVIC(USART_Peripheral_t peripheral);
static inline void MUSART_vDisableNVIC(USART_Peripheral_t peripheral) ;// A single, private helper to rule them all


static inline USART_RegDef_t* MUSART_pGetRegDef(USART_Peripheral_t peripheral) {
    if (peripheral == USART_PERIPH_1) return USART1;
    if (peripheral == USART_PERIPH_2) return USART2;
    if (peripheral == USART_PERIPH_6) return USART6;
    return NULL;
}

static inline u8 MUSART_GetFlagStatus(USART_Peripheral_t peripheral, USART_Flags_t flag){
    USART_RegDef_t* USARTx = MUSART_pGetRegDef(peripheral);
    if (USARTx == NULL) return 0;

    return (USARTx->SR & (1 << flag)) ? 1 : 0;
}

static inline USART_Status_t MUSART_EnableInterrupt(USART_Peripheral_t peripheral , USART_Interrupts_t interrupt){
    USART_RegDef_t* USARTx = MUSART_pGetRegDef(peripheral);
    if (USARTx == NULL) return USART_ERR_BAD_PERIPH;
    SET_BIT(USARTx->CR1, interrupt);
    return USART_OK;
}

static inline USART_Status_t MUSART_DisableInterrupt(USART_Peripheral_t peripheral, USART_Interrupts_t interrupt) {
    USART_RegDef_t* USARTx = MUSART_pGetRegDef(peripheral);
    if (USARTx == NULL) return USART_ERR_BAD_PERIPH;
    CLR_BIT(USARTx->CR1, interrupt);
    return USART_OK;
}

void MUSART_vBaudRateCalculations(u32 A_u32BaudRateValue ,u8 A_u8SampleRate ,u32 A_u32USART_Fclk,USART_BaudRate_cfg_t* A_sBaudRateCfg){
    A_sBaudRateCfg->DIV_Mantissa = (A_u32USART_Fclk) / (A_u8SampleRate * A_u32BaudRateValue);
    u8 A_u8Fraction = (u8) (((A_u32USART_Fclk) % (A_u8SampleRate * A_u32BaudRateValue) * A_u8SampleRate) / (A_u8SampleRate * A_u32BaudRateValue));
    A_sBaudRateCfg->DIV_Fraction = (A_u8SampleRate == 8 ) ? (A_u8Fraction & 0x07) : A_u8Fraction;
}

static inline void MUSART_vEnableNVIC(USART_Peripheral_t peripheral){
    switch (peripheral) {
        case USART_PERIPH_1:
            MNVIC_vEnableInterrupt(USART1_IRQn);
            break;
        case USART_PERIPH_2:
            MNVIC_vEnableInterrupt(USART2_IRQn);
            break;
        case USART_PERIPH_6:
            MNVIC_vEnableInterrupt(USART6_IRQn);
            break;
        default:
            // Invalid peripheral, do nothing or handle error
            break;
    }
}

static inline void MUSART_vDisableNVIC(USART_Peripheral_t peripheral){
    switch (peripheral) {
        case USART_PERIPH_1:
            MNVIC_vDisableInterrupt(USART1_IRQn);
            break;
        case USART_PERIPH_2:
            MNVIC_vDisableInterrupt(USART2_IRQn);
            break;
        case USART_PERIPH_6:
            MNVIC_vDisableInterrupt(USART6_IRQn);
            break;
        default:
            // Invalid peripheral, do nothing or handle error
            break;
    }
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

    USART_RegDef_t* USARTx = MUSART_pGetRegDef(cfg->peripheral);
    if (USARTx == NULL) return USART_ERR_BAD_PERIPH;

    MUSART_vEnableNVIC(cfg->peripheral);

    MSYSTICK_vEnableBckgroundMillis();
    // ENABLE USART
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


u8 MUSART_u8ReadByte(USART_Peripheral_t A_thisID){
    if (A_thisID < USART_PERIPH_1 || A_thisID > USART_PERIPH_6) return USART_ERR_BAD_PERIPH ;

    USART_Buffer_t* L_spUSART_buffData = &G_aUSART_Buffer_data[A_thisID] ;
    u8 L_u8readData = 0 ;
    
    if (L_spUSART_buffData->rxGetPtr == L_spUSART_buffData->rxPutPtr )
        return 0 ;
    
    else {
        MUSART_vDisableNVIC(A_thisID);
         // critical section: disable RXNE interrupt only
        L_u8readData = L_spUSART_buffData->USART_RX_BUFFER[L_spUSART_buffData->rxGetPtr++];
        L_spUSART_buffData->rxGetPtr =(L_spUSART_buffData->rxGetPtr ) % USART_MAX_RX_BUFFER_SIZE ;
        MUSART_vEnableNVIC(A_thisID);
         // re-enable RXNE interrupt
        return L_u8readData ;
    }            
}
u8 MUSART_u8BytesAvailable(USART_Peripheral_t A_thisID){
    if (A_thisID < USART_PERIPH_1 || A_thisID > USART_PERIPH_6) return USART_ERR_BAD_PERIPH ;
    USART_Buffer_t* L_spUSART_buffData = &G_aUSART_Buffer_data[A_thisID] ;

    return (L_spUSART_buffData->rxPutPtr - L_spUSART_buffData->rxGetPtr + USART_MAX_RX_BUFFER_SIZE) % USART_MAX_RX_BUFFER_SIZE;
}

USART_Status_t MUSART_u8WriteByte(USART_Peripheral_t A_thisID , u8 A_u8ByteToPush) {
    if (A_thisID < USART_PERIPH_1 || A_thisID > USART_PERIPH_6) return USART_ERR_BAD_PERIPH;
    if (A_u8ByteToPush == '\0') return USART_OK; // ignore null char

    USART_Buffer_t* L_spUSART_buffData = &G_aUSART_Buffer_data[A_thisID];

    u32 nextPtr = (L_spUSART_buffData->txPutPtr + 1) % USART_MAX_TX_BUFFER_SIZE;
    if (nextPtr == L_spUSART_buffData->txGetPtr) {
        return USART_ERR_BUFFER_FULL; // no space
    }

    // critical section: disable TXE interrupt only
    MUSART_vDisableNVIC(A_thisID);

    L_spUSART_buffData->USART_TX_BUFFER[L_spUSART_buffData->txPutPtr] = A_u8ByteToPush;
    L_spUSART_buffData->txPutPtr = nextPtr;

    MUSART_EnableInterrupt(A_thisID, USART_TRANSMIT_DATA_REG_EMPTY_INT);
    MUSART_vEnableNVIC(A_thisID);

    G_aUSART_InterruptStatus[A_thisID].Tx_enabled = 1;

    return USART_OK;
}

USART_Status_t MUSART_u8WriteString(USART_Peripheral_t A_thisID ,const u8* A_u8StringToPush){
    while (*A_u8StringToPush != '\0'){
    	USART_Status_t status = MUSART_u8WriteByte(A_thisID , *(A_u8StringToPush++)) ;
        if (status != USART_OK) {
            if (status == USART_ERR_BUFFER_FULL ) {
                #if OVERWRITE_OLD_DATA_TX
                    continue;
                #else 
                    return USART_ERR_BUFFER_FULL ;
                #endif
            }
            else 
                return status ;
        }
    }
    return USART_OK ;
}

USART_Status_t MUSART_u8ReadStringUntil(USART_Peripheral_t A_thisID, u8 *A_u8pStringBuffer, u32 A_u32BufferSize, u8 A_u8TerminatingChar) {
    // --- Precondition Checks (Safety) ---
    if (A_u8pStringBuffer == NULL || A_u32BufferSize == 0) {
        return INVALID_ARGUMENT;
    }
    if (A_thisID >= USART_NUMBER) { // Use zero-indexed check
        return INVALID_ARGUMENT;
    }

    // Use a dedicated, persistent state for this function
    USART_StringParseStatus_t* state = &G_aUSART_StringParseStatus[A_thisID];

    // --- Non-Blocking Read Loop (Processes available data only) ---
    while (MUSART_u8BytesAvailable(A_thisID)) {
        // Check for buffer overflow BEFORE reading a new byte
        if (state->idx >= A_u32BufferSize - 1) {
            // Buffer is full. Discard further data until reset.
            state->overflow = 1; // Mark overflow state
            (void)MUSART_u8ReadByte(A_thisID); // Read byte to discard it
            continue; // Get next byte
        }

        u8 byte = MUSART_u8ReadByte(A_thisID);

        if (byte == A_u8TerminatingChar) {
            // End of line found.
            A_u8pStringBuffer[state->idx] = '\0'; // Null-terminate the string

            // Store the final status before resetting the state
            USART_Status_t final_status = state->overflow ? USART_STRING_BUFFER_OVF : DONE_PARSING;

            // Reset state for the next call
            state->idx = 0;
            state->overflow = 0;
            
            return final_status;
        } else {
            // Regular character, add it to the buffer
            A_u8pStringBuffer[state->idx++] = byte;
        }
    }

    // If we exit the loop, it means no more bytes are available right now.
    return STILL_PARSING;
}

/* the serial read till terminal pattern was inspred from this C code i have written 

#include <stdio.h>

int main(void){
    char c = 0 ;
    char comp[] = "OK" ;
    char buffer[50];
    int idx = 0 ;
    int jdx = 0 ;
    int entered = 0 ;
    int startIdx = 0 ;
    int exit = 0 ;
    while ( (c = getchar() ) != '\n' ){
        if (c == comp[jdx]) {
            if (!entered){
                startIdx = idx ;
                entered = 1 ;
            }   
            jdx++ ;
            if (comp[jdx] == '\0') 
                exit = 1 ;
        }
        else {
            if (entered) {
                if (c == comp[0]) {
                    jdx = 1 ;
                    startIdx = idx ;
                }
                else {
                    jdx = 0 ;
                    entered = 0 ;
                    startIdx = 0 ;
                }
            }
        }

        buffer[idx++] = c ; 

        if (exit){
            buffer[startIdx] = '\0' ;
            break ;
        }           
    }

    printf("String: %s\n", buffer) ;

    return 0 ;
}
*/
USART_Status_t MUSART_u8ReadStringUntilBufferPatern(USART_Peripheral_t A_thisID, u8 *A_u8pStringBuffer, u32 A_u32BufferSize ,const u8 *A_u8pTerminatingBuffer){
    if (A_thisID < USART_PERIPH_1 || A_thisID > USART_PERIPH_6) return USART_ERR_BAD_PERIPH ;
    if (A_u8pStringBuffer == NULL || A_u8pTerminatingBuffer == NULL) return INVALID_ARGUMENT ;
    if (A_u32BufferSize == 0 || A_u32BufferSize > STRING_BUFFER_MAX_SIZE) return INVALID_BUFFER_SIZE ;
    
    volatile USART_StringFunctionStatus_t* L_spUSART_stringFunStatus = &G_aUSART_StringFunStatus[A_thisID] ;
    while (MUSART_u8BytesAvailable(A_thisID)){
        u8 L_u8ByteRead = MUSART_u8ReadByte(A_thisID) ;
        if (L_u8ByteRead == A_u8pTerminatingBuffer[L_spUSART_stringFunStatus->jdx] ){
            // for the first iteration we check if the read character equals the first element in the terminating string buffered
            if (!L_spUSART_stringFunStatus->entered){                                               // if we did not enter a part of a string ( first time or maybe a wrong start )
                L_spUSART_stringFunStatus->startIdx = L_spUSART_stringFunStatus->idx ;      // register the begining of the pattern in the main sent buffer
                L_spUSART_stringFunStatus->entered = 1 ;
            }
            // update the index
            L_spUSART_stringFunStatus->jdx++ ;
            // if the next character in the array is \0 m3naha eno 5las n exit b2a
            if (A_u8pTerminatingBuffer[L_spUSART_stringFunStatus->jdx] == '\0')
                L_spUSART_stringFunStatus->exit = 1 ;
        }
        
        // if not equal first check if we were inside a pattern thus it was a false beginning we reset the values 
        else {
            if (L_spUSART_stringFunStatus->entered){
                if (L_u8ByteRead == A_u8pTerminatingBuffer[0]) {
                    // if the current character equals the first character in the pattern we consider it as a new begining
                    L_spUSART_stringFunStatus->startIdx = L_spUSART_stringFunStatus->idx ;
                    L_spUSART_stringFunStatus->jdx = 1 ; // we set it to one because we already matched the first character
                }
                else {
                    // if not we just reset all the values
                    L_spUSART_stringFunStatus->entered = 0 ;
                    L_spUSART_stringFunStatus->jdx = 0 ;
                    L_spUSART_stringFunStatus->startIdx = 0 ;
                }
            }
        }
        
        // check for buffer overflow
        if (L_spUSART_stringFunStatus->idx >= A_u32BufferSize - 1){
            L_spUSART_stringFunStatus->idx = 0 ;
            L_spUSART_stringFunStatus->jdx = 0 ;
            L_spUSART_stringFunStatus->entered = 0 ;
            L_spUSART_stringFunStatus->startIdx = 0 ;
            L_spUSART_stringFunStatus->exit = 0 ;

            return USART_STRING_BUFFER_OVF ;
        }

        // after all push the byte value in the buffer
        A_u8pStringBuffer[L_spUSART_stringFunStatus->idx++] = L_u8ByteRead;

        // if we are to exit ( we found the pattern )
        if (G_aUSART_StringFunStatus[A_thisID].exit){
            // reset all the values for the next call
            A_u8pStringBuffer[L_spUSART_stringFunStatus->startIdx] = '\0' ;
            L_spUSART_stringFunStatus->idx = 0 ;
            L_spUSART_stringFunStatus->jdx = 0 ;
            L_spUSART_stringFunStatus->entered = 0 ;
            L_spUSART_stringFunStatus->startIdx = 0 ;
            L_spUSART_stringFunStatus->exit = 0 ;

            return DONE_PARSING ;
        }
    }

    return STILL_PARSING ;
}

USART_Status_t MUSART_u32ParseIntBlocking(USART_Peripheral_t A_thisID,  s32* A_ps32Result,  u32 timeout_ms) {

    if (A_thisID < USART_PERIPH_1 || A_thisID > USART_PERIPH_6) return USART_ERR_BAD_PERIPH ;
    if (A_ps32Result == NULL) return INVALID_ARGUMENT ;

    USART_parsingIntStatus_t* L_spUSART_parsingStatus = &G_aUSART_parsingStates[A_thisID] ;
   

    L_spUSART_parsingStatus->result = 0;
    L_spUSART_parsingStatus->sign = 1;
    L_spUSART_parsingStatus->isFirstByte = 1;

    // Scale timeout to something based on your system tick
    L_spUSART_parsingStatus->entryTime = MSYSTICK_millis(); // if you treat loop ~1µs

    while (MSYSTICK_millis() - L_spUSART_parsingStatus->entryTime < timeout_ms) {
        if (!MUSART_u8BytesAvailable(A_thisID))
            continue; // wait until data arrives

        u8 byte = MUSART_u8ReadByte(A_thisID);

        if (L_spUSART_parsingStatus->isFirstByte) {
            if (byte == '-') {
                L_spUSART_parsingStatus->sign = -1;
                L_spUSART_parsingStatus->isFirstByte = 0;
                continue;
            } else if (byte >= '0' && byte <= '9') {
                L_spUSART_parsingStatus->result = (byte - '0');
                L_spUSART_parsingStatus->isFirstByte = 0;
                continue;
            } else {
                // Ignore other leading chars
                continue;
            }
        }

        if (byte >= '0' && byte <= '9') {
            L_spUSART_parsingStatus->result = L_spUSART_parsingStatus->result * 10 + (byte - '0');
        } else {
            break; // stop on non-digit
        }
    }
    if ((MSYSTICK_millis() - L_spUSART_parsingStatus->entryTime + timeout_ms ) >= 0)
        return USART_ERR_TIMEOUT; // timeout occurred

    *A_ps32Result = L_spUSART_parsingStatus->result * L_spUSART_parsingStatus->sign;    

    return USART_OK ;
}

USART_Status_t MUSART_u8ParseInt(USART_Peripheral_t A_thisID , s32* A_ps32Result) {
    if (A_thisID < USART_PERIPH_1 || A_thisID > USART_PERIPH_6) return USART_ERR_BAD_PERIPH ;

    if (A_ps32Result == NULL) return INVALID_ARGUMENT ;

    USART_parsingIntStatus_t* L_spUSART_parsingStatus = &G_aUSART_parsingStates[A_thisID] ;

    while (MUSART_u8BytesAvailable(A_thisID)) {
        u8 byte = MUSART_u8ReadByte(A_thisID);

        // Handle first byte (sign or digit)
        if (L_spUSART_parsingStatus->isFirstByte) {
            L_spUSART_parsingStatus->isParsing = 1;
            if (byte == '-') {
                L_spUSART_parsingStatus->sign = -1;
                L_spUSART_parsingStatus->isFirstByte = 0;
                continue;
            } else if (byte >= '0' && byte <= '9') {
                L_spUSART_parsingStatus->result = (byte - '0');
                L_spUSART_parsingStatus->isFirstByte = 0;
                continue;
            } else {
                // Ignore garbage until valid number starts
                continue;
            }
        }

        // Handle digits
        if (byte >= '0' && byte <= '9') {
            L_spUSART_parsingStatus->result = L_spUSART_parsingStatus->result * 10 + (byte - '0');
        } else {
            // End of number detected
            *A_ps32Result = L_spUSART_parsingStatus->result * L_spUSART_parsingStatus->sign;

            // Reset state for next call
            L_spUSART_parsingStatus->result = 0;
            L_spUSART_parsingStatus->isFirstByte = 1;
            L_spUSART_parsingStatus->sign = 1;
            L_spUSART_parsingStatus->isParsing = 0;
            return DONE_PARSING ;
        }
    }

    // No full number yet
    return (L_spUSART_parsingStatus->isParsing ? STILL_PARSING : DONE_PARSING);
}

// f32 MUSART_f32ParseFloatBlocking(USART_Peripheral_t A_thisID, u32 timeout_ms) {
//     f32 result = 0.0;
//     u8 isFirstByte = 1;
//     s8 sign = 1;
//     f32 decimalFactor = 0.1;
//     u8 inDecimalPart = 0;

//     // Scale timeout to something based on your system tick
//     u32 countdown = timeout_ms * 1000; // if you treat loop ~1µs

//     while (countdown--) {
//         if (!MUSART_u8BytesAvailable(A_thisID))
//             continue; // wait until data arrives

//         u8 byte = MUSART_u8ReadByte(A_thisID);

//         if (isFirstByte) {
//             if (byte == '-') {
//                 sign = -1;
//                 isFirstByte = 0;
//                 continue;
//             } else if (byte >= '0' && byte <= '9') {
//                 result = (byte - '0');
//                 isFirstByte = 0;
//                 continue;
//             } else {
//                 // Ignore other leading chars
//                 continue;
//             }
//         }

//         if (byte >= '0' && byte <= '9') {
//             if (inDecimalPart) {
//                 result += (byte - '0') * decimalFactor;
//                 decimalFactor *= 0.1;
//             } else {
//                 result = result * 10 + (byte - '0');
//             }
//         } else if (byte == '.' && !inDecimalPart) {
//             inDecimalPart = 1; // start processing decimal part
//         } else {
//             break; // stop on non-digit/non-decimal point
//         }
//     }

//     return result * sign;
// }

USART_Status_t MUSART_vFlush(USART_Peripheral_t A_thisID){
    
     if (A_thisID < USART_PERIPH_1 || A_thisID > USART_PERIPH_6) return USART_ERR_BAD_PERIPH ;
    USART_Buffer_t* L_spUSART_buffData = &G_aUSART_Buffer_data[A_thisID] ;

    MUSART_DisableInterrupt(A_thisID ,  USART_READ_DATA_READY_INT);
    L_spUSART_buffData->rxGetPtr = L_spUSART_buffData->rxPutPtr ;
    MUSART_EnableInterrupt(A_thisID ,  USART_READ_DATA_READY_INT);
    return USART_OK ;

}

USART_Status_t USART_vHandlerRoutine(USART_Peripheral_t thisID){

    USART_RegDef_t* USARTx = NULL;

    switch (thisID) {
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

     if (MUSART_GetFlagStatus(thisID , USART_FLAG_READ_DATA_READY)){                   // if there is data to read
        G_aUSART_Buffer_data[thisID].USART_RX_BUFFER[G_aUSART_Buffer_data[thisID].rxPutPtr] = USARTx->DR  ;       // reading from the data register clears the flag
        G_aUSART_Buffer_data[thisID].rxPutPtr++ ;
        G_aUSART_Buffer_data[thisID].rxPutPtr = G_aUSART_Buffer_data[thisID].rxPutPtr % USART_MAX_RX_BUFFER_SIZE ;       // constrain to the range of the buffer
    }

    if (MUSART_GetFlagStatus(thisID , USART_FLAG_TRANSMIT_DATA_REG_EMPTY)){
        if (G_aUSART_Buffer_data[thisID].txPutPtr == G_aUSART_Buffer_data[thisID].txGetPtr )
        {
            // if no new data to send disable the interrupt
            MUSART_DisableInterrupt(thisID , USART_TRANSMIT_DATA_REG_EMPTY_INT) ;
            G_aUSART_InterruptStatus[thisID].Tx_enabled = 0 ;
        }

        else {
            USARTx->DR = G_aUSART_Buffer_data[thisID].USART_TX_BUFFER[G_aUSART_Buffer_data[thisID].txGetPtr++] ;
            G_aUSART_Buffer_data[thisID].txGetPtr = (G_aUSART_Buffer_data[thisID].txGetPtr) % USART_MAX_TX_BUFFER_SIZE ;
        }
    }
    return USART_OK ;
}

void USART1_IRQHandler(void){
    USART_vHandlerRoutine(USART_PERIPH_1) ;    
}

void USART2_IRQHandler(void){
    USART_vHandlerRoutine(USART_PERIPH_2) ;   
}

void USART6_IRQHandler(void){
    USART_vHandlerRoutine(USART_PERIPH_6) ;
}
