#include "USART_int.h"
#include "USART_cfg.h"
#include "USART_prv.h"

void MUSART_Init(void){
    // enable the usart
    SET_BIT(USART1->CR1 , UE);
    // set word length to 8 bits
    CLR_BIT(USART1->CR1 , M);
    // one stop bit
    USART1->CR2 &= ~(0b11 << STOP);
    // config the baud rate
    USART1->BRR = (162 << 4) | 12 ; // 9600 baud rate
    // 16 times sample rate
    CLR_BIT(USART1->CR1 , OVER8);
    // enable transmitter and receiver
    SET_BIT(USART1->CR1 , TE);
    SET_BIT(USART1->CR1 , RE);
}
void MUSART_SendData(u8 data){
    while (!(USART1->SR & (1 << TXE))) ; // wait until TXE is set
    USART1->DR = data;
}
u8 MUSART_ReceiveData(void){
    while (!(USART1->SR & (1 << RXNE))) ; // wait until RXNE is set
    return (u8)(USART1->DR) ;
}

void MUSART_SendString(const char* str){
    while (*str)
        MUSART_SendData(*str++);
}