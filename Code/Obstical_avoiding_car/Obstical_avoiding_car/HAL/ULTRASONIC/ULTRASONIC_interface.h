/**
 * @file ULTRASONIC_interface.h
 *
 * @date 2023-08-23
 * @author Arafa Arafa
 */
/************************************************************************************************/
/*									File Guard										*/
/************************************************************************************************/
#ifndef ULTRASONIC_INTERFACE_H_
#define ULTRASONIC_INTERFACE_H_

#define DELAY_10_U     10
#define CONSTANT_TO_DISTANCE  0.0010718

/************************************************************************************************/
/*									User Defined types									*/
/************************************************************************************************/
typedef void(*HULTRASONIC_ptr_func)(void);




/************************************************************************************************/
/*									Function Protoyypes											*/
/************************************************************************************************/

/**
 * @brief Initialize the ultrasonic sensor.
 *
 * This function initializes the ultrasonic sensor by configuring the necessary pins
 * and setting up external interrupt and timing for signal detection and measurement.
 */
void HULTRASONIC_vidInit(void);


/**
 * @brief Read the distance from the ultrasonic sensor.
 *
 * This function triggers the ultrasonic sensor to measure distance and returns
 * the calculated distance value in centimeters.
 *
 * @return The calculated distance in centimeters.
 */
float64_t HULTRASONIC_u8Read(void);


/**
 * @brief Enable the external interrupt for the ultrasonic sensor.
 *
 * This function enables the external interrupt for the ultrasonic sensor with
 * the specified configuration.
 */
void HULTRASONIC_vidInterruptEnable(void);


/**
 * @brief Disable the external interrupt for the ultrasonic sensor.
 *
 * This function disables the external interrupt for the ultrasonic sensor and
 * stops the associated timing.
 */
void HULTRASONIC_vidInterruptDisable(void);

#endif /* HAL_ULTRASONIC_ULTRASONIC_H_ */
