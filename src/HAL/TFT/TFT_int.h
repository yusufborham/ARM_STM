#ifndef TFT_INT_H
#define TFT_INT_H

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Delay.h"

#include "../../MCAL/GPIO/GPIO_int.h"
#include "../../MCAL/GPIO/GPIO_prv.h"

#include "../../MCAL/RCC/RCC_int.h"
#include "../../MCAL/RCC/RCC_prv.h"

#include "../../MCAL/SYSTICK/SYSTICK_int.h"
#include "../../MCAL/SYSTICK/SYSTICK_prv.h"

#include "../../MCAL/EXTI/EXTI_int.h"
#include "../../MCAL/EXTI/EXTI_prv.h"

#include "../../MCAL/NVIC/NVIC_int.h"
#include "../../MCAL/NVIC/NVIC_prv.h"

#include "../../MCAL/SPI/SPI_int.h"

 

#include "../../MCAL/SYSCFG/SYSCFG_int.h"

#include "font.h"

// New color definitions use for all my libraries
#define TFT_BLACK       0x0000      /*   0,   0,   0 */
#define TFT_NAVY        0x000F      /*   0,   0, 128 */
#define TFT_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define TFT_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define TFT_MAROON      0x7800      /* 128,   0,   0 */
#define TFT_PURPLE      0x780F      /* 128,   0, 128 */
#define TFT_OLIVE       0x7BE0      /* 128, 128,   0 */
#define TFT_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define TFT_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define TFT_BLUE        0x001F      /*   0,   0, 255 */
#define TFT_GREEN       0x07E0      /*   0, 255,   0 */
#define TFT_CYAN        0x07FF      /*   0, 255, 255 */
#define TFT_RED         0xF800      /* 255,   0,   0 */
#define TFT_MAGENTA     0xF81F      /* 255,   0, 255 */
#define TFT_YELLOW      0xFFE0      /* 255, 255,   0 */
#define TFT_WHITE       0xFFFF      /* 255, 255, 255 */
#define TFT_ORANGE      0xFD20      /* 255, 165,   0 */
#define TFT_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define TFT_PINK        0xF81F

typedef enum {
    PIXEL_FORMAT_12BIT ,
    PIXEL_FORMAT_16BIT ,
    PIXEL_FORMAT_18BIT
} HTFT_pixelFormat_t;

typedef enum {
    SCREEN_SIZE_128X160 ,
    SCREEN_SIZE_128X128 ,
    SCREEN_SIZE_240X320
} HTFT_screenSize_t;

typedef struct {
     const u16 *data;
     u16 width;
     u16 height;
     u8 dataSize;
} tImage;

#include "TFT_prv.h"

void HTFT_vInit(HTFT_cfg_t* cfg);
void HTFT_vSet_Xposition(u8 X_start , u8 X_end );
void HTFT_vSet_Yposition(u8 Y_start , u8 Y_end );
void HTFT_vDrawImage(const tImage* image, u8 x, u8 y);
void HTFT_vDrawRect(u8 x, u8 y, u8 width, u8 height, u16 color);
void HTFT_vFillBackground(u16 color);
void HTFT_vDrawAsciiChar(u8 x_start, u8 y_start , u8 character, u16 color, u16 bgColor) ;
void HTFT_vWriteString(u8 x_start, u8 y_start , u8* str ,u16 color, u16 bgColor );
// Your code here

#endif