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

	SPCR|=(1<<SPE)|(1<<MSTR)|(1<<SPR0);


}


void SPI_VidSlaveInit()
{
	DIO_VidSetPinDirection(1,5,0);
	DIO_VidSetPinDirection(1,6,1);
	DIO_VidSetPinDirection(1,4,0);
	DIO_VidSetPinDirection(1,7,0);
	SPCR|=(1<<SPE)|(1<<SPIE)|(1<<SPR0);

}



u8 SPI_U8Transaction(u8 data)
{
	SPDR=data;
	while(!GET_BIT(SPSR,SPIF));
	return SPDR;
}
void SPI_VidSetRecCb(void(*ptr)(void))
{
	SPI_SLAVE_CALLBACK=ptr;
}
