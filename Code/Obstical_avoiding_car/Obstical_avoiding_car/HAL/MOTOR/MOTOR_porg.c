/*
 * MOTOR_prog.c
 *
 * Created: 21/8/2023 
 *  Author: Arafa Arafa
 */ 

/*including sections*/
#include "MOTOR_interface.h"



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
motor_enu_return_state_t MOTOR_INIT(const motor_str_config_t *ptr_str_motor_config)
{
	motor_enu_return_state_t enu_return_state = MOTOR_OK; 
	dio_enu_return_state_t enu_return_state_pin_1 = DIO_init(ptr_str_motor_config->port,ptr_str_motor_config->pin_num1,DIO_PIN_OUTPUT);
	dio_enu_return_state_t enu_return_state_pin_2 = DIO_init(ptr_str_motor_config->port,ptr_str_motor_config->pin_num2,DIO_PIN_OUTPUT);
	if( (enu_return_state_pin_1 == DIO_OK) && (enu_return_state_pin_2 == DIO_OK))
	{
		enu_return_state = MOTOR_OK;
	}
	else
	{
		enu_return_state = MOTOR_NOK;
	}
	
	return enu_return_state;
}

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
motor_enu_return_state_t MOTOR_FORWARD(const motor_str_config_t *ptr_str_motor_config)
{
	motor_enu_return_state_t enu_return_state = MOTOR_OK; 
	dio_enu_return_state_t enu_return_state_pin_1 = DIO_write_pin(ptr_str_motor_config->port,ptr_str_motor_config->pin_num1,DIO_PIN_HIGH_LEVEL);
	dio_enu_return_state_t enu_return_state_pin_2 = DIO_write_pin(ptr_str_motor_config->port,ptr_str_motor_config->pin_num2,DIO_PIN_LOW_LEVEL);
	if( (enu_return_state_pin_1 == DIO_OK) && (enu_return_state_pin_2 == DIO_OK))
	{
		enu_return_state = MOTOR_OK;
	}
	else
	{
		enu_return_state = MOTOR_NOK;
	}
	
	return enu_return_state;
}

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
motor_enu_return_state_t MOTOR_BACKWARD(const motor_str_config_t *ptr_str_motor_config)
{
	motor_enu_return_state_t enu_return_state = MOTOR_OK; 
	dio_enu_return_state_t enu_return_state_pin_1 = DIO_write_pin(ptr_str_motor_config->port,ptr_str_motor_config->pin_num1,DIO_PIN_LOW_LEVEL);
	dio_enu_return_state_t enu_return_state_pin_2 = DIO_write_pin(ptr_str_motor_config->port,ptr_str_motor_config->pin_num2,DIO_PIN_HIGH_LEVEL);
	
	if( (enu_return_state_pin_1 == DIO_OK) && (enu_return_state_pin_2 == DIO_OK))
	{
		enu_return_state = MOTOR_OK;
	}
	else
	{
		enu_return_state = MOTOR_NOK;
	}
	
	return enu_return_state;
}


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
motor_enu_return_state_t MOTOR_STOP(const motor_str_config_t *ptr_str_motor_config)
{
	motor_enu_return_state_t enu_return_state = MOTOR_OK; 
	dio_enu_return_state_t enu_return_state_pin_1 = DIO_write_pin(ptr_str_motor_config->port,ptr_str_motor_config->pin_num1,DIO_PIN_LOW_LEVEL);
	dio_enu_return_state_t enu_return_state_pin_2 = DIO_write_pin(ptr_str_motor_config->port,ptr_str_motor_config->pin_num2,DIO_PIN_LOW_LEVEL);
	
	if( (enu_return_state_pin_1 == DIO_OK) && (enu_return_state_pin_2 == DIO_OK))
	{   
		enu_return_state = MOTOR_OK; 
	}
	else
	{
		enu_return_state = MOTOR_NOK;
	}
	
	return enu_return_state;
}