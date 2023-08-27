/**
 * @file TIMER_prog.c
 *
 * @date 2023-08-21
 * @author Arafa Arafa
*/




#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "../AVR_ARCH/ISR_interface.h"

// Pointer to a function that represents the callback for Timer overflow interrupt (for Timer 0)
static void (*timer_callback_OVF)(void) = NULL;

// Pointer to a function that represents the callback for Timer compare match interrupt (for Timer 0)
static void (*timer_callback_COMP)(void) = NULL;

// Pointer to a function that represents the callback for Timer1 overflow interrupt
static void (*timer1_callback_OVF)(void) = NULL;

// Pointer to a function that represents the callback for Timer1 compare match interrupt
static void (*timer1_callback_COMP)(void) = NULL;

// Pointer to a function that represents the callback for Timer2 overflow interrupt
static void (*timer2_callback_OVF)(void) = NULL;

// Pointer to a function that represents the callback for Timer2 compare match interrupt
static void (*timer2_callback_COMP)(void) = NULL;



/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/*								START_TIMER_0_impelementation									*/
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/

/**
 * @brief Initializes Timer 0 with the provided configuration.
 *
 * This function initializes Timer 0 based on the provided configuration settings.
 *
 * @param ptr_timer_config Pointer to the timer_configuration_t structure containing configuration settings.
 * @return timer_enu_return_state_t The return state of the timer initialization operation.
 *                                 Possible values:
 *                                 - TIMER_OK: The timer initialization was successful.
 *                                 - TIMER_NOK: The provided configuration pointer is NULL.
 */
timer_enu_return_state_t timer0_initialization(timer_configuration_t *ptr_timer_config){
	timer_enu_return_state_t enu_return_state = TIMER_OK;
	if(ptr_timer_config == NULL ){
		enu_return_state =TIMER_NOK;
	}
	else{
		TCNT0_ADD = 0;
		TCCR0_ADD |= ((1&ptr_timer_config->timer_mode)<<WGM00_bit);
		TCCR0_ADD |= ((ptr_timer_config->timer_mode>>1)<<WGM01_bit);
		if(ptr_timer_config->timer_mode == TIMER_MODE_NORMAL){
			
			TIMSK_ADD |= ((ptr_timer_config->timer_oc_interrupt<<1)|ptr_timer_config->timer_of_interrupt);
			if(ptr_timer_config->timer_of_interrupt == 1 || ptr_timer_config->timer_oc_interrupt == 1){
				sei();
			}
		}
	}

	return enu_return_state;
}

/**
 * @brief Starts the timer based on the provided configuration.
 *
 * This function starts the timer based on the provided configuration.
 *
 * @param ptr_timer_config Pointer to the timer configuration structure.
 * @return timer_enu_return_state_t The return state of the timer start operation.
 *                                Possible values:
 *                                - TIMER_OK: The timer start operation was successful.
 *                                - TIMER_NOK: The provided timer configuration pointer is NULL.
 */
timer_enu_return_state_t timer_start(timer_configuration_t *ptr_timer_config){
	timer_enu_return_state_t enu_return_state = TIMER_OK;
	if(ptr_timer_config == NULL ){
		enu_return_state =TIMER_NOK;
	}
	else{
		
		
		if(ptr_timer_config->timer_mode == TIMER_MODE_NORMAL){
			TCNT0_ADD = ptr_timer_config->OCR;
			TCCR0_ADD |= ptr_timer_config->timer_prescaller;
		}
	}

	return enu_return_state;
	
}

/**
 * @brief Sets the Timer/Counter (TCNT) value based on the provided configuration.
 *
 * This function sets the Timer/Counter (TCNT) value based on the provided configuration.
 *
 * @param ptr_timer_config Pointer to the timer configuration structure.
 * @return timer_enu_return_state_t The return state of the timer set TCNT operation.
 *                                Possible values:
 *                                - TIMER_OK: The timer set TCNT operation was successful.
 *                                - TIMER_NOK: The provided timer configuration pointer is NULL.
 */
timer_enu_return_state_t timer_set_tcnt(timer_configuration_t *ptr_timer_config){
	timer_enu_return_state_t enu_return_state = TIMER_OK;
	if(ptr_timer_config == NULL ){
		enu_return_state =TIMER_NOK;
	}
	else{
		
		
		if(ptr_timer_config->timer_mode == TIMER_MODE_NORMAL){
			TCNT0_ADD = ptr_timer_config->OCR;
		}
	}

	return enu_return_state;
	
}


