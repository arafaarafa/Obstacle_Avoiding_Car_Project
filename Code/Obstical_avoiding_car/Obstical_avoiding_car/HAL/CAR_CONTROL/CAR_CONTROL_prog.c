/**
 * @file CAR_CONTROL_prog.c
 *
 * @date 2023-08-21
 * @author Arafa Arafa
 */
#include "CAR_CONTROL_interface.h"



/* APIs Implementation */

/************************************************************************
* @brief Initializes the car by initializing two motors and PWM.
*
* This function initializes the car by initializing two motors and PWM. It takes pointers
* to the configuration of both motors and the PWM configuration. The function returns the
* initialization state of the car.
*
* @param ptr_str_motor_1 Pointer to the configuration of motor 1.
* @param ptr_str_motor_2 Pointer to the configuration of motor 2.
* @param ptr_str_pwm_config Pointer to the PWM configuration.
* @return The initialization state of the car.
*         - CAR_OK: Car initialized successfully.
*         - CAR_NOK: Car initialization failed due to motor initialization errors.
*         - CAR_NULL_PTR: Car initialization failed due to NULL pointers.
*
* @note The function initializes the motors and PWM and starts the PWM tick.
************************************************************************/
car_enu_return_state_t CAR_INIT(const motor_str_config_t *ptr_str_motor_1,const motor_str_config_t *ptr_str_motor_2, pwm_str_configuration_t *ptr_str_pwm_config)
{
	car_enu_return_state_t enu_return_state=CAR_OK;
	
	motor_enu_return_state_t enu_motor_error_1 ;
	motor_enu_return_state_t enu_motor_error_2 ;
	if((ptr_str_motor_1 !=NULL) && (ptr_str_motor_2 != NULL))
	{
		enu_motor_error_1 = MOTOR_INIT(ptr_str_motor_1);
		enu_motor_error_2 = MOTOR_INIT(ptr_str_motor_2);
		pwm_init(ptr_str_pwm_config);
		pwm_start_tick();
		if((enu_motor_error_1 != MOTOR_OK) || (enu_motor_error_2 != MOTOR_OK)){
			enu_return_state=CAR_NOK;
		}else{
			
		}
	}
	else
	{
		enu_return_state=CAR_NULL_PTR;
	}
	return enu_return_state;
}

/************************************************************************
* @brief Moves the car forward with a specific speed.
*
* This function moves the car forward with a specific speed. It takes pointers to the
* configuration of both motors and the PWM configuration. The function returns the
* movement state of the car.
*
* @param ptr_str_motor_1 Pointer to the configuration of motor 1.
* @param ptr_str_motor_2 Pointer to the configuration of motor 2.
* @param ptr_str_pwm_config Pointer to the PWM configuration.
* @return The movement state of the car.
*         - CAR_OK: Car moved forward successfully.
*         - CAR_NOK: Car movement failed due to motor movement errors.
*         - CAR_NULL_PTR: Car movement failed due to NULL pointers.
*
* @note The function moves both motors forward and starts the PWM.
************************************************************************/
car_enu_return_state_t CAR_FORWARD(const motor_str_config_t *ptr_str_motor_1,const motor_str_config_t *ptr_str_motor_2, pwm_str_configuration_t *ptr_str_pwm_config)
{
	car_enu_return_state_t enu_return_state=CAR_OK;
	motor_enu_return_state_t enu_motor_error_1;
	motor_enu_return_state_t enu_motor_error_2;
	
	if((ptr_str_motor_1 !=NULL) && (ptr_str_motor_2 != NULL))
	{
		enu_motor_error_1 = MOTOR_FORWARD(ptr_str_motor_1);
		enu_motor_error_2 = MOTOR_FORWARD(ptr_str_motor_2);
		pwm_change_frequency_or_duty_cycle(ptr_str_pwm_config);
		pwm_start(ptr_str_pwm_config);
		if((enu_motor_error_1 != MOTOR_OK) || (enu_motor_error_2 != MOTOR_OK)){
			enu_return_state=CAR_NOK;
		}else{
			
		}
	}
	else
	{
		enu_return_state=CAR_NULL_PTR;
	}
	return enu_return_state;
}


