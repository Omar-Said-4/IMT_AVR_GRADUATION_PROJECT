/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : SPI_PROG.c       *******************/
/******** Date	     : 23/10/2022           ****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : --             **********************/
/***********************************************************/
/***********************************************************/
#include"SPI_PRIV.h"
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"DIO_INTERFACE.h"

static void(*SPI_SLAVE_CALLBACK)(void)=0;
void __vector_12(void)
{
  SPI_SLAVE_CALLBACK();
}


void SPI_VidMasterInit()
{
	DIO_VidSetPinDirection(1,5,1);
	DIO_VidSetPinDirection(1,6,0);
	DIO_VidSetPinDirection(1,4,1);
	DIO_VidSetPinDirection(1,7,1);
	
	/*SPI Enable*/
	SET_BIT(SPCR,6);
	
	/*Set Master*/
	SET_BIT(SPCR,4);
	
	/*Clock Polarity Rising*/
	CLR_BIT(SPCR,3);
	
	/*Clock Phase no sampling*/
	SET_BIT(SPCR,2);
	
	/*Lowest Prescalar*/
	SET_BIT(SPCR,1);
	SET_BIT(SPCR,0);

	/* Disable Interrupt */
	CLR_BIT(SPCR,7);

	
}


void SPI_VidSlaveInit()
{
	DIO_VidSetPinDirection(1,5,0);
	DIO_VidSetPinDirection(1,6,1);
	DIO_VidSetPinDirection(1,4,0);
	DIO_VidSetPinDirection(1,7,0);
	/*SPI ENable*/
    SET_BIT(SPCR,6);

	/*Set Slave*/
	CLR_BIT(SPCR,4);
	
	/*Clock Phase no sampling*/
	SET_BIT(SPCR,2);
	
	/*Clock Polarity Rising*/
	CLR_BIT(SPCR,3);
	
	/*
	Lowest Prescalar useless
	SET_BIT(SPCR,1);
	SET_BIT(SPCR,0);
    */

	/* Enable Interrupt */
	SET_BIT(SPCR,7);

}



u8 SPI_U8Transaction(u8 data)
{
	SPDR=data;
	while(!GET_BIT(SPSR,7));
	return SPDR;
}
void SPI_VidSetRecCb(void(*ptr)(void))
{
SPI_SLAVE_CALLBACK=ptr;
}
