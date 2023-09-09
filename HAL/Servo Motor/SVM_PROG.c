#include"../../LIB/STD_TYPES.h"
#include"../../MCAL/TIMERS/TIM1_INTERFACE.h"
#include"SVM_CFG.h"
#include"../../MCAL/DIO/DIO_INTERFACE.h"
void SVM_VidInit()
{
	TIM1_VidInit();
	TIM1_VidSetPrescalar(2);
	TIM1_VidSetICR1(20000);
#if(OC1A==ON)
DIO_VidSetPinDirection(3,5,1);
#endif

#if(OC1B==ON)
DIO_VidSetPinDirection(3,4,1);
#endif
}

#if(OC1A==1)
void SVM_SetAngleOC1A(s8 angle)
{

    u16 res=((angle+90)*11.4+450);
	TIM1_VidWritePwmOCR1A(res);

}
#endif
#if(OC1B==1)
void SVM_SetAngleOC1B(u8 angle)
{

	u16 res=((angle+90)*11.4+450);
	//u16 res=position/180.0*1000+1000
	TIM1_VidWritePwmOCR1B(res);

}
#endif
void SVM_VidSTOP()
{
	TIM1_VidReset();
}


