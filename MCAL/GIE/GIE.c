/*

 * GIE.c
 *
 *  Created on: Jun 17, 2023
 *      Author: saziz
 */
#include"GIE.h"
#include"BIT_MATH.h"
#include"STD_TYPES.h"
void GIE_VidEnable()
{
	SET_BIT(SREG,7);
}


