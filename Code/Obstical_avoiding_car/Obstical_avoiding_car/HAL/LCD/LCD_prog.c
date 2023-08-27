/**
 * @file LCD_prog.c
 *
 * @date 2023-08-23
 * @author Arafa Arafa
 */



#include "LCD_interface.h"


/**
 * @brief Enable the LCD for data/command transmission.
 *
 * This function is responsible for generating the enabling pulse for the LCD's data/command transmission.
 * It sets the 'E' (Enable) signal to a high level for a brief moment, followed by setting it back to a low level.
 * This pulse triggers the LCD to read the data or command being sent to it.
 *
 * @param ptr_str_config Pointer to the LCD configuration structure.
 *
 * @note This function is a part of the mechanism to enable the LCD for data or command transmission.
 * It generates the necessary pulse on the 'E' signal to initiate the read or write operation.
 * A short delay is included after setting 'E' high and before setting it low again to ensure proper timing.
 */
static void ENABLE(lcd_str_config_t* ptr_str_config);

/**
 * @brief Delay for approximately 3 milliseconds.
 *
 * This function implements a busy-wait delay for a duration of approximately 3 milliseconds.
 * It uses a loop to execute a certain number of iterations to achieve the desired delay period.
 * The loop counter is declared as 'volatile' to prevent compiler optimization.
 *
 * @note The actual delay period may vary based on factors such as the processor clock frequency.
 * This delay method is not accurate and may not be suitable for precise timing requirements.
 */
static void delay_3_ms(void);


/**
 * @brief Initialize the LCD module based on the provided configuration.
 *
 * This function initializes the LCD module based on the provided LCD configuration. It sets up the required
 * control and data pins and sends the necessary initialization commands to configure the LCD display.
 *
 * @param ptr_str_config Pointer to the LCD configuration structure.
 * @return The initialization state of the LCD.
 *         - LCD_E_OK: LCD initialized successfully.
 *         - LCD_E_NOT_OK: LCD initialization failed due to an unsupported mode.
 *
 * @note The LCD configuration structure contains pin information for control pins (RS, RW, E) and data pins,
 * as well as the LCD mode (4-bit or 8-bit).
 */
lcd_enu_return_state_t LCD_init(lcd_str_config_t* ptr_str_config)
{
	lcd_enu_return_state_t enu_return_state = LCD_E_OK;
	
	enu_return_state |=DIO_init(ptr_str_config->str_RSpin.enu_port, ptr_str_config->str_RSpin.enu_pin, DIO_PIN_OUTPUT);
	enu_return_state |=DIO_init(ptr_str_config->str_RWpin.enu_port, ptr_str_config->str_RWpin.enu_pin, DIO_PIN_OUTPUT);
	enu_return_state |=DIO_init(ptr_str_config->str_Epin.enu_port, ptr_str_config->str_Epin.enu_pin, DIO_PIN_OUTPUT);
	
	if(ptr_str_config->enu_mode == LCD_4_BIT_MODE)
	{
		
		
		for(uint8_t u8_counter = U8_ZERO_VALUE; u8_counter < LCD_MAX_DATA_PINS_MOD_4; u8_counter++){
			enu_return_state |=DIO_init(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin, DIO_PIN_OUTPUT);
		}
		LCD_cmd(ptr_str_config, LCD_CMD_CURSOR_HOME);
		LCD_cmd(ptr_str_config, LCD_4BITS_2LINES_58DM);
		LCD_cmd(ptr_str_config, LCD_DISPLAY_ON_CUR_OFF_BLOCK_OFF);
		LCD_cmd(ptr_str_config, LCD_CMD_ENTRY_MODE_INCREMENT_ON_SHIFT_OFF);
		LCD_cmd(ptr_str_config, LCD_CMD_CLEAR);						
								
	}else if(ptr_str_config->enu_mode == LCD_8_BIT_MODE){
		for(uint8_t u8_counter = U8_ZERO_VALUE; u8_counter < LCD_MAX_DATA_PINS_MOD_8; u8_counter++){
			enu_return_state |=DIO_init(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin, DIO_PIN_OUTPUT);
		}
		LCD_cmd(ptr_str_config, LCD_8BITS_2LINES_58DM);
		LCD_cmd(ptr_str_config, LCD_DISPLAY_ON_CUR_OFF_BLOCK_OFF);
		LCD_cmd(ptr_str_config, LCD_CMD_ENTRY_MODE_INCREMENT_ON_SHIFT_OFF);
		LCD_cmd(ptr_str_config, LCD_CMD_CLEAR);
							
	}else{
		enu_return_state=LCD_E_NOT_OK;						
	}
	return enu_return_state;
}

