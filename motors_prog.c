#include "STD_TYPES.h"
#include "DIO_int.h"
#include "motors_config.h"
#include "TIM0_INTERFACE.h"
#include "TIM2_INTERFACE.h"

/*
 * IN1, IN2 for Right Motor
 * IN3, IN4 for Left Motor
 */
void MOTORS_VidMoveForward (void)
{
		// Right Motors CW
		DIO_VidSetPinValue(MOTORS_PORT,IN1,PinLow);
		DIO_VidSetPinValue(MOTORS_PORT,IN2,PinHigh);
		// Left Motors CCW
		DIO_VidSetPinValue(MOTORS_PORT,IN3,PinLow);
		DIO_VidSetPinValue(MOTORS_PORT,IN4,PinHigh);
}
void MOTORS_VidMoveBackward (void)
{
	// Right Motors CCW
	DIO_VidSetPinValue(MOTORS_PORT,IN1,PinHigh);
	DIO_VidSetPinValue(MOTORS_PORT,IN2,PinLow);
	// Left Motors CW
	DIO_VidSetPinValue(MOTORS_PORT,IN3,PinHigh);
	DIO_VidSetPinValue(MOTORS_PORT,IN4,PinLow);
}
void MOTORS_VidMoveRight (void)
{
	// Right Motors CCW
	DIO_VidSetPinValue(MOTORS_PORT,IN1,PinHigh);
	DIO_VidSetPinValue(MOTORS_PORT,IN2,PinLow);
	// Left Motors CCW
	DIO_VidSetPinValue(MOTORS_PORT,IN3,PinLow);
	DIO_VidSetPinValue(MOTORS_PORT,IN4,PinHigh);

}
void MOTORS_VidMoveLeft (void)
{
		// Right Motors CW
		DIO_VidSetPinValue(MOTORS_PORT,IN1,PinLow);
		DIO_VidSetPinValue(MOTORS_PORT,IN2,PinHigh);
		// Left Motors CW
		DIO_VidSetPinValue(MOTORS_PORT,IN3,PinHigh);
		DIO_VidSetPinValue(MOTORS_PORT,IN4,PinLow);
}
void MOTORS_VidStop (void)
{
	// All Motors Stop
	DIO_VidSetPinValue(MOTORS_PORT,IN1,PinLow);
	DIO_VidSetPinValue(MOTORS_PORT,IN2,PinLow);
	DIO_VidSetPinValue(MOTORS_PORT,IN3,PinLow);
	DIO_VidSetPinValue(MOTORS_PORT,IN4,PinLow);
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
