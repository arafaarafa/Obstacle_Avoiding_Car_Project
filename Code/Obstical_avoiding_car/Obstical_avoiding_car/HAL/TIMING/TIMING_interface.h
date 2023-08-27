/**
 * @file TIMING_interface.h
 * @date 2023-08-23
 * @author Arafa Arafa

*/

#ifndef TIMING_INTERFACE_H_
#define TIMING_INTERFACE_H_
#include "Timing_config.h"
#include "../../MCAL/TIMER/TIMER_interface.h"
#include "../../STD_LIB/std_types.h"
#include "../../STD_LIB/bit_math.h"

#ifndef MCU_CLOCK
#error "MCU_CLOCK didn't define" //error to force user to define CPU Frequency
#endif 

/* Maximum system tick value */
#define TIMING_MAX_SYS_TICK             65535

/* Timer prescaler value */
#define TIMING_PRESCALLER_1024          1024

/* Maximum value for a 16-bit unsigned integer */
#define TIMING_MAX_U16_VALUE            65536

/* Conversion constant for converting 1000 to milliseconds */
#define TIMING_1000_TO_CONVERT_TO_MS    1000

/* Value representing 1 second in milliseconds */
#define TIMING_1_SEC_VALUE_IN_MS        1000

/************************************************************************************************/
/*									Enumerated Datatypes										*/
/************************************************************************************************/

/* Enumeration for capturing system tick state */
typedef enum {
	TIMING_CATCH = 0,
	TIMING_NOT_CATCH
} timing_enu_take_timestamp_state_t;

/* Enumeration for timeout state */
typedef enum {
	TIMING_TIME_OUT = 0,
	TIMING_NOT_TIME_OUT
} timing_enu_timeout_state_t;

/* Enumeration for return states */
typedef enum {
	TIMING_OK,
	TIMING_NOK
} timing_enu_return_state_t;




/************************************************************************************************/
/*									Function Prototypes     									*/
/************************************************************************************************/

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
timing_enu_return_state_t timing_init(uint16_t time_us , void (*callback)(void));


/**
 * @brief Starts the timing module.
 *
 * This function starts the timing module by calling the underlying function to start the timer
 * based on the previously configured timer settings.
 */
void timing_start(void);

/**
 * @brief Stops the timing module.
 *
 * This function stops the timing module by calling the underlying function to stop the timer
 * that was previously started.
 */
void timing_stop(void);




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
timing_enu_return_state_t timing_init_1(uint16_t u16_time_ms);

/**
 * @brief Starts the timer for timing module 1.
 *
 * This function starts the timer associated with timing module 1 using the configured timer
 * configuration parameters.
 */
void timing_start_1(void);

/**
 * @brief Stops the timer for timing module 1.
 *
 * This function stops the timer associated with timing module 1.
 */
void timing_stop_1(void);


/**
 * @brief Delays the program execution for a specified number of seconds.
 *
 * This function blocks the program execution for the specified duration in seconds.
 *
 * @param copy_u16_delay The delay duration in seconds.
 */
void delay_s(uint16_t copy_u16_delay);

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
timing_enu_timeout_state_t timing_time_out(uint16_t copy_u16_time_out_sec);
/**
 * @brief Breaks a time-out condition and resets the catch state.
 *
 * This function resets the catch state and the timestamp used for time-out calculations.
 * It can be used to prematurely exit a time-out condition.
 */
void timing_break_time_out(void);



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
timing_enu_return_state_t timing_init_2( void (*callback)(void));

/**
 * @brief Breaks a time-out condition and resets the catch state.
 *
 * This function resets the catch state and the timestamp used for time-out calculations.
 * It can be used to prematurely exit a time-out condition.
 */
void timing_start_2(void);

/**
 * @brief Stops timer 2.
 *
 * This function stops timer 2, halting its counting operation.
 */
void timing_stop_2(void);


/**
 * @brief Gets the current tick count of timer 2.
 *
 * This function retrieves the current tick count of timer 2 and stores it in the provided pointer.
 *
 * @param[inout] ptr_u8_ticks Pointer to a variable where the tick count will be stored.
 */
void timing_get_ticks_2(uint8_t *ptr_u8_ticks);




#endif