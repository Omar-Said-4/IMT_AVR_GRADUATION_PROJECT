#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"
#include"DIO_PRIVATE.h" 

void DIO_VidSetPinDirection(u8 port, u8 pin, u8 dir)
{
	if(0==dir)
	{
		switch(port)
		{
		case 0: CLR_BIT(DDRA,pin); break;
		case 1: CLR_BIT(DDRB,pin); break;
		case 2: CLR_BIT(DDRC,pin); break;
		case 3: CLR_BIT(DDRD,pin); break;
		}
	}
	else if(1==dir)
	{
		switch(port)
		{
		case 0: SET_BIT(DDRA,pin); break;
		case 1: SET_BIT(DDRB,pin); break;
		case 2: SET_BIT(DDRC,pin); break;
		case 3: SET_BIT(DDRD,pin); break;
		}
	}
	else
	{
		/* Do nothing */
	}
}

void DIO_VidSetPortDirection(u8 port, u8 dir)
{
	switch(port)
	{
	case 0: DDRA=dir; break;
	case 1: DDRB=dir; break;
	case 2: DDRC=dir; break;
	case 3: DDRD=dir; break;
	}
}
void DIO_VidSetPinValue(u8 port, u8 pin, u8 val)
{
	if(0==val)
	{
		switch(port)
		{
		case 0: CLR_BIT(PORTA,pin); break;
		case 1: CLR_BIT(PORTB,pin); break;
		case 2: CLR_BIT(PORTC,pin); break;
		case 3: CLR_BIT(PORTD,pin); break;
		}
	}
	else if(1==val)
	{
		switch(port)
		{
		case 0: SET_BIT(PORTA,pin); break;
		case 1: SET_BIT(PORTB,pin); break;
		case 2: SET_BIT(PORTC,pin); break;
		case 3: SET_BIT(PORTD,pin); break;
		}
	}
	else
	{
		/* Do nothing */
	}
}
void DIO_VidSetPortValue(u8 port,u8 val)
{
	switch(port)
	{
	case 0: PORTA=val; break;
	case 1: PORTB=val; break;
	case 2: PORTC=val; break;
	case 3: PORTD=val; break;
	}

}
u8 DIO_U8GetPinValue(u8 port, u8 pin)
{
	u8 x=0;
	switch (port)
	{
	case 0: x = GET_BIT(PINA,pin); break;
	case 1: x = GET_BIT(PINB,pin); break;
	case 2: x = GET_BIT(PINC,pin); break;
	case 3: x = GET_BIT(PIND,pin); break;
	default: break; /*Do Nothing*/
	}
	return x;
}
void DIO_VidTogglePinValue(u8 port,u8 pin)
{
	switch (port)
	{
	case 0: TOGGLE_BIT(PORTA,pin);  break;
	case 1: TOGGLE_BIT(PORTB,pin);  break;
	case 2: TOGGLE_BIT(PORTC,pin);  break;
	case 3: TOGGLE_BIT(PORTD,pin);  break;
	}
}
