#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H
#define OUTPUT 1
#define INPUT 0
#define HIGH 1
#define LOW 0
#define PORT_OUTPUT 255
#define PORT_INPUT 0
typedef enum {

	Port_A,
	Port_B,
	Port_C,
	Port_D



} et_Port;

typedef enum {
	Pin_0,
	Pin_1,
	Pin_2,
	Pin_3,
	Pin_4,
	Pin_5,
	Pin_6,
	Pin_7


}et_Pin;

void DIO_VidSetPinDirection(u8 port, u8 pin, u8 dir);
void DIO_VidSetPortDirection(u8 port, u8 dir);
void DIO_VidSetPinValue(u8 port, u8 pin, u8 val);
void DIO_VidSetPortValue(u8 port,u8 val);
u8 DIO_U8GetPinValue(u8 port, u8 pin);
void DIO_VidTogglePinValue(u8 port,u8 pin);

#endif
