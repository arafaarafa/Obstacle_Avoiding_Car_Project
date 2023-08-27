/**
 * @file TIMER_private.c
 *
 * @date 2023-08-21
 * @author Arafa Arafa
*/


#ifndef TIMER_PRIVATE_H
#define TIMER_PRIVATE_H

/****************************************TIMER0_REGISTERS **********************************************/

// Timer/Counter Control Register 0 (TCCR0)
#define TCCR0_ADD			 (*((volatile uint8_t *) 0x53))
#define WGM00_bit			 6
#define WGM01_bit			 3

// Timer/Counter Register 0 (TCNT0)
#define TCNT0_ADD			 (*((volatile uint8_t *) 0x52))

// Timer Interrupt Mask Register (TIMSK)
#define TIMSK_ADD			 (*((volatile uint8_t *) 0x59))
#define TOIE0_bit			 0
#define OCIE0_bit			 1

/****************************************TIMER1_REGISTERS **********************************************/

// Timer/Counter 1 Control Registers A and B (TCCR1A and TCCR1B)
#define TCCR1A_ADD   (*(volatile uint8_t*)0x4F)
#define TCCR1B_ADD   (*(volatile uint8_t*)0x4E)

// Timer/Counter 1 Register (TCNT1)
#define TCNT1_ADD   (*(volatile uint16_t*)0x4C)
#define TCNT1H_ADD   (*(volatile uint8_t*)0x4D)
#define TCNT1L_ADD   (*(volatile uint8_t*)0x4C)

// Output Compare Registers 1A and 1B (OCR1A and OCR1B)
#define OCR1AH_ADD   (*(volatile uint8_t*)0x4B)
#define OCR1AL_ADD   (*(volatile uint8_t*)0x4A)
#define OCR1BH_ADD  (*(volatile uint8_t*)0x49)
#define OCR1BL_ADD   (*(volatile uint8_t*)0x48)

// Bit positions in TCCR1A and TCCR1B
#define COM1A0_BIT		6
#define COM1A1_BIT		7
#define COM1B0_BIT		4
#define COM1B1_BIT		5
#define FOC1A_BIT		3
#define FOC1B_BIT		2
#define WGM10_BIT		0
#define WGM11_BIT		1
#define ICNC1_BIT		7
#define ICES1_BIT		6
#define WGM12_BIT		4
#define WGM13_BIT		3
#define CS12_BIT		2
#define CS11_BIT		1
#define CS10_BIT		0
#define TOIE1_BIT		2
#define OCIE1A_BIT		4
#define OCIE1B_BIT		3
#define OCF1A_BIT		4
#define OCF1B_BIT		3
#define TOV1_BIT		2

/****************************************TIMER2_REGISTERS **********************************************/

// Timer/Counter 2 Control Register (TCCR2)
#define TCCR2_ADD   (*(volatile uint8_t*)0x45)
#define WGM20_BIT	6
#define WGM21_BIT	3

// Timer/Counter Register 2 (TCNT2)
#define TCNT2_ADD   (*(volatile uint8_t*)0x44)

// Output Compare Register 2 (OCR2)
#define OCR2_ADD    (*(volatile uint8_t*)0x43)

// Bit positions in TCCR2
#define FOC2		7
#define COM20		4
#define COM21		5
#define CS20		2
#define CS21		1
#define CS22		0
#define OCIE2_BIT	7
#define TOIE2_BIT	6
#define OCF2		7
#define TOV2		6


#endif