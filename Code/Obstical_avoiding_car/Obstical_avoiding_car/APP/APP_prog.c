/**
 * @file App_prog.c
 *
 * @date 2023-08-23
 * @author Arafa Arafa
 */

/************************************************************************************************/
/*									INCLUDES													*/
/************************************************************************************************/

#include "APP_interface.h"



#define MOTOR_TURN_RIGHT			0
#define MOTOR_TURN_LEFT				1
/************************************************************************************************/
/*									extern functions											*/



/************************************************************************************************/
/*									Static Function Prototype									*/
/************************************************************************************************/

/**
 * @brief Change the motor state based on button press.
 *
 * This function toggles the motor state between start and stop when the button is pressed.
 */
static void BUTTON_vidChangeState(void);

/**
 * @brief Update the car's direction based on user button input.
 *
 * This function allows the user to set the car's default rotation direction by pressing a button.
 * The user can switch between left and right directions. The function displays the selected direction
 * on an LCD screen and waits for a specific time before proceeding.
 */
static void APP_updateDirection(void);

/**
 * @brief Convert an unsigned 8-bit integer to a string representation.
 *
 * This function takes an unsigned 8-bit integer and converts it to its string representation.
 * The resulting string is stored in the provided buffer, and the buffer is null-terminated.
 * The function handles the special case of zero and converts each digit of the number to a character.
 *
 * @param[in] copy_u8_num The unsigned 8-bit integer to be converted.
 * @param[out] ptr_string Pointer to the buffer where the string representation will be stored.
 */
static void intToString(uint8_t copy_u8_num, uint8_t *ptr_string);


/**
 * @brief Make a decision based on the distance measured by the ultrasonic sensor.
 *
 * This function reads the distance from the ultrasonic sensor, and based on the measured distance,
 * it makes a decision about the obstacles in the car's path. The decision is stored in the provided
 * pointer to an en_Dist_states_t variable.
 *
 * @param[in,out] ptr_f_distination Pointer to the variable storing the measured distance.
 * @param[in,out] ptr_enu_decision Pointer to the variable where the decision will be stored.
 */
static void APP_make_decision(float64_t *ptr_f_distination, en_Dist_states_t *ptr_enu_decision);
/************************************************************************************************/
/*									Global variables											*/
/************************************************************************************************/

/* Initial direction state counter */
uint8_t u8_g_dirStateCounter = MOTOR_TURN_RIGHT;  // Initial direction state is right

/* Motor selection state */
en_motorSel_t en_motorSel = EN_MOTOR_STOP;  // Initial motor state is stopped

/* State for the application */
en_start_states_t en_start_state = EN_UPDATE_DIR;  // Initial start state is updating direction

/* Current obstacle detection state */
en_Dist_states_t en_Dist_states = OBSTACLE_IDLE;  // Initial obstacle detection state is idle

/* Static variables for storing data */
static double gs_fl_dist;  // Stores the measured distance
static uint8_t gs_arr_u8_string[APP_MAX_STRING_SIZE];  // Array for converting numbers to strings
static uint8_t gs_u8_rotate_counter = 1;  // Counter for rotation iterations

/* LCD configuration */
static lcd_str_config_t gs_str_lcd_config;  // LCD configuration structure

/* External Interrupt configuration for the button */
static extim_str_config_t gs_str_extim_config_btn;  // External Interrupt configuration structure

/* PWM configuration for controlling motor speed */
static pwm_str_configuration_t gs_str_pwm_pin;  // PWM configuration structure

/* Motor configurations */
static motor_str_config_t gs_str_motor_1;  // Motor 1 configuration structure
static motor_str_config_t gs_str_motor_2;  // Motor 2 configuration structure

/* Button state configuration */
static btn_str_config_t gs_btn_dir_state;  // Button configuration structure

/* Button enumerated state */
static btn_enu_state_t gs_enu_btn_dir_state;  // Button enumerated state


