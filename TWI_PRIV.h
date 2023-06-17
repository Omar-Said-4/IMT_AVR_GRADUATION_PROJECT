/*
 * TWI_PRIV.h
 *
 *  Created on: Jun 18, 2023
 *      Author: saziz
 */

#ifndef TWI_PRIV_H_
#define TWI_PRIV_H_

#define TWBR *((volatile u8*)0x20)
#define TWCR *((volatile u8*)0x56)
#define TWDR *((volatile u8*)0x23)
#define TWAR *((volatile u8*)0x22)
#define TWSR *((volatile u8*)0x21)
#define TWI_BITRATE 2
#endif /* TWI_PRIV_H_ */
