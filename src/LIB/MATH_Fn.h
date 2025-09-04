#ifndef MATH_FN_H
#define MATH_FN_H

#include "STD_TYPES.h"

u32 MATH_u32floor(f64 num);
u32 MATH_u32ceil(f64 num);
f64 MATH_f64GetDecimalPart(f64 num);
void itoa(s32 number , u8* buffer );
s32 atoi(const char* str) ;
void ftoa(f32 number, u8* buffer);

#endif /* MATH_FN_H */
