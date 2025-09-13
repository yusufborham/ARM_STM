/*
 * Fonts.h
 *
 *  Created on: Sep 2, 2025
 *      Author: drago
 */

#ifndef HAL_FONTS_FONTS_H_
#define HAL_FONTS_FONTS_H_

#include "../../LIB/STD_TYPES.h"


typedef struct {
    const u8 width;
    const u8 height;
    const u16 *data;   // pointer to font bitmap
} FontDef;




extern FontDef Font_16x26;
extern  FontDef Arial28x28;
extern  FontDef Arial12x12;
extern FontDef Font_8x13;

#endif /* HAL_FONTS_FONTS_H_ */