/************************************************************************************************/
/*									Function Implementation										*/
/************************************************************************************************/
/**
 * @brief Initialize the application.
 *
 * This function initializes various components of the application, including the ultrasonic sensor,
 * LCD, buttons, external interrupts, timing system, and motor control.
 */
void APP_vidInit(void)
{
    // Initialize ultrasonic sensor and enable interrupts
    HULTRASONIC_vidInit();
    HULTRASONIC_vidInterruptEnable();

    /* LCD Initialization */
    // Configuration for the LCD
    gs_str_lcd_config.enu_mode = LCD_4_BIT_MODE;

    gs_str_lcd_config.str_data_pins[APP_LCD_PIN_DATA_INDEX_0].enu_port = PORTC;
    gs_str_lcd_config.str_data_pins[APP_LCD_PIN_DATA_INDEX_1].enu_pin  = PIN0;

    gs_str_lcd_config.str_data_pins[APP_LCD_PIN_DATA_INDEX_1].enu_port = PORTC;
    gs_str_lcd_config.str_data_pins[APP_LCD_PIN_DATA_INDEX_1].enu_pin  = PIN1;

    gs_str_lcd_config.str_data_pins[APP_LCD_PIN_DATA_INDEX_2].enu_port = PORTC;
    gs_str_lcd_config.str_data_pins[APP_LCD_PIN_DATA_INDEX_2].enu_pin  = PIN2;

    gs_str_lcd_config.str_data_pins[APP_LCD_PIN_DATA_INDEX_3].enu_port = PORTC;
    gs_str_lcd_config.str_data_pins[APP_LCD_PIN_DATA_INDEX_3].enu_pin  = PIN3;

    gs_str_lcd_config.str_RSpin.enu_port = PORTC;
    gs_str_lcd_config.str_RSpin.enu_pin  = PIN4;

    gs_str_lcd_config.str_RWpin.enu_port = PORTC;
    gs_str_lcd_config.str_RWpin.enu_pin  = PIN5;

    gs_str_lcd_config.str_Epin.enu_port = PORTC;
    gs_str_lcd_config.str_Epin.enu_pin  = PIN6;

    // Initialize the LCD with the configured settings
    LCD_init(&gs_str_lcd_config);

    /* Button Initialization */
    gs_btn_dir_state.enu_port  = PORTD;
    gs_btn_dir_state.enu_pin   = PIN1;
    BTN_init(&gs_btn_dir_state);

    /* External Interrupt Initialization */
    gs_str_extim_config_btn.enu_exti_interrupt_no = EXTI_0;
    gs_str_extim_config_btn.enu_edge_detection    = EXTI_FALLING_EDGE;
    extim_init(&gs_str_extim_config_btn, BUTTON_vidChangeState);

    /* Timing Initialization */
    timing_init_1(APP_SYS_TICK_DURATION);

    /* Motor Initialization */
    gs_str_motor_1.port        = PORTA;
    gs_str_motor_1.pin_num1    = PIN3;
    gs_str_motor_1.pin_num2    = PIN4;

    gs_str_motor_2.port        = PORTA;
    gs_str_motor_2.pin_num1    = PIN0;
    gs_str_motor_2.pin_num2    = PIN1;

    // PWM Configuration for Car Control
    gs_str_pwm_pin.frequency       = APP_CAR_PWM_FREQ;
    gs_str_pwm_pin.duty_cycle      = APP_CAR_SPEED_30_PRE;
    gs_str_pwm_pin.enu_pin_index   = PIN2;
    gs_str_pwm_pin.enu_port_index  = PORTA;
    CAR_INIT(&gs_str_motor_1, &gs_str_motor_2, &gs_str_pwm_pin);

    // Start the timing system
    timing_start_1();
}


/**
 * @brief Start the application logic.
 *
 * This function handles the main application logic including decision making based on obstacle
 * distances and controlling the car's movement accordingly.
 */
