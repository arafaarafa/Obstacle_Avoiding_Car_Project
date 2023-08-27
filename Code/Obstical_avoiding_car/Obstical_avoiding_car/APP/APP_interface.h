/**
 * @file APP_interface.h
 *
 * @date 2023-08-23
 * @author Arafa Arafa
 */



#ifndef APP_INTERFACE_H_
#define APP_INTERFACE_H_


#include "../HAL/BUTTON/BUTTON_interface.h"
#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/EXTI_manager/EXTI_manager_interface.h"
#include "../HAL/MOTOR/MOTOR_interface.h"
#include "../HAL/TIMING/TIMING_interface.h"
#include "../HAL/ULTRASONIC/ULTRASONIC_interface.h"
#include "../HAL/PWM/PWM_interface.h"
#include "../HAL/CAR_CONTROL/CAR_CONTROL_interface.h"
#include "../STD_LIB/bit_math.h"
#include "../STD_LIB/std_types.h"



/* Maximum measured distance for the ultrasonic sensor */
#define APP_MAX_MEASURED_DIST              (double)99.0

/* To get first digit of number by division */
#define APP_SELECT_TENS_DIGIT				10

/* Value of zero in char */
#define APP_0_CHAR							'0'

/* NULL termination during the loop on string */
#define APP_NULL_TERMINATION_STRING			'\0'

/* Maximum size for the string array used for number-to-string conversion */
#define APP_MAX_STRING_SIZE                 5

/* Duration of the system tick in milliseconds */
#define APP_SYS_TICK_DURATION               1000ul

/* Time to wait for setting direction in seconds */
#define APP_WAIT_TO_SET_DIR_TIME            5

/* Obstacle distances in centimeters */
#define APP_DISTANCE_70_CM                 70.0
#define APP_DISTANCE_30_CM                 30.0
#define APP_DISTANCE_20_CM                 20.0

/* Time intervals in seconds */
#define APP_5_SEC_WITHOUT_OBSTACLES        5
#define APP_2_SEC_TO_ROTATE                2
#define APP_3_SEC_HOLD_MOVE                3

/* PWM frequency for controlling the car */
#define APP_CAR_PWM_FREQ                   20

/* Speed settings for the car */
#define APP_CAR_SPEED_30_PRE               30
#define APP_CAR_SPEED_50_PRE               50

/* Maximum number of rotations for the car */
#define APP_MAX_CAR_ROTATE                 5

/* Index values for LCD pin data */
#define APP_LCD_PIN_DATA_INDEX_0           0
#define APP_LCD_PIN_DATA_INDEX_1           1
#define APP_LCD_PIN_DATA_INDEX_2           2
#define APP_LCD_PIN_DATA_INDEX_3           3


/************************************************************************************************/
/*									Enumerated Datatypes										*/
/************************************************************************************************/
		

/* Enumeration for selecting the motor state */
typedef enum
{
	EN_MOTOR_START = 0,     // Motor start command
	EN_MOTOR_STOP,          // Motor stop command
	EN_MOTOR_STOP_V2,       // Alternate motor stop command
	EN_MOTOR_IDLE           // Motor idle state
} en_motorSel_t;

/* Enumeration for different start states */
typedef enum
{
	EN_UPDATE_DIR = 0,      // Update car's direction
	UPDATE_OBSTACLE_STATE   // Update obstacle detection state
} en_start_states_t;

/* Enumeration for different obstacle detection states */
typedef enum
{
	OBSTACLE_IDLE = 0,      // No obstacle detected, idle state
	NO_OBSTACLES,           // No obstacles within safe range
	OBSTACLE_70_30,         // Obstacle detected within 70-30 cm range
	OBSTACLE_30_20,         // Obstacle detected within 30-20 cm range
	OBSTACLE_LESS_20,       // Obstacle detected within less than 20 cm range
	OBSTACLE_HOLD_MOVING,   // Obstacle detected, car on hold and moving
	NO_DECISION             // No decision made yet
} en_Dist_states_t;


/************************************************************************************************/
/*									Function Prototypes     									*/
/************************************************************************************************/


/**
 * @brief Initialize the application.
 *
 * This function initializes various components of the application, including the ultrasonic sensor,
 * LCD, buttons, external interrupts, timing system, and motor control.
 */
void APP_vidInit(void);

/**
 * @brief Start the application logic.
 *
 * This function handles the main application logic including decision making based on obstacle
 * distances and controlling the car's movement accordingly.
 */
void APP_vidStart(void);

#endif /* APP_H	*/