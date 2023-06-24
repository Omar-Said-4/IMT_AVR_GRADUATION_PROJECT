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

	SPCR|=(1<<6)|(1<<4)|(1<<0);


}


void SPI_VidSlaveInit()
{
	DIO_VidSetPinDirection(1,5,0);
	DIO_VidSetPinDirection(1,6,1);
	DIO_VidSetPinDirection(1,4,0);
	DIO_VidSetPinDirection(1,7,0);
	u8 SPCR_HELP=0;

	SET_BIT(SPCR_HELP,6);

	/*Set Slave*/
	CLR_BIT(SPCR_HELP,4);

	/*Clock Phase no sampling*/
	SET_BIT(SPCR_HELP,2);

	/*Clock Polarity Rising*/
	CLR_BIT(SPCR_HELP,3);

	/*Lowest Prescalar useless*/
	/* Enable Interrupt */
	SET_BIT(SPCR_HELP,7);
	SPCR=SPCR_HELP;
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
