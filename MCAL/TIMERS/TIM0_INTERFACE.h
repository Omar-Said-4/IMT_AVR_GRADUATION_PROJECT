
/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : TIM0_INTERFACE.h     ****************/
/******** Date	     : 23/10/2022           ****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : --             **********************/
/***********************************************************/
/***********************************************************/


#ifndef TIM0_INTERFACE_H
#define TIM0_INTERFACE_H

void TIM0_VidInit(u16 AlarmOrFreqOrPrescalar);
void TIM0_VidWritePwm(u8 val);
#endif