/**
 * @brief Clear the LCD display.
 *
 * This function sends the command to clear the LCD display, which removes any content displayed
 * on the screen and resets the cursor position to the beginning of the first line.
 *
 * @param ptr_str_config Pointer to the LCD configuration structure.
 * @return The state of the LCD clear operation.
 *         - LCD_E_OK: LCD cleared successfully.
 *         - LCD_E_NOT_OK: LCD clear operation failed.
 *
 * @note This function sends the clear command and then introduces a delay of approximately 3 milliseconds
 * to ensure the clear operation completes before returning.
 */
lcd_enu_return_state_t LCD_clear (lcd_str_config_t* ptr_str_config)
{

	lcd_enu_return_state_t enu_return_state=LCD_E_OK;
	enu_return_state |= LCD_cmd(ptr_str_config,LCD_CMD_CLEAR);
	delay_3_ms();
	return enu_return_state;

}


/**
 * @brief Set the cursor position on the LCD display.
 *
 * This function sets the position of the cursor on the LCD display based on the specified row
 * and column indices. It calculates the appropriate DDRAM address based on the selected row
 * and column, and sends the command to position the cursor at that address.
 *
 * @param ptr_str_config Pointer to the LCD configuration structure.
 * @param copy_enu_row The row on the LCD where the cursor should be positioned.
 * @param copy_enu_col The column on the LCD where the cursor should be positioned.
 * @return The state of the cursor position setting operation.
 *         - LCD_E_OK: Cursor position set successfully.
 *         - LCD_E_NOT_OK: Cursor position setting operation failed due to an invalid row selection.
 *
 * @note The function calculates the appropriate DDRAM address for the specified row and column indices,
 * and sends the command to set the cursor position to that address on the LCD.
 */
lcd_enu_return_state_t LCD_setCursor (lcd_str_config_t* ptr_str_config, lcd_enu_row_select_t copy_enu_row, lcd_enu_col_select_t copy_enu_col)
{
	lcd_enu_return_state_t enu_return_state=LCD_E_OK;
	if(copy_enu_row == LCD_ROW_1)
	{
		LCD_cmd(ptr_str_config, LCD_DDRAM_START_ADD_LINE_1 + copy_enu_col);
		
	}else if(copy_enu_row == LCD_ROW_2){
		LCD_cmd(ptr_str_config, LCD_DDRAM_START_ADD_LINE_2 + copy_enu_col);	

	}else{
		
		enu_return_state=LCD_E_NOT_OK;
	}

	return enu_return_state;

}

/**
 * @brief Write a null-terminated string to the LCD display.
 *
 * This function writes a null-terminated string of characters to the LCD display.
 * It iterates through each character in the input string and sends individual characters
 * to the LCD using the LCD_char function. The function continues writing characters
 * until the null-terminator is encountered.
 *
 * @param ptr_str_config Pointer to the LCD configuration structure.
 * @param ptr_u8_data Pointer to the null-terminated string to be written.
 * @return The state of the string writing operation.
 *         - LCD_E_OK: String written successfully.
 *         - LCD_NULL_PTR: The input string pointer is NULL.
 *
 * @note The function iterates through the input string and sends each character to the LCD using
 * the LCD_char function until the null-terminator ('\0') is encountered.
 */
lcd_enu_return_state_t LCD_writeString (lcd_str_config_t *ptr_str_config, uint8_t *ptr_u8_data)
{
	uint8_t u8_char_counter = 0;
	lcd_enu_return_state_t enu_return_state=LCD_E_OK;
	if(ptr_u8_data == NULL)
	{
		enu_return_state = LCD_NULL_PTR;
	}

	else
	{
		while(ptr_u8_data[u8_char_counter] !='\0')
		{
			LCD_char(ptr_str_config,ptr_u8_data[u8_char_counter]);
			u8_char_counter++;
			
		}
	}
	return enu_return_state;
	

}


