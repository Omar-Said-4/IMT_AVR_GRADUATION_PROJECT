/*
 * TWI_INTERFACE.h
 *
 *  Created on: Jun 18, 2023
 *      Author: saziz
 */
#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_
#include"TWI_PRIV.h"
#include"STD_TYPES.h"
void TWI_VidInit(void);
void TWI_VidStart(void);
void TWI_VidStop(void);
void TWI_VidSendByte(unsigned char data);
u8 TWI_U8ReadACK(void);
u8 TWI_U8ReadNACK(void);
u8 TWI_U8GetStatus(void);


#endif /* TWI_INTERFACE_H_ */
