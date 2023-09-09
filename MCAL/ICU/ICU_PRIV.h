/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : ICU_PRIV.h       *******************/
/******** Date	     : 4/11/2022           ****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : --             **********************/
/***********************************************************/
/***********************************************************/

#ifndef ICU_PRIV_H
#define ICU_PRIV_H

#define TCCR1A *((volatile u8*)0x4F)
#define TCCR1B *((volatile u8*)0x4E)
#define TCNT1 *((volatile u16*)0x4C)
#define OCR1A *((volatile u16*)0x4A)
#define OCR1B *((volatile u16*)0x48)
#define ICR1 *((volatile u16*)0x46)
#define TIMSK *((volatile u8*)0x59)

void __vector_9(void) __attribute__((signal));
void __vector_6(void) __attribute__((signal));


#endif
