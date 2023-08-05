/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : EXIT_INTERFACE_H.h     *****************/
/******** Date	     : 8/10/2022           *****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : --             **********************/
/***********************************************************/
/***********************************************************/



#ifndef EXIT_INTERFACE_H
#define EXIT_INTERFACE_H
typedef enum
{
	INT0,
	INT1,
	INT2
}Interrupts;

typedef enum
{

	LL,  /*low level*/
	ANY,  /*Any change*/
	Falling, /*falling edge*/
	Rising    /*Rising edge*/
}Int_Type;
void INTR_VidI0Cb(void(*ptr)(void));
void EXIT_VidInit(Interrupts Intr, Int_Type type);
void INTR_VidDisable(Interrupts Intr);




#endif
