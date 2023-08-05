/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : EXIT_PRIVATE_H.h     *****************/
/******** Date	     : 8/10/2022           *****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : --             **********************/
/***********************************************************/
/***********************************************************/

#ifndef EXIT_PRIVATE_H
#define EXIT_PRIVATE_H
#include"STD_TYPES.h"
#define MCUCR *((volatile u8*)0x55)

#define SREG *((volatile u8*)0x5F)

#define GICR *((volatile u8*)0x5B)

#define GIFR *((volatile u8*)0x5A)

#define MCUCSR *((volatile u8*)0x54)
//attribute-->talks to linker

void __vector_1(void) __attribute__((signal)); //Data Sheet -1
void __vector_2(void) __attribute__((signal));
void __vector_3(void) __attribute__((signal));

#endif