void APP_vidStart(void)
{
	// Enable external interrupt
	extim_enable(&gs_str_extim_config_btn);

	if(en_motorSel == EN_MOTOR_START){

		if (en_start_state == EN_UPDATE_DIR)
		{
			// Clear LCD and display message
			LCD_clear (&gs_str_lcd_config);
			LCD_setCursor (&gs_str_lcd_config, LCD_ROW_1, LCD_COL_1);
			LCD_writeString (&gs_str_lcd_config, (uint8_t*) "Set Def. Rot.");
			// Update direction based on obstacle detection
			APP_updateDirection();
			en_start_state = UPDATE_OBSTACLE_STATE;
		}

		// Continuously loop while motor is started
		while(en_motorSel == EN_MOTOR_START){
			// Check if maximum rotation count has not been reached
			if(gs_u8_rotate_counter < APP_MAX_CAR_ROTATE){
				APP_make_decision(&gs_fl_dist, &en_Dist_states);
			}

			if(en_Dist_states == NO_OBSTACLES){
				// Display speed and direction information on LCD
				LCD_setCursor (&gs_str_lcd_config, LCD_ROW_1, LCD_COL_1);
				LCD_writeString (&gs_str_lcd_config, (uint8_t*)"Speed:30% ");
				LCD_writeString (&gs_str_lcd_config, (uint8_t*)"Dir:F");

				// Continue moving forward for a set time period
				while((timing_time_out(APP_5_SEC_WITHOUT_OBSTACLES) == TIMING_NOT_TIME_OUT) && (en_motorSel == EN_MOTOR_START)){
					LCD_setCursor (&gs_str_lcd_config, LCD_ROW_2, LCD_COL_1);
					LCD_writeString (&gs_str_lcd_config, (uint8_t*)"Dist: ");
					intToString((uint8_t)gs_fl_dist, gs_arr_u8_string);
					LCD_writeString (&gs_str_lcd_config, gs_arr_u8_string);
					LCD_writeString (&gs_str_lcd_config,(uint8_t*)" cm ");
					gs_str_pwm_pin.duty_cycle = APP_CAR_SPEED_30_PRE;
					CAR_FORWARD(&gs_str_motor_1, &gs_str_motor_2, &gs_str_pwm_pin);
					APP_make_decision(&gs_fl_dist, &en_Dist_states);
				}

				// Check obstacle state again after time period
				if(en_Dist_states == NO_OBSTACLES){
					LCD_setCursor (&gs_str_lcd_config, LCD_ROW_1, LCD_COL_1);
					LCD_writeString (&gs_str_lcd_config, (uint8_t*)"Speed:50% ");
					gs_str_pwm_pin.duty_cycle = APP_CAR_SPEED_50_PRE;
					CAR_FORWARD(&gs_str_motor_1, &gs_str_motor_2, &gs_str_pwm_pin);

					// Continue moving forward while monitoring obstacle state
					while((en_Dist_states == NO_OBSTACLES) && (en_motorSel == EN_MOTOR_START)){
						LCD_setCursor (&gs_str_lcd_config, LCD_ROW_2, LCD_COL_1);
						LCD_writeString (&gs_str_lcd_config, (uint8_t*)"Dist: ");
						intToString((uint8_t)gs_fl_dist, gs_arr_u8_string);
						LCD_writeString (&gs_str_lcd_config, gs_arr_u8_string);
						LCD_writeString (&gs_str_lcd_config,(uint8_t*)" cm ");
						APP_make_decision(&gs_fl_dist, &en_Dist_states);
					}
					} else {
					// No action needed
				}
				} else if(en_Dist_states == OBSTACLE_70_30){
				LCD_setCursor (&gs_str_lcd_config, LCD_ROW_1, LCD_COL_1);
				LCD_writeString (&gs_str_lcd_config, (uint8_t*)"Speed:30% ");
				LCD_writeString (&gs_str_lcd_config, (uint8_t*)"Dir:F");

				gs_str_pwm_pin.duty_cycle = APP_CAR_SPEED_30_PRE;
				CAR_FORWARD(&gs_str_motor_1, &gs_str_motor_2, &gs_str_pwm_pin);

				while((en_Dist_states == OBSTACLE_70_30) && (en_motorSel == EN_MOTOR_START)){
					LCD_setCursor (&gs_str_lcd_config, LCD_ROW_2, LCD_COL_1);
					LCD_writeString (&gs_str_lcd_config, (uint8_t*)"Dist: ");
					intToString((uint8_t)gs_fl_dist, gs_arr_u8_string);
					LCD_writeString (&gs_str_lcd_config, gs_arr_u8_string);
					LCD_writeString (&gs_str_lcd_config,(uint8_t*)" cm ");
					APP_make_decision(&gs_fl_dist, &en_Dist_states);
				}

				} else if(en_Dist_states == OBSTACLE_30_20){

				LCD_setCursor (&gs_str_lcd_config, LCD_ROW_1, LCD_COL_1);
				LCD_writeString (&gs_str_lcd_config, (uint8_t*)"Speed:30% ");
				LCD_writeString (&gs_str_lcd_config, (uint8_t*)"Dir:R");
				CAR_STOP(&gs_str_motor_1, &gs_str_motor_2, &gs_str_pwm_pin);

				gs_str_pwm_pin.duty_cycle = APP_CAR_SPEED_30_PRE;
				if(u8_g_dirStateCounter == MOTOR_TURN_LEFT){
					CAR_REVERSE_LEFT(&gs_str_motor_1, &gs_str_motor_2, &gs_str_pwm_pin);
					} else {
					CAR_REVERSE_RIGHT(&gs_str_motor_1, &gs_str_motor_2, &gs_str_pwm_pin);
				}
				while((timing_time_out(APP_2_SEC_TO_ROTATE) == TIMING_NOT_TIME_OUT) && (en_motorSel == EN_MOTOR_START)){
					LCD_setCursor (&gs_str_lcd_config, LCD_ROW_2, LCD_COL_1);
					LCD_writeString (&gs_str_lcd_config, (uint8_t*)"Dist: ");
					intToString((uint8_t)gs_fl_dist, gs_arr_u8_string);
					LCD_writeString (&gs_str_lcd_config, gs_arr_u8_string);
					LCD_writeString (&gs_str_lcd_config,(uint8_t*)" cm ");
					APP_make_decision(&gs_fl_dist, &en_Dist_states);
				}
				CAR_STOP(&gs_str_motor_1, &gs_str_motor_2, &gs_str_pwm_pin);
				APP_make_decision(&gs_fl_dist, &en_Dist_states);
				if(en_Dist_states == OBSTACLE_30_20){
					gs_u8_rotate_counter++;
					if(gs_u8_rotate_counter >= APP_MAX_CAR_ROTATE){
						en_Dist_states = OBSTACLE_HOLD_MOVING;
						} else {
						// No action needed
					}
					} else {
					gs_u8_rotate_counter = U8_ONE_VALUE;
				}

				} else if(en_Dist_states == OBSTACLE_LESS_20){
				LCD_setCursor (&gs_str_lcd_config, LCD_ROW_1, LCD_COL_1);
				LCD_writeString (&gs_str_lcd_config, (uint8_t*)"Speed:30% ");
				LCD_writeString (&gs_str_lcd_config, (uint8_t*)"Dir:B");
				gs_str_pwm_pin.duty_cycle = APP_CAR_SPEED_30_PRE;
				CAR_BACKWARD(&gs_str_motor_1, &gs_str_motor_2, &gs_str_pwm_pin);
				while((en_Dist_states == OBSTACLE_LESS_20) && (en_motorSel == EN_MOTOR_START)){
					LCD_setCursor (&gs_str_lcd_config, LCD_ROW_2, LCD_COL_1);
					LCD_writeString (&gs_str_lcd_config, (uint8_t*)"Dist: ");
					intToString((uint8_t)gs_fl_dist, gs_arr_u8_string);
					LCD_writeString (&gs_str_lcd_config, gs_arr_u8_string);
					LCD_writeString (&gs_str_lcd_config,(uint8_t*)" cm ");
					APP_make_decision(&gs_fl_dist, &en_Dist_states);
				}
			} else if(en_Dist_states == OBSTACLE_HOLD_MOVING)
			{
				LCD_clear(&gs_str_lcd_config);
				LCD_setCursor (&gs_str_lcd_config, LCD_ROW_1, LCD_COL_1);
				LCD_writeString (&gs_str_lcd_config, (uint8_t*)"Hold move 3S");
				while((timing_time_out(APP_3_SEC_HOLD_MOVE) == TIMING_NOT_TIME_OUT) && (en_motorSel == EN_MOTOR_START));
				gs_u8_rotate_counter = U8_ONE_VALUE;
				APP_make_decision(&gs_fl_dist, &en_Dist_states);
				} else {
				// No action needed
			}
		}
		} else if(en_motorSel == EN_MOTOR_STOP){/** if stop button pressed**/

		LCD_clear (&gs_str_lcd_config);
		LCD_setCursor(&gs_str_lcd_config, LCD_ROW_1, LCD_COL_1);
		LCD_writeString (&gs_str_lcd_config, (uint8_t*) "Motor Stopped");
		CAR_STOP(&gs_str_motor_1, &gs_str_motor_2, &gs_str_pwm_pin);
		en_start_state = EN_UPDATE_DIR;
		timing_break_time_out();
		while(en_motorSel == EN_MOTOR_STOP);

		} else {
		// No action needed
	}
}



