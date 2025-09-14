#ifndef IR_LINEFOLLOWING_INT_H
#define IR_LINEFOLLOWING_INT_H

#include "../../LIB/STD_TYPES.h"
#include "../GPIO/GPIO_int.h"
#include "IR_LineFollowing_cfg.h"

// --- Type Definitions ---

/**
 * @brief Defines the logic level of the IR sensor when a black line is detected.
 */
typedef enum {
    LOW_WHEN_LINE_DETECTED,  /**< Sensor output is logic LOW on a black line. */
    HIGH_WHEN_LINE_DETECTED  /**< Sensor output is logic HIGH on a black line. */
} IR_SensorType_t;

/**
 * @brief Defines the status codes returned by the driver functions.
 */
typedef enum {
    IR_STATUS_OK,             /**< Operation completed successfully. */
    IR_STATUS_LINE_AQUIRED,   /**< The sensor array has a valid lock on the line. */
    IR_STATUS_LINE_LOST,      /**< No sensors in the array detect the line. */
    IR_STATUS_INTERSECTION,   /**< All sensors detect the line, indicating a possible intersection or junction. */
    IR_STATUS_ERROR_NULL_PTR  /**< A null pointer was passed as an argument. */
} IR_Status_t;

/**
 * @brief Configuration structure for an instance of the IR line-following sensor array.
 * This structure must be initialized by the application and passed to the driver.
 */
typedef struct {
    u8 IR_ports[NUM_IR_SENSORS];  /**< Array of GPIO port IDs for each sensor (e.g., GPIO_A). */
    u8 IR_pins[NUM_IR_SENSORS];   /**< Array of GPIO pin IDs for each sensor (e.g., GPIO_PIN_0). */
    IR_SensorType_t sensorType;   /**< The logic type of the sensors in the array. */
    
    // --- Private Driver State ---
    u8 blackLevel;                /**< Internal state, do not modify. Stores the logic level for "black". */
} IR_LineFollowing_cfg_t;


/**
 * @brief Initializes the GPIO pins for the IR sensor array.
 * * @param cfg Pointer to a user-defined configuration structure for the sensor array.
 * @return IR_Status_t 
 * - IR_STATUS_OK on success.
 * - IR_STATUS_ERROR_NULL_PTR if cfg is NULL.
 */
IR_Status_t HIR_vInit(IR_LineFollowing_cfg_t* cfg);

/**
 * @brief Reads all sensors, calculates the line position, and provides status.
 * This is the primary function to be called by the GNC task.
 * * @param cfg Pointer to the initialized configuration structure.
 * @param position_out Pointer to a float where the calculated line position will be stored.
 * The range is from -2.0 (far left) to +2.0 (far right), with 0.0 being centered.
 * * @return IR_Status_t 
 * - IR_STATUS_LINE_AQUIRED if the line is detected normally.
 * - IR_STATUS_LINE_LOST if no sensors detect the line.
 * - IR_STATUS_INTERSECTION if all sensors detect the line.
 * - IR_STATUS_ERROR_NULL_PTR if a null pointer argument is provided.
 */
IR_Status_t HIR_f32ReadSensors(IR_LineFollowing_cfg_t* cfg, f32* position_out);

#endif /* IR_LINEFOLLOWING_INT_H */
