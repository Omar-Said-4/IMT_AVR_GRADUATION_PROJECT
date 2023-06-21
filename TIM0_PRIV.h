/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : TIM0_PRIV.h       *******************/
/******** Date	     : 23/10/2022           ****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : --             **********************/
/***********************************************************/
/***********************************************************/

#ifndef TIMO_PRIV_H
#define TIMO_PRIV_H

#define TCCR0 *((volatile u8*)0x53)
#define TCNT0 *((volatile u8*)0x52)
#define OCR0 *((volatile u8*)0x5C)
#define TIMSK *((volatile u8*)0x59)
#define TIFR *((volatile u8*)0x58)
#define SFIOR *((volatile u8*)0x50)

#define NORMAL_MODE 0
#define PHASE_CORRECT_PWM_MODE 1
#define FAST_PWM 2
#define CTC_MODE 3
#define OVERFLOW 4
#define INTERNAL_CLK 0

#define EXTRNAL_CLK 1

#define INVERTING_MODE 0
#define NON_INVERTING_MODE 1

void __vector_11(void) __attribute__((signal));
void __vector_10(void) __attribute__((signal));


#endif