/************************************************************************************************/
/*									Static Function Implementation                				*/
/************************************************************************************************/

/**
 * @brief Change the motor state based on button press.
 *
 * This function toggles the motor state between start and stop when the button is pressed.
 */

void BUTTON_vidChangeState(void)
{
	if(en_motorSel == EN_MOTOR_STOP){	
		en_motorSel = EN_MOTOR_START;
	}else{
		en_motorSel = EN_MOTOR_STOP;
	}
	
}


/**
 * @brief Update the car's direction based on user button input.
 *
 * This function allows the user to set the car's default rotation direction by pressing a button.
 * The user can switch between left and right directions. The function displays the selected direction
 * on an LCD screen and waits for a specific time before proceeding.
 */
void APP_updateDirection(void)
{
	HULTRASONIC_vidInterruptDisable();

	LCD_setCursor(&gs_str_lcd_config, LCD_ROW_2, LCD_COL_1);
	LCD_writeString (&gs_str_lcd_config, (uint8_t*)"Right");
	while(timing_time_out(APP_WAIT_TO_SET_DIR_TIME) == TIMING_NOT_TIME_OUT)
	{
		BTN_get_state(&gs_btn_dir_state, &gs_enu_btn_dir_state);
		if(gs_enu_btn_dir_state == BTN_PUSHED){
			if(u8_g_dirStateCounter == MOTOR_TURN_LEFT){
				u8_g_dirStateCounter = MOTOR_TURN_RIGHT;
				LCD_setCursor(&gs_str_lcd_config, LCD_ROW_2, LCD_COL_1);
				LCD_writeString (&gs_str_lcd_config, (uint8_t*)"Right");
			}else{
				u8_g_dirStateCounter = MOTOR_TURN_LEFT;
				LCD_setCursor(&gs_str_lcd_config, LCD_ROW_2, LCD_COL_1);
				LCD_writeString (&gs_str_lcd_config, (uint8_t*)"Left ");
			}
		}
		else {
			/* do nothing  */
		}
	}
	LCD_clear(&gs_str_lcd_config);
	HULTRASONIC_vidInterruptEnable();
	LCD_setCursor(&gs_str_lcd_config, LCD_ROW_1, LCD_COL_1);
	LCD_writeString (&gs_str_lcd_config, (uint8_t*)"Motor starts in");
	LCD_setCursor(&gs_str_lcd_config, LCD_ROW_2, LCD_COL_1);
	LCD_writeString (&gs_str_lcd_config, (uint8_t*)"2 Sec.");
	delay_s(2);
	LCD_clear (&gs_str_lcd_config);
}


