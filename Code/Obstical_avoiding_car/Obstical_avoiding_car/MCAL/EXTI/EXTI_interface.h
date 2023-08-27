/**
 * @file EXTI_interface.h
 *
 * @date 2023-08-21
 * @author Arafa Arafa
 */

#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H


/************************************************************************************************/
/*									Enumerated Datatypes										*/
/************************************************************************************************/

// Enumeration for the return state of external interrupt functions
typedef enum {
	EXTI_E_OK = 0,  // Operation was successful
	EXTI_E_NOK      // Operation encountered an error
} exti_enu_return_state_t;

// Enumeration for external interrupt numbers
typedef enum {
	EXTI_0 = 0,  // External Interrupt 0
	EXTI_1,      // External Interrupt 1
	EXTI_2       // External Interrupt 2
} exti_interrupt_no_t;

// Enumeration for different edge detection modes for external interrupts
typedef enum {
	EXTI_LOW_LEVEL = 0,     // Low level detection
	EXTI_LOGICAL_CHANGE,    // Logical change detection
	EXTI_FALLING_EDGE,      // Falling edge detection
	EXTI_RISING_EDGE        // Rising edge detection
} exti_edge_detection_t;




/************************************************************************************************/
/*									Function Prototypes     									*/
/************************************************************************************************/

/**
 * @brief Initializes an external interrupt with the specified edge detection.
 *
 * @param copy_enu_exti_interrupt_no The external interrupt number to initialize.
 * @param copy_enu_edge_detection The desired edge detection mode for the interrupt.
 * @return exti_enu_return_state_t The return state of the EXTI initialization:
 *         - EXTI_E_OK: Operation was successful.
 *         - EXTI_E_INVALID_ARG: Invalid interrupt number provided.
 * @note This function initializes the specified external interrupt with the provided edge detection mode.
 *       It updates the corresponding control registers and enables the global interrupt flag if needed.
 *       The return value indicates the success or failure of the initialization.
 */
exti_enu_return_state_t ext_interrupt_init(exti_interrupt_no_t copy_enu_exti_interrupt_no, exti_edge_detection_t copy_enu_edge_detection);

/**
 * @brief Enables an external interrupt.
 *
 * @param copy_enu_exti_interrupt_no The external interrupt number to enable.
 * @return exti_enu_return_state_t The return state of the EXTI enable operation:
 *         - EXTI_E_OK: Operation was successful.
 *         - EXTI_E_INVALID_ARG: Invalid interrupt number provided.
 * @note This function enables the specified external interrupt by setting the corresponding global interrupt enable bit.
 *       It also invokes the "sei()" assembly instruction to globally enable interrupts.
 *       The return value indicates the success or failure of the enable operation.
 */
exti_enu_return_state_t ext_interrupt_enable(exti_interrupt_no_t copy_enu_exti_interrupt_no);

/**
 * @brief Disables an external interrupt.
 *
 * @param copy_enu_exti_interrupt_no The external interrupt number to disable.
 * @return exti_enu_return_state_t The return state of the EXTI disable operation:
 *         - EXTI_E_OK: Operation was successful.
 *         - EXTI_E_INVALID_ARG: Invalid interrupt number provided.
 * @note This function disables the specified external interrupt by clearing the corresponding global interrupt enable bit.
 *       The return value indicates the success or failure of the disable operation.
 */
exti_enu_return_state_t ext_interrupt_disable(exti_interrupt_no_t copy_enu_exti_interrupt_no);

/**
 * @brief Sets a callback function for an external interrupt and initializes it.
 *
 * @param copy_enu_exti_interrupt_no The external interrupt number to set the callback for.
 * @param callback A pointer to the callback function to be set.
 * @return exti_enu_return_state_t The return state of the EXTI callback and initialization:
 *         - EXTI_E_OK: Operation was successful.
 *         - EXTI_E_INVALID_ARG: Invalid interrupt number provided.
 * @note This function sets the provided callback function for the specified external interrupt,
 *       and also initializes the interrupt by disabling its global interrupt enable bit.
 *       The return value indicates the success or failure of the operation.
 */
exti_enu_return_state_t ext_interrupt_set_callback_init(exti_interrupt_no_t copy_enu_exti_interrupt_no ,void(*callback)(void));

#endif