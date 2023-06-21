/***************************************************************************/
/**************SWC      : DIO Driver****************************************/
/**************BY       : Mahmoud Essam*************************************/
/**************Date     : 27Aug22*******************************************/
/**************Version  : 1.0***********************************************/
/***************************************************************************/
#include "STD_Types.h"
#include "BIT_MATH.H"
#include "DIO_private.h"
#include "DIO_int.h"


/* Setting Pin Direction */

void DIO_VidSetPinDirection (u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction){
	
	if (Copy_u8Direction == Input)
	{
		switch (Copy_u8Port) {
			
			case Port_A : CLR_BIT(DDRA, Copy_u8Pin); break;
			case Port_B : CLR_BIT(DDRB, Copy_u8Pin); break;
			case Port_C : CLR_BIT(DDRC, Copy_u8Pin); break;
			case Port_D : CLR_BIT(DDRD, Copy_u8Pin); break;
			
			
		}
	}
	else if (Copy_u8Direction == Output)
	{
		
		switch (Copy_u8Port){
			
			case Port_A : SET_BIT(DDRA, Copy_u8Pin); break;
			case Port_B : SET_BIT(DDRB, Copy_u8Pin); break;
			case Port_C : SET_BIT(DDRC, Copy_u8Pin); break;
			case Port_D : SET_BIT(DDRD, Copy_u8Pin); break;
		
		
	}
	
}
}

/* Setting Pin Value */

void DIO_VidSetPinValue (u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value){
	
	if (Copy_u8Value == PinHigh)
	{
		switch (Copy_u8Port){
			
			case Port_A : SET_BIT(PORTA, Copy_u8Pin); break;
			case Port_B : SET_BIT(PORTB, Copy_u8Pin); break;
			case Port_C : SET_BIT(PORTC, Copy_u8Pin); break;
			case Port_D : SET_BIT(PORTD, Copy_u8Pin); break;
			
			
		}
	}
	else if (Copy_u8Value == PinLow)
	{
		
		switch (Copy_u8Port){
			
			case Port_A : CLR_BIT(PORTA, Copy_u8Pin); break;
			case Port_B : CLR_BIT(PORTB, Copy_u8Pin); break;
			case Port_C : CLR_BIT(PORTC, Copy_u8Pin); break;
			case Port_D : CLR_BIT(PORTD, Copy_u8Pin); break;
		
		
	}
	
	}
	
}

/* Getting Pin Value */

void DIO_VidGetPinValue (u8 Copy_u8Port, u8 Copy_u8Pin, u8 *pu8Data){
	
		switch (Copy_u8Port){
			
			case Port_A : *pu8Data = GET_BIT(PINA, Copy_u8Pin); break;
			case Port_B : *pu8Data = GET_BIT(PINB, Copy_u8Pin); break;
			case Port_C : *pu8Data = GET_BIT(PINC, Copy_u8Pin); break;
			case Port_D : *pu8Data = GET_BIT(PIND, Copy_u8Pin); break;
			
			
		}
 }
	
	
void DIO_VidSetPortDirection(u8 Copy_u8Port, u8 Copy_u8DirectionValue)
{
	switch(Copy_u8Port)
	{
		case Port_A : DDRA = Copy_u8DirectionValue; break;
		case Port_B : DDRB = Copy_u8DirectionValue; break;
		case Port_C : DDRC = Copy_u8DirectionValue; break;
		case Port_D : DDRD = Copy_u8DirectionValue; break;

	}
}

void DIO_VidSetPortValue(u8 Copy_u8Port, u8 Copy_u8PortValue)
{
	switch(Copy_u8Port)
	{
		case Port_A : PORTA =  Copy_u8PortValue; break;
		case Port_B : PORTB =  Copy_u8PortValue; break;
		case Port_C : PORTC =  Copy_u8PortValue; break;
		case Port_D : PORTD =  Copy_u8PortValue; break;

	}
}

void DIO_VidGetPortValue( u8 Copy_u8Port, u8 *pu8Data){

	switch (Copy_u8Port){

	case Port_A : *pu8Data = PORTA; break;
	case Port_B : *pu8Data = PORTB; break;
	case Port_C : *pu8Data = PORTC; break;
	case Port_D : *pu8Data = PORTD; break;


	}



}



