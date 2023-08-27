/**
 * @file keypad_interface.h
 *
 * @date 2023-08-23
 * @author Arafa Arafa
 */


#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_


#include "../../MCAL/DIO/DIO_interface.h"

/**
 * @def KEYPAD_ROWS_MAX
 * @brief Maximum number of rows in the keypad matrix.
 *
 * This macro defines the maximum number of rows in the keypad matrix.
 */
#define KEYPAD_ROWS_MAX             4

/**
 * @def KEYPAD_COLS_MAX
 * @brief Maximum number of columns in the keypad matrix.
 *
 * This macro defines the maximum number of columns in the keypad matrix.
 */
#define KEYPAD_COLS_MAX             3



/************************************************************************************************/
/*									Enumerated Datatypes										*/
/************************************************************************************************/
/**
 * @struct keypad_str_unit_t
 * @brief Keypad Row or Column Unit Configuration
 *
 * This structure defines the configuration for a single unit (row or column) of the keypad.
 * It includes the port and pin information to identify the specific unit.
 */
typedef struct
{
    dio_enu_port_t enu_port; /**< The port of the keypad unit. */
    dio_enu_pin_t enu_pin;   /**< The pin of the keypad unit. */
} keypad_str_unit_t;

/**
 * @struct keypad_str_config_t
 * @brief Keypad Configuration
 *
 * This structure defines the configuration for the keypad. It includes arrays of row and column units
 * to represent the rows and columns of the keypad. Each unit is defined by its port and pin information.
 */
typedef struct
{
    keypad_str_unit_t str_row_pins[KEYPAD_ROWS_MAX]; /**< Array of keypad row units. */
    keypad_str_unit_t str_col_pins[KEYPAD_COLS_MAX]; /**< Array of keypad column units. */
} keypad_str_config_t;

/**
 * @enum keypad_enu_return_state_t
 * @brief Keypad Operation Return States
 *
 * This enumeration defines the possible return states for keypad operations.
 * - KEYPAD_E_OK: Operation was successful.
 * - KEYPAD_E_NOT_OK: Operation failed.
 * - KEYPAD_NULL_PTR: Operation failed due to a NULL pointer.
 * - KEYPAD_NO_DATA: No data was read from the keypad.
 */
typedef enum{
    KEYPAD_E_OK,
    KEYPAD_E_NOT_OK,
    KEYPAD_NULL_PTR,
    KEYPAD_NO_DATA
}keypad_enu_return_state_t;





/************************************************************************************************/
/*									Function Prototypes     									*/
/************************************************************************************************/
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
keypad_enu_return_state_t KEYPAD_init(keypad_str_config_t *ptr_str_keypad_config);



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
keypad_enu_return_state_t KEYPAD_read(keypad_str_config_t *ptr_str_keypad_config, uint8_t *ptr_u8_data);



#endif /* KEYPAD_H	*/