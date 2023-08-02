/*
 * Path finding and Going to a specific cell after receiving Acknowledge are non interruptible
 *
 *
 * */

#include"TIM0_INTERFACE.h"
#include"TWI_INTERFACE.h"
#include"MPU_INTERFACE.h"
#include"UART_INTERFACE.h"
#include"NRF_INTERFACE.h"
#include"DIO_INTERFACE.h"
#include"ICU_INTERFACE.h"
#include"UTS_INTERFACE.h"
#include"LINE_FOLLOW.h"
#include"STD_TYPES.h"
#include"BUT_INT.h"
#include"DFS.h"
#include"GIE.h"
#include"Car_DFS.h"
#include"BT_INTERFACE.h"
#include"motors_int.h"
#include"GRID.h"
#include"bluetooth_control.h"
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
					//UART_VidPrintString(message);
					//UART_VidPrintString("\n\r");
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
//f32 ax,ay,az,t,gx,gy,gz;
//Buttons currbut=None;
//Buttons prevbut=None;
//bool gesture=false;
//Movs currmov=stop;
//Movs prevmov=stop;
//void main()
//{
//	//UART_VidInit(8);
//	//UART_VidPrintString("welcome\n\r");
//	DIO_VidSetPinDirection(LED1,1);
//	DIO_VidSetPinDirection(LED2,1);
//	DIO_VidSetPinDirection(LED3,1);
//	DIO_VidSetPinDirection(LED4,1);
//	NRF_VidInit();
//	But_VidInit();
//	MPU_VidInit();
//	while(1)
//	{
//		if(gesture)
//		{
//			prevmov=currmov;
//			//UART_VidPrintString("MPU\n\r");
//			MPU_VidGetReadings(&ax,&ay,&az,&t,&gx,&gy,&gz);
////			UART_VidParseFloat(ax);
//	//		UART_VidPrintString("  ");
//		//	UART_VidParseFloat(ay);
//			//UART_VidPrintString("\n\r");
//			//_delay_ms(1000);
//			if(ax>0.8)
//			{
//				currmov=back;
//				if(currmov!=prevmov){
//			     NRF_U8SendMessage("b",1);
//				}
//			}
//			else if(ax<0)
//			{
//				currmov=front;
//				if(currmov!=prevmov){
//					NRF_U8SendMessage("f",1);
//				}
//
//			}
//			else if(ay>0.6)
//			{
//				currmov=right;
//				if(currmov!=prevmov){
//					NRF_U8SendMessage("r",1);
//				}
//			}
//			else if(ay<-0.5)
//			{
//				currmov=left;
//				if(currmov!=prevmov){
//					NRF_U8SendMessage("l",1);
//				}
//			}
//			else
//			{
//				currmov=stop;
//				if(currmov!=prevmov){
//					NRF_U8SendMessage("s",1);
//				}
//			}
//		}
//		else
//		{
//			prevmov=currmov=stop;
//		}
//		currbut=But_VidGetPressed();
//
//		if(currbut==prevbut)continue;
//		prevbut=currbut;
//		if(currbut==Button1)
//		{
//			DIO_VidSetPinValue(LED1,1);
//			DIO_VidSetPinValue(LED2,0);
//			DIO_VidSetPinValue(LED3,0);
//			DIO_VidSetPinValue(LED4,0);
//			gesture=false;
//			NRF_U8SendMessage("1",1);
//
//		}
//		else if(currbut==Button2)
//		{
//			DIO_VidSetPinValue(LED2,1);
//			DIO_VidSetPinValue(LED1,0);
//			DIO_VidSetPinValue(LED3,0);
//			DIO_VidSetPinValue(LED4,0);
//			gesture=false;
//			NRF_U8SendMessage("2",1);
//		}
//		else if(currbut==Button3)
//		{
//			DIO_VidSetPinValue(LED3,1);
//			DIO_VidSetPinValue(LED2,0);
//			DIO_VidSetPinValue(LED1,0);
//			DIO_VidSetPinValue(LED4,0);
//			gesture=false;
//			NRF_U8SendMessage("3",1);
//		}
//		else if(currbut==Button4)
//		{
//			DIO_VidSetPinValue(LED4,1);
//			DIO_VidSetPinValue(LED2,0);
//			DIO_VidSetPinValue(LED3,0);
//			DIO_VidSetPinValue(LED1,0);
//			gesture=true;
//			NRF_U8SendMessage("4",1);
//		}
//	}
//
//}
