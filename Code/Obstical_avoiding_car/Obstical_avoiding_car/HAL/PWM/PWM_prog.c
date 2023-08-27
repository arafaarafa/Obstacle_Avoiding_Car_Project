/**
 * @file PWM_prog.c
 *
 * @date 2023-08-23
 * @author Arafa Arafa
 */

#include "PWM_interface.h"
#include "PWM_config.h"
static uint8_t gs_u8_pwm_channel_counter = U8_ZERO_VALUE;
static pwm_str_configuration_t *gs_arr_str_pwm_configuration[PWM_CHANNEL_MAX] = {NULL};
static volatile uint32_t pwm_tick = 0;

void pwm_tick_counter(void){
	pwm_tick++;
	for(uint8_t u8_counter=U8_ZERO_VALUE; (u8_counter <= gs_u8_pwm_channel_counter) && (gs_u8_pwm_channel_counter < PWM_CHANNEL_MAX); u8_counter++){
		
		pwm_checking(gs_arr_str_pwm_configuration[u8_counter]);
	}
	
	
};
	
	

/**
 * @brief Initialize the PWM channel based on the provided configuration.
 *
 * This function initializes a PWM channel based on the provided PWM configuration.
 * It sets the specified port and pin as an output pin to generate the PWM signal.
 * The cycle duration and time-on (duty cycle) are calculated based on the provided frequency
 * and duty cycle values.
 *
 * @param ptr_str_pwm_configuration Pointer to the PWM configuration structure.
 * @return The initialization state of the PWM channel.
 *         - PWM_OK: PWM channel initialized successfully.
 *         - PWM_NOK: PWM channel initialization failed due to a NULL configuration pointer.
 *
 * @note The PWM configuration structure contains the port, pin, frequency, and duty cycle information.
 */

pwm_enu_return_state_t pwm_init(pwm_str_configuration_t *ptr_str_pwm_configuration){
	
	pwm_enu_return_state_t ret = PWM_OK;
	if(ptr_str_pwm_configuration == NULL ){
		ret =PWM_NOK;
	}
	else{
				
		DIO_init (ptr_str_pwm_configuration->enu_port_index, ptr_str_pwm_configuration->enu_pin_index, DIO_PIN_OUTPUT);
		ptr_str_pwm_configuration->cycle_duration = 1/(double)ptr_str_pwm_configuration->frequency*PWMM_TO_CONVERT_TO_US; 
		ptr_str_pwm_configuration->t_on = (((double)ptr_str_pwm_configuration->duty_cycle)/PWMM_TO_CONVERT_FROM_PRESENTAGE)*(ptr_str_pwm_configuration->cycle_duration);
		ptr_str_pwm_configuration->pwm_state = PWM_OFF;
		gs_arr_str_pwm_configuration[gs_u8_pwm_channel_counter] = ptr_str_pwm_configuration;
		
	}
	return ret;
}



/**
 * @brief Start the PWM tick generation using the timing module.
 *
 * This function initializes the timing module with a tick interval of 1000 microseconds (1 ms)
 * and the specified callback function "pwm_tick_counter" as the callback to be executed on each tick.
 * After initializing the timing module, it starts the timing mechanism to generate ticks at the specified interval.
 *
 * @note This function assumes that the "timing_init" and "timing_start" functions are part of the timing module.
 *       It also assumes that the "pwm_tick_counter" function is defined and will be called on each tick.
 */
void pwm_start_tick(void){
	timing_init(PWM_1000_US, pwm_tick_counter);
	timing_start();
}

/**
 * @brief Start the PWM signal generation.
 *
 * This function starts the PWM signal generation for the specified PWM configuration.
 * It sets the PWM state to "PWM_ON", writes a high-level signal to the specified port and pin,
 * and records the current value of the "pwm_tick" variable as the start of the PWM tick count.
 *
 * @param[in] ptr_str_pwm_configuration A pointer to the PWM configuration structure.
 * @return The return state of the PWM operation, which is either "PWM_OK" or "PWM_NOK".
 */
pwm_enu_return_state_t pwm_start(pwm_str_configuration_t *ptr_str_pwm_configuration){
	pwm_enu_return_state_t ret = PWM_OK;
	if(ptr_str_pwm_configuration == NULL ){
		ret =PWM_NOK;
	}
	else{
		ptr_str_pwm_configuration->pwm_state = PWM_ON;
		DIO_write_pin(ptr_str_pwm_configuration->enu_port_index, ptr_str_pwm_configuration->enu_pin_index, DIO_PIN_HIGH_LEVEL);
		ptr_str_pwm_configuration->pwm_tick_ss = pwm_tick;
	}
	return ret;
}