/**
 * @brief Initializes the overflow callback function for Timer 0.
 *
 * This function initializes the overflow callback function for Timer 0 with the provided function pointer.
 *
 * @param ptr_func Pointer to the overflow callback function.
 * @return timer_enu_return_state_t The return state of the timer initialize callback OVF operation.
 *                                Possible values:
 *                                - TIMER_OK: The timer initialize callback OVF operation was successful.
 *                                - TIMER_NOK: The provided function pointer is NULL.
 */
timer_enu_return_state_t timer_initialize_callback_OVF(void (*ptr_func)(void)){
	timer_enu_return_state_t enu_return_state = TIMER_OK;
	if(ptr_func == NULL ){
		enu_return_state =TIMER_NOK;
	}
	else{
		timer_callback_OVF = ptr_func;
	}

	return enu_return_state;
}


/**
 * @brief Initializes the compare match callback function for Timer 0.
 *
 * This function initializes the compare match callback function for Timer 0 with the provided function pointer.
 *
 * @param ptr_func Pointer to the compare match callback function.
 * @return timer_enu_return_state_t The return state of the timer initialize callback COMP operation.
 *                                Possible values:
 *                                - TIMER_OK: The timer initialize callback COMP operation was successful.
 *                                - TIMER_NOK: The provided function pointer is NULL.
 */
timer_enu_return_state_t timer_initialize_callback_COMP(void (*ptr_func)(void)){
	timer_enu_return_state_t enu_return_state = TIMER_OK;
	if(ptr_func == NULL ){
		enu_return_state =TIMER_NOK;
	}
	else{
		timer_callback_COMP = ptr_func;
	}

	return enu_return_state;
	
}


// Timer 0 overflow interrupt
ISR(TIMER0_OVF) {
	// Call the Timer 0 overflow callback function
	(*timer_callback_OVF)();
}

// Timer 0 compare match interrupt
ISR(TIMER0_COMP) {
	// Call the Timer 0 compare match callback function
	(*timer_callback_COMP)();
}
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/*								START_TIMER_1_impelementation									*/
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/


/**
 * @brief Initializes Timer 1 with the provided configuration.
 *
 * This function initializes Timer 1 based on the provided configuration settings.
 *
 * @param ptr_timer_config Pointer to the timer_configuration_t structure containing configuration settings.
 * @return timer_enu_return_state_t The return state of the timer initialization operation.
 *                                 Possible values:
 *                                 - TIMER_OK: The timer initialization was successful.
 *                                 - TIMER_NOK: The provided configuration pointer is NULL.
 */
timer_enu_return_state_t timer1_initialization (timer_configuration_t *ptr_timer_config){
	timer_enu_return_state_t enu_return_state = TIMER_OK;
	if(ptr_timer_config == NULL ){
		enu_return_state =TIMER_NOK;
	}
	else{
		TCNT1_ADD = 0;
		TCCR1A_ADD |= ((1&ptr_timer_config->timer_mode)<<WGM10_BIT);
		TCCR1A_ADD |= ((ptr_timer_config->timer_mode>>1)<< WGM11_BIT);
		if(ptr_timer_config->timer_mode == TIMER_MODE_NORMAL){
			TIMSK_ADD |= ((ptr_timer_config->timer_oc_interrupt<<OCIE1A_BIT) | (ptr_timer_config->timer_of_interrupt << TOIE1_BIT));
			if(ptr_timer_config->timer_of_interrupt == U8_ONE_VALUE || ptr_timer_config->timer_oc_interrupt == U8_ONE_VALUE){
				sei();
			}
		}
	}
	return enu_return_state;
}

/**
 * @brief Stops the timer based on the provided configuration.
 *
 * This function stops the timer based on the provided configuration.
 *
 * @param ptr_timer_config Pointer to the timer configuration structure.
 * @return timer_enu_return_state_t The return state of the timer stop operation.
 *                                Possible values:
 *                                - TIMER_OK: The timer stop operation was successful.
 *                                - TIMER_NOK: The provided timer configuration pointer is NULL.
 */
timer_enu_return_state_t timer_stop(timer_configuration_t *ptr_timer_config){
	timer_enu_return_state_t enu_return_state = TIMER_OK;
	if(ptr_timer_config == NULL ){
		enu_return_state =TIMER_NOK;
	}
	else{
		
		
		if(ptr_timer_config->timer_mode == TIMER_MODE_NORMAL){
			TCCR0_ADD &= ~TIMER_CLEAR_CLOCK_SETTING;
		}
	}

	return enu_return_state;
	
}


