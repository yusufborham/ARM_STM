#include "USART_int.h"
#include "USART_cfg.h"
#include "USART_prv.h"

void MUSART_vBaudRateCalculations(u32 A_u32BaudRateValue ,u8 A_u8SampleRate ,u32 A_u32USART_Fclk,USART_BaudRate_cfg_t* A_sBaudRateCfg);
u8 MUSART_GetFlagStatus(USART_Peripheral_t peripheral ,USART_Flags_t flag) ;
USART_Status_t MUSART_DisableInterrupt(USART_Peripheral_t peripheral, USART_Interrupts_t interrupt);
USART_Status_t MUSART_EnableInterrupt(USART_Peripheral_t peripheral,USART_Interrupts_t interrupt);

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

USART_Status_t MUSART_Init(USART_Config_t* cfg){
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
    USART_BaudRate_cfg_t L_sU1BaudRateCfg;
    MUSART_vBaudRateCalculations(cfg->baudRate , L_u8USART_SampleRate , L_u32USART_Fclk, &L_sU1BaudRateCfg);
    USARTx->BRR = (L_sU1BaudRateCfg.DIV_Mantissa << 4) | (L_sU1BaudRateCfg.DIV_Fraction & 0x0F);

    return USART_OK;
}

USART_Status_t MUSART_SendData(USART_Peripheral_t A_peripheral , u8 data){
    USART_RegDef_t *USARTx = NULL;
    switch (A_peripheral){
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
    while (!MUSART_GetFlagStatus(A_peripheral ,USART_FLAG_TRANSMIT_DATA_REG_EMPTY)) ; // wait until TXE is set
    USARTx->DR = data;
    return USART_OK;
}
u8 MUSART_ReceiveData(USART_Peripheral_t A_peripheral){
    USART_RegDef_t *USARTx = NULL;
    switch (A_peripheral){
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
    while (!MUSART_GetFlagStatus(A_peripheral ,USART_FLAG_READ_DATA_READY)) ; // wait until RXNE is set
    return (u8)(USARTx->DR) ;
}

void MUSART_SendString(USART_Peripheral_t A_peripheral ,const char* str){
    while (*str)
        MUSART_SendData(A_peripheral , *str++);
}

void MUSART_vBaudRateCalculations(u32 A_u32BaudRateValue ,u8 A_u8SampleRate ,u32 A_u32USART_Fclk,USART_BaudRate_cfg_t* A_sBaudRateCfg){
    A_sBaudRateCfg->DIV_Mantissa = (A_u32USART_Fclk) / (A_u8SampleRate * A_u32BaudRateValue);
    u8 A_u8Fraction = (u8) (((A_u32USART_Fclk) % (A_u8SampleRate * A_u32BaudRateValue) * A_u8SampleRate) / (A_u8SampleRate * A_u32BaudRateValue));
    A_sBaudRateCfg->DIV_Fraction = (A_u8SampleRate == 8 ) ? (A_u8Fraction & 0x07) : A_u8Fraction;
}