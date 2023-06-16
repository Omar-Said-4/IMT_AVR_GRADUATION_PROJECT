/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : BIT_MATH.h          *****************/
/******** Date	     : 17/9/2022           *****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : ..                  *****************/
/***********************************************************/
/***********************************************************/


#ifndef BIT_MATH_H
#define BIT_MATH_H


#define SET_BIT(var , num)    var|=(1<<num)

#define CLR_BIT(var , num)    var&=(~(1<<num))

#define TOGGLE_BIT(var , num) var^=(1<<num)

#define GET_BIT(var , num)   ((var>>num)&1)

#define POWEROF2(var)        !(var&(var-1))


	
// printf("%hhu", ch); for unsigned chars.
#endif