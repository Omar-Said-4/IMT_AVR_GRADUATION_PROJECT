/*

 * LINE_FOLLOW.c
 *
 *  Created on: Jul 24, 2023
 *      Author: saziz
 */
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"motors_int.h"
#include"LINE_FOLLOW_DFS.h"
#include"SVM_INTERFACE.h"
#include"LINE_FOLLOW.h"
#include"DIO_INTERFACE.h"
#include"UTS_INTERFACE.h"
#include<util/delay.h>
static feedback currstate=sforward;
static feedback prevstate=snone;
void LF_VidInit()
{

	DIO_VidSetPinDirection(SENSOR_1_PIN,0);
	DIO_VidSetPinDirection(SENSOR_2_PIN,0);
	SVM_VidInit();
	SVM_SetAngleOC1A(-90);
	_delay_ms(300);

	SVM_VidSTOP();


}

void LF_VidFindPath()
{

	feedback sen=LF_VidGetState();
	while(sen!=sright&&sen!=sleft)
	{
		feedback uts=LF_BoolObstacle();
		if(uts==snone)
			MOTORS_VidMoveForward();
		else if(uts==fobstacle)
		{
			MOTORS_VidMoveLeft();
			_delay_ms(250);
			MOTORS_VidStop();
		}
		else if(uts==lfobstacle)
		{
			MOTORS_VidMoveRight();
			_delay_ms(250);
			MOTORS_VidStop();
		}
		else
		{
			MOTORS_VidMoveRight();
			_delay_ms(300);
			MOTORS_VidStop();
		}
		sen=LF_VidGetState();

	}
	UTS_VidStop();
	MOTORS_VidStop();
}
feedback LF_BoolObstacle()
{
	f32 initr=UTS_F32GetReading();
	UTS_VidStop();
	//UART_VidParseFloat(initr);
	//UART_VidPrintString("\n\r");
	if(initr<15)
	{
		MOTORS_VidStop();
		//UART_VidPrintString("left\n\r");
		SVM_VidInit();
		SVM_SetAngleOC1A(-45);
		_delay_ms(300);
		SVM_VidSTOP();
		UTS_VidInit();
		_delay_ms(300);
		for(int i=0;i<5;i++)
			initr=UTS_F32GetReading();
		//UART_VidParseFloat(initr);
		//UART_VidPrintString("left\n\r");
		//UART_VidPrintString("R\n\r");
		if(initr<20)
		{
			UTS_VidStop();
			SVM_VidInit();
			SVM_SetAngleOC1A(-90);
			_delay_ms(300);
			SVM_VidSTOP();
			UTS_VidInit();

			return lfobstacle;
		}
		else
		{
			UTS_VidStop();
			SVM_VidInit();
			SVM_SetAngleOC1A(-90);
			_delay_ms(300);

			SVM_VidSTOP();
			UTS_VidInit();

			return fobstacle;
		}
	}
	return snone;
}
feedback LF_VidGetState()
{
	if((DIO_U8GetPinValue(SENSOR_1_PIN)==0)&&DIO_U8GetPinValue(SENSOR_2_PIN)==0)
	{
		////UART_VidPrintString("F\n\r");
		return sforward;
	}
	else if((DIO_U8GetPinValue(SENSOR_1_PIN)==1)&&DIO_U8GetPinValue(SENSOR_2_PIN)==0)
	{
		////UART_VidPrintString("R\n\r");
		return sright;
	}

	else if((DIO_U8GetPinValue(SENSOR_1_PIN)==0)&&DIO_U8GetPinValue(SENSOR_2_PIN)==1)
	{
		////UART_VidPrintString("L\n\r");
		return sleft;
	}
	else if((DIO_U8GetPinValue(SENSOR_1_PIN)==1)&&DIO_U8GetPinValue(SENSOR_2_PIN)==1)
	{
		////UART_VidPrintString("S\n\r");
		return sstop;
	}
	return snone;
}

void LF_VidProcess(u8 mode)
{
	currstate=LF_VidGetState();
	if(mode==2){
		if(currstate==prevstate)return;
		else
		{
			MOTORS_VidStop();
		}
	}
	switch(currstate)
	{
	case sforward:
		MOTORS_VidMoveForward();
		break;
	case sright:
		MOTORS_VidMoveRight();
		// _delay_ms(250);

		break;
	case sleft:
		MOTORS_VidMoveLeft();
		//_delay_ms(250);
		break;
	case sstop:
		if(prevstate==sforward)
			MOTORS_VidStop();
		else
			currstate=prevstate;
		break;
	default:
		break;

	}
	prevstate=currstate;
}

void LF_VidProcess2()
{
	currstate=LF_VidGetState();
	switch(currstate)
	{
	case sforward:
		MOTORS_VidStop();
		break;
	case sright:
		MOTORS_VidMoveRight();
		break;
	case sleft:
		MOTORS_VidMoveLeft();
		//_delay_ms(250);
		break;
	case sstop:
		MOTORS_VidMoveForward();
		break;
	default:
		break;
	}
	prevstate=currstate;
}

