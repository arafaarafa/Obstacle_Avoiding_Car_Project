/**
 * @file EXTI_prog.c
 *
 * @date 2023-08-21
 * @author Arafa Arafa
 */ 
#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "../AVR_ARCH/ISR_interface.h"

// Pointer to a function that represents the callback for External Interrupt 0
static void (*callback_EXT_0)(void) = NULL;

// Pointer to a function that represents the callback for External Interrupt 1
static void (*callback_EXT_1)(void) = NULL;

/**
 * @brief Initializes an external interrupt with the specified edge detection.
 *
 * @param copy_enu_exti_interrupt_no The external interrupt number to initialize.
 * @param copy_enu_edge_detection The desired edge detection mode for the interrupt.
 * @return exti_enu_return_state_t The return state of the EXTI initialization:
 *         - EXTI_E_OK: Operation was successful.
 *         - EXTI_E_INVALID_ARG: Invalid interrupt number provided.
 * @note This function initializes the specified external interrupt with the provided edge detection mode.
 *       It updates the corresponding control registers and enables the global interrupt flag if needed.
 *       The return value indicates the success or failure of the initialization.
 */
exti_enu_return_state_t ext_interrupt_init(exti_interrupt_no_t copy_enu_exti_interrupt_no, exti_edge_detection_t copy_enu_edge_detection){
    exti_enu_return_state_t ret_val=EXTI_E_OK;
    switch (copy_enu_exti_interrupt_no)
    {
    case EXTI_0:
        MCUCR_ADD = (MCUCR_ADD & (~0x3)) | copy_enu_edge_detection;	
		SREG_ADD |= (1<<Globle_INT);
        break;

    case EXTI_1:
        MCUCR_ADD = (MCUCR_ADD & (~(0x3<<INT1_MODE_INDEX))) | (copy_enu_edge_detection<<INT1_MODE_INDEX);	
		SREG_ADD |= (1<<Globle_INT);
        break;

    case EXTI_2:
        /* code */
        break;    
    
    default:
        break;
    }

    return ret_val;
}

/**
 * @brief Enables an external interrupt.
 *
 * @param copy_enu_exti_interrupt_no The external interrupt number to enable.
 * @return exti_enu_return_state_t The return state of the EXTI enable operation:
 *         - EXTI_E_OK: Operation was successful.
 *         - EXTI_E_INVALID_ARG: Invalid interrupt number provided.
 * @note This function enables the specified external interrupt by setting the corresponding global interrupt enable bit.
 *       It also invokes the "sei()" assembly instruction to globally enable interrupts.
 *       The return value indicates the success or failure of the enable operation.
 */
exti_enu_return_state_t ext_interrupt_enable(exti_interrupt_no_t copy_enu_exti_interrupt_no){
    exti_enu_return_state_t ret_val=EXTI_E_OK;
    switch (copy_enu_exti_interrupt_no)
    {
		sei();
    case EXTI_0:
        GICR_ADD |= (1<<INT0_Globle);
        break;

    case EXTI_1:
        GICR_ADD |= (1<<INT1_Globle);

        break;

    case EXTI_2:
        /* code */
        break;    
    
    default:
        break;
    }
    return ret_val;
}

/**
 * @brief Disables an external interrupt.
 *
 * @param copy_enu_exti_interrupt_no The external interrupt number to disable.
 * @return exti_enu_return_state_t The return state of the EXTI disable operation:
 *         - EXTI_E_OK: Operation was successful.
 *         - EXTI_E_INVALID_ARG: Invalid interrupt number provided.
 * @note This function disables the specified external interrupt by clearing the corresponding global interrupt enable bit.
 *       The return value indicates the success or failure of the disable operation.
 */
exti_enu_return_state_t ext_interrupt_disable(exti_interrupt_no_t copy_enu_exti_interrupt_no){
    exti_enu_return_state_t ret_val=EXTI_E_OK;
    switch (copy_enu_exti_interrupt_no)
    {
    case EXTI_0:
       GICR_ADD &= ~(1<<INT0_Globle);

        break;

    case EXTI_1:
        GICR_ADD &= ~(1<<INT1_Globle);

        break;

    case EXTI_2:
        /* code */
        break;    
    
    default:
        break;
    }
    return ret_val;

}


/**
 * @brief Sets a callback function for an external interrupt and initializes it.
 *
 * @param copy_enu_exti_interrupt_no The external interrupt number to set the callback for.
 * @param callback A pointer to the callback function to be set.
 * @return exti_enu_return_state_t The return state of the EXTI callback and initialization:
 *         - EXTI_E_OK: Operation was successful.
 *         - EXTI_E_INVALID_ARG: Invalid interrupt number provided.
 * @note This function sets the provided callback function for the specified external interrupt,
 *       and also initializes the interrupt by disabling its global interrupt enable bit.
 *       The return value indicates the success or failure of the operation.
 */
exti_enu_return_state_t ext_interrupt_set_callback_init(exti_interrupt_no_t copy_enu_exti_interrupt_no ,void(*callback)(void)){
    exti_enu_return_state_t ret_val=EXTI_E_OK;
    switch (copy_enu_exti_interrupt_no)
    {
    case EXTI_0:
        GICR_ADD &= ~(1<<INT0_Globle);
        callback_EXT_0 = callback;
		
        break;

    case EXTI_1:
        GICR_ADD &= ~(1<<INT1_Globle);
        callback_EXT_1 = callback;
        break;

    case EXTI_2:
        /* code */
        break;    
    
    default:
        break;
    }
    return ret_val;
}

/*
*   -Description-
*-interrupt service routine for  external interrupt 0
*
*/
ISR(EXT_INT0)
{
	callback_EXT_0();
}


/*
*   -Description-
*-interrupt service routine for  external interrupt10
*
*/
ISR(EXT_INT1)
{
	callback_EXT_1();
}

/*
*   -Description-
*-interrupt service routine for  external interrupt 2
*
*/
/*ISR(EXT_INT2)
{
	callback_int2();
}*/