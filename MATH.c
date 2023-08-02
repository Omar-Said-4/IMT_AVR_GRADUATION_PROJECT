/*
 * math.c
 *
 *  Created on: Jul 5, 2023
 *      Author: saziz
 */

#include"STD_TYPES.h"
u32 power(u8 base,u8 pow)
{
		u32 acc=1;
		while(pow)
		{
			if(pow&1)
			 acc*=base;
			pow>>=1;
			base*=base;
		}
		return acc;
	}
bool strcmp(string str1,string str2,int length)
{

	for(u8 i=0;i<length;i++)
	{
		if(str1[i]!=str2[i])
			return false;
	}
	return true;
}
