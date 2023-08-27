/**
 * @file EXTI_private.h
 *
 * @date 2023-08-21
 * @author Arafa Arafa
 */


#ifndef EXT_INTERRUPT_PRIVATE_REG_H_
#define EXT_INTERRUPT_PRIVATE_REG_H_
#include "../../STD_LIB/std_types.h"


// Macro to access the General Interrupt Control Register (GICR) register in memory
#define GICR_ADD             (*((volatile uint8_t *) 0x5B))

// Definitions for bit positions of different external interrupt enable flags
#define INT0_Globle           6  // Bit position for enabling External Interrupt 0
#define INT1_Globle           7  // Bit position for enabling External Interrupt 1
#define INT2_Globle           5  // Bit position for enabling External Interrupt 2

// Macro to access the MCU Control Register (MCUCR) register in memory
#define MCUCR_ADD            (*((volatile uint8_t *) 0x55))

// Definitions for bit positions of different external interrupt mode bits
#define INT0_MODE_INDEX       0  // Bit position for External Interrupt 0 mode
#define INT1_MODE_INDEX       2  // Bit position for External Interrupt 1 mode

// Macro to access the MCU Control and Status Register (MCUCSR) register in memory
#define MCUCSR_ADD           (*((volatile uint8_t *) 0x54))

// Definition for the bit position of the external interrupt 2 mode bit
#define INT2_MODE_INDEX       6  // Bit position for External Interrupt 2 mode

// Macro to access the Status Register (SREG) register in memory
#define SREG_ADD             (*((volatile uint8_t *) 0x5F))

// Definition for the bit position of the global interrupt enable flag
#define Globle_INT           7  // Bit position for enabling global interrupts




#endif /* EXT_INTERRUPT_PRIVATE_REG_H_ */