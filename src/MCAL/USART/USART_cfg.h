#ifndef USART_CFG_H
#define USART_CFG_H

/* Configuration settings for USART */

#define DEFAULT_SAMPLE_RATE 16 
#define DEFAULT_USART_CLK 25000000UL

#define MAX_TX_BUFFER_SIZE  256
#define MAX_RX_BUFFER_SIZE  256

#define STRING_BUFFER_MAX_SIZE 256

#define OVERWRITE_OLD_DATA_TX 1  // if set to 1, new data will overwrite old data when buffer is full. If set to 0, new data will be discarded when buffer is full.
#define OVERWRITE_OLD_DATA_RX 1  // if set to 1, new data will overwrite old data when buffer is full. If set to 0, new data will be discarded when buffer is full.

#endif /* USART_CFG_H */