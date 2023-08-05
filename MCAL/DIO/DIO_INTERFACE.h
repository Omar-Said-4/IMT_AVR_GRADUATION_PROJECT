#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H
#include"STD_TYPES.h"
#define OUTPUT 1
#define INPUT 0
#define HIGH 1
#define LOW 0
#define PORT_OUTPUT 255
#define PORT_INPUT 0
void DIO_VidSetPinDirection(u8 port, u8 pin, u8 dir);
void DIO_VidSetPortDirection(u8 port, u8 dir);
void DIO_VidSetPinValue(u8 port, u8 pin, u8 val);
void DIO_VidSetPortValue(u8 port,u8 val);
u8 DIO_U8GetPinValue(u8 port, u8 pin);
void DIO_VidTogglePinValue(u8 port,u8 pin);

#endif