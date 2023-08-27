/**
 * @file KEYPAD_prog.c
 *
 * @date 2023-08-23
 * @author Arafa Arafa
 */




#include "KEYPAD_interface.h"

/**
 * @brief 2D array representing the layout of a keypad.
 *
 * This 2D array holds the characters arranged in rows and columns to represent the layout of a keypad.
 * Each cell contains a character corresponding to a button on the keypad. This array can be used to map
 * row and column indexes to specific button characters.
 */
static uint8_t keypad[KEYPAD_ROWS_MAX][KEYPAD_COLS_MAX] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};
	
/**
 * @brief Initialize a keypad based on the provided configuration.
 *
 * This function initializes a keypad based on the provided keypad configuration. It configures
 * the specified row and column pins of the keypad and sets them to appropriate initial states.
 *
 * @param ptr_str_keypad_config Pointer to the keypad configuration structure.
 * @return The initialization state of the keypad.
 *         - KEYPAD_E_OK: Keypad initialized successfully.
 *         - KEYPAD_E_NOT_OK: Keypad initialization failed due to a NULL configuration pointer.
 *
 * @note The keypad configuration structure contains arrays of port and pin information for rows and columns.
 */
	
keypad_enu_return_state_t KEYPAD_init(keypad_str_config_t *ptr_str_keypad_config)
{
	keypad_enu_return_state_t enu_return_state = KEYPAD_E_OK;
	if(ptr_str_keypad_config == NULL)
	{
		enu_return_state=KEYPAD_E_NOT_OK;
	}
	else
	{
		
		for(uint8_t u8_counter = U8_ZERO_VALUE; u8_counter < KEYPAD_ROWS_MAX; u8_counter++){
			DIO_init(ptr_str_keypad_config->str_row_pins[u8_counter].enu_port, ptr_str_keypad_config->str_row_pins[u8_counter].enu_pin, DIO_PIN_INPUT);
			DIO_write_pin(ptr_str_keypad_config->str_row_pins[u8_counter].enu_port, ptr_str_keypad_config->str_row_pins[u8_counter].enu_pin, DIO_PIN_HIGH_LEVEL);
		}
		for(uint8_t u8_counter = U8_ZERO_VALUE; u8_counter < KEYPAD_COLS_MAX; u8_counter++){
			DIO_init(ptr_str_keypad_config->str_col_pins[u8_counter].enu_port, ptr_str_keypad_config->str_col_pins[u8_counter].enu_pin, DIO_PIN_OUTPUT);
			DIO_write_pin(ptr_str_keypad_config->str_col_pins[u8_counter].enu_port, ptr_str_keypad_config->str_col_pins[u8_counter].enu_pin, DIO_PIN_HIGH_LEVEL);
		}
	}
	return enu_return_state;
}



/**
 * @brief Read data from the keypad.
 *
 * This function reads data from the keypad based on the provided keypad configuration.
 * It scans through the columns and rows of the keypad to detect button presses and
 * returns the corresponding character. If no button is pressed, it returns 'N'.
 *
 * @param ptr_str_keypad_config Pointer to the keypad configuration structure.
 * @param ptr_u8_data Pointer to the variable where the read data will be stored.
 * @return The state of the keypad read operation.
 *         - KEYPAD_E_OK: Data read successfully.
 *         - KEYPAD_NULL_PTR: Null pointer provided for configuration or data.
 *         - KEYPAD_NO_DATA: No button data detected.
 */
keypad_enu_return_state_t KEYPAD_read (keypad_str_config_t *ptr_str_keypad_config, uint8_t *ptr_u8_data){
	
	keypad_enu_return_state_t enu_return_state=KEYPAD_E_OK;
	uint8_t u8_col_counter;
	uint8_t u8_row_counter;
	uint8_t	u8_catched_data_flag = U8_ZERO_VALUE;
	dio_enu_level_t enu_pin_level;
	

	
	if((ptr_str_keypad_config == NULL) || (ptr_u8_data == NULL)){
		enu_return_state = KEYPAD_NULL_PTR;
	}else{
		
		for(uint8_t u8_counter = U8_ZERO_VALUE; u8_counter < KEYPAD_COLS_MAX; u8_counter++){
			DIO_write_pin(ptr_str_keypad_config->str_col_pins[u8_counter].enu_port, ptr_str_keypad_config->str_col_pins[u8_counter].enu_pin, DIO_PIN_HIGH_LEVEL);
		}
		
		for(u8_col_counter = U8_ZERO_VALUE; (u8_col_counter < KEYPAD_COLS_MAX) && (u8_catched_data_flag != U8_ONE_VALUE); u8_col_counter++)
		{
			DIO_write_pin(ptr_str_keypad_config->str_col_pins[u8_col_counter].enu_port, ptr_str_keypad_config->str_col_pins[u8_col_counter].enu_pin, DIO_PIN_LOW_LEVEL);
			for(u8_row_counter = U8_ZERO_VALUE; u8_row_counter<KEYPAD_ROWS_MAX; u8_row_counter++)
			{
				DIO_read_pin(ptr_str_keypad_config->str_row_pins[u8_row_counter].enu_port, ptr_str_keypad_config->str_row_pins[u8_row_counter].enu_pin, &enu_pin_level);
				if(enu_pin_level == DIO_PIN_LOW_LEVEL)
				{
					while(enu_pin_level == DIO_PIN_LOW_LEVEL)
					{
						DIO_read_pin(ptr_str_keypad_config->str_row_pins[u8_row_counter].enu_port, ptr_str_keypad_config->str_row_pins[u8_row_counter].enu_pin, &enu_pin_level);
					}
					*ptr_u8_data = keypad[u8_row_counter][u8_col_counter];
					u8_catched_data_flag = U8_ONE_VALUE;
					break;
				}
				
			}
			DIO_write_pin(ptr_str_keypad_config->str_col_pins[u8_col_counter].enu_port, ptr_str_keypad_config->str_col_pins[u8_col_counter].enu_pin, DIO_PIN_HIGH_LEVEL);
		}
		
	}
	
	if(u8_catched_data_flag != U8_ONE_VALUE)
	{   
		*ptr_u8_data = 'N';
		enu_return_state = KEYPAD_NO_DATA;
	}
	else
	{
		
	}
	return enu_return_state;
}