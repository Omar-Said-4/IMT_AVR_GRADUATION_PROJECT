/*

 * bluetooth_control.c
 *
 *  Created on: Jul 23, 2023
 *      Author: saziz
 */
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_INTERFACE.h"
#include"motors_int.h"
#include"UART_INTERFACE.h"
#include"BT_INTERFACE.h"
static u8 command=0;

void BTC_VidProcess()
{   if(UART_U8Available())
    {
      command=UART_U8GetData();
    }
	switch(command)
	{
	case 'F':
		MOTORS_VidMoveForward();
		command=0;
		break;
	case 'B':
			MOTORS_VidMoveBackward();
			command=0;
			break;
	case 'R':
			MOTORS_VidMoveRight();
			command=0;
			break;
	case 'L':
			MOTORS_VidMoveLeft();
			command=0;
			break;
	case 'S':
				MOTORS_VidStop();
				command=0;
				break;
	case '1':
			MOTORS_SetSpeed(160);
			command=0;
			break;
	case '2':
			MOTORS_SetSpeed(165);
			command=0;
			break;
	case '3':
		MOTORS_SetSpeed(170);
			command=0;
			break;
	case '4':
		MOTORS_SetSpeed(180);
			command=0;
			break;
	case '5':
		MOTORS_SetSpeed(190);
			command=0;
			break;
	case '6':
		MOTORS_SetSpeed(200);
			command=0;
			break;
	case '7':
		MOTORS_SetSpeed(215);
			command=0;
			break;
	case '8':
		MOTORS_SetSpeed(235);
			command=0;
			break;
	case '9':
		MOTORS_SetSpeed(245);
			command=0;
			break;
	case 'q':
		MOTORS_SetSpeed(255);
			command=0;
			break;

	}
}
