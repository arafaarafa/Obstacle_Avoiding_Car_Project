
/**
 * @file EXTI_manager_prog.c
 *
 * @date 2023-08-21
 * @author Arafa Arafa
 */

#include "EXTI_manager_interface.h"



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
extim_enu_return_state_t extim_init(extim_str_config_t *ptr_str_extim_config, ptr_to_v_fun_in_void_t ptr_callback_func){

    extim_enu_return_state_t enu_return_state = EXTIM_E_OK;
	
	if((ptr_str_extim_config != NULL) && (ptr_callback_func != NULL)){
		ext_interrupt_set_callback_init(ptr_str_extim_config->enu_exti_interrupt_no , ptr_callback_func);
		ext_interrupt_init(ptr_str_extim_config->enu_exti_interrupt_no, ptr_str_extim_config->enu_edge_detection);
	}else{
		enu_return_state = EXTIM_NULL_PTR;
	}
    
    return enu_return_state;
}

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
extim_enu_return_state_t extim_enable(extim_str_config_t *ptr_str_extim_config){
    
    extim_enu_return_state_t enu_return_state = EXTIM_E_OK;
	if( ptr_str_extim_config != NULL ){
		ext_interrupt_enable(ptr_str_extim_config->enu_exti_interrupt_no);
	}else{
		enu_return_state = EXTIM_NULL_PTR;
	}
    return enu_return_state;
}

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
extim_enu_return_state_t extim_disable(extim_str_config_t *ptr_str_extim_config){

	extim_enu_return_state_t enu_return_state = EXTIM_E_OK;
	if( ptr_str_extim_config != NULL ){
		ext_interrupt_disable(ptr_str_extim_config->enu_exti_interrupt_no);
	}else{
		enu_return_state = EXTIM_NULL_PTR;
	}
    return enu_return_state;
}
