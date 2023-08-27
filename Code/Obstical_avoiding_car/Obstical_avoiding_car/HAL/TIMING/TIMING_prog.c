
/**
 * @file TIMING_prog.c
 *
 * @date 2023-08-23
 * @author Arafa Arafa
 */

#include "TIMING_interface.h"



/* Global variable to hold the configuration settings for a timer */
timer_configuration_t timer_configuration;

/* Global variable to hold the configuration settings for another timer */
timer_configuration_t timer_configuration_1;

/* Global variable to hold the configuration settings for yet another timer */
timer_configuration_t timer_configuration_2;

/* Global variable to store the current system tick count */
static volatile uint16_t gs_u16_sys_tick = U8_ZERO_VALUE;

/* Global variable indicating the state of catching a timestamp */
static timing_enu_take_timestamp_state_t gs_enu_catch_state = TIMING_CATCH;

/* Global variable to store a timestamp value */
static uint16_t gs_u16_timestamp = (uint16_t)U8_ZERO_VALUE;


/* Pointer to a callback function */
void (*tmp_callBack)(void);





/* Callback function for a timer interrupt */
static void function_callback(void)
{
	(*tmp_callBack)(); // Call the user-defined callback function
	timer_set_tcnt(&timer_configuration); // Reset the timer counter value
}

/* Callback function for another timer interrupt */
static void function_callback_1(void)
{
	gs_u16_sys_tick++; // Increment the system tick count
	timer1_set_tcnt(&timer_configuration_1); // Reset the timer counter value
}



/**
 * @brief Initializes the timing module with a specified time interval and callback function.
 *
 * This function initializes the timing module by calculating the appropriate timer settings
 * based on the desired time interval in microseconds and the CPU clock frequency. It then
 * configures the timer and sets up an overflow interrupt to trigger the provided callback function.
 *
 * @param[in] time_us The desired time interval in microseconds.
 * @param[in] callback A pointer to the callback function to be executed on timer overflow interrupt.
 * @return The return state of the timing initialization.
 */
timing_enu_return_state_t timing_init(uint16_t time_us , void (*callback)(void)){
	volatile uint16_t timer_init_value =0;
	/*volatile uint32_t max_delay =0;*/
	volatile uint32_t cycle_time=0;	
	volatile uint32_t prescaller = 256;
	volatile uint64_t prscaller_max_regiter = 256;
	timing_enu_return_state_t enu_return_state = TIMING_OK;
	cycle_time = ((double)prescaller/MCU_CLOCK)*1000000;
	timer_init_value = (uint16_t)((double)prscaller_max_regiter - ((double)time_us/cycle_time));
	
	if(time_us < 1000 ){
		enu_return_state =TIMING_NOK;
	}else{
		if(MCU_CLOCK ==0)
			enu_return_state = TIMING_NOK;
		timer_configuration.OCR=timer_init_value;
		timer_configuration.timer_mode = TIMER_MODE_NORMAL;
		timer_configuration.timer_prescaller=TIMER_PRESCALLER_256;
		timer_configuration.timer_of_interrupt =TIMER_OVERFLOW_INTERRUPT_ENABLE;
		tmp_callBack = callback;
		timer_initialize_callback_OVF(function_callback);
		timer0_initialization(&timer_configuration);			
	}

	return enu_return_state;
}



/**
 * @brief Starts the timing module.
 *
 * This function starts the timing module by calling the underlying function to start the timer
 * based on the previously configured timer settings.
 */
void timing_start(void) {
	// Start the timer using the configured timer settings
	timer_start(&timer_configuration);
}


/**
 * @brief Stops the timing module.
 *
 * This function stops the timing module by calling the underlying function to stop the timer
 * that was previously started.
 */
void timing_stop(void) {
	// Stop the timer that was previously started
	timer_stop(&timer_configuration);
}



/**
 * @brief Initializes the timing module with a specified time in milliseconds.
 *
 * This function initializes the timing module with the specified time in milliseconds. It calculates
 * the appropriate timer initialization value and configures the timer accordingly. If the specified time
 * is less than 1000 milliseconds, the function returns a TIMING_NOK state, indicating an error.
 *
 * @param u16_time_ms The time in milliseconds for the timing module.
 * @return The status of the timing initialization.
 */
timing_enu_return_state_t timing_init_1( uint16_t u16_time_ms){
	
	volatile uint16_t timer_init_value = U8_ZERO_VALUE;
	volatile double cycle_time= U8_ZERO_VALUE;
	volatile uint32_t prescaller = TIMING_PRESCALLER_1024;
	volatile uint64_t prscaller_max_regiter = TIMING_MAX_U16_VALUE;
	timing_enu_return_state_t enu_return_state = TIMING_OK;

	cycle_time = ((double)prescaller)/(MCU_CLOCK/TIMING_1000_TO_CONVERT_TO_MS);
	timer_init_value = ((double)prscaller_max_regiter - ((double)u16_time_ms/cycle_time));
	
	if(u16_time_ms < TIMING_1_SEC_VALUE_IN_MS ){
		enu_return_state =TIMING_NOK;
	}else{
		timer_configuration_1.OCR = timer_init_value;
		timer_configuration_1.timer_mode = TIMER_MODE_NORMAL;
		timer_configuration_1.timer_prescaller = TIMER_PRESCALLER_1024;
		timer_configuration_1.timer_of_interrupt =TIMER_OVERFLOW_INTERRUPT_ENABLE;
		timer1_initialize_callback_OVF(function_callback_1);
		timer1_initialization(&timer_configuration_1);
	}

	return enu_return_state;
	
}

