/*
 * MOTOR_interface.h
 *
 * Created: 21/8/2023 
 *  Author: Arafa Arafa
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_
/*including sections*/
#include "../../MCAL/DIO/DIO_interface.h"




/************************************************************************************************/
/*									Enumerated Datatypes										*/
/************************************************************************************************/

/**
 * @brief Structure for motor configuration.
 *
 * This structure defines the configuration for a motor, including the port and pin numbers.
 */
typedef struct motor_str_config_t {
    dio_enu_port_t port;         /**< Port to which the motor pins are connected. */
    dio_enu_pin_t pin_num1;      /**< Pin number for motor control 1. */
    dio_enu_pin_t pin_num2;      /**< Pin number for motor control 2. */
} motor_str_config_t;

/**
 * @brief Enumeration for motor return states.
 *
 * This enumeration defines the possible return states of motor control functions.
 */
typedef enum motor_enu_return_state_t {
    MOTOR_OK,        /**< Motor control operation successful. */
    MOTOR_NOK        /**< Motor control operation failed. */
} motor_enu_return_state_t;

	

/************************************************************************************************/
/*									Function Prototypes     									*/
/************************************************************************************************/

/**
 * @brief Initialize a motor based on the provided configuration.
 *
 * This function initializes a motor based on the provided motor configuration. It sets the specified pins of the specified port
 * as output pins, configuring them to control the motor's operation.
 *
 * @param ptr_str_motor_config Pointer to the motor configuration structure.
 * @return The initialization state of the motor.
 *         - MOTOR_OK: Motor initialized successfully.
 *         - MOTOR_NOK: Motor initialization failed due to pin initialization errors.
 *
 * @note The motor configuration structure contains the port and pin information for controlling the motor.
 */
motor_enu_return_state_t MOTOR_INIT(const motor_str_config_t *ptr_str_motor_config);


/**
 * @brief Turn the motor forward based on the provided configuration.
 *
 * This function controls the motor to rotate in the forward direction by setting the corresponding pins of the specified port.
 *
 * @param ptr_str_motor_config Pointer to the motor configuration structure.
 * @return The state of the motor operation.
 *         - MOTOR_OK: Motor moved forward successfully.
 *         - MOTOR_NOK: Motor forward operation failed due to pin write errors.
 *
 * @note The motor configuration structure contains the port and pin information for controlling the motor.
 */
motor_enu_return_state_t MOTOR_FORWARD(const motor_str_config_t* ptr_str_motor_config);


/**
 * @brief Turn the motor backward based on the provided configuration.
 *
 * This function controls the motor to rotate in the backward direction by setting the corresponding pins of the specified port.
 *
 * @param ptr_str_motor_config Pointer to the motor configuration structure.
 * @return The state of the motor operation.
 *         - MOTOR_OK: Motor moved backward successfully.
 *         - MOTOR_NOK: Motor backward operation failed due to pin write errors.
 *
 * @note The motor configuration structure contains the port and pin information for controlling the motor.
 */
motor_enu_return_state_t MOTOR_BACKWARD(const motor_str_config_t* ptr_str_motor_config);


/**
 * @brief Stop the motor based on the provided configuration.
 *
 * This function stops the motor by setting both pins of the specified port to a low level.
 *
 * @param ptr_str_motor_config Pointer to the motor configuration structure.
 * @return The state of the motor operation.
 *         - MOTOR_OK: Motor stopped successfully.
 *         - MOTOR_NOK: Motor stop operation failed due to pin write errors.
 *
 * @note The motor configuration structure contains the port and pin information for controlling the motor.
 */
motor_enu_return_state_t MOTOR_STOP(const motor_str_config_t* ptr_str_motor_config);





#endif /* MOTOR_H_ */