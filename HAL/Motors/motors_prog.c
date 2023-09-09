#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_INTERFACE.h"
#include "../../MCAL/TIMERS/TIM0_INTERFACE.h"
#include "../../MCAL/TIMERS/TIM2_INTERFACE.h"
#include "motors_config.h"
#include"motors_int.h"

void MOTORS_VidInit(void)
{
	DIO_VidSetPinDirection(MOTORS_PORT,IN1,1);
	DIO_VidSetPinDirection(MOTORS_PORT,IN2,1);
	DIO_VidSetPinDirection(MOTORS_PORT,IN3,1);
	DIO_VidSetPinDirection(MOTORS_PORT,IN4,1);
	TIM0_VidInit(2000);
	TIM2_VidInit(2000);
	DIO_VidSetPinValue(MOTORS_PORT,IN1,0);
	DIO_VidSetPinValue(MOTORS_PORT,IN2,0);
	DIO_VidSetPinValue(MOTORS_PORT,IN3,0);
	DIO_VidSetPinValue(MOTORS_PORT,IN4,0);
	MOTORS_VidMoveForward();
	MOTORS_SetSpeed(150);
    MOTORS_VidStop();
}
/*
 * IN1, IN2 for Right Motor
 * IN3, IN4 for Left Motor
 */
void MOTORS_VidMoveForward (void)
{
	// Right Motors CW
	DIO_VidSetPinValue(MOTORS_PORT,IN1,0);
	DIO_VidSetPinValue(MOTORS_PORT,IN2,1);
	// Left Motors CCW
	DIO_VidSetPinValue(MOTORS_PORT,IN3,0);
	DIO_VidSetPinValue(MOTORS_PORT,IN4,1);
}
void MOTORS_VidMoveBackward (void)
{
	// Right Motors CCW
	DIO_VidSetPinValue(MOTORS_PORT,IN1,1);
	DIO_VidSetPinValue(MOTORS_PORT,IN2,0);
	// Left Motors CW
	DIO_VidSetPinValue(MOTORS_PORT,IN3,1);
	DIO_VidSetPinValue(MOTORS_PORT,IN4,0);
}
void MOTORS_VidMoveRight (void)
{
	// Right Motors CCW
	DIO_VidSetPinValue(MOTORS_PORT,IN1,1);
	DIO_VidSetPinValue(MOTORS_PORT,IN2,0);
	// Left Motors CCW
	DIO_VidSetPinValue(MOTORS_PORT,IN3,0);
	DIO_VidSetPinValue(MOTORS_PORT,IN4,1);

}
void MOTORS_VidMoveLeft (void)
{
	// Right Motors CW
	DIO_VidSetPinValue(MOTORS_PORT,IN1,0);
	DIO_VidSetPinValue(MOTORS_PORT,IN2,1);
	// Left Motors CW
	DIO_VidSetPinValue(MOTORS_PORT,IN3,1);
	DIO_VidSetPinValue(MOTORS_PORT,IN4,0);
}
void MOTORS_VidStop (void)
{
	// All Motors Stop
	DIO_VidSetPinValue(MOTORS_PORT,IN1,0);
	DIO_VidSetPinValue(MOTORS_PORT,IN2,0);
	DIO_VidSetPinValue(MOTORS_PORT,IN3,0);
	DIO_VidSetPinValue(MOTORS_PORT,IN4,0);

}
void MOTORS_SetSpeed (u8 Copy_u8MotorSpeed)
{
	TIM0_VidWritePwm(Copy_u8MotorSpeed); //ENA
	TIM2_VidWritePwm(Copy_u8MotorSpeed); //ENB
}
void RIGHT_MOTOR_SetSpeed (u8 Copy_u8MotorSpeed)
{
	TIM0_VidWritePwm(Copy_u8MotorSpeed); //ENA
}
void LEFT_MOTOR_SetSpeed (u8 Copy_u8MotorSpeed)
{
	TIM2_VidWritePwm(Copy_u8MotorSpeed); //ENB
}
