/*
 * BT_PROG.c
 *
 *  Created on: Jun 17, 2023
 *      Author: saziz
 */

#include"BT_INTERFACE.h"
#include"UART_INTERFACE.h"
void BT_VidInit()
{
	UART_VidInit(8);
}
void BT_VIDDisable()
{
	UART_VidDisable();
}