/**
 * @brief Check the PWM signal generation status.
 *
 * This function checks the status of the PWM signal generation for the specified PWM configuration.
 * It calculates the actual time since the PWM signal started and compares it with the "t_on" and
 * "cycle_duration" values in the configuration. Depending on the comparison, it updates the PWM state
 * and writes appropriate signal levels to the specified port and pin.
 *
 * @param[in] ptr_str_pwm_configuration A pointer to the PWM configuration structure.
 * @return The return state of the PWM operation, which is either "PWM_OK" or "PWM_NOK".
 */
pwm_enu_return_state_t pwm_checking(pwm_str_configuration_t *ptr_str_pwm_configuration){
	pwm_enu_return_state_t ret = PWM_OK;
	if(ptr_str_pwm_configuration == NULL ){
		ret =PWM_NOK;
	}
	else{
		uint32_t pwm_tick_temp = pwm_tick, actual_time =0;
		if(ptr_str_pwm_configuration->pwm_tick_ss > pwm_tick_temp){
			actual_time = MAX_VALUE_UINT32-ptr_str_pwm_configuration->pwm_tick_ss+pwm_tick_temp;
		}else{
			actual_time = pwm_tick_temp - ptr_str_pwm_configuration->pwm_tick_ss;
		}
		
		if(ptr_str_pwm_configuration->t_on > actual_time){
			if(ptr_str_pwm_configuration->pwm_state != PWM_ON){
				ptr_str_pwm_configuration->pwm_state = PWM_ON;
				DIO_write_pin(ptr_str_pwm_configuration->enu_port_index, ptr_str_pwm_configuration->enu_pin_index, DIO_PIN_HIGH_LEVEL);
			}	
		}else if(ptr_str_pwm_configuration->cycle_duration > actual_time){
			if(ptr_str_pwm_configuration->pwm_state != PWM_OFF){
				ptr_str_pwm_configuration->pwm_state = PWM_OFF;
				DIO_write_pin(ptr_str_pwm_configuration->enu_port_index, ptr_str_pwm_configuration->enu_pin_index, DIO_PIN_LOW_LEVEL);
			}
		}else{
			ptr_str_pwm_configuration->pwm_tick_ss =  pwm_tick_temp;
		}
		
	}
	return ret;
	
}

/**
 * @brief Update PWM frequency or duty cycle and recalculate timing parameters.
 *
 * This function updates the PWM frequency or duty cycle in the specified PWM configuration.
 * It recalculates the "cycle_duration" and "t_on" values based on the new frequency or duty cycle.
 *
 * @param[in] ptr_str_pwm_configuration A pointer to the PWM configuration structure.
 * @return The return state of the PWM operation, which is either "PWM_OK" or "PWM_NOK".
 */
pwm_enu_return_state_t pwm_change_frequency_or_duty_cycle(pwm_str_configuration_t *ptr_str_pwm_configuration){
	pwm_enu_return_state_t ret = PWM_OK;
	if(ptr_str_pwm_configuration == NULL ){
		ret =PWM_NOK;
	}
	else{
		ptr_str_pwm_configuration->cycle_duration = U8_ONE_VALUE/(double)ptr_str_pwm_configuration->frequency*PWMM_TO_CONVERT_TO_US;
		ptr_str_pwm_configuration->t_on = (((double)ptr_str_pwm_configuration->duty_cycle)/100)*(ptr_str_pwm_configuration->cycle_duration);
		
	}
	return ret;
}

/**
 * @brief Stop the PWM signal by turning off the PWM output and resetting related variables.
 *
 * This function stops the PWM signal by setting the PWM state to OFF, turning off the PWM output,
 * and resetting the PWM tick snapshot. It updates the specified PWM configuration accordingly.
 *
 * @param[in] ptr_str_pwm_configuration A pointer to the PWM configuration structure.
 * @return The return state of the PWM operation, which is either "PWM_OK" or "PWM_NOK".
 */
pwm_enu_return_state_t pwm_stop(pwm_str_configuration_t *ptr_str_pwm_configuration){
	pwm_enu_return_state_t ret = PWM_OK;
	if(ptr_str_pwm_configuration == NULL ){
		ret =PWM_NOK;
	}else{
		ptr_str_pwm_configuration->pwm_state = PWM_OFF;
		DIO_write_pin(ptr_str_pwm_configuration->enu_port_index, ptr_str_pwm_configuration->enu_pin_index, DIO_PIN_LOW_LEVEL);
		ptr_str_pwm_configuration->pwm_tick_ss = U8_ZERO_VALUE;
	}
	return ret;
}

/**
 * @brief End the PWM timing tick.
 *
 * This function stops the timing tick used for PWM signal management.
 * It can be called when PWM operation is complete or needs to be paused.
 */
void pwm_end_tick(void) {
    timing_stop(); // Stop the timing tick used for PWM
}
