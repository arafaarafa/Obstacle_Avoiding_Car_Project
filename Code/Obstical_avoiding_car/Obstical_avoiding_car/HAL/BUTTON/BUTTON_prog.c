/**
 * @file BUTTON_prog.c
 *
 * @date 2023-08-23
 * @author Arafa Arafa
 */


#include "BUTTON_interface.h"
#include "BUTTON_config.h"
#include "../../MCAL/DIO/DIO_interface.h"

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
btn_enu_return_state_t BTN_init(const btn_str_config_t *ptr_str_btn_config)
{
	btn_enu_return_state_t enu_return_state = BTN_E_OK;

	if(ptr_str_btn_config != NULL) {
		// Initialize the specified pin of the specified port as an input pin
		DIO_init(ptr_str_btn_config->enu_port, ptr_str_btn_config->enu_pin, DIO_PIN_INPUT);
	} else {
		enu_return_state = BTN_NOT_OK;
	}

	return enu_return_state;
}

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
btn_enu_return_state_t BTN_get_state(const btn_str_config_t *ptr_str_btn_config, btn_enu_state_t *ptr_enu_btn_state)
{
	btn_enu_return_state_t enu_return_state = BTN_E_OK;
	dio_enu_level_t enu_pin_state;
	uint16_t u16_button_time_counter = 0;
	uint16_t u16_debounceThreshold_counter = 0;

	if((ptr_str_btn_config != NULL) && (ptr_enu_btn_state != NULL)) {
		DIO_read_pin(ptr_str_btn_config->enu_port, ptr_str_btn_config->enu_pin, &enu_pin_state);

		if(enu_pin_state == DIO_PIN_LOW_LEVEL) {
			u16_debounceThreshold_counter++;

			while(u16_button_time_counter < BUTTON_CHECKING_TIME) {
				DIO_read_pin(ptr_str_btn_config->enu_port, ptr_str_btn_config->enu_pin, &enu_pin_state);
				
				if(enu_pin_state == DIO_PIN_LOW_LEVEL) {
					u16_debounceThreshold_counter++;
				} else {
					/* Button released during the checking time */
				}
				
				u16_button_time_counter++;
			}
			
			if(u16_debounceThreshold_counter >= BUTTON_DEBOUNCE_THRESHOLD) {
				*ptr_enu_btn_state = BTN_PUSHED;
			} else {
				*ptr_enu_btn_state = BTN_RELEASED;
			}
		} else {
			/* Button is not pushed */
			*ptr_enu_btn_state = BTN_RELEASED;
		}
	} else {
		/* Invalid input parameters */
		enu_return_state = BTN_NOT_OK;
	}

	return enu_return_state;
}


