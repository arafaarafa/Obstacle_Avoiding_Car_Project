
/**
 * @file LCD_cmd.h
 *
 * @date 2023-08-22
 * @author Arafa Arafa
 */ 




#ifndef LCD_CMD_H_
#define LCD_CMD_H_
/**
 * @def LCD_CGRAM_START_ADD
 * @brief LCD Character Generator RAM Start Address
 *
 * This constant defines the start address of the Character Generator RAM (CGRAM) in the LCD module.
 */
#define LCD_CGRAM_START_ADD              0x40

/**
 * @def LCD_DDRAM_START_ADD_LINE_1
 * @brief LCD Display Data RAM Start Address for Line 1
 *
 * This constant defines the start address of the Display Data RAM (DDRAM) for the first line of the LCD display.
 */
#define LCD_DDRAM_START_ADD_LINE_1       0x80

/**
 * @def LCD_DDRAM_START_ADD_LINE_2
 * @brief LCD Display Data RAM Start Address for Line 2
 *
 * This constant defines the start address of the Display Data RAM (DDRAM) for the second line of the LCD display.
 */
#define LCD_DDRAM_START_ADD_LINE_2       0xC0

/**
 * @def LCD_CMD_CLEAR
 * @brief Clear Display Command
 *
 * This constant defines the command code to clear the entire content of the LCD display.
 */
#define LCD_CMD_CLEAR                    0x01

/**
 * @def LCD_CMD_CURSOR_HOME
 * @brief Return Home (Cursor to Start) Command
 *
 * This constant defines the command code to return the cursor to the starting position (home) of the LCD display.
 */
#define LCD_CMD_CURSOR_HOME              0x02

 

/**
 * @def LCD_DISPLAY_ON_CUR_ON_BLOCK_ON
 * @brief Display On, Cursor On, Blinking Block Cursor On
 *
 * This constant defines the command code to turn on the display, enable the cursor, and enable blinking of the block cursor.
 */
#define LCD_DISPLAY_ON_CUR_ON_BLOCK_ON   0x0F

/**
 * @def LCD_DISPLAY_OFF_CUR_OFF_BLOCK_OFF
 * @brief Display Off, Cursor Off, Block Cursor Off
 *
 * This constant defines the command code to turn off the display, disable the cursor, and disable the block cursor.
 */
#define LCD_DISPLAY_OFF_CUR_OFF_BLOCK_OFF 0x08

/**
 * @def LCD_DISPLAY_ON_CUR_OFF_BLOCK_OFF
 * @brief Display On, Cursor Off, Block Cursor Off
 *
 * This constant defines the command code to turn on the display, disable the cursor, and disable the block cursor.
 */
#define LCD_DISPLAY_ON_CUR_OFF_BLOCK_OFF 0x0C

/**
 * @def LCD_DISPLAY_ON_CUR_ON_BLOCK_OFF
 * @brief Display On, Cursor On, Block Cursor Off
 *
 * This constant defines the command code to turn on the display, enable the cursor, and disable the block cursor.
 */
#define LCD_DISPLAY_ON_CUR_ON_BLOCK_OFF  0x0E

/**
 * @def LCD_DISPLAY_ON_CUR_OFF_BLOCK_ON
 * @brief Display On, Cursor Off, Blinking Block Cursor On
 *
 * This constant defines the command code to turn on the display, disable the cursor, and enable blinking of the block cursor.
 */
#define LCD_DISPLAY_ON_CUR_OFF_BLOCK_ON  0x0D

/**
 * @def LCD_4BITS_2LINES_58DM
 * @brief LCD Configuration: 4-bit Data Mode, 2 Lines, 5x8 Dot Matrix
 *
 * This constant defines the command code for configuring the LCD to work in 4-bit data mode, 2 lines, and 5x8 dot matrix.
 */
#define LCD_4BITS_2LINES_58DM             0x28

/**
 * @def LCD_8BITS_2LINES_511DM
 * @brief LCD Configuration: 8-bit Data Mode, 2 Lines, 5x11 Dot Matrix
 *
 * This constant defines the command code for configuring the LCD to work in 8-bit data mode, 2 lines, and 5x11 dot matrix.
 */
#define LCD_8BITS_2LINES_511DM            0x32

/**
 * @def LCD_8BITS_2LINES_58DM
 * @brief LCD Configuration: 8-bit Data Mode, 2 Lines, 5x8 Dot Matrix
 *
 * This constant defines the command code for configuring the LCD to work in 8-bit data mode, 2 lines, and 5x8 dot matrix.
 */
#define LCD_8BITS_2LINES_58DM             0x38

/**
 * @def LCD_CMD_ENTRY_MODE_INCREMENT_ON_SHIFT_OFF
 * @brief LCD Command: Entry Mode Set - Increment Cursor, Shift Off
 *
 * This constant defines the command code for configuring the LCD entry mode to increment the cursor position
 * after each data write and disable the display shift.
 */
#define LCD_CMD_ENTRY_MODE_INCREMENT_ON_SHIFT_OFF   0x06

#endif