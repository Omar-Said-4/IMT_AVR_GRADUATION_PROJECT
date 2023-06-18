
/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : TIM0_INTERFACE.h     ****************/
/******** Date	     : 23/10/2022           ****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : --             **********************/
/***********************************************************/
/***********************************************************/


#ifndef TIM1_INTERFACE_H
#define TIM1_INTERFACE_H

#include"STD_TYPES.h"
void TIM1_VidSetPrescalar(u8 prescalar);
void TIM1_VidInit();
void TIM1_VidSetICR1(u16 val);
void TIM1_VidWritePwmOCR1A(u16 val);
void TIM1_VidWritePwmOCR1B(u16 val);
#endif
