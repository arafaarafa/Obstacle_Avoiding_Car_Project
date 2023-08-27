/*
 * STD_TYPES.h
 *
 * Created: 8/21/2023 
 *  Author: Arafa Arafa 
 */ 


#ifndef STD_TYPES_H_
#define STD_TYPES_H_
/**********************************  section 1: Includes ********************************************************/

/**********************************  section 2: Macro Declarations ***********************************************/

#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif

#define HIGH        (1u)
#define LOW         (0u)

#define NULL    ((void*)0)

#define MAX_VALUE_UINT32	4294967295UL

/**********************************  section 3: Macro Like Function Declarations *************************** *****/


/**********************************  section 4: Data Type Declarations  ******************************************/
typedef unsigned char         uint8_t;          /*           0 .. 255             */
typedef signed char           sint8_t;          /*        -128 .. +127            */
typedef unsigned short        uint16_t;         /*           0 .. 65535           */
typedef signed short          sint16_t;         /*      -32768 .. +32767          */
typedef unsigned long         uint32_t;         /*           0 .. 4294967295      */
typedef signed long           sint32_t;         /* -2147483648 .. +2147483647     */
typedef unsigned long long    uint64_t;         /*       0..18446744073709551615  */
typedef signed long long      sint64_t;
typedef float                 float32_t;
typedef double                float64_t;

typedef void(*ptr_to_v_fun_in_void_t)(void);

/**********************************  section 5: Function Declarations ********************************************/



#endif /* STD_TYPES_H_ */