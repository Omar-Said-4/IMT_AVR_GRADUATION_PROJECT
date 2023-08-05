/*
 * TIM2_PRIVATE.h
 *
 *  Created on: Jun 21, 2023
 *      Author: saziz
 */

#ifndef TIM2_PRIVATE_H_
#define TIM2_PRIVATE_H_

#define TCCR2 *((volatile u8*)0x45)
#define TCNT2 *((volatile u8*)0x44)
#define OCR2 *((volatile u8*)0x43)
#define ASSR *((volatile u8*)0x42)
#define TIMSK *((volatile u8*)0x59)
#define SFIOR *((volatile u8*)0x50)
#define TIFR *((volatile u8*)0x58)


#endif /* TIM2_PRIVATE_H_ */
