/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : TIM0_PROG.c       *******************/
/******** Date	     : 23/10/2022           ****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : --             **********************/
/***********************************************************/
/***********************************************************/
#include"TIM0_PRIV.h"
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"TIM0_CONFIG.h"
#include"DIO_INTERFACE.h"
#if(TIM0_OPERATION_MODE==OVERFLOW)
static u32 OVF_COUNTER;
static u8 preload=0;
#endif
#if(TIM0_OPERATION_MODE==NORMAL_MODE||TIM0_OPERATION_MODE==FAST_PWM)
void TIM0_VidGetPresValNORMAL(u16 AlarmOrFreq)
{
	/* Find best matching frequency */
		u8 pres=1;
	#if(TIM0_CLK_TYPE ==INTERNAL_CLK)
		#if(TIM0_OPERATION_MODE==NORMAL_MODE)
	/*TOV*/
	f64 T=256.0/8000.0;
	T=AlarmOrFreq/T;
	f32 min=100000;
	/*ov-count*/
	OVF_COUNTER=T;
	/*prescalar*/
	for(int i=1;i<=5;i++)
	{
		f32 x=T;
		if(i==1);
		else if(i==2)
		{
			x/=8;
		}
		else if (i==3)
		{
			x/=64;
		}
		else if(i==4)
		{
			x/=256;
		}
		else if(i==5)
		{
			x/=1024;
		}
		u32 ovfc=x;
		x = x-(u32)x;
		x*=256;
		x=256-x;
		u8 pre=x;
		x-=pre;
		if(min>x)
		{
			OVF_COUNTER=ovfc;
			min=x;
			pres=i;
			preload=pre;
		}
	}
	
	TCNT0=preload;
	OVF_COUNTER++;
	#elif(TIM0_OPERATION_MODE==FAST_PWM)
     u32 minm=100000;
     	 
	for(int i=1;i<=5;i++)
	{
   	    u32 xfreq=(8000000)/256;
		if(i==1);
		else if(i==2)
		{
			xfreq/=8;
		}
		else if (i==3)
		{
			xfreq/=64;
		}
		else if(i==4)
		{
			xfreq/=256;
		}
		else if(i==5)
		{
			xfreq/=1024;
		}
		u16 diff;
		if(xfreq>AlarmOrFreq)
		diff=xfreq-AlarmOrFreq;
        else
        diff=AlarmOrFreq-xfreq;
        if(diff<minm)
		{minm=diff;
         pres=i;
		}		 	
	}
	#endif
	TCCR0&=0b11111000;
	TCCR0|=pres;
#endif
}
#endif
/*takes alarm in normal mode, frequency in fast pwm mode, prescalar value in CTC mode*/
void TIM0_VidInit(u32 AlarmOrFreqOrPrescalar)
{


	/*OVERFLOW FLAG ENABLE*/
#if (TIM0_OPERATION_MODE == NORMAL_MODE)
	SET_BIT(TIMSK,0);
#elif (TIM0_OPERATION_MODE==FAST_PWM)
SET_BIT(TCCR0,3);	
SET_BIT(TCCR0,6);
DIO_VidSetPinDirection(1,3,1);
#if(PWM_MODE==NON_INVERTING_MODE)
SET_BIT(TCCR0,5);	
CLR_BIT(TCCR0,4);	
#elif(PWM_MODE==INVERTING_MODE)
SET_BIT(TCCR0,5);	
CLR_BIT(TCCR0,4);
#endif
#elif (TIM0_OPERATION_MODE==CTC_MODE)
SET_BIT(TCCR0,3);	
CLR_BIT(TCCR0,6);
#endif
#if(TIM0_OPERATION_MODE==NORMAL_MODE||TIM0_OPERATION_MODE==FAST_PWM)
TIM0_VidGetPresValNORMAL(AlarmOrFreqOrPrescalar);
#elif(TIM0_OPERATION_MODE==CTC_MODE)
	AlarmOrFreqOrPrescalar&=0b00000111;
    TCCR0&=0b11111000;
	TCCR0|=AlarmOrFreqOrPrescalar;
#endif
}
#if(TIM0_OPERATION_MODE==FAST_PWM)
void TIM0_VidWritePwm(u8 val)
{
	#if(PWM_MODE==NON_INVERTING_MODE)
		OCR0=val;
	#elif(PWM_MODE==INVERTING_MODE)
		OCR0=255-val;
	#endif
}
#endif
#if(TIM0_OPERATION_MODE==CTC_MODE)
void TIM0_VidSetOCR0(u8 val)
{
	OCR0=val;
}
#endif
#if(TIM0_OPERATION_MODE==OVERFLOW)
static u32 counts=0;
void __vector_11(void)
{
	counts++;
	if(counts==OVF_COUNTER)
	{
	  TCNT0=preload;
	  DIO_VidTogglePinValue(0,0);
	  counts=0;
	}

}
#endif
#if(TIM0_OPERATION_MODE==CTC_MODE)
void __vector_10(void)
{
	counts++;
	if(counts==OVF_COUNTER)
	{
	  TCNT0=preload;
	  DIO_VidTogglePinValue(0,0);
	  counts=0;
	}

}
#endif



