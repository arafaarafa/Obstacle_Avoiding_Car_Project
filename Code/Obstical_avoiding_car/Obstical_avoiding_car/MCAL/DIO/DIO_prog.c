/**
 * @file DIO_prog.c
 *
 * @date 2023-08-21
 * @author Arafa Arafa
 */ 



#include "DIO_interface.h"
#include "DIO_private_.h"




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

dio_enu_return_state_t DIO_init (dio_enu_port_t copy_enu_port, dio_enu_pin_t copy_enu_pin, dio_u8_enu_direction_t copy_enu_direction)
{
	dio_enu_return_state_t enu_return_state = DIO_OK;

	if (copy_enu_pin < DIO_MAX_PINS)
	{
		if (copy_enu_port == PORTA)
		{
			DATA_DIRECTION_PORTA |= copy_enu_direction << copy_enu_pin;
			
		}
		else if (copy_enu_port == PORTB)
		{
			DATA_DIRECTION_PORTB |= copy_enu_direction << copy_enu_pin;
			
		}
		else if (copy_enu_port == PORTC)
		{
			DATA_DIRECTION_PORTC |= copy_enu_direction << copy_enu_pin;
			
		}
		else if (copy_enu_port == PORTD)
		{
			DATA_DIRECTION_PORTD |= copy_enu_direction << copy_enu_pin;
			
		}
		else
		{
			enu_return_state = DIO_INVALID_PORT;
		}
		
	}
	else{
		enu_return_state = DIO_INVALID_PIN;
	}

	return enu_return_state;
}


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

dio_enu_return_state_t DIO_write_pin (dio_enu_port_t copy_enu_port, dio_enu_pin_t copy_enu_pin, dio_enu_level_t copy_enu_state)
{

	dio_enu_return_state_t enu_return_state = DIO_OK;

	if (copy_enu_pin < DIO_MAX_PINS)
	{
		if (copy_enu_port == PORTA)
		{
			if (copy_enu_state == DIO_PIN_HIGH_LEVEL)
			{
				WR_PORT_A |= (U8_ONE_VALUE << copy_enu_pin);
			}
			else{
				WR_PORT_A &= ~(U8_ONE_VALUE << copy_enu_pin);
			}

		}
		else if (copy_enu_port == PORTB)
		{
			if (copy_enu_state == DIO_PIN_HIGH_LEVEL)
			{
				WR_PORT_B |= (U8_ONE_VALUE << copy_enu_pin);
			}
			else{
				WR_PORT_B &= ~(U8_ONE_VALUE << copy_enu_pin);
			}

		}
		else if (copy_enu_port == PORTC)
		{
			if (copy_enu_state == DIO_PIN_HIGH_LEVEL)
			{
				WR_PORT_C |= (U8_ONE_VALUE << copy_enu_pin);
			}
			else{
				WR_PORT_C &= ~(U8_ONE_VALUE << copy_enu_pin);
			}

		}
		else if (copy_enu_port == PORTD)
		{
			if (copy_enu_state == DIO_PIN_HIGH_LEVEL)
			{
				WR_PORT_D |= (U8_ONE_VALUE << copy_enu_pin);
			}
			else{
				WR_PORT_D &= ~(U8_ONE_VALUE << copy_enu_pin);
			}

		}
		else
		{
			enu_return_state = DIO_INVALID_PORT;
		}
		
	}
	else{
		enu_return_state = DIO_INVALID_PIN;
	}



	return enu_return_state;
}

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
dio_enu_return_state_t DIO_read_pin (dio_enu_port_t copy_enu_port, dio_enu_pin_t copy_enu_pin, dio_enu_level_t	*ptr_enu_state)
{

	dio_enu_return_state_t enu_return_state = DIO_OK;

	if (copy_enu_pin < DIO_MAX_PINS)
	{
		if (copy_enu_port == PORTA)
		{
			*ptr_enu_state = ((RE_PORT_A & (U8_ONE_VALUE<<copy_enu_pin))>>copy_enu_pin);
			
		}
		else if (copy_enu_port == PORTB)
		{
			*ptr_enu_state = ((RE_PORT_B & (U8_ONE_VALUE<<copy_enu_pin))>>copy_enu_pin);
			
		}
		else if (copy_enu_port == PORTC)
		{
			*ptr_enu_state = ((RE_PORT_C & (U8_ONE_VALUE<<copy_enu_pin))>>copy_enu_pin);
			
		}
		else if (copy_enu_port == PORTD)
		{
			*ptr_enu_state = ((RE_PORT_D & (U8_ONE_VALUE<<copy_enu_pin))>>copy_enu_pin);
			
		}
		else
		{
			enu_return_state = DIO_INVALID_PORT;
		}
		
	}
	else{
		enu_return_state = DIO_INVALID_PIN;
	}

	return enu_return_state;
}