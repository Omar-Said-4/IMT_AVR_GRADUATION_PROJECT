#include "STD_TYPES.h"
#include "DIO_int.h"
#include "GIE.h"
#include "UART_INTERFACE.h"
#include "BT_INTERFACE.h"
#include "TIM0_INTERFACE.h"
#include "TIM2_INTERFACE.h"
#include "motors_config.h"
#include "motors_int.h"

int main()
{
	GIE_VidEnable();
	u8 command;
	BT_VidInit();
	DIO_VidSetPinDirection(MOTORS_PORT,IN1,Output);
	DIO_VidSetPinDirection(MOTORS_PORT,IN2,Output);
	DIO_VidSetPinDirection(MOTORS_PORT,IN3,Output);
	DIO_VidSetPinDirection(MOTORS_PORT,IN4,Output);
	MOTORS_VidStop();
	TIM0_VidInit(8);
	TIM2_VidInit(8);
	MOTORS_SetSpeed(100);
	while(1)
	{
		command = UART_U8RecieveData();
		switch(command)
		{
			case 'F':
				MOTORS_VidMoveForward();
				break;
			case 'B':
				MOTORS_VidMoveBackward();
				break;
			case 'L':
				MOTORS_VidMoveLeft();
				break;
			case 'R':
				MOTORS_VidMoveRight();
				break;
			case 'S':
				MOTORS_VidStop();
				break;
			case '1':
			      MOTORS_SetSpeed (10);
			      break;
			    case '2':
			      MOTORS_SetSpeed (20);
			      break;
			    case '3':
			    	MOTORS_SetSpeed (30);
			      break;
			    case '4':
			    	MOTORS_SetSpeed (40);
			      break;
			      case '5':
			    	  MOTORS_SetSpeed (50);
			      break;
			      case '6':
			    	  MOTORS_SetSpeed (60);
			      break;
			      case '7':
			    	  MOTORS_SetSpeed (70);
			      break;
			      case '8':
			    	  MOTORS_SetSpeed (80);
			      break;
			      case '9':
			    	  MOTORS_SetSpeed (90);
			      break;
			      case 'q':
			    	  MOTORS_SetSpeed (100);
			      break;
			      default: break;

		}
	}

	return 0;
}