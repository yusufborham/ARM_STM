#ifndef USART_INT_H
#define USART_INT_H

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Delay.h"

void MUSART_Init(void);
void MUSART_SendData(u8 data);
u8 MUSART_ReceiveData(void);
void MUSART_SendString(const char* str);

#endif /* USART_INT_H */