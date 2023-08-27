/*
 * ULTRASONIC_prog.c
 *
 *  Created on: May 15, 2023
 *  Author: hp
 */
/************************************************************************************************/
/*									INCLUDES													*/
/************************************************************************************************/
#include "../../MCAL/DIO/DIO_interface.h"
#include "../TIMING/TIMING_interface.h"
#include "../EXTI_manager/EXTI_manager_interface.h"
#include "../../STD_LIB/std_types.h"
#include "../../STD_LIB/bit_math.h"
#include "ULTRASONIC_interface.h"
#include "ULTRASONIC_config.h"




/************************************************************************************************/
/*									Global variables											*/
/************************************************************************************************/
/**
 * @brief Global variable to store overflow counts for timing.
 *
 * This variable holds the number of overflow counts that occur during timing measurements.
 */
volatile uint32_t g_v_u16_ovfCounts = 0;

/**
 * @brief Global variable to store overflow value.
 *
 * This variable holds the overflow value for timing measurements.
 */
volatile uint16_t g_v_u16_ovf;

/**
 * @brief Flag to indicate if the ultrasonic sensor measurement is in progress.
 *
 * This flag is used to keep track of the state of the ultrasonic sensor measurement process.
 */
volatile uint8_t g_v_u8_flag = 0;

/**
 * @brief Variable to store capture value.
 *
 * This variable holds the captured value for timing measurements.
 */
static uint8_t g_v_u8_cap;

/**
 * @brief Global variable to store calculated distance.
 *
 * This variable holds the calculated distance value based on ultrasonic sensor measurements.
 */
static double global_f64distance;

/**
 * @brief Global variable to store ticks for timing measurements.
 *
 * This variable holds the number of ticks used for timing measurements.
 */
uint32_t global_u32Ticks;

/************************************************************************************************/
/*										STATIC Function 										*/
/************************************************************************************************/
/**
 * @brief Delay function for 10 microseconds.
 *
 * This function implements a delay of approximately 10 microseconds.
 * It is used for timing purposes in the ultrasonic sensor module.
 */
static void delay_10u(void);

/**
 * @brief Signal Calculation Function for Ultrasonic Sensor.
 *
 * This function is used to calculate the signal response time of the ultrasonic sensor.
 * It utilizes the external interrupt and timer to measure the signal time.
 */
static void HULTRASONIC_vidSigCalc(void);

/************************************************************************************************/
/*									Functions for CBF										*/
/************************************************************************************************/

/**
 * @brief Timer Callback Function for Ultrasonic Sensor.
 *
 * This function is a callback that is executed when the timer overflows.
 * It increments the overflow count for timing purposes in the ultrasonic sensor module.
 */
static void HULTRASONIC_vidTimerCBF(void)
{
	g_v_u16_ovfCounts++;
}


/**
 * @brief Calculate the signal time of the ultrasonic sensor.
 *
 * This function calculates the time it takes for the signal from the ultrasonic sensor
 * to travel to an object and back, based on the captured ticks. It uses external interrupt
 * to capture the signal changes and calculates the distance using the sound velocity and
 * tick time.
 */
void HULTRASONIC_vidSigCalc(void)
{
	extim_str_config_t ptr_str_extim_config;
	ptr_str_extim_config.enu_exti_interrupt_no= EXTI_1;
	
	if (g_v_u8_flag == 0)
	{
		g_v_u8_flag = 1;
		g_v_u16_ovfCounts = 0;
		timing_start_2();	
		ptr_str_extim_config.enu_edge_detection = EXTI_FALLING_EDGE;
		extim_init(&ptr_str_extim_config, HULTRASONIC_vidSigCalc);
		extim_enable(&ptr_str_extim_config);
	}
	else if (g_v_u8_flag == 1)
	{
		timing_stop_2();
		timing_get_ticks_2(&g_v_u8_cap);
		g_v_u16_ovf = g_v_u16_ovfCounts;
	
		/*********************  Calculate total ticks   *******************************************/
		global_u32Ticks = g_v_u8_cap + (256*((uint32_t)g_v_u16_ovf));

		/* sound velocity = 34300 cm/sec
			 tick time = 1/(F_CPU) as 1 is prescalar -> tick_time = 0.0625us -> 6.25*e-8 sec
			 total_time = t_ticks * 6.25e-8 sec
			 distance = (sound_velocity * total_time)/2 -> (343000 * total_time)/2 -> (17150 * t_ticks * 6.25*e-8) -> (t_ticks * 0.0010718)
		 */		
		global_f64distance = (double)global_u32Ticks * CONSTANT_TO_DISTANCE;

		/*********************  reset global ovf counts and flag    *******************************************/
		g_v_u16_ovf = 0; g_v_u16_ovfCounts = 0;  g_v_u8_flag = 0;

		/*********************  Set EXTINT sense Rising Edge    *******************************************/
		
		ptr_str_extim_config.enu_edge_detection= EXTI_RISING_EDGE;
		extim_init(&ptr_str_extim_config, HULTRASONIC_vidSigCalc);
		extim_enable(&ptr_str_extim_config);

	}
}

/**
 * @brief Disable the external interrupt for the ultrasonic sensor.
 *
 * This function disables the external interrupt for the ultrasonic sensor and
 * stops the associated timing.
 */
static void HULTRASONIC_vidTrigger(void)
{
	
	(void) DIO_write_pin(TRIG_PIN, DIO_PIN_HIGH_LEVEL);
	delay_10u();
	(void) DIO_write_pin(TRIG_PIN, DIO_PIN_LOW_LEVEL);
}

/************************************************************************************************/
/*									Function Implementation										*/
/************************************************************************************************/


/**
 * @brief Initialize the ultrasonic sensor.
 *
 * This function initializes the ultrasonic sensor by configuring the necessary pins
 * and setting up external interrupt and timing for signal detection and measurement.
 */
void HULTRASONIC_vidInit(void)
{
	extim_str_config_t ptr_str_extim_config={.enu_exti_interrupt_no= EXTI_1, .enu_edge_detection = EXTI_RISING_EDGE};
	
	DIO_init(TRIG_PIN, DIO_PIN_OUTPUT);
	DIO_init(SIG_PIN, DIO_PIN_INPUT);
	DIO_write_pin(TRIG_PIN, DIO_PIN_LOW_LEVEL);
	extim_init(&ptr_str_extim_config, HULTRASONIC_vidSigCalc);
	timing_init_2(HULTRASONIC_vidTimerCBF);
	

}



/**
 * @brief Enable the external interrupt for the ultrasonic sensor.
 *
 * This function enables the external interrupt for the ultrasonic sensor with
 * the specified configuration.
 */
void HULTRASONIC_vidInterruptEnable(void)
{
	extim_str_config_t ptr_str_extim_config={.enu_exti_interrupt_no= EXTI_1, .enu_edge_detection= EXTI_RISING_EDGE};
	extim_enable(&ptr_str_extim_config);

}

/**
 * @brief Disable the external interrupt for the ultrasonic sensor.
 *
 * This function disables the external interrupt for the ultrasonic sensor and
 * stops the associated timing.
 */
void HULTRASONIC_vidInterruptDisable(void)
{
	extim_str_config_t ptr_str_extim_config = {.enu_exti_interrupt_no= EXTI_1, .enu_edge_detection= EXTI_RISING_EDGE};
	timing_stop_2();
	extim_disable(&ptr_str_extim_config);
}




/**
 * @brief Read the distance from the ultrasonic sensor.
 *
 * This function triggers the ultrasonic sensor to measure distance and returns
 * the calculated distance value in centimeters.
 *
 * @return The calculated distance in centimeters.
 */
float64_t HULTRASONIC_u8Read(void)
{
	HULTRASONIC_vidTrigger();
	
	return global_f64distance;
}

void delay_10u(void){
	volatile uint16_t u16_counter;
	for(u16_counter= U8_ZERO_VALUE; u16_counter < DELAY_10_U; u16_counter++);
}





/************************************************************************************************/
/*									END															*/
/************************************************************************************************/
