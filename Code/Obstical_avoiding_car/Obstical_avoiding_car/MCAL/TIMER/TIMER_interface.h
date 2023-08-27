/**
 * @file TIMRT_interface.c
 *
 * @date 2023-08-21
 * @author Arafa Arafa
*/




#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H
/* section : includes*/
#include "../../STD_LIB/std_types.h"
#include "../../STD_LIB/bit_math.h"


	

// Definition of values for enabling/disabling timer interrupts
#define TIMER_OUTPUT_COMPARE_MATCH_INTERRUPT_ENABLE      1
#define TIMER_OUTPUT_COMPARE_MATCH_INTERRUPT_DISABLE     0

#define TIMER_OVERFLOW_INTERRUPT_ENABLE                  1
#define TIMER_OVERFLOW_INTERRUPT_DISABLE                 0

// Definition of clock settings to clear the timer clock prescaler bits
#define TIMER_CLEAR_CLOCK_SETTING						0b00000111

// Enumeration of possible return states for timer functions
typedef enum{
	TIMER_OK,     // Timer operation was successful
	TIMER_NOK     // Timer operation failed
} timer_enu_return_state_t;

// Enumeration of different timer modes
typedef enum timer_mode_t{
	TIMER_MODE_NORMAL,  // Normal mode
	TIMER_MODE_PWM,     // Pulse Width Modulation (PWM) mode
	TIMER_MODE_CTC      // Clear Timer on Compare (CTC) mode
} timer_mode_t;

// Enumeration of PWM modes
typedef enum PWM_mode_t{
	PWM_NORMAL_DISCONNECTED,  // Normal mode with disconnected PWM
	PWM_MODE_0 = 2,           // PWM Mode 0
	PWM_MODE_1 = 3            // PWM Mode 1
} PWM_mode_t;

// Enumeration of timer prescaler settings
typedef enum{
	TIMER_STOP,                   // Timer is stopped
	TIMER_PRESCALLER_0,           // No prescaler
	TIMER_PRESCALLER_8,           // Prescaler of 8
	TIMER_PRESCALLER_64,          // Prescaler of 64
	TIMER_PRESCALLER_256,         // Prescaler of 256
	TIMER_PRESCALLER_1024,        // Prescaler of 1024
	TIMER_EXT_CLK_FALLING_EDGE,   // External clock source, falling edge
	TIMER_EXT_CLK_RISING_EDGE     // External clock source, rising edge
} timer_prescaller_t;

// Configuration structure for timer settings
typedef struct{
	timer_mode_t timer_mode;      // Timer mode (normal, PWM, CTC)
	timer_prescaller_t timer_prescaller; // Timer prescaler setting
	uint16_t OCR;                 // Output Compare Register value
	uint8_t timer_oc_interrupt : 1; // Enable/disable output compare interrupt
	uint8_t timer_of_interrupt : 1; // Enable/disable overflow interrupt
} timer_configuration_t;



/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/*									START_TIMER_0_prototypes									*/
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
timer_enu_return_state_t timer0_initialization(timer_configuration_t *timer_configuration);


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

timer_enu_return_state_t timer_start(timer_configuration_t *timer_configuration);


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
timer_enu_return_state_t timer_stop(timer_configuration_t *timer_configuration);

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
timer_enu_return_state_t timer_initialize_callback_OVF(void (*ptr_func)(void));

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
timer_enu_return_state_t timer_initialize_callback_COMP(void (*ptr_func)(void));



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
timer_enu_return_state_t timer_set_tcnt(timer_configuration_t *ptr_timer_config);


/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/*									START_TIMER_1_prototypes									*/
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
timer_enu_return_state_t timer1_initialization (timer_configuration_t *ptr_timer_config);

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
timer_enu_return_state_t timer1_start(timer_configuration_t *ptr_timer_config);

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

timer_enu_return_state_t timer1_stop(timer_configuration_t *ptr_timer_config);


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
timer_enu_return_state_t timer1_set_tcnt(timer_configuration_t *ptr_timer_config);

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

timer_enu_return_state_t timer1_get_tcnt(timer_configuration_t *ptr_timer_config,uint8_t *ptr_u8_tcnt_value);


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
timer_enu_return_state_t timer1_initialize_callback_OVF(void (*ptr_func)(void));

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
timer_enu_return_state_t timer1_initialize_callback_COMP(void (*ptr_func)(void));





/************************************************************************************************/
/************************************************************************************************/
/************************************************************************************************/
/*									START_TIMER_2_prototypes									*/
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
timer_enu_return_state_t timer2_initialization (timer_configuration_t *ptr_timer_config);

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
timer_enu_return_state_t timer2_start(timer_configuration_t *ptr_timer_config);


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
timer_enu_return_state_t timer2_stop(timer_configuration_t *ptr_timer_config);


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
timer_enu_return_state_t timer2_set_tcnt(timer_configuration_t *ptr_timer_config);

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
timer_enu_return_state_t timer2_get_tcnt(timer_configuration_t *ptr_timer_config,uint8_t *ptr_u8_tcnt_value);

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
timer_enu_return_state_t timer2_initialize_callback_OVF(void (*ptr_func)(void));


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
timer_enu_return_state_t timer2_initialize_callback_COMP(void (*ptr_func)(void));





#endif