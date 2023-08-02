/*
 * GRID.c
 *
 *  Created on: Jul 26, 2023
 *      Author: saziz
 */

#include"LINE_FOLLOW.h"
#include"motors_int.h"
#include"LINE_FOLLOW.h"
#include"DIO_INTERFACE.h"
#include<util/delay.h>
#include"GRID_DFS.h"
#include"LINE_FOLLOW_DFS.h"
#include"UART_INTERFACE.h"
static u8 currX=1;
static u8 currY=0;
static u8 destX=0;
static u8 destY=0;
nozzle carn=nright;

void GRID_VidRotateRight()
{


	//	feedback temp=LF_VidGetState();
	//	while(temp!=sforward)
	//	{
	//		if (temp==sstop){
	//			MOTORS_VidMoveForward();
	//			_delay_ms(500);
	//		}
	//		else if(temp==sright)
	//		{
	//			MOTORS_VidMoveRight();
	//		}
	//		else if(temp==sleft)
	//		{
	//			MOTORS_VidMoveLeft();
	//		}
	//
	//		temp=LF_VidGetState();
	//	}
	//	MOTORS_VidStop();
	//	//_delay_ms(3000);
	while(DIO_U8GetPinValue(SENSOR_1_PIN)!=1)
	{
		MOTORS_VidMoveRight();
	}
	MOTORS_VidStop();
	//_delay_ms(3000);
	while(LF_VidGetState()!=sforward)
	{
		MOTORS_VidMoveRight();
	}
	_delay_ms(100);
	MOTORS_VidStop();


}
void GRID_VidRotateLeft()
{
	MOTORS_SetSpeed(150);

	//	while(LF_VidGetState()!=sstop)
	//	{
	//		MOTORS_VidMoveForward();
	//	}
	//	MOTORS_VidStop();
	//	//_delay_ms(3000);
	//	feedback temp=LF_VidGetState();
	//	while(temp!=sforward)
	//	{
	//		if (temp==sstop){
	//			MOTORS_VidMoveForward();
	//			_delay_ms(500);
	//		}
	//		else if(temp==sright)
	//		{
	//			MOTORS_VidMoveRight();
	//		}
	//		else if(temp==sleft)
	//		{
	//			MOTORS_VidMoveLeft();
	//		}
	//
	//		temp=LF_VidGetState();
	//	}
	//	MOTORS_VidStop();
	//	//_delay_ms(3000);
	while(DIO_U8GetPinValue(SENSOR_2_PIN)!=1)
	{
		MOTORS_VidMoveLeft();
	}
	MOTORS_VidStop();
	//	_delay_ms(3000);
	while(LF_VidGetState()!=sforward)
	{
		MOTORS_VidMoveLeft();
	}
	MOTORS_VidStop();
	MOTORS_SetSpeed(155);
	RIGHT_MOTOR_SetSpeed(159);

}
u8 GRID_U8GetXY(u8 cellNum,u8 *y)
{
	u8 x=cellNum%3;
	*(y)=(cellNum/3);
	return x;
}
void GRID_VidGotoY()
{
	if(destY>currY)
	{
		if(carn==nright)
		{
			GRID_VidRotateLeft();
		}
		else if(carn==nleft)
		{
			GRID_VidRotateRight();
		}
		for(u8 i=currY;i<destY;i++)
		{

			while(LF_VidGetState()!=sstop)
			{
				_delay_ms(50);
				LF_VidProcess(1);
			}
			MOTORS_VidMoveForward();
			_delay_ms(300);
			MOTORS_VidStop();
			while(LF_VidGetState()!=sforward)
			{
				_delay_ms(50);
				LF_VidProcess2();
			}

			MOTORS_VidStop();
			//_delay_ms(3000);
		}
		carn=nup;
	}
	else if(currY>destY)
	{
		if(carn==nleft)
		{
			GRID_VidRotateLeft();
		}
		else if(carn==nright)
		{
			GRID_VidRotateRight();
		}
		for(u8 i=currY;i>destY;i--)
		{
			while(LF_VidGetState()!=sstop)
			{
				_delay_ms(50);
				LF_VidProcess(1);
			}
			MOTORS_VidMoveForward();
			_delay_ms(300);
			MOTORS_VidStop();
			while(LF_VidGetState()!=sforward)
			{
				_delay_ms(50);
				LF_VidProcess2();
			}

			MOTORS_VidStop();
			//_delay_ms(3000);
		}
		carn=ndown;
	}
	if((carn==nup&&destX>=currX))
	{
		GRID_VidRotateRight();
		carn=nright;
	}
	else if((carn==ndown&&destX<currX))
	{
		GRID_VidRotateRight();
		carn=nleft;
	}
	else if((carn==ndown&&destX>=currX))
	{
		GRID_VidRotateLeft();
		carn=nright;
	}
	else if((carn==nup&&destX<currX))
	{
		GRID_VidRotateLeft();
		carn=nleft;
	}
	currY=destY;

}

void GRID_VidGotoX()
{

	if(destX>currX)
	{
		if(carn!=nright)
		{
			GRID_VidRotateRight();
			GRID_VidRotateRight();
			carn=nright;
		}
		for(u8 i=currX;i<destX;i++)
		{

			while(LF_VidGetState()!=sstop)
			{
				_delay_ms(50);
				LF_VidProcess(1);
			}
			MOTORS_VidMoveForward();
			_delay_ms(300);
			MOTORS_VidStop();
			while(LF_VidGetState()!=sforward)
			{
				_delay_ms(50);
				LF_VidProcess2();
			}

			MOTORS_VidStop();
			//_delay_ms(3000);
		}
	}
	else if(destX<currX)
	{
		if(carn!=nleft)
		{
			GRID_VidRotateLeft();
			GRID_VidRotateLeft();
			carn=nleft;
		}
		for(u8 i=currX;i>destX;i--)
		{

			while(LF_VidGetState()!=sstop)
			{
				_delay_ms(50);
				LF_VidProcess(1);
			}
			MOTORS_VidMoveForward();
			_delay_ms(300);
			MOTORS_VidStop();
			while(LF_VidGetState()!=sforward)
			{
				_delay_ms(50);
				LF_VidProcess2();
			}

			MOTORS_VidStop();
			//_delay_ms(3000);
		}
	}

	currX=destX;
}

void GRID_VidProccess(u8 cellnum)
{

	destX=GRID_U8GetXY(cellnum,&destY);
	GRID_VidGotoY();
	GRID_VidGotoX();
}
void GRID_VidInteract()
{
	if(!UART_U8Available())
		return;
	u8 rec=UART_U8GetData();
	if(rec=='A')
	{

		rec=UART_U8RecieveData();

		rec-='0';
		UART_VidParseInt(rec);
				UART_VidPrintString("\n\r");
		GRID_VidProccess(rec);
	}
}