/**
 * @brief Starts the timer based on the provided configuration.
 *
 * This function starts the timer based on the provided configuration.
 *
 * @param ptr_timer_config Pointer to the timer configuration structure.
 * @return timer_enu_return_state_t The return state of the timer start operation.
 *                                Possible values:
 *                                - TIMER_OK: The timer start operation was successful.
 *                                - TIMER_NOK: The provided timer configuration pointer is NULL.
 */
timer_enu_return_state_t timer1_start(timer_configuration_t *ptr_timer_config){
	timer_enu_return_state_t enu_return_state = TIMER_OK;
	if(ptr_timer_config == NULL){
		enu_return_state =TIMER_NOK;
	}
	else{
		
		
		if(ptr_timer_config->timer_mode == TIMER_MODE_NORMAL){
			TCNT1_ADD = ptr_timer_config->OCR;
			TCCR1B_ADD |= ptr_timer_config->timer_prescaller;
		}
	}

	return enu_return_state;
	
}

/**
 * @brief Stops the timer based on the provided configuration.
 *
 * This function stops the timer based on the provided configuration.
 *
 * @param ptr_timer_config Pointer to the timer configuration structure.
 * @return timer_enu_return_state_t The return state of the timer stop operation.
 *                                Possible values:
 *                                - TIMER_OK: The timer stop operation was successful.
 *                                - TIMER_NOK: The provided timer configuration pointer is NULL.
 */
timer_enu_return_state_t timer1_stop(timer_configuration_t *ptr_timer_config){
	timer_enu_return_state_t enu_return_state = TIMER_OK;
	if(ptr_timer_config == NULL ){
		enu_return_state =TIMER_NOK;
	}
	else{
		
		
		if(ptr_timer_config->timer_mode == TIMER_MODE_NORMAL){
			TCCR1B_ADD &= ~TIMER_CLEAR_CLOCK_SETTING;
		}
	}

	return enu_return_state;
}

/**
 * @brief Sets the Timer/Counter (TCNT) value based on the provided configuration.
 *
 * This function sets the Timer/Counter (TCNT) value based on the provided configuration.
 *
 * @param ptr_timer_config Pointer to the timer configuration structure.
 * @return timer_enu_return_state_t The return state of the timer set TCNT operation.
 *                                Possible values:
 *                                - TIMER_OK: The timer set TCNT operation was successful.
 *                                - TIMER_NOK: The provided timer configuration pointer is NULL.
 */
timer_enu_return_state_t timer1_set_tcnt(timer_configuration_t *ptr_timer_config){
	
	timer_enu_return_state_t enu_return_state = TIMER_OK;
	if(ptr_timer_config == NULL ){
		enu_return_state =TIMER_NOK;
	}
	else{
		
		
		if(ptr_timer_config->timer_mode == TIMER_MODE_NORMAL){
			TCNT1_ADD = ptr_timer_config->OCR;
		}
	}

	return enu_return_state;
	
}

/**
 * @brief Retrieves the Timer/Counter (TCNT) value of Timer 1.
 *
 * This function retrieves the Timer/Counter (TCNT) value of Timer 1 and stores it in the provided pointer.
 *
 * @param ptr_timer_config Pointer to the timer configuration structure (not used in this function).
 * @param ptr_u8_tcnt_value Pointer to store the retrieved TCNT value.
 * @return timer_enu_return_state_t The return state of the timer get TCNT operation.
 *                                Possible values:
 *                                - TIMER_OK: The timer get TCNT operation was successful.
 *                                - TIMER_NOK: The provided timer configuration pointer is NULL.
 */
timer_enu_return_state_t timer1_get_tcnt(timer_configuration_t *ptr_timer_config,uint8_t *ptr_u8_tcnt_value){
	timer_enu_return_state_t enu_return_state = TIMER_OK;
	if(ptr_timer_config == NULL ){
		enu_return_state =TIMER_NOK;
	}
	else{
		*ptr_u8_tcnt_value =TCNT1_ADD;
	}

	return enu_return_state;
}

/**
 * @brief Initializes the overflow callback function for Timer 1.
 *
 * This function initializes the overflow callback function for Timer 1 with the provided function pointer.
 *
 * @param ptr_func Pointer to the overflow callback function.
 * @return timer_enu_return_state_t The return state of the timer initialize callback OVF operation.
 *                                Possible values:
 *                                - TIMER_OK: The timer initialize callback OVF operation was successful.
 *                                - TIMER_NOK: The provided function pointer is NULL.
 */
