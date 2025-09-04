#include "MATH_Fn.h"

// u32 MATH_u32floor(f64 num) {
//     return (u32)num;
// }

// u32 MATH_u32ceil(f64 num) {
//     return (u32)(num + 1);
// }

// f64 MATH_f64GetDecimalPart(f64 num) {
//     f64 decimalPart = num - (f64)MATH_u32floor(num);
//     return decimalPart;
// }

s32 atoi(const char* str) {
    s32 result = 0;
    s32 sign = 1;

    if (*str == '-') {
        sign = -1;
        str++;
    }

    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return result * sign;
}

void itoa(s32 number , u8* buffer ){
    u8 isNegative = 0;
    u8 i = 0;

    if (number < 0) {
        isNegative = 1;
        number = -number;
    }

    do {
        buffer[i++] = (number % 10) + '0';
        number /= 10;
    } while (number > 0);

    if (isNegative) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0';

    // Reverse the string
    for (u8 j = 0; j < i / 2; j++) {
        u8 temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
}

void ftoa(f32 number, u8* buffer) {
    s32 integerPart = (s32)number;
    f32 decimalPart = number - (f32)integerPart;

    itoa(integerPart, buffer);

    // Find the end of the integer part
    u8 i = 0;
    while (buffer[i] != '\0') {
        i++;
    }

    buffer[i++] = '.';  // Add decimal point

    // Convert decimal part to string
    for (u8 j = 0; j < 6; j++) {  // Limit to 6 decimal places
        decimalPart *= 10;
        s32 digit = (s32)decimalPart;
        buffer[i++] = digit + '0';
        decimalPart -= digit;
    }

    buffer[i] = '\0';
}
