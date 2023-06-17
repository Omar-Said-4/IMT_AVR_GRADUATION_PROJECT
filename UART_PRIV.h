/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : UART_PRIV.h       *******************/
/******** Date	     : 4/11/2022           ****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : --             **********************/
/***********************************************************/
/***********************************************************/

#ifndef UART_PRIV_H
#define UART_PRIV_H

#include"STD_TYPES.h"
#define UDR *((volatile u8*)0x2C)
#define UCSRA *((volatile u8*)0x2B)
#define UCSRB *((volatile u16*)0x2A)
#define UBRRL *((volatile u16*)0x29)
#define UBRRH *((volatile u16*)0x40)
#define UCSRC *((volatile u16*)0x40)

#define BAUD_RATE_LOW_VAL 51
#define BAUD_RATE_HIGH_VAL 0
#define INTERRUPT_MOD 0
#define POLLING_MOD 1
#define MODE INTERRUPT_MOD
#define RXC 7
#define RXCIE 7
#define UDRE 5
#define UCSZ2 2
#define TXEN 3
#define RXEN 4
void __vector_13(void) __attribute__((signal));
#endif
