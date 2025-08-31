#ifndef LEDMATRIX_INT_H
#define LEDMATRIX_INT_H

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/GPIO/gpio_int.h"
#include "../../MCAL/GPIO/gpio_prv.h"

#include "../../MCAL/RCC/rcc_int.h"
#include "../../MCAL/RCC/rcc_prv.h"

#include "../../MCAL/SYSTICK/systick_int.h"
#include "../../MCAL/SYSTICK/systick_prv.h"

#include "../../HAL/STP/STP_int.h"
#include "../../LIB/Delay.h"
// Your code here

typedef struct {
    u8 Pin ;
}Pin_cfg_t;

typedef enum{
    LED_MATRIX_NORMAL_MODE , 
    LED_MATRIX_STP_MODE 
}LedMatrix_Mode_t ;
typedef struct {
    LedMatrix_Mode_t Mode ;
    union {
        struct {
                u8 Port1;
                Pin_cfg_t RowPins[8];
                u8 Port2;
                Pin_cfg_t ColPins[8];
        }normalConfig; 

        STP_Config_t stpConfig;
    } Config;

} LedMatrix_config_t;

/*
 * @brief Initialize the GPIO pins for the LED matrix.
 * @param LedMatrix_cfg Pointer to the LED matrix configuration structure.
 */
void HLedMatrix_vInitPins(LedMatrix_config_t* LedMatrix_cfg);

/*
 * @brief Display a specific row on the LED matrix.
 * @param LedMatrix_cfg Pointer to the LED matrix configuration structure.
 * @param row The row data to display (8 bits).
 */
void HLedMatrix_vDisplayRow(LedMatrix_config_t* LedMatrix_cfg, u8 row);

/*
 * @brief Display a specific column on the LED matrix.
 * @param LedMatrix_cfg Pointer to the LED matrix configuration structure.
 * @param col The column data to display (8 bits).
 */
void HLedMatrix_vDisplayColumn(LedMatrix_config_t* LedMatrix_cfg, u8 col);

/*
 * @brief Display a specific frame on the LED matrix.
 * @param LedMatrix_cfg Pointer to the LED matrix configuration structure.
 * @param A_au8FrameData Array containing the frame data (8 rows).
 */
void HLedMatrix_vDisplayFrame(LedMatrix_config_t* LedMatrix_cfg , u8 A_au8FrameData[8]);

/*
 * @brief Display a specific frame on the LED matrix.
 * @param LedMatrix_cfg Pointer to the LED matrix configuration structure.
 * @param A_au8FrameData Array containing the frame data (8 rows).
 */
void HLedMatrix_vDisplayFrame(LedMatrix_config_t* LedMatrix_cfg , u8 A_au8FrameData[8]);

/*
 * @brief Display a specific frame on the LED matrix for a given duration.
 * @param A_u32DurationMs Duration to display the frame (in milliseconds).
 * @param LedMatrix_cfg Pointer to the LED matrix configuration structure.
 * @param A_au8FrameData Array containing the frame data (8 rows).
 */
void HLedMatrix_vDisplayFrameFor(u32 A_u32DurationMs , LedMatrix_config_t* LedMatrix_cfg , u8 A_au8FrameData[8]);

#endif // LEDMATRIX_INT_H
