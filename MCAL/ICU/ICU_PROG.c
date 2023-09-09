/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : TIM0_PROG.c       *******************/
/******** Date	     : 23/10/2022           ****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : --             **********************/
/***********************************************************/
/***********************************************************/
#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"
#include"../TIMERS/TIM1_PRIV.h"
u8 OVF;
u32 snap1,snap2;
u8 flag=0;
void ICU_VidInit()
{       /* Overflow Mode */
     	CLR_BIT(TCCR1A,1);	
        CLR_BIT(TCCR1A,0);
     	CLR_BIT(TCCR1B,4);	
     	CLR_BIT(TCCR1B,3);
     	/* Sense rising edge  */
     	SET_BIT(TCCR1B,6);	

     	/* Enable specific interrupts */
     	SET_BIT(TIMSK,5);	
     	SET_BIT(TIMSK,2);	
		
}
void ICU_VidStart()
{
	/* reset timer */
	TCNT1=0;
	/* start timer with prescalar 1/8 */
 	SET_BIT(TCCR1B,1);

}
void ICU_VidStop()
{
	CLR_BIT(TCCR1B,1);
}
void ICU_VidDisInterrupt()
{

	CLR_BIT(TIMSK,5);
	CLR_BIT(TIMSK,2);
}
void __vector_9(void)
{
	OVF++;
}
void __vector_6(void)
{
	if(flag==0)
	{
		snap1=ICR1;
		OVF=0;
		flag=1;
     	CLR_BIT(TCCR1B,6);
	}
	else if(flag==1)
	{
	   snap2=ICR1+(OVF*65536);
	   SET_BIT(TCCR1B,6);
       flag=2;	   
	}
}