timer_enu_return_state_t timer1_initialize_callback_OVF(void (*ptr_func)(void)){
	timer_enu_return_state_t enu_return_state = TIMER_OK;
	if(ptr_func == NULL ){
		enu_return_state =TIMER_NOK;
	}
	else{
		timer1_callback_OVF = ptr_func;
	}

	return enu_return_state;	
}


/**
 * @brief Initializes the compare match callback function for Timer 1.
 *
 * This function initializes the compare match callback function for Timer 1 with the provided function pointer.
 *
 * @param ptr_func Pointer to the compare match callback function.
 * @return timer_enu_return_state_t The return state of the timer initialize callback COMP operation.
 *                                Possible values:
 *                                - TIMER_OK: The timer initialize callback COMP operation was successful.
 *                                - TIMER_NOK: The provided function pointer is NULL.
 */
timer_enu_return_state_t timer1_initialize_callback_COMP(void (*ptr_func)(void)){
	timer_enu_return_state_t enu_return_state = TIMER_OK;
	if(ptr_func == NULL ){
		enu_return_state =TIMER_NOK;
	}
	else{
		timer1_callback_COMP = ptr_func;
	}

	return enu_return_state;
}

// Timer 1 overflow interrupt
ISR(TIMER1_OVF) {
	// Call the Timer 1 overflow callback function
	(*timer1_callback_OVF)();
}

// Timer 1 compare match A interrupt
ISR(TIMER1_COMPA) {
	// Call the Timer 1 compare match A callback function
	(*timer1_callback_COMP)();
}
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/*								START_TIMER_2_impelementation									*/
/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/**
 * @brief Initializes Timer 2 with the provided configuration.
 *
 * This function initializes Timer 2 based on the provided configuration settings.
 *
 * @param ptr_timer_config Pointer to the timer_configuration_t structure containing configuration settings.
 * @return timer_enu_return_state_t The return state of the timer initialization operation.
 *                                 Possible values:
 *                                 - TIMER_OK: The timer initialization was successful.
 *                                 - TIMER_NOK: The provided configuration pointer is NULL.
 */
timer_enu_return_state_t timer2_initialization (timer_configuration_t *ptr_timer_config)
{
	timer_enu_return_state_t enu_return_state = TIMER_OK;
	if(ptr_timer_config == NULL ){
		enu_return_state =TIMER_NOK;
	}
	else{
		TCNT2_ADD = 0;
		TCCR2_ADD |= ((1&ptr_timer_config->timer_mode)<<WGM20_BIT);
		TCCR2_ADD |= ((ptr_timer_config->timer_mode>>1)<<WGM21_BIT);
		if(ptr_timer_config->timer_mode == TIMER_MODE_NORMAL){
			
			TIMSK_ADD |= ((ptr_timer_config->timer_oc_interrupt<<OCIE2_BIT)|ptr_timer_config->timer_of_interrupt<<TOIE2_BIT);
			if(ptr_timer_config->timer_of_interrupt == U8_ONE_VALUE || ptr_timer_config->timer_oc_interrupt == U8_ONE_VALUE){
				sei();
			}
		}
	}
	return enu_return_state;
}





/**
 * @brief Starts the timer based on the provided configuration.
 *
 * This function starts the timer based on the provided configuration.
 *
 * @param ptr_timer_config Pointer to the timer configuration structure.
 * @return timer_enu_return_state_t The return state of the timer start operation.
 *                                Possible values:
 *                                - TIMER_OK: The timer start operation was successful.
 *                                - TIMER_NOK: The provided timer configuration pointer is NULL.
 */
timer_enu_return_state_t timer2_start(timer_configuration_t *ptr_timer_config){
	timer_enu_return_state_t enu_return_state = TIMER_OK;
	if(ptr_timer_config == NULL ){
		enu_return_state =TIMER_NOK;
	}
	else{
		
		
		if(ptr_timer_config->timer_mode == TIMER_MODE_NORMAL){
			TCNT2_ADD = ptr_timer_config->OCR;
			TCCR2_ADD |= ptr_timer_config->timer_prescaller;
		}
	}

	return enu_return_state;
	
}


/**
 * @brief Stops the timer based on the provided configuration.
 *
 * This function stops the timer based on the provided configuration.
 *
 * @param ptr_timer_config Pointer to the timer configuration structure.
 * @return timer_enu_return_state_t The return state of the timer stop operation.
 *                                Possible values:
 *                                - TIMER_OK: The timer stop operation was successful.
 *                                - TIMER_NOK: The provided timer configuration pointer is NULL.
 */
