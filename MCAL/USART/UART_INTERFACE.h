
/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : UART_INTERFACE.h     ****************/
/******** Date	     : 23/10/2022           ****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : --             **********************/
/***********************************************************/
/***********************************************************/


#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#include"STD_TYPES.h"
void UART_VidSendData(u8 data);
void UART_VidPrintString(string x);
void UART_VidParseInt(s32 x);
void UART_VidParseFloat(f32 x);
void UART_VidInit(u8 bits);
void UART_VidDisable();
u8 UART_U8Available();
u8 UART_U8GetData();
void UART_VidSetRecCb(void(*ptr)(void));
u8 UART_U8RecieveData();
#endif
