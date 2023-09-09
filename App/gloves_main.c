#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
#include"DFS.h"
#include"../HAL/Push Button/BUT_INT.h"
#include"../HAL/NRF/NRF_INTERFACE.h"
#include"../MCAL/DIO/DIO_INTERFACE.h"
#include"../HAL/MPU/MPU_INTERFACE.h"
f32 ax,ay,az,t,gx,gy,gz;
Buttons currbut=None;
Buttons prevbut=None;
bool gesture=false;
Movs currmov=stop;
Movs prevmov=stop;
void main()
{

	DIO_VidSetPinDirection(LED1,OUTPUT);
	DIO_VidSetPinDirection(LED2,OUTPUT);
	DIO_VidSetPinDirection(LED3,OUTPUT);
	DIO_VidSetPinDirection(LED4,OUTPUT);
	NRF_VidInit();
	But_VidInit();
	MPU_VidInit();
	while(1)
	{
		if(gesture)
		{
			prevmov=currmov;
			MPU_VidGetReadings(&ax,&ay,&az,&t,&gx,&gy,&gz);
			if(ax>0.8)
			{
				currmov=back;
				if(currmov!=prevmov){
			     NRF_U8SendMessage("b",1);
				}
			}
			else if(ax<0)
			{
				currmov=front;
				if(currmov!=prevmov){
					NRF_U8SendMessage("f",1);
				}

			}
			else if(ay>0.6)
			{
				currmov=right;
				if(currmov!=prevmov){
					NRF_U8SendMessage("r",1);
				}
			}
			else if(ay<-0.5)
			{
				currmov=left;
				if(currmov!=prevmov){
					NRF_U8SendMessage("l",1);
				}
			}
			else
			{
				currmov=stop;
				if(currmov!=prevmov){
					NRF_U8SendMessage("s",1);
				}
			}
		}
		else
		{
			prevmov=currmov=stop;
		}
		currbut=But_VidGetPressed();

		if(currbut==prevbut)continue;
		prevbut=currbut;
		if(currbut==Button1)
		{
			DIO_VidSetPinValue(LED1,HIGH);
			DIO_VidSetPinValue(LED2,LOW);
			DIO_VidSetPinValue(LED3,LOW);
			DIO_VidSetPinValue(LED4,LOW);
			gesture=false;
			NRF_U8SendMessage("1",1);

		}
		else if(currbut==Button2)
		{
			DIO_VidSetPinValue(LED2,HIGH);
			DIO_VidSetPinValue(LED1,LOW);
			DIO_VidSetPinValue(LED3,LOW);
			DIO_VidSetPinValue(LED4,LOW);
			gesture=false;
			NRF_U8SendMessage("2",1);
		}
		else if(currbut==Button3)
		{
			DIO_VidSetPinValue(LED3,HIGH);
			DIO_VidSetPinValue(LED2,LOW);
			DIO_VidSetPinValue(LED1,LOW);
			DIO_VidSetPinValue(LED4,LOW);
			gesture=false;
			NRF_U8SendMessage("3",1);
		}
		else if(currbut==Button4)
		{
			DIO_VidSetPinValue(LED4,HIGH);
			DIO_VidSetPinValue(LED2,LOW);
			DIO_VidSetPinValue(LED3,LOW);
			DIO_VidSetPinValue(LED1,LOW);
			gesture=true;
			NRF_U8SendMessage("4",1);
		}
	}

}