timer_enu_return_state_t timer2_stop(timer_configuration_t *ptr_timer_config){
	timer_enu_return_state_t enu_return_state = TIMER_OK;
	if(ptr_timer_config == NULL ){
		enu_return_state =TIMER_NOK;
	}
	else{
		
		
		if(ptr_timer_config->timer_mode == TIMER_MODE_NORMAL){
			TCCR2_ADD &= ~TIMER_CLEAR_CLOCK_SETTING;
		}
	}

	return enu_return_state;
	
}

/**
 * @brief Sets the Timer/Counter (TCNT) value based on the provided configuration.
 *
 * This function sets the Timer/Counter (TCNT) value based on the provided configuration.
 *
 * @param ptr_timer_config Pointer to the timer configuration structure.
 * @return timer_enu_return_state_t The return state of the timer set TCNT operation.
 *                                Possible values:
 *                                - TIMER_OK: The timer set TCNT operation was successful.
 *                                - TIMER_NOK: The provided timer configuration pointer is NULL.
 */
timer_enu_return_state_t timer2_set_tcnt(timer_configuration_t *ptr_timer_config){
	timer_enu_return_state_t enu_return_state = TIMER_OK;
	if(ptr_timer_config == NULL ){
		enu_return_state =TIMER_NOK;
	}
	else{
		
		
		if(ptr_timer_config->timer_mode == TIMER_MODE_NORMAL){
			TCNT2_ADD = ptr_timer_config->OCR;
		}
	}

	return enu_return_state;
	
}






/**
 * @brief Retrieves the Timer/Counter (TCNT) value of Timer 2.
 *
 * This function retrieves the Timer/Counter (TCNT) value of Timer 2 and stores it in the provided pointer.
 *
 * @param ptr_timer_config Pointer to the timer configuration structure (not used in this function).
 * @param ptr_u8_tcnt_value Pointer to store the retrieved TCNT value.
 * @return timer_enu_return_state_t The return state of the timer get TCNT operation.
 *                                Possible values:
 *                                - TIMER_OK: The timer get TCNT operation was successful.
 *                                - TIMER_NOK: The provided timer configuration pointer is NULL.
 */
timer_enu_return_state_t timer2_get_tcnt(timer_configuration_t *ptr_timer_config,uint8_t *ptr_u8_tcnt_value){
	timer_enu_return_state_t enu_return_state = TIMER_OK;
	if(ptr_timer_config == NULL ){
		enu_return_state =TIMER_NOK;
	}
	else{
		*ptr_u8_tcnt_value =TCNT2_ADD;
	}

	return enu_return_state;
	
}

/**
 * @brief Initializes the overflow callback function for Timer 2.
 *
 * This function initializes the overflow callback function for Timer 2 with the provided function pointer.
 *
 * @param ptr_func Pointer to the overflow callback function.
 * @return timer_enu_return_state_t The return state of the timer initialize callback OVF operation.
 *                                Possible values:
 *                                - TIMER_OK: The timer initialize callback OVF operation was successful.
 *                                - TIMER_NOK: The provided function pointer is NULL.
 */
timer_enu_return_state_t timer2_initialize_callback_OVF(void (*ptr_func)(void)){
	timer_enu_return_state_t enu_return_state = TIMER_OK;
	if(ptr_func == NULL ){
		enu_return_state =TIMER_NOK;
	}
	else{
		timer2_callback_OVF = ptr_func;
	}

	return enu_return_state;
}


/**
 * @brief Initializes the compare match callback function for Timer 2.
 *
 * This function initializes the compare match callback function for Timer 2 with the provided function pointer.
 *
 * @param ptr_func Pointer to the compare match callback function.
 * @return timer_enu_return_state_t The return state of the timer initialize callback COMP operation.
 *                                Possible values:
 *                                - TIMER_OK: The timer initialize callback COMP operation was successful.
 *                                - TIMER_NOK: The provided function pointer is NULL.
 */
timer_enu_return_state_t timer2_initialize_callback_COMP(void (*ptr_func)(void)){
	timer_enu_return_state_t enu_return_state = TIMER_OK;
	if(ptr_func == NULL ){
		enu_return_state =TIMER_NOK;
	}
	else{
		timer2_callback_COMP = ptr_func;
	}

	return enu_return_state;
	
}


// Timer 2 overflow interrupt
ISR(TIMER2_OVF) {
	// Call the Timer 2 overflow callback function
	(*timer2_callback_OVF)();
}

// Timer 2 compare match interrupt
ISR(TIMER2_COMP) {
	// Call the Timer 2 compare match callback function
	(*timer2_callback_COMP)();
}
