/**
 * @file EXTI_manager_interface.h
 *
 * @date 2023-08-21
 * @author Arafa Arafa
 */


#ifndef EXTI_MANAGER_INTERFACE_H_
#define EXTI_MANAGER_INTERFACE_H_

#include "../../STD_LIB/bit_math.h"
#include "../../STD_LIB/std_types.h"
#include "../../MCAL/EXTI/EXTI_interface.h"




/************************************************************************************************/
/*									Enumerated Datatypes										*/
/************************************************************************************************/
/**
 * @brief Enumeration of possible return states for the external interrupt module.
 */
typedef enum{
	EXTIM_E_OK = 0,         /**< External interrupt operation completed successfully. */
	EXTIM_E_NOK,            /**< External interrupt operation completed with an error. */
	EXTIM_NULL_PTR          /**< External interrupt operation failed due to a NULL pointer. */
} extim_enu_return_state_t;

/**
 * @brief Configuration structure for external interrupts.
 *
 * This structure holds the configuration parameters for setting up an external interrupt,
 * including the interrupt number and edge detection type.
 */
typedef struct 
{
	exti_interrupt_no_t					enu_exti_interrupt_no;    /**< External interrupt number. */
	exti_edge_detection_t				enu_edge_detection;       /**< Edge detection type for the interrupt. */
} extim_str_config_t;





/************************************************************************************************/
/*									Enumerated Datatypes										*/
/************************************************************************************************/



/************************************************************************************************/
/*									Function Prototypes     									*/
/************************************************************************************************/

/**
 * @brief Initialize an external interrupt based on the provided configuration.
 *
 * This function initializes an external interrupt based on the provided external interrupt configuration.
 * It sets the callback function for the specified external interrupt number and configures the edge detection.
 *
 * @param ptr_str_extim_config Pointer to the external interrupt configuration structure.
 * @param ptr_callback_func Pointer to the callback function to be invoked on interrupt.
 * @return The initialization state of the external interrupt.
 *         - EXTIM_E_OK: External interrupt initialized successfully.
 *         - EXTIM_NULL_PTR: External interrupt initialization failed due to a NULL pointer.
 */
extim_enu_return_state_t extim_init(extim_str_config_t *ptr_str_extim_config, ptr_to_v_fun_in_void_t ptr_callback_func);

/**
 * @brief Enable an external interrupt based on the provided configuration.
 *
 * This function enables an external interrupt based on the provided external interrupt configuration.
 *
 * @param ptr_str_extim_config Pointer to the external interrupt configuration structure.
 * @return The enabling state of the external interrupt.
 *         - EXTIM_E_OK: External interrupt enabled successfully.
 *         - EXTIM_NULL_PTR: External interrupt enabling failed due to a NULL pointer.
 */
extim_enu_return_state_t extim_enable(extim_str_config_t *ptr_str_extim_config);

/**
 * @brief Disable an external interrupt based on the provided configuration.
 *
 * This function disables an external interrupt based on the provided external interrupt configuration.
 *
 * @param ptr_str_extim_config Pointer to the external interrupt configuration structure.
 * @return The disabling state of the external interrupt.
 *         - EXTIM_E_OK: External interrupt disabled successfully.
 *         - EXTIM_NULL_PTR: External interrupt disabling failed due to a NULL pointer.
 */
extim_enu_return_state_t extim_disable(extim_str_config_t *ptr_str_extim_config);


#endif