/**
 * @brief Convert an unsigned 8-bit integer to a string representation.
 *
 * This function takes an unsigned 8-bit integer and converts it to its string representation.
 * The resulting string is stored in the provided buffer, and the buffer is null-terminated.
 * The function handles the special case of zero and converts each digit of the number to a character.
 *
 * @param[in] copy_u8_num The unsigned 8-bit integer to be converted.
 * @param[out] ptr_string Pointer to the buffer where the string representation will be stored.
 */
void intToString(uint8_t copy_u8_num, uint8_t *ptr_string){
	uint8_t u8_digit_counter = U8_ZERO_VALUE;
	
	// Calculate the number of digits in the number
	if (copy_u8_num == U8_ZERO_VALUE) {
		u8_digit_counter = U8_ONE_VALUE;
	} else {
		uint8_t temp = copy_u8_num;  // Store a temporary copy of the number
		while (temp != U8_ZERO_VALUE) {
			temp /= APP_SELECT_TENS_DIGIT;
			u8_digit_counter++;
		}
	}
	u8_digit_counter++;

	uint8_t u8_string_counter = u8_digit_counter - U8_ONE_VALUE;  // Start from the end of the buffer
	ptr_string[u8_string_counter] = APP_NULL_TERMINATION_STRING;  // Null-terminate the string

	if (copy_u8_num == U8_ZERO_VALUE) {
		ptr_string[--u8_string_counter] = APP_0_CHAR;  // Handle the special case of zero
	} else {
		while (copy_u8_num > 0 && u8_string_counter > U8_ZERO_VALUE) {
			ptr_string[--u8_string_counter] = APP_0_CHAR + (copy_u8_num % APP_SELECT_TENS_DIGIT); // Convert the digit to character
			copy_u8_num /= APP_SELECT_TENS_DIGIT;
		}
	}
}


