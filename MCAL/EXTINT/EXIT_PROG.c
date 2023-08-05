/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : EXIT_PROG.c         *****************/
/******** Date	     : 8/10/2022           *****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : --             **********************/
/***********************************************************/
/***********************************************************/
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"EXIT_PRIVATE.h"
#include"EXIT_INTERFACE.h"
static void(*I0)(void)=0;

void EXIT_VidInit(Interrupts Intr, Int_Type type)
{
	/*GIE->Enable*/
	SET_BIT(SREG,7);
	switch(Intr)
	{
	case INT0:
		/*PIE->Enable*/
		SET_BIT(GICR,6);
		if(type==Falling)
		{
			/*Sense control of interrupt 0 is falling edge*/
			SET_BIT(MCUCR,1);
			CLR_BIT(MCUCR,0);
		}
		else if(type==Rising)
		{
			/*Sense control of interrupt 0 is rising edge*/
			SET_BIT(MCUCR,1);
			SET_BIT(MCUCR,0);
		}
		else if(type==LL)
		{
			/*Sense control of interrupt 0 is LOW Level*/
			CLR_BIT(MCUCR,1);
			CLR_BIT(MCUCR,0);
		}
		else if(type==ANY)
		{
			/*Sense control of interrupt 0 is any logical change*/
			CLR_BIT(MCUCR,1);
			SET_BIT(MCUCR,0);
		}
		else
		{
			/*Do Nothing*/
		}
		break;
	case INT1:
		/*PIE->Enable*/
		SET_BIT(GICR,7);
		if(type==Falling)
		{
			/*Sense control of interrupt 1 is falling edge*/
			SET_BIT(MCUCR,3);
			CLR_BIT(MCUCR,2);
		}
		else if(type==Rising)
		{
			/*Sense control of interrupt 1 is rising edge*/
			SET_BIT(MCUCR,3);
			SET_BIT(MCUCR,2);
		}
		else if(type==LL)
		{
			/*Sense control of interrupt 1 is LOW Level*/
			CLR_BIT(MCUCR,3);
			CLR_BIT(MCUCR,2);
		}
		else if(type==ANY)
		{
			/*Sense control of interrupt 1 is any logical change*/
			CLR_BIT(MCUCR,3);
			SET_BIT(MCUCR,2);
		}
		else
		{
			/*Do Nothing*/
		}
		break;
	case INT2:
		/*PIE->Enable*/
		SET_BIT(GICR,5);
		if(type==Falling)
		{
			/*Sense control of interrupt 2 is falling edge*/
			CLR_BIT(MCUCSR,6);
		}
		else if(type==Rising)
		{
			/*Sense control of interrupt 2 is rising edge*/
			SET_BIT(MCUCSR,6);
		}
		else
		{
			/*Do Nothing*/
		}
		break;
	}
}
void INTR_VidDisable(Interrupts Intr)
{
	switch(Intr)
	{
	case INT0:	CLR_BIT(GICR,6); break;
	case INT1:	CLR_BIT(GICR,7); break;
	case INT2:	CLR_BIT(GICR,5); break;
	}
}
void INTR_VidI0Cb(void(*ptr)(void))
{
	I0=ptr;
}

void __vector_1(void)  
{
	I0();
}
void __vector_2(void)  
{
	DIO_VidTogglePinValue(0,0);

}
void __vector_3(void)  
{
	DIO_VidTogglePinValue(0,0);

}
