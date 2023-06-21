/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : TIM1_PRIV.h       *******************/
/******** Date	     : 4/11/2022           ****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : --             **********************/
/***********************************************************/
/***********************************************************/

#ifndef TIM1_PRIV_H
#define TIM1_PRIV_H

#include"STD_TYPES.h"
#define TCCR1A *((volatile u8*)0x4F)
#define TCCR1B *((volatile u8*)0x4E)
#define TCNT1H *((volatile u8*)0x4D)
#define TCNT1 *((volatile u16*)0x4C)
#define TCNT1L *((volatile u8*)0x4C)
#define OCR1AH *((volatile u8*)0x4B)
#define OCR1AL *((volatile u8*)0x4A)
#define OCR1A *((volatile u16*)0x4A)
#define OCR1BH *((volatile u8*)0x49)
#define OCR1BL *((volatile u8*)0x48)
#define OCR1B *((volatile u16*)0x48)
#define ICR1H *((volatile u8*)0x47)
#define ICR1L *((volatile u8*)0x46)
#define ICR1 *((volatile u16*)0x46)
#define TIMSK *((volatile u8*)0x59)
#define TIFR *((volatile u8*)0x58)
#define SREG *((volatile u8*)0x5F)


#define NORMAL_MODE 0
#define PHASE_CORRECT_PWM_MODE 1
#define FAST_PWM_ICR1 2
#define CTC_MODE 3

#define INTERNAL_CLK 0

#define EXTRNAL_CLK 1

#define INVERTING_MODE 0
#define NON_INVERTING_MODE 1

void __vector_6(void) __attribute__((signal));
void __vector_8(void) __attribute__((signal));
void __vector_9(void) __attribute__((signal));

#endif