/**
* @brief Write a custom special character to the LCD display.
*
* This function writes a custom special character to the LCD display.
* It takes a special character type as input and uses predefined data values to generate
* the custom character's pattern. The generated character pattern is written to the LCD CGRAM
* (Character Generator RAM) at the specified position for special characters.
*
* @param ptr_str_config Pointer to the LCD configuration structure.
* @param u8_SpChar The type of special character to be written.
* @return The state of the special character writing operation.
*         - LCD_E_OK: Special character written successfully.
*
* @note This function generates the custom special character pattern using predefined data values
* and writes it to the LCD CGRAM (Character Generator RAM) at the specified position for special characters.
* The function then positions the cursor at the start of the next line and writes the special character to the display.
*/
lcd_enu_return_state_t LCD_writeSpChar (lcd_str_config_t *ptr_str_config, u8_en_lcdSpCharType u8_SpChar)
{   lcd_enu_return_state_t enu_return_state=LCD_E_OK;
	uint8_t sp_char[]= {0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00};
	uint8_t i;
	LCD_cmd(ptr_str_config,0x40+( u8_SpChar* 8));
	for(i=0;i<8;i++)
	{
		LCD_char(ptr_str_config,sp_char[i]);
	}	
	
	LCD_cmd(ptr_str_config,0xc0);
	LCD_char(ptr_str_config,LCD_BELL);
	return enu_return_state;
}

/**
 * @brief Send a command to the LCD display.
 *
 * This function sends a command to the LCD display. It takes a command value as input and
 * transmits the command using appropriate control signals and data pins according to the
 * LCD's mode (4-bit or 8-bit).
 *
 * @param ptr_str_config Pointer to the LCD configuration structure.
 * @param cmd The command to be sent to the LCD.
 * @return The state of the command transmission operation.
 *         - LCD_E_OK: Command transmitted successfully.
 *
 * @note This function handles the transmission of the command to the LCD display.
 * It uses control signals like 'E', 'RS', and 'RW' to manage the data transmission.
 * Depending on the LCD's mode, it uses the appropriate number of data pins to transmit the command.
 */
lcd_enu_return_state_t LCD_cmd(lcd_str_config_t *ptr_str_config,uint8_t cmd)
{   lcd_enu_return_state_t enu_return_state=LCD_E_OK;
	lcd_enu_return_state_t u8_bit_counter = LCD_MSB_INDEX;
	DIO_write_pin(ptr_str_config->str_Epin.enu_port,ptr_str_config->str_Epin.enu_pin,DIO_PIN_LOW_LEVEL);
	DIO_write_pin(ptr_str_config->str_RSpin.enu_port,ptr_str_config->str_RSpin.enu_pin,DIO_PIN_LOW_LEVEL);
	DIO_write_pin(ptr_str_config->str_RWpin.enu_port,ptr_str_config->str_RWpin.enu_pin,DIO_PIN_LOW_LEVEL);
	if(ptr_str_config->enu_mode == LCD_4_BIT_MODE)
	{
		for(sint8_t u8_counter = LCD_MAX_DATA_PINS_MOD_4 - U8_ONE_VALUE; u8_counter >= U8_ZERO_VALUE; u8_counter--){
			if(READ_BIT(cmd,u8_bit_counter) == U8_ONE_VALUE){
				DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_HIGH_LEVEL);
			}else{
				DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_LOW_LEVEL);
			}
			u8_bit_counter--;
		}
		ENABLE(ptr_str_config);
		delay_3_ms();
	   for(sint8_t u8_counter = LCD_MAX_DATA_PINS_MOD_4-U8_ONE_VALUE; u8_counter >= U8_ZERO_VALUE; u8_counter--){
		   if(READ_BIT(cmd,u8_bit_counter) == U8_ONE_VALUE){
			   DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_HIGH_LEVEL);
			}else{
			   DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_LOW_LEVEL);
		   }
		   u8_bit_counter--;
	   }
		ENABLE(ptr_str_config);
		delay_3_ms();
	}
	else if(ptr_str_config->enu_mode == LCD_8_BIT_MODE)
	{
		for(uint8_t u8_counter = U8_ZERO_VALUE; u8_counter < LCD_MAX_DATA_PINS_MOD_8; u8_counter++){
			if(READ_BIT(cmd,u8_bit_counter) == U8_ONE_VALUE){
				DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_HIGH_LEVEL);
				}else{
				DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_LOW_LEVEL);
			}
			u8_bit_counter--;
		}
		ENABLE(ptr_str_config);
		delay_3_ms();	
	}
	else
	{
		//do nothing
		enu_return_state=LCD_E_NOT_OK;
	}
	delay_3_ms();
	return enu_return_state;
}


