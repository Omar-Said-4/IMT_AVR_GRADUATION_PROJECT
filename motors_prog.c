#include "STD_Types.h"
#include "DIO_int.h"
#include "motors_config.h"
#include "motors_int.h"
void MOTORS_VidMoveForward (void)
{
	// Left Motors CCW
	DIO_VidSetPinValue(MOTORS_PORT,IN1,PinLow);
	DIO_VidSetPinValue(MOTORS_PORT,IN2,PinHigh);
	// Right Motors CW
	DIO_VidSetPinValue(MOTORS_PORT,IN3,PinLow);
	DIO_VidSetPinValue(MOTORS_PORT,IN4,PinHigh);
}
void MOTORS_VidMoveBackward (void)
{
	// Left Motors CW
	DIO_VidSetPinValue(MOTORS_PORT,IN1,PinHigh);
	DIO_VidSetPinValue(MOTORS_PORT,IN2,PinLow);
	// Right Motors CCW
	DIO_VidSetPinValue(MOTORS_PORT,IN3,PinHigh);
	DIO_VidSetPinValue(MOTORS_PORT,IN4,PinLow);
}
void MOTORS_VidMoveRight (void)
{
	// Left Motors CCW
	DIO_VidSetPinValue(MOTORS_PORT,IN1,PinLow);
	DIO_VidSetPinValue(MOTORS_PORT,IN2,PinHigh);
	// Right Motors CCW
	DIO_VidSetPinValue(MOTORS_PORT,IN3,PinHigh);
	DIO_VidSetPinValue(MOTORS_PORT,IN4,PinLow);
}
void MOTORS_VidMoveLeft (void)
{
	// Left Motors CW
	DIO_VidSetPinValue(MOTORS_PORT,IN1,PinHigh);
	DIO_VidSetPinValue(MOTORS_PORT,IN2,PinLow);
	// Right Motors CW
	DIO_VidSetPinValue(MOTORS_PORT,IN3,PinLow);
	DIO_VidSetPinValue(MOTORS_PORT,IN4,PinHigh);
}
void MOTORS_VidStop (void)
{
	// All Motors Stop
	DIO_VidSetPinValue(MOTORS_PORT,IN1,PinLow);
	DIO_VidSetPinValue(MOTORS_PORT,IN2,PinLow);
	DIO_VidSetPinValue(MOTORS_PORT,IN3,PinLow);
	DIO_VidSetPinValue(MOTORS_PORT,IN4,PinLow);
}
