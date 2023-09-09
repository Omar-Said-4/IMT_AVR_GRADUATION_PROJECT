/*
 * Path finding and Going to a specific cell after receiving Acknowledge are non interruptible
 *
 *
 * */

#include"../LIB/STD_TYPES.h"
#include"../LIB/MATH.h"
//#include"TIM0_INTERFACE.h"
//#include"TWI_INTERFACE.h"
//#include"MPU_INTERFACE.h"
//#include"UART_INTERFACE.h"
#include"../HAL/NRF/NRF_INTERFACE.h"
//#include"DIO_INTERFACE.h"
#include"../MCAL/ICU/ICU_INTERFACE.h"
//#include"UTS_INTERFACE.h"
#include"Line Following/LINE_FOLLOW_DFS.h"
#include"Line Following/LINE_FOLLOW.h"
//#include"STD_TYPES.h"
//#include"BUT_INT.h"
#include"DFS.h"
#include"../MCAL/GIE/GIE.h"
#include"Car_DFS.h"
#include"../HAL/Bluetooth/BT_INTERFACE.h"
#include"../HAL/Motors/motors_int.h"
#include"Grids/GRID.h"
#include"Bluetooth Control/bluetooth_control.h"
#include<util/delay.h>
mode currmode=none;
mode prevmode=none;
Movs gestmov=stop;
string message;
bool goOn=false;
void VidCarStateMov()
{
	switch(gestmov)
	{
	case front:
		MOTORS_VidMoveForward();
		break;
	case left:
		MOTORS_VidMoveLeft();
		break;
	case back:
		MOTORS_VidMoveBackward();
		break;
	case right:
		MOTORS_VidMoveRight();
		break;
	case stop:
		MOTORS_VidStop();
		break;
	}
}
void main()
{


	BT_VidInit();
	MOTORS_VidInit();
	NRF_VidInit();
	GIE_VidEnable();
	LF_VidInit();


	NRF_VidStartListening();
	while(1)
	{
		if(NRF_VidAvailable())
		{
			MOTORS_VidStop();
			message=NRF_VidReadMessage();

			if(message[0]=='1')
			{
				currmode=RC;
			}
			else if(message[0]=='2')
			{
				currmode=LineFollowing;

			}
			else if(message[0]=='3')
			{
				currmode=Grid;
			}
			else if(message[0]=='4')
			{
				MOTORS_SetSpeed(160);
				currmode=Gesture;
			}
			else if(message[0]=='f')
			{
				gestmov=front;
			}
			else if(message[0]=='b')
			{
				gestmov=back;
			}
			else if(message[0]=='l')
			{
				gestmov=left;
			}
			else if(message[0]=='r')
			{
				gestmov=right;
			}
			else if(message[0]=='s')
			{
				gestmov=stop;
			}
			else
			{
				currmode=none;
			}
		}

		if(prevmode==LineFollowing&&currmode!=prevmode)
		{
			ICU_VidDisInterrupt();
		}
		switch(currmode)
		{
		case RC:
			BTC_VidProcess();
			break;
		case LineFollowing:
			if(currmode!=prevmode)
			{
				MOTORS_SetSpeed(160);

				UTS_VidInit();
				LF_VidFindPath();
			}
			LF_VidProcess(2);
			break;
		case Gesture:
			VidCarStateMov();
			break;
		case Grid:
			if(prevmode!=currmode)
			{
				MOTORS_SetSpeed(155);
				RIGHT_MOTOR_SetSpeed(159);
			}
			GRID_VidInteract();
			break;
		default:
			break;

		}
		prevmode=currmode;

	}
}

