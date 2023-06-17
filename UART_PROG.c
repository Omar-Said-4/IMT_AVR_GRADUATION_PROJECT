/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : UART_PROG.c       *******************/
/******** Date	     : 23/10/2022           ****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : --             **********************/
/***********************************************************/
/***********************************************************/
#include"UART_PRIV.h"
#include"STD_TYPES.h"
#include"BIT_MATH.h"
static void(*UART_REC_CALLBACK)(void)=0;
void UART_VidDisable()
{
	CLR_BIT(UCSRB,TXEN);
	CLR_BIT(UCSRB,RXEN);
#if (MODE == INTERRUPT_MODE)
	CLR_BIT(UCSRB,RXCIE);
#endif
}
void UART_VidInit(u8 bits)
{

	/*NUMBER OF BITS*/
	if(bits!=9)
	{
		bits-=5;
		bits<<=1;
		UCSRC|=bits;
		CLR_BIT(UCSRB,UCSZ2);
	}
	else
	{
	  bits-=6;
	  bits<<=1;
      UCSRC|=bits;
      SET_BIT(UCSRB,UCSZ2);
	}
//	CLR_BIT(UBRRH,7);
//    SET_BIT(UCSRC,1);
//    SET_BIT(UCSRC,2);
//    CLR_BIT(UCSRB,2);

//	/*SELECTING BAUD RATE OF 9600*/

	UBRRL=BAUD_RATE_LOW_VAL;
	UBRRH=BAUD_RATE_HIGH_VAL;
//	/*ENABLE TRANSMITTER AND RECIEVER*/

	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
#if (MODE == INTERRUPT_MODE)
	SET_BIT(UCSRB,RXCIE);
#endif
}

void UART_VidSendData(u8 data)
{
   while(!GET_BIT(UCSRA,UDRE));
   UDR=data;
}

u8 UART_U8RecieveData()
{
#if (MODE == POLLING_MOD)
	while(!GET_BIT(UCSRA,RXC));
#endif
	   return UDR;
}
void UART_VidSetRecCb(void(*ptr)(void))
{
UART_REC_CALLBACK=ptr;
}
void __vector_13(void)
{
UART_REC_CALLBACK();
}
