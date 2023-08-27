/**
 * @file DIO_interface.h
 *
 * @date 2023-08-21
 * @author Arafa Arafa
 */


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


#include "../../STD_LIB/bit_math.h"
#include "../../STD_LIB/std_types.h"

/**
 * @brief Enumeration of available port options.
 *
 * This enumeration defines the available port options for digital I/O operations.
 * These options correspond to the different ports on a microcontroller.
 */
typedef enum 
{
	PORTA=0, 
	PORTB,
	PORTC,
	PORTD
} dio_enu_port_t;

/**
 * @brief Enumeration of available pin options.
 *
 * This enumeration defines the available pin options for digital I/O operations.
 * These options correspond to the different pins on a microcontroller.
 */
typedef enum 
{
	PIN0=0,
	PIN1, 
	PIN2, 
	PIN3, 
	PIN4, 
	PIN5, 
	PIN6, 
	PIN7
} dio_enu_pin_t;

/**
 * @brief Enumeration of possible output levels for a pin.
 *
 * This enumeration defines the possible output levels for a digital pin.
 * It is used to set the output state of a pin to either a high or low level.
 */
typedef enum{

	DIO_PIN_LOW_LEVEL,    /**< Pin output is set to low level. */
	DIO_PIN_HIGH_LEVEL    /**< Pin output is set to high level. */

}dio_enu_level_t;

/**
 * @brief Enumeration of possible return states for DIO functions.
 *
 * This enumeration defines the possible return states for various DIO functions.
 * It indicates the success or failure of the DIO operations and can be used to handle errors.
 */
typedef enum{
	DIO_OK,                /**< DIO operation successful. */
	DIO_INVALID_PIN,       /**< Invalid pin specified. */
	DIO_INVALID_PORT       /**< Invalid port specified. */
}dio_enu_return_state_t;

/**
 * @brief Enumeration of possible directions for a pin.
 *
 * This enumeration defines the possible directions that a pin can be configured as.
 * It is used to set whether a pin functions as an input or output.
 */
typedef enum{
	DIO_PIN_INPUT = 0,     /**< Pin is configured as input. */
	DIO_PIN_OUTPUT         /**< Pin is configured as output. */

}dio_u8_enu_direction_t;





/**
 * @brief Initializes a digital I/O pin.
 *
 * This function sets the data direction (input or output) of a specific pin on a specific port.
 *
 * @param copy_enu_port The port to which the pin belongs (PORTA, PORTB, PORTC, or PORTD).
 * @param copy_enu_pin The pin number to be initialized.
 * @param copy_enu_direction The desired data direction (DIO_PIN_INPUT or DIO_PIN_OUTPUT).
 * @return dio_enu_return_state_t The return state of the initialization operation.
 *                                Possible values:
 *                                - DIO_OK: The pin initialization was successful.
 *                                - DIO_INVALID_PORT: The specified port is not valid.
 *                                - DIO_INVALID_PIN: The specified pin number is not valid.
 */
dio_enu_return_state_t DIO_init (dio_enu_port_t copy_enu_port, dio_enu_pin_t copy_enu_pin, dio_u8_enu_direction_t copy_enu_direction);

/**
 * @brief Writes a digital value to a specific pin on a specific port.
 *
 * This function sets the output state (high or low) of a specific pin on a specific port.
 *
 * @param copy_enu_port The port to which the pin belongs (PORTA, PORTB, PORTC, or PORTD).
 * @param copy_enu_pin The pin number to write to.
 * @param copy_enu_state The desired output state (DIO_PIN_HIGH_LEVEL or DIO_PIN_LOW_LEVEL).
 * @return dio_enu_return_state_t The return state of the write operation.
 *                                Possible values:
 *                                - DIO_OK: The write operation was successful.
 *                                - DIO_INVALID_PORT: The specified port is not valid.
 *                                - DIO_INVALID_PIN: The specified pin number is not valid.
 */
dio_enu_return_state_t DIO_write_pin (dio_enu_port_t copy_enu_port, dio_enu_pin_t copy_enu_pin, dio_enu_level_t copy_enu_state);

/**
 * @brief Reads the digital value of a specific pin on a specific port.
 *
 * This function reads the current state (high or low) of a specific pin on a specific port
 * and stores the result in the provided pointer.
 *
 * @param copy_enu_port The port to which the pin belongs (PORTA, PORTB, PORTC, or PORTD).
 * @param copy_enu_pin The pin number to read from.
 * @param ptr_enu_state Pointer to the location where the read value will be stored.
 * @return dio_enu_return_state_t The return state of the read operation.
 *                                Possible values:
 *                                - DIO_OK: The read operation was successful.
 *                                - DIO_INVALID_PORT: The specified port is not valid.
 *                                - DIO_INVALID_PIN: The specified pin number is not valid.
 */
dio_enu_return_state_t DIO_read_pin (dio_enu_port_t copy_enu_port, dio_enu_pin_t copy_enu_pin, dio_enu_level_t	*ptr_enu_state);

#endif /* DIO_H_ */