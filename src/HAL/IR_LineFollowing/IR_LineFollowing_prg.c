#include "IR_LineFollowing_int.h"
#include "IR_LineFollowing_cfg.h"

IR_Status_t HIR_vInit(IR_LineFollowing_cfg_t* cfg) {

    if (cfg == NULL) {
        return IR_STATUS_ERROR_NULL_PTR;
    }

    cfg->blackLevel = (cfg->sensorType == HIGH_WHEN_LINE_DETECTED) ? 1 : 0;


    for (u8 i = 0; i < NUM_IR_SENSORS; i++) {
        GPIOx_PinConfig_t IR_sensor_pin_cfg = {
            .Port = cfg->IR_ports[i],
            .Pin = cfg->IR_pins[i],
            .Mode = GPIO_MODE_INPUT,
            .PullType = GPIO_PUPD_NONE                                     
        };
        MGPIO_vPinInit(&IR_sensor_pin_cfg);
    }

    return IR_STATUS_OK;
}

IR_Status_t HIR_f32ReadSensors(IR_LineFollowing_cfg_t* cfg, f32* position_out) {

    if (cfg == NULL || position_out == NULL) {
        return IR_STATUS_ERROR_NULL_PTR;
    }

    u8 sensor_values[NUM_IR_SENSORS];
    u8 active_sensor_count = 0;
    f32 weighted_sum = 0.0f; 

    for (u8 i = 0; i < NUM_IR_SENSORS; i++) {
        sensor_values[i] = MGPIO_u8GetPinValue(cfg->IR_ports[i], cfg->IR_pins[i]);
        
        if (sensor_values[i] == cfg->blackLevel) {
            active_sensor_count++;
            weighted_sum += i;
        }
    }
    
    // All sensors are off the line.
    if (active_sensor_count == 0) {
        *position_out = 0.0f; 
        return IR_STATUS_LINE_LOST;
    }

    // All sensors are on the line (e.g., T-junction, cross).
    if (active_sensor_count == NUM_IR_SENSORS) {
        *position_out = 0.0f;  
        return IR_STATUS_INTERSECTION;
    }

    // Normal line tracking.
    f32 calculated_position = weighted_sum / active_sensor_count;

    // Normalize the position to a range of -2.0 to 2.0 
    *position_out = calculated_position - ((NUM_IR_SENSORS - 1) / 2.0f);

    return IR_STATUS_LINE_AQUIRED;
}
