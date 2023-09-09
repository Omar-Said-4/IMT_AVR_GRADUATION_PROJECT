/*
 * BT_PROG.c
 *
 *  Created on: Jun 17, 2023
 *      Author: saziz
 */

#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"
#include"BT_INTERFACE.h"
#include"../../MCAL/USART/UART_INTERFACE.h"
void BT_VidInit()
{
	UART_VidInit(8);
}
void BT_VIDDisable()
{
	UART_VidDisable();
}
