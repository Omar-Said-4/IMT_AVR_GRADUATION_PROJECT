
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"UART_INTERFACE.h"
#include"DIO_INTERFACE.h"
#include "GIE.h"
#include"BT_INTERFACE.h"
#include<avr/delay.h>
#include"SVM_INTERFACE.h"
#include"UTS_INTERFACE.h"
#include"TIM2_INTERFACE.h"
#include"NRF_INTERFACE.h"
volatile bool message_received = false;
volatile bool status = false;
void test()
{
	message_received=true;
}
void main()
{

	GIE_VidEnable();

	//UART_VidInit(8);
	//UTS_VidInit();
//   TWI_VidInit();
//   MPU_VidInit();
// 	f32 accx,accy,accz,gyrox,gyroy,gyroz,temp;
    NRF_VidInit();
    INTR_VidI0Cb(test);
    /*recieve
	NRF_VidStartListening();
	while(1)
	{
		if (message_received)
				{
					//	Message received, print it
					message_received = false;
					//	Send message as response
					  if(    NRF_VidReadMessage()[0]=='O')
					  {

					  //led on
					  }
					_delay_ms(200);

				}
		*/
    /*send*/
/*
    string tx_message="Omar";

    while(1)
    {
		status = NRF_U8SendMessage(tx_message,4);
							_delay_ms(500);

		if (status == true)
		{
			//led on
		}
    }
    */
//		accx=1;
//     MPU_VidGetReadings(&accx,&accy,&accz,&temp,&gyrox,&gyroy,&gyroz);
//     UART_VidPrintString("accx= ");
//     UART_VidParseFloat(accx/16384.0);
//     UART_VidPrintString("  accy= ");
//     UART_VidParseFloat(accy);
//     UART_VidPrintString("  accz= ");
//     UART_VidParseFloat(accz);
//     UART_VidPrintString("  temp= ");
//     UART_VidParseFloat(temp);
//     UART_VidPrintString("  gyrox= ");
//     UART_VidParseFloat(gyrox);
//     UART_VidPrintString("  gyroy= ");
//     UART_VidParseFloat(gyroy);
//     UART_VidPrintString("  gyroz= ");
//     UART_VidParseFloat(gyroz);
		//UART_VidPrintString("Distance: ");
	//	UART_VidParseFloat(UTS_F32GetReading());
		//UART_VidPrintString(" Cm");
     //UART_VidPrintString("\n\r");


	}

}
