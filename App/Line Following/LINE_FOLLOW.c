/*

 * LINE_FOLLOW.c
 *
 *  Created on: Jul 24, 2023
 *      Author: saziz
 */
#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"
#include"LINE_FOLLOW_DFS.h"
#include"../../HAL/Motors/motors_int.h"
#include"LINE_FOLLOW_DFS.h"
#include"../../HAL/Servo Motor/SVM_INTERFACE.h"
#include"LINE_FOLLOW.h"
#include"../../MCAL/DIO/DIO_INTERFACE.h"
#include"../../HAL/Ultrasonic/UTS_INTERFACE.h"
#include<util/delay.h>
/*
 *
 *   delays values are based on try and error
 *
 * */
static feedback currstate=sforward;
static feedback prevstate=snone;
void LF_VidInit()
{

	DIO_VidSetPinDirection(SENSOR_1_PIN,INPUT);
	DIO_VidSetPinDirection(SENSOR_2_PIN,INPUT);
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
	if(initr<15)
	{
		MOTORS_VidStop();
		SVM_VidInit();
		SVM_SetAngleOC1A(-45);
		_delay_ms(300);
		SVM_VidSTOP();
		UTS_VidInit();
		_delay_ms(300);
		for(int i=0;i<5;i++)
			initr=UTS_F32GetReading();
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
		return sforward;
	}
	else if((DIO_U8GetPinValue(SENSOR_1_PIN)==1)&&DIO_U8GetPinValue(SENSOR_2_PIN)==0)
	{
		return sright;
	}

	else if((DIO_U8GetPinValue(SENSOR_1_PIN)==0)&&DIO_U8GetPinValue(SENSOR_2_PIN)==1)
	{
		return sleft;
	}
	else if((DIO_U8GetPinValue(SENSOR_1_PIN)==1)&&DIO_U8GetPinValue(SENSOR_2_PIN)==1)
	{
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
		break;
	case sstop:
		MOTORS_VidMoveForward();
		break;
	default:
		break;
	}
	prevstate=currstate;
}

