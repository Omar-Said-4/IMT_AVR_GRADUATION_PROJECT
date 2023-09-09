/*
 * BUT_PROG.c
 *
 *  Created on: Jul 7, 2023
 *      Author: saziz
 */


#include"../../LIB/STD_TYPES.h"
#include"../../App/DFS.h"
#include"../../MCAL/DIO/DIO_INTERFACE.h"
#include<util/delay.h>

#define B1 0,0
#define B2 0,1
#define B3 0,2
#define B4 0,3

void But_VidInit()
{
	DIO_VidSetPinDirection(B1,0);
	DIO_VidSetPinDirection(B2,0);
	DIO_VidSetPinDirection(B3,0);
	DIO_VidSetPinDirection(B4,0);
}

Buttons But_VidGetPressed()
{
	/* delay is for de-bouncing effect*/
	if(!DIO_U8GetPinValue(B1))
	{
		_delay_ms(50);
		return Button1;
	}
	if(!DIO_U8GetPinValue(B2))
	{
		_delay_ms(50);
		return Button2;
	}
	if(!DIO_U8GetPinValue(B3))
	{
		_delay_ms(50);
		return Button3;
	}
	if(!DIO_U8GetPinValue(B4))
	{
		_delay_ms(50);
		return Button4;
	}

	return None;
}
