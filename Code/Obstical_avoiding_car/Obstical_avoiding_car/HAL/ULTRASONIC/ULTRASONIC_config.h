/**
 * @file ULTRASONIC_config.h
 * @date 2023-08-26
 * @author Arafa Arafa
 */

#ifndef ULTRASONIC_CONFIG_H_
#define ULTRASONIC_CONFIG_H_

/* Configuration for the Trigger pin of the ultrasonic sensor */
#define TRIG_PIN        PORTB, PIN3

/* Configuration for the Signal pin of the ultrasonic sensor */
#define SIG_PIN         PORTD, PIN3

/* Configuration for an LED indicator */
#define LED             PORTD, PIN7

#endif /* ULTRASONIC_CONFIG_H_ */
