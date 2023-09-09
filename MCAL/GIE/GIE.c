/*

 * GIE.c
 *
 *  Created on: Jun 17, 2023
 *      Author: saziz
 */
#include"../../LIB/BIT_MATH.h"
#include"../../LIB/STD_TYPES.h"
#include"GIE.h"
void GIE_VidEnable()
{
	SET_BIT(SREG,7);
}


