/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : TIM0_PROG.c       *******************/
/******** Date	     : 23/10/2022           ****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : --             **********************/
/***********************************************************/
/***********************************************************/
#include"TIM1_PRIV.h"
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"TIM1_CONFIG.h"
#include"DIO_INTERFACE.h"
//static u32 OVF_COUNTER;
//static u16 preload=0;
//static u16 PWM_MAX_VAL;
void TIM1_VidSetPrescalar(u8 prescalar)
{
	prescalar&=0b00000111;
	TCCR1B&=0b11011000;
	TCCR1B|=prescalar;
}
void TIM1_VidInit()
{
	TIMSK=0;

	#if (TIM1_OPERATION_MODE==FAST_PWM_ICR1)
     	SET_BIT(TCCR1A,1);	
     	SET_BIT(TCCR1B,4);	
     	SET_BIT(TCCR1B,3);	
        CLR_BIT(TCCR1A,0);
	#if(PWM_MODE==NON_INVERTING_MODE)
        SET_BIT(TCCR1A,7);	
     	SET_BIT(TCCR1A,5);	
		CLR_BIT(TCCR1A,6);
        CLR_BIT(TCCR1A,4);
	#endif
	#endif
}
#if (TIM1_OPERATION_MODE==FAST_PWM_ICR1)
void TIM1_VidSetICR1(u16 val)
{
    ICR1=val;
}
#endif
#if (TIM1_OPERATION_MODE==FAST_PWM_ICR1)
void TIM1_VidWritePwmOCR1A(u16 val)
{

		OCR1A=val;
}
#endif
void TIM1_VidWritePwmOCR1B(u16 val)
{

		OCR1BH=val;
}
void TIM1_VidReset()
{
	TCCR1A=0;
	TCCR1B=0;
	ICR1=0;
}
