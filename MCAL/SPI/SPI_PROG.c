/***********************************************************/
/***********************************************************/
/******** Author  	 : Omar Said           *****************/
/******** File name  : SPI_PROG.c       *******************/
/******** Date	     : 23/10/2022           ****************/
/******** Version  	 : V1                  *****************/
/******** Desc  	 : --             **********************/
/***********************************************************/
/***********************************************************/
#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"
#include"SPI_PRIV.h"
#include"../DIO/DIO_INTERFACE.h"

static void(*SPI_SLAVE_CALLBACK)(void)=0;
void __vector_12(void)
{
	if(SPI_SLAVE_CALLBACK!=(void *)(0)){
		SPI_SLAVE_CALLBACK();
	}
}


void SPI_VidMasterInit()
{
	DIO_VidSetPinDirection(Port_B,5,OUTPUT);
	DIO_VidSetPinDirection(Port_B,6,INPUT);
	DIO_VidSetPinDirection(Port_B,4,OUTPUT);
	DIO_VidSetPinDirection(Port_B,7,OUTPUT);

	SPCR|=(1<<SPE)|(1<<MSTR)|(1<<SPR0);


}


void SPI_VidSlaveInit()
{
	DIO_VidSetPinDirection(Port_B,5,INPUT);
	DIO_VidSetPinDirection(Port_B,6,OUTPUT);
	DIO_VidSetPinDirection(Port_B,4,INPUT);
	DIO_VidSetPinDirection(Port_B,7,INPUT);
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
