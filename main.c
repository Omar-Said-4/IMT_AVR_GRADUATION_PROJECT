
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"UART_INTERFACE.h"
#include"DIO_INTERFACE.h"
#include "GIE.h"
#include"BT_INTERFACE.h"
#include<avr/delay.h>
void test()
{
	u8 x=UART_U8RecieveData();
	//UART_VidSendData('a');
//	DIO_VidTogglePinValue(0,0);
	DIO_VidTogglePinValue(3,3);
}
void main()
{
	/* General Inteurrpt Enable*/
	GIE_VidEnable();
	BT_VidInit();
	DIO_VidSetPinDirection(3,3,1);

 	UART_VidSetRecCb(&test);

	while(1)
	{



	}

}
