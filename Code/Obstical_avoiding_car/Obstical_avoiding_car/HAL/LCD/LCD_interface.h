/**
 * @file LCD_interface.h
 *
 * @date 2023-08-23
 * @author Arafa Arafa
 */


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
#include "LCD_cmd.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../STD_LIB/bit_math.h"

/**
 * @brief Index of the most significant bit (MSB) in a byte (7 for an 8-bit byte).
 */
#define LCD_MSB_INDEX                   7

/**
 * @brief Maximum number of data pins used by the LCD (8 data pins).
 */
#define LCD_MAX_DATA_PINS               8

/**
 * @brief Maximum number of data pins used by the LCD in 4-bit mode (4 data pins).
 */
#define LCD_MAX_DATA_PINS_MOD_4         4

/**
 * @brief Maximum number of data pins used by the LCD in 8-bit mode (8 data pins).
 */
#define LCD_MAX_DATA_PINS_MOD_8         8


/**
 * @brief Pre-defined value representing the bell character in the user-defined special characters.
 */
#define LCD_BELL    ((u8_en_lcdSpCharType)0X03)

/************************************************************************************************/
/*									Enumerated Datatypes										*/
/************************************************************************************************/
/**
 * @brief Enumeration for different LCD operation modes.
 */
typedef enum{
    LCD_4_BIT_MODE,   /**< 4-bit mode */
    LCD_8_BIT_MODE,   /**< 8-bit mode */
    LCD_INVALID_MODE  /**< Invalid mode */
}lcd_enu_mode_t;

/**
 * @brief Enumeration for selecting the LCD row (line) to write data or perform actions.
 */
typedef enum{
	LCD_ROW_1 = 0,   /**< First row of the LCD */
	LCD_ROW_2        /**< Second row of the LCD */
}lcd_enu_row_select_t;

/**
 * @brief Enumeration for selecting the LCD column to write data or perform actions.
 *
 * This enumeration provides values for selecting the desired column (character position) on the LCD display.
 * Columns are numbered from 1 to 16 in a typical 16x2 character LCD module.
 */
typedef enum{
	LCD_COL_1 = 0,   /**< Column 1 of the LCD display */
	LCD_COL_2,       /**< Column 2 of the LCD display */
	LCD_COL_3,       /**< Column 3 of the LCD display */
	LCD_COL_4,       /**< Column 4 of the LCD display */
	LCD_COL_5,       /**< Column 5 of the LCD display */
	LCD_COL_6,       /**< Column 6 of the LCD display */
	LCD_COL_7,       /**< Column 7 of the LCD display */
	LCD_COL_8,       /**< Column 8 of the LCD display */
	LCD_COL_9,       /**< Column 9 of the LCD display */
	LCD_COL_10,      /**< Column 10 of the LCD display */
	LCD_COL_11,      /**< Column 11 of the LCD display */
	LCD_COL_12,      /**< Column 12 of the LCD display */
	LCD_COL_13,      /**< Column 13 of the LCD display */
	LCD_COL_14,      /**< Column 14 of the LCD display */
	LCD_COL_15,      /**< Column 15 of the LCD display */
	LCD_COL_16,      /**< Column 16 of the LCD display */
}lcd_enu_col_select_t;


/**
 * @brief Structure representing a unit of the LCD, consisting of a port and a pin.
 */
typedef struct
{
	dio_enu_port_t enu_port; /**< Port of the unit */
	dio_enu_pin_t enu_pin;   /**< Pin of the unit */
}lcd_str_unit_t;

/**
 * @brief Structure representing the configuration of the LCD module.
 */
typedef struct
{
	lcd_enu_mode_t enu_mode;           /**< Operating mode of the LCD */
	lcd_str_unit_t str_data_pins[LCD_MAX_DATA_PINS]; /**< Data pins of the LCD */
	lcd_str_unit_t str_RSpin;          /**< RS (Register Select) pin of the LCD */
	lcd_str_unit_t str_RWpin;          /**< RW (Read/Write) pin of the LCD */
	lcd_str_unit_t str_Epin;           /**< Enable (E) pin of the LCD */
}lcd_str_config_t;

/**
 * @brief Enumeration for the return states of LCD functions.
 */
typedef enum{
    LCD_E_OK,       /**< Function executed successfully */
    LCD_E_NOT_OK,   /**< Function execution failed */
	LCD_NULL_PTR    /**< Null pointer provided as argument */
}lcd_enu_return_state_t;

/**
 * @brief Type definition for user-defined special character types for the LCD.
 */
typedef uint8_t u8_en_lcdSpCharType;



/************************************************************************************************/
/*									Function Prototypes     									*/
/************************************************************************************************/

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
lcd_enu_return_state_t LCD_init (lcd_str_config_t *ptr_str_config);

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
lcd_enu_return_state_t LCD_cmd(lcd_str_config_t *ptr_str_config, uint8_t copy_u8_cmd);

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
void LCD_char(lcd_str_config_t *ptr_str_config, uint8_t copy_u8_data);


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
lcd_enu_return_state_t LCD_clear (lcd_str_config_t* ptr_str_config);

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
lcd_enu_return_state_t LCD_setCursor (lcd_str_config_t *ptr_str_config, lcd_enu_row_select_t copy_enu_row, lcd_enu_col_select_t copy_enu_col);


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
lcd_enu_return_state_t LCD_writeString (lcd_str_config_t *ptr_str_config, uint8_t *ptr_u8_data);

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
lcd_enu_return_state_t LCD_writeSpChar (lcd_str_config_t *ptr_str_config, u8_en_lcdSpCharType copy_u8_SpChar);


#endif /* LCD_INTERFACE_H	*/