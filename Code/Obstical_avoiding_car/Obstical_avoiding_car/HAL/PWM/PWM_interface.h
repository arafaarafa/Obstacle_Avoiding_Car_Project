/**
 * @file PWM_interface.h
 *
 * @date 2023-08-23
 * @author Arafa Arafa
 */


#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_
#include "../TIMING/TIMING_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"

#define PWM_1000_US									1000
#define PWMM_TO_CONVERT_TO_US						1000
#define PWMM_TO_CONVERT_FROM_PRESENTAGE				100
/************************************************************************************************/
/*									Enumerated Datatypes										*/
/************************************************************************************************/
/**
 * @brief Enumeration for PWM return states.
 *
 * This enumeration defines the possible return states for PWM functions.
 */
typedef enum {
    PWM_OK,      /**< PWM operation successful. */
    PWM_NOK      /**< PWM operation failed. */
} pwm_enu_return_state_t;

/**
 * @brief Enumeration for PWM states.
 *
 * This enumeration defines the possible states of a PWM channel.
 */
typedef enum {
    PWM_OFF = 0, /**< PWM channel is turned off. */
    PWM_ON       /**< PWM channel is turned on. */
} pwm_state_t;

/**
 * @brief Structure to hold PWM configuration.
 *
 * This structure defines the configuration parameters for a PWM channel.
 */
typedef struct {
    dio_enu_port_t enu_port_index; /**< Port index of the PWM pin. */
    dio_enu_pin_t enu_pin_index;   /**< Pin index of the PWM pin. */
    uint8_t duty_cycle;            /**< Duty cycle of the PWM signal. */
    uint32_t frequency;            /**< Frequency of the PWM signal. */
    uint16_t t_on;                 /**< Time ON of the PWM signal. */
    uint16_t cycle_duration;       /**< Duration of a single PWM cycle. */
    pwm_state_t pwm_state;         /**< Current state of the PWM channel. */
    uint32_t pwm_tick_ss;          /**< Stored PWM tick snapshot. */
} pwm_str_configuration_t;



/************************************************************************************************/
/*									Function Prototypes     									*/
/************************************************************************************************/

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
pwm_enu_return_state_t pwm_init(pwm_str_configuration_t *ptr_str_pwm_configuration);

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
void pwm_start_tick(void);


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
pwm_enu_return_state_t pwm_start(pwm_str_configuration_t *ptr_str_pwm_configuration);

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
pwm_enu_return_state_t pwm_checking(pwm_str_configuration_t *ptr_str_pwm_configuration);

/**
 * @brief Update PWM frequency or duty cycle and recalculate timing parameters.
 *
 * This function updates the PWM frequency or duty cycle in the specified PWM configuration.
 * It recalculates the "cycle_duration" and "t_on" values based on the new frequency or duty cycle.
 *
 * @param[in] ptr_str_pwm_configuration A pointer to the PWM configuration structure.
 * @return The return state of the PWM operation, which is either "PWM_OK" or "PWM_NOK".
 */
pwm_enu_return_state_t pwm_change_frequency_or_duty_cycle(pwm_str_configuration_t *ptr_str_pwm_configuration);

/**
 * @brief Stop the PWM signal by turning off the PWM output and resetting related variables.
 *
 * This function stops the PWM signal by setting the PWM state to OFF, turning off the PWM output,
 * and resetting the PWM tick snapshot. It updates the specified PWM configuration accordingly.
 *
 * @param[in] ptr_str_pwm_configuration A pointer to the PWM configuration structure.
 * @return The return state of the PWM operation, which is either "PWM_OK" or "PWM_NOK".
 */
pwm_enu_return_state_t pwm_stop(pwm_str_configuration_t *ptr_str_pwm_configuration);

/**
 * @brief End the PWM timing tick.
 *
 * This function stops the timing tick used for PWM signal management.
 * It can be called when PWM operation is complete or needs to be paused.
 */
void pwm_end_tick(void);

#endif /* PWM_H_ */