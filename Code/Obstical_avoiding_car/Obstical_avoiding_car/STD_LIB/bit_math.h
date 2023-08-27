/*
 * bit_math.h
 *
 * Created: 21/8/2023 
 *  Author: Arafa Arafa
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_
/**********************************  section 1: Includes ********************************************************/
#include "std_types.h"
/**********************************  section 2: Macro Declarations ***********************************************/

/*mask 1-bit (LSB)*/
#define BIT_MASK  (uint8_t)1
/*mask 8-bit_reg*/
#define U8_BIT_REG_MASK                                     ((uint8_t)0xFF)
#define U16_BIT_REG_MASK                                    ((uint16_t)0xFFFF)

#define  U8_ONE_VALUE	                                    ((uint8_t)1)
#define  U8_ZERO_VALUE                                      ((uint8_t)0)

/**********************************  section 3: Macro Like Function Declarations *************************** *****/


/*set a certain bit in a 8-bit register*/
#define SET_BIT(REG,BIT_POSN)                               (REG |=  (BIT_MASK << BIT_POSN))
/*reset a certain bit in a 8-bit register*/
#define CLEAR_BIT(REG,BIT_POSN)                             (REG &= ~(BIT_MASK << BIT_POSN))
/*toggle a certain bit in a 8-bit register*/
#define TOGGLE_BIT(REG,BIT_POS)                             (REG ^=  (BIT_MASK << BIT_POS) )

/*read a certain bit in a 8-bit register*/
#define READ_BIT(REG,BIT_POS)                               ((REG & (BIT_MASK<<BIT_POS)) >> BIT_POS)

#define CLEAR_REG(REG)		                                (REG = ((uint8_t)U8_ZERO_VALUE))

/**********************************  section 4: Data Type Declarations  ******************************************/

/**********************************  section 5: Function Declarations ********************************************/
#endif /* BIT_MATH_H_ */