/************************************************************************
* @brief Moves the car backward with a specific speed.
*
* This function moves the car backward with a specific speed. It takes pointers to the
* configuration of both motors and the PWM configuration. The function returns the
* movement state of the car.
*
* @param ptr_str_motor_1 Pointer to the configuration of motor 1.
* @param ptr_str_motor_2 Pointer to the configuration of motor 2.
* @param ptr_str_pwm_config Pointer to the PWM configuration.
* @return The movement state of the car.
*         - CAR_OK: Car moved backward successfully.
*         - CAR_NOK: Car movement failed due to motor movement errors.
*         - CAR_NULL_PTR: Car movement failed due to NULL pointers.
*
* @note The function moves both motors backward and starts the PWM.
************************************************************************/
car_enu_return_state_t CAR_BACKWARD(const motor_str_config_t *ptr_str_motor_1,const motor_str_config_t *ptr_str_motor_2, pwm_str_configuration_t *ptr_str_pwm_config)
{
	car_enu_return_state_t enu_return_state=CAR_OK;
	motor_enu_return_state_t enu_motor_error_1;
	motor_enu_return_state_t enu_motor_error_2;
	
	if((ptr_str_motor_1 !=NULL) && (ptr_str_motor_2 != NULL))
	{
		enu_motor_error_1 = MOTOR_BACKWARD(ptr_str_motor_1);
		enu_motor_error_2 = MOTOR_BACKWARD(ptr_str_motor_2);
		pwm_change_frequency_or_duty_cycle(ptr_str_pwm_config);
		pwm_start(ptr_str_pwm_config);
		if((enu_motor_error_1 != MOTOR_OK) || (enu_motor_error_2 != MOTOR_OK)){
			enu_return_state=CAR_NOK;
			}else{
			
		}
	}
	else
	{
		enu_return_state=CAR_NULL_PTR;
	}
	return enu_return_state;
}

/************************************************************************
* @brief Reverses the car to the right.
*
* This function reverses the car to the right. It takes pointers to the configuration
* of both motors and the PWM configuration. The function returns the movement state
* of the car.
*
* @param ptr_str_motor_1 Pointer to the configuration of motor 1.
* @param ptr_str_motor_2 Pointer to the configuration of motor 2.
* @param ptr_str_pwm_config Pointer to the PWM configuration.
* @return The movement state of the car.
*         - CAR_OK: Car reversed to the right successfully.
*         - CAR_NOK: Car movement failed due to motor movement errors.
*         - CAR_NULL_PTR: Car movement failed due to NULL pointers.
*
* @note The function reverses motor 1 forward and motor 2 backward, then starts the PWM.
************************************************************************/
car_enu_return_state_t CAR_REVERSE_RIGHT(const motor_str_config_t *ptr_str_motor_1,const motor_str_config_t *ptr_str_motor_2, pwm_str_configuration_t *ptr_str_pwm_config)
{
	car_enu_return_state_t enu_return_state=CAR_OK;
	motor_enu_return_state_t enu_motor_error_1;
	motor_enu_return_state_t enu_motor_error_2;
	if((ptr_str_motor_1 !=NULL) && (ptr_str_motor_2 != NULL))
	{
		enu_motor_error_1 = MOTOR_FORWARD(ptr_str_motor_1);
		enu_motor_error_2 = MOTOR_BACKWARD(ptr_str_motor_2);
		pwm_change_frequency_or_duty_cycle(ptr_str_pwm_config);
		pwm_start(ptr_str_pwm_config);
		if((enu_motor_error_1 != MOTOR_OK) || (enu_motor_error_2 != MOTOR_OK)){
			enu_return_state=CAR_NOK;
			}else{
			
		}
	}
	else
	{
		enu_return_state=CAR_NULL_PTR;
	}
	return enu_return_state;
}

/************************************************************************
* @brief Reverses the car to the left.
*
* This function reverses the car to the left. It takes pointers to the configuration
* of both motors and the PWM configuration. The function returns the movement state
* of the car.
*
* @param ptr_str_motor_1 Pointer to the configuration of motor 1.
* @param ptr_str_motor_2 Pointer to the configuration of motor 2.
* @param ptr_str_pwm_config Pointer to the PWM configuration.
* @return The movement state of the car.
*         - CAR_OK: Car reversed to the left successfully.
*         - CAR_NOK: Car movement failed due to motor movement errors.
*         - CAR_NULL_PTR: Car movement failed due to NULL pointers.
*
* @note The function reverses motor 1 backward and motor 2 forward, then starts the PWM.
************************************************************************/
car_enu_return_state_t CAR_REVERSE_LEFT(const motor_str_config_t *ptr_str_motor_1,const motor_str_config_t *ptr_str_motor_2, pwm_str_configuration_t *ptr_str_pwm_config)
{
	car_enu_return_state_t enu_return_state=CAR_OK;
	motor_enu_return_state_t enu_motor_error_1;
	motor_enu_return_state_t enu_motor_error_2;
	if((ptr_str_motor_1 !=NULL) && (ptr_str_motor_2 != NULL))
	{
		enu_motor_error_1 = MOTOR_BACKWARD(ptr_str_motor_1);
		enu_motor_error_2 = MOTOR_FORWARD(ptr_str_motor_2);
		pwm_change_frequency_or_duty_cycle(ptr_str_pwm_config);
		pwm_start(ptr_str_pwm_config);
		if((enu_motor_error_1 != MOTOR_OK) || (enu_motor_error_2 != MOTOR_OK)){
			enu_return_state=CAR_NOK;
			}else{
			
		}
	}
	else
	{
		enu_return_state=CAR_NULL_PTR;
	}
	return enu_return_state;
}

/************************************************************************
* @brief Stops the car.
*
* This function stops the car by stopping both motors and the PWM. It takes pointers to
* the configuration of both motors and the PWM configuration. The function returns the
* stop state of the car.
*
* @param ptr_str_motor_1 Pointer to the configuration of motor 1.
* @param ptr_str_motor_2 Pointer to the configuration of motor 2.
* @param ptr_str_pwm_config Pointer to the PWM configuration.
* @return The stop state of the car.
*         - CAR_OK: Car stopped successfully.
*         - CAR_NOK: Car stop failed due to motor stop errors.
*         - CAR_NULL_PTR: Car stop failed due to NULL pointers.
*
* @note The function stops both motors and the PWM.
************************************************************************/
car_enu_return_state_t CAR_STOP(const motor_str_config_t *ptr_str_motor_1,const motor_str_config_t *ptr_str_motor_2, pwm_str_configuration_t *ptr_str_pwm_config)
{
	car_enu_return_state_t enu_return_state=CAR_OK;
	motor_enu_return_state_t enu_motor_error_1;
	motor_enu_return_state_t enu_motor_error_2;
	if((ptr_str_motor_1 !=NULL) && (ptr_str_motor_2 != NULL))
	{
		enu_motor_error_1 = MOTOR_STOP(ptr_str_motor_1);
		enu_motor_error_2 = MOTOR_STOP(ptr_str_motor_2);
		pwm_stop(ptr_str_pwm_config);
		if((enu_motor_error_1 != MOTOR_OK) || (enu_motor_error_2 != MOTOR_OK)){
			enu_return_state=CAR_NOK;
			}else{
			
		}
	}
	else
	{
		enu_return_state=CAR_NULL_PTR;
	}
	return enu_return_state;
}