/*
 * UTS_PROG.c

 *
 *  Created on: Jun 19, 2023
 *      Author: saziz
 */
#include"../../LIB/STD_TYPES.h"
#include"../../MCAL/ICU/ICU_INTERFACE.h"
#include"../../MCAL/DIO/DIO_INTERFACE.h"
#include<avr/delay.h>
#define TRIGGER_PIN 0,7
extern u32 snap1,snap2;
extern u8 flag;
void UTS_VidInit()
{
	ICU_VidInit();
	DIO_VidSetPinDirection(TRIGGER_PIN,1);
}
void UTS_VidStop()
{
	ICU_VidStop();
}

f32  UTS_F32GetReading()
{
	f32 distance=0;
	/* take ten samples for more accurate measurements*/
  for(int i=0;i<10;i++){
  ICU_VidStart();
  DIO_VidSetPinValue(TRIGGER_PIN,1);
  _delay_us(10);
  DIO_VidSetPinValue(TRIGGER_PIN,0);
  while(flag!=2);
  ICU_VidStop();
  flag=0;
  distance+=((snap2-snap1)*0.034/2);
}
  return distance/10;

}

