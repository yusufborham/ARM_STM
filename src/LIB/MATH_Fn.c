#include "MATH_Fn.h"

u32 MATH_u32floor(f64 num) {
    return (u32)num;
}

u32 MATH_u32ceil(f64 num) {
    return (u32)(num + 1);
}

f64 MATH_f64GetDecimalPart(f64 num) {
    f64 decimalPart = num - (f64)MATH_u32floor(num);
    return decimalPart;
}