/**
 * @brief Display a character on the LCD.
 *
 * This function displays a character on the LCD screen. It takes a character value as input and
 * transmits the character's ASCII code to the LCD using appropriate control signals and data pins
 * based on the LCD's mode (4-bit or 8-bit).
 *
 * @param ptr_str_config Pointer to the LCD configuration structure.
 * @param cmd The character to be displayed on the LCD.
 *
 * @note This function sends the character data to the LCD display to show it on the screen.
 * It uses control signals 'E', 'RS', and 'RW' to manage the data transmission. Depending on
 * the LCD's mode, it uses the appropriate number of data pins to transmit the character's ASCII code.
 */

  void LCD_char(lcd_str_config_t *ptr_str_config, uint8_t cmd)
{
	lcd_enu_return_state_t u8_bit_counter = LCD_MSB_INDEX;
	DIO_write_pin(ptr_str_config->str_Epin.enu_port,ptr_str_config->str_Epin.enu_pin,DIO_PIN_LOW_LEVEL);
	DIO_write_pin(ptr_str_config->str_RSpin.enu_port,ptr_str_config->str_RSpin.enu_pin,DIO_PIN_HIGH_LEVEL);
	DIO_write_pin(ptr_str_config->str_RWpin.enu_port,ptr_str_config->str_RWpin.enu_pin,DIO_PIN_LOW_LEVEL);
	
	
	if(ptr_str_config->enu_mode == LCD_4_BIT_MODE)
	{
		
		for(sint8_t u8_counter = LCD_MAX_DATA_PINS_MOD_4-U8_ONE_VALUE; u8_counter >= U8_ZERO_VALUE; u8_counter--){
			if(READ_BIT(cmd,u8_bit_counter) == U8_ONE_VALUE){
				DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_HIGH_LEVEL);
				}else{
				DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_LOW_LEVEL);
			}
			u8_bit_counter--;
		}
		ENABLE(ptr_str_config);
		delay_3_ms();
		for(sint8_t u8_counter = LCD_MAX_DATA_PINS_MOD_4-U8_ONE_VALUE; u8_counter >= U8_ZERO_VALUE; u8_counter--){
			if(READ_BIT(cmd,u8_bit_counter) == U8_ONE_VALUE){
				DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_HIGH_LEVEL);
				}else{
				DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_LOW_LEVEL);
			}
			u8_bit_counter--;
		}
		ENABLE(ptr_str_config);
		delay_3_ms();
	}
	else if(ptr_str_config->enu_mode == LCD_8_BIT_MODE)
	{
		for(uint8_t u8_counter = U8_ZERO_VALUE; u8_counter < LCD_MAX_DATA_PINS_MOD_8; u8_counter++){
			if(READ_BIT(cmd,u8_bit_counter) == U8_ONE_VALUE){
				DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_HIGH_LEVEL);
				}else{
				DIO_write_pin(ptr_str_config->str_data_pins[u8_counter].enu_port, ptr_str_config->str_data_pins[u8_counter].enu_pin,DIO_PIN_LOW_LEVEL);
			}
			u8_bit_counter--;
		}
		ENABLE(ptr_str_config);
		delay_3_ms();
	}
	else
	{
		//do nothing
	}
}


/**
 * @brief Enable the LCD for data/command transmission.
 *
 * This function is responsible for generating the enabling pulse for the LCD's data/command transmission.
 * It sets the 'E' (Enable) signal to a high level for a brief moment, followed by setting it back to a low level.
 * This pulse triggers the LCD to read the data or command being sent to it.
 *
 * @param ptr_str_config Pointer to the LCD configuration structure.
 *
 * @note This function is a part of the mechanism to enable the LCD for data or command transmission.
 * It generates the necessary pulse on the 'E' signal to initiate the read or write operation.
 * A short delay is included after setting 'E' high and before setting it low again to ensure proper timing.
 */
void ENABLE(lcd_str_config_t* ptr_str_config)
{
	
	DIO_write_pin(ptr_str_config->str_Epin.enu_port, ptr_str_config->str_Epin.enu_pin, DIO_PIN_HIGH_LEVEL);
	delay_3_ms();
	DIO_write_pin(ptr_str_config->str_Epin.enu_port, ptr_str_config->str_Epin.enu_pin, DIO_PIN_LOW_LEVEL);


}


/**
 * @brief Delay for approximately 3 milliseconds.
 *
 * This function implements a busy-wait delay for a duration of approximately 3 milliseconds.
 * It uses a loop to execute a certain number of iterations to achieve the desired delay period.
 * The loop counter is declared as 'volatile' to prevent compiler optimization.
 *
 * @note The actual delay period may vary based on factors such as the processor clock frequency.
 * This delay method is not accurate and may not be suitable for precise timing requirements.
 */
void delay_3_ms(void){
	static uint32_t u32_desired_ticks = 5000;
	for(volatile uint32_t u32_counter = 0; u32_counter < u32_desired_ticks; u32_counter++);
	
}