/*
 * TIM2_PROG.c
 *
 *  Created on: Jun 21, 2023
 *      Author: saziz
 */
#include"TIM2_PRIVATE.h"
#include"DIO_INTERFACE.h"
#include"STD_TYPES.h"
#include"BIT_MATH.h"
void TIM2_VidGetPresValNORMAL(u16 FREQ)
{
	u8 pres=1;
	u32 minm=100000;

	for(int i=1;i<=5;i++)
	{
		u32 xfreq=(8000000)/256;
		if(i==1);
		else if(i==2)
		{
			xfreq/=8;
		}
		else if (i==3)
		{
			xfreq/=64;
		}
		else if(i==4)
		{
			xfreq/=256;
		}
		else if(i==5)
		{
			xfreq/=1024;
		}
		u16 diff;
		if(xfreq>FREQ)
			diff=xfreq-FREQ;
		else
			diff=FREQ-xfreq;
		if(diff<minm)
		{minm=diff;
		pres=i;
		}
	}
	TCCR2&=0b11111000;
	TCCR2|=pres;
}
void TIM2_VidInit(u32 FREQ)
{
	SET_BIT(TCCR2,3);
	SET_BIT(TCCR2,6);
	SET_BIT(TCCR2,5);
	CLR_BIT(TCCR2,4);
	TIM2_VidGetPresValNORMAL(FREQ);
	DIO_VidSetPinDirection(3,7,1);
}
void TIM2_VidWritePwm(u8 val)
{

		OCR2=val;

}
