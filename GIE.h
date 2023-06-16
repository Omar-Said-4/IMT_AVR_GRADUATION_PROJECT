/*
 * GIE.h
 *
 *  Created on: Jun 17, 2023
 *      Author: saziz
 */

#ifndef GIE_H_
#define GIE_H_
#define SREG *((volatile u8*)0x5F)

void GIE_VidEnable();

#endif /* GIE_H_ */
