/*
 * @file ISR_interface.h
 * @brief Interface for working with interrupts in AVR microcontrollers.
 * Created: 21/8/2023 11:34:08 PM
 *  Author: Arafa Arafa
 */ 


/**

 */

#ifndef ISR_INTERFACE_H_
#define ISR_INTERFACE_H_

/** Enable global interrupts. */
#define sei() __asm__ __volatile__("sei" ::: "memory")

/** Disable global interrupts. */
#define cli() __asm__ __volatile__("cli" ::: "memory")

// Interrupt vectors

/** External Interrupt Request 0 */
#define EXT_INT0 __vector_1

/** External Interrupt Request 1 */
#define EXT_INT1 __vector_2

/** External Interrupt Request 2 */
#define EXT_INT2 __vector_3

/** Timer/Counter2 Compare Match */
#define TIMER2_COMP __vector_4

/** Timer/Counter2 Overflow */
#define TIMER2_OVF __vector_5

/** Timer/Counter1 Capture Event */
#define TIMER1_CAPT __vector_6

/** Timer/Counter1 Compare Match A */
#define TIMER1_COMPA __vector_7

/** Timer/Counter1 Compare Match B */
#define TIMER1_COMPB __vector_8

/** Timer/Counter1 Overflow */
#define TIMER1_OVF __vector_9

/** Timer/Counter0 Compare Match */
#define TIMER0_COMP __vector_10

/** Timer/Counter0 Overflow */
#define TIMER0_OVF __vector_11

/** SPI Serial Transfer Complete */
#define SPI_STC __vector_12

/** USART, Rx Complete */
#define USART_RXC __vector_13

/** USART Data Register Empty */
#define USART_UDRE __vector_14

/** USART, Tx Complete */
#define USART_TXC __vector_15

/** ADC Conversion Complete */
#define ADC __vector_16

/** EEPROM Ready */
#define EE_RDY __vector_17

/** Analog Comparator */
#define ANA_COMP __vector_18

/** Two-wire Serial Interface */
#define TWI __vector_19

/** Store Program Memory Read */
#define SPM_RDY __vector_20

/**
 * @brief Macro to define an ISR (Interrupt Service Routine).
 *
 * This macro is used to define an ISR for a specific interrupt vector.
 * The defined function will be executed when the corresponding interrupt occurs.
 *
 * Example usage:
 * ISR(EXT_INT0) {
 *     // ISR code here
 * }
 */
#define ISR(INT_VECT) void INT_VECT(void) __attribute__((signal,used));\
void INT_VECT(void)

#endif /* ISR_INTERFACE_H_ */
