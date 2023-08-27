
/**
 * @file BUTTON_interface.h
 *
 * @date 2023-08-23
 * @author Arafa Arafa
 */


#ifndef BUTTON_INTERFACE_H_
#define BUTTON_INTERFACE_H_
#include "BUTTON_config.h"
#include "../../MCAL/DIO/DIO_interface.h"


/************************************************************************************************/
/*									Enumerated Datatypes										*/
/************************************************************************************************/

/**
 * @brief Enumeration for button states.
 *
 * This enumeration defines the possible states of a button.
 */
typedef enum {
	BTN_PUSHED,     /**< Button is pushed. */
	BTN_RELEASED,   /**< Button is released. */
} btn_enu_state_t;

/**
 * @brief Enumeration for button return states.
 *
 * This enumeration defines the return states of button-related functions.
 */
typedef enum {
	BTN_E_OK,       /**< Button-related function executed successfully. */
	BTN_NOT_OK      /**< Button-related function encountered an error. */
} btn_enu_return_state_t;

/**
 * @brief Button configuration structure.
 *
 * This structure holds the configuration information for a button.
 */
typedef struct {
	dio_enu_port_t 	enu_port;   /**< Button's connected port. */
	dio_enu_pin_t 	enu_pin;    /**< Button's connected pin. */
} btn_str_config_t;




/************************************************************************************************/
/*									Function Prototypes     									*/
/************************************************************************************************/
/**
 * @brief Initialize a button based on the provided configuration.
 *
 * This function initializes a button based on the provided button configuration. It sets the
 * specified pin of the specified port as an input pin, configuring it to be used as a button.
 *
 * @param ptr_str_btn_config Pointer to the button configuration structure.
 * @return The initialization state of the button.
 *         - BTN_E_OK: Button initialized successfully.
 *         - BTN_NOT_OK: Button initialization failed due to a NULL configuration pointer.
 *
 * @note The button configuration structure contains the port and pin information.
 */
btn_enu_return_state_t BTN_init(const btn_str_config_t *ptr_str_btn_config);


/**
 * @brief Get the state of a button based on the provided configuration.
 *
 * This function reads the state of a button based on the provided button configuration.
 * It employs a debounce mechanism to ensure accurate button state detection. The function
 * reads the button's pin state and checks it over a specified time period to account for
 * bouncing. After the debounce period, the button's state is determined as pushed or released.
 *
 * @param ptr_str_btn_config Pointer to the button configuration structure.
 * @param ptr_enu_btn_state Pointer to the button state variable to be updated.
 * @return The state of the button reading operation.
 *         - BTN_E_OK: Button state read successfully.
 *         - BTN_NOT_OK: Button state reading failed due to NULL configuration or state pointer.
 *
 * @note The button configuration structure contains the port and pin information.
 * @note The function employs a debounce mechanism to ensure accurate button state detection.
 * @note The debounce threshold and checking time are constants defined in the module.
 */
btn_enu_return_state_t BTN_get_state(const btn_str_config_t *ptr_str_btn_config, btn_enu_state_t *ptr_enu_btn_state);


#endif 