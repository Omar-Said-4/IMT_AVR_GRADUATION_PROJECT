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
void UART_VidPrintString(string x)
{
	for(int i=0;x[i]!='\0';i++)
	{
		UART_VidSendData(x[i]);
	}
}
void UART_VidParseInt(s32 num)
{
	u8 x=0;
	s32 rev =0;
	bool neg=false;
	if(num<0)
	{neg=true;
	num=-num;}
	if(num==0)
	{
		UART_VidSendData(48);
		return;
	}
	if(neg)
		UART_VidSendData('-');
	while(num)
	{
		rev=(rev*10)+(num%10);
		num/=10;
		x++;
	}

	while(x)
	{
		u8 p=rev%10+48;
		UART_VidSendData(p);
		rev/=10;
		x--;
	}
}
void UART_VidParseFloat(f32 x)
{
	if(x<0)
	{
		UART_VidSendData('-');
		x=-x;
	}
	s32 intx= (s32)x;
	UART_VidParseInt(intx);
	UART_VidSendData('.');
	u32 fx=(u32)((x-intx)*1000.0);
	if(fx<0)
		fx=-fx;
	UART_VidParseInt(fx);

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
u8 UART_U8GetData()
{
	   return UDR;
}
u8 UART_U8Available()
{
	return GET_BIT(UCSRA,RXC);
}
void UART_VidSetRecCb(void(*ptr)(void))
{
UART_REC_CALLBACK=ptr;
}
void __vector_13(void)
{
UART_REC_CALLBACK();
}