/**
 * @brief Starts the timer for timing module 1.
 *
 * This function starts the timer associated with timing module 1 using the configured timer
 * configuration parameters.
 */
void timing_start_1(void) {
	timer1_start(&timer_configuration_1);
}

/**
 * @brief Stops the timer for timing module 1.
 *
 * This function stops the timer associated with timing module 1.
 */
void timing_stop_1(void){
	timer1_stop(&timer_configuration_1);
}


/**
 * @brief Checks for a timeout.
 *
 * This function checks whether the specified timeout period has passed.
 *
 * @param copy_u16_time_out_sec The timeout period in seconds to check against.
 * @return The timeout state:
 *         - TIMING_TIME_OUT if the timeout has occurred.
 *         - TIMING_NOT_TIME_OUT if the timeout has not occurred.
 */
timing_enu_timeout_state_t timing_time_out(uint16_t copy_u16_time_out_sec){
	timing_enu_timeout_state_t enu_time_state = TIMING_NOT_TIME_OUT;
	uint16_t u16_systick_copy  = U8_ZERO_VALUE;
	uint16_t u16_actual_time  = U8_ZERO_VALUE;
	if(gs_enu_catch_state == TIMING_CATCH){
		gs_u16_timestamp = gs_u16_sys_tick;
		u16_systick_copy = gs_u16_sys_tick;
		gs_enu_catch_state =TIMING_NOT_CATCH;
		}else{
		u16_systick_copy = gs_u16_sys_tick;
	}
	
	if(gs_u16_timestamp > u16_systick_copy){
		u16_actual_time = (TIMING_MAX_SYS_TICK-gs_u16_timestamp)+ u16_systick_copy;
		}else{
		u16_actual_time = u16_systick_copy - gs_u16_timestamp;
	}
	
	if(u16_actual_time >= copy_u16_time_out_sec){
		gs_enu_catch_state = TIMING_CATCH;
		enu_time_state = TIMING_TIME_OUT;
		gs_u16_timestamp = (uint16_t)U8_ZERO_VALUE;
		}else{
		enu_time_state = TIMING_NOT_TIME_OUT;
	}
	return  enu_time_state;
	
}


/**
 * @brief Breaks a time-out condition and resets the catch state.
 *
 * This function resets the catch state and the timestamp used for time-out calculations.
 * It can be used to prematurely exit a time-out condition.
 */
void timing_break_time_out(void){
	gs_enu_catch_state = TIMING_CATCH;
	gs_u16_timestamp = (uint16_t)U8_ZERO_VALUE;
}

/**
 * @brief Delays the program execution for a specified number of seconds.
 *
 * This function blocks the program execution for the specified duration in seconds.
 *
 * @param copy_u16_delay The delay duration in seconds.
 */
void delay_s(uint16_t copy_u16_delay) {
    // Loop until the specified delay time has passed
    while (timing_time_out(copy_u16_delay) != TIMING_TIME_OUT) {
        // Do nothing, waiting for the delay to complete
    }
}

/**
 * @brief Initializes timing module 2.
 *
 * This function initializes timing module 2 with the provided callback function.
 * If the callback is NULL, it returns an error status (TIMING_NOK).
 *
 * @param callback A pointer to the callback function to be called on timer overflow.
 * @return The status of the timing initialization:
 *         - TIMING_OK if initialization was successful.
 *         - TIMING_NOK if the provided callback is NULL.
 */
timing_enu_return_state_t timing_init_2(void (*callback)(void)){
	timing_enu_return_state_t enu_return_state = TIMING_OK;
	if(callback == NULL ){
		enu_return_state =TIMING_NOK;
	}else{
		timer_configuration_2.OCR= U8_ZERO_VALUE;
		timer_configuration_2.timer_mode = TIMER_MODE_NORMAL;
		timer_configuration_2.timer_prescaller=TIMER_PRESCALLER_0;
		timer_configuration_2.timer_of_interrupt =TIMER_OVERFLOW_INTERRUPT_ENABLE;
		timer2_initialize_callback_OVF(callback);
		timer2_initialization(&timer_configuration_2);
	}

	return enu_return_state;
}

/**
 * @brief Breaks a time-out condition and resets the catch state.
 *
 * This function resets the catch state and the timestamp used for time-out calculations.
 * It can be used to prematurely exit a time-out condition.
 */
void timing_start_2(void){
	timer2_start(&timer_configuration_2);
	
}


/**
 * @brief Stops timer 2.
 *
 * This function stops timer 2, halting its counting operation.
 */
void timing_stop_2(void){
	timer2_stop(&timer_configuration_2);
}

/**
 * @brief Gets the current tick count of timer 2.
 *
 * This function retrieves the current tick count of timer 2 and stores it in the provided pointer.
 *
 * @param[inout] ptr_u8_ticks Pointer to a variable where the tick count will be stored.
 */
void timing_get_ticks_2(uint8_t *ptr_u8_ticks){
	
	timer2_get_tcnt(&timer_configuration_2,ptr_u8_ticks);
}