/**
 * @brief Make a decision based on the distance measured by the ultrasonic sensor.
 *
 * This function reads the distance from the ultrasonic sensor, and based on the measured distance,
 * it makes a decision about the obstacles in the car's path. The decision is stored in the provided
 * pointer to an en_Dist_states_t variable.
 *
 * @param[in,out] ptr_f_distination Pointer to the variable storing the measured distance.
 * @param[in,out] ptr_enu_decision Pointer to the variable where the decision will be stored.
 */
void APP_make_decision(float64_t *ptr_f_distination, en_Dist_states_t *ptr_enu_decision){
	double f_distination = HULTRASONIC_u8Read();  // Read distance from ultrasonic sensor
	if(f_distination > APP_MAX_MEASURED_DIST) {
		f_distination = APP_MAX_MEASURED_DIST;  // Limit the distance to 99.0 cm
	}
	*ptr_f_distination = f_distination;  // Update the measured distance

	// Make a decision based on the measured distance
	if(f_distination > APP_DISTANCE_70_CM) {
		*ptr_enu_decision = NO_OBSTACLES;  // No obstacles in the path
	} else if ((f_distination > APP_DISTANCE_30_CM) && (f_distination <= APP_DISTANCE_70_CM)) {
		*ptr_enu_decision = OBSTACLE_70_30;  // Obstacle at 70-30 cm distance
	} else if ((f_distination >= APP_DISTANCE_20_CM) && (f_distination <= APP_DISTANCE_30_CM)) {
		*ptr_enu_decision = OBSTACLE_30_20;  // Obstacle at 30-20 cm distance
	} else if (f_distination < APP_DISTANCE_20_CM) {
		*ptr_enu_decision = OBSTACLE_LESS_20;  // Obstacle less than 20 cm distance
	} else {
		*ptr_enu_decision = NO_DECISION;  // No decision based on the given conditions
	}
	// Note: The last condition, 'else', covers any unexpected cases
}



/************************************************************************************************/
/*									END                 										*/
/************************************************************************************************/