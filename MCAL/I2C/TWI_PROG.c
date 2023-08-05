/*
 * TWI_PROG.c
 *
 *  Created on: Jun 18, 2023
 *      Author: saziz
 */


#include"TWI_INTERFACE.h"
#include"STD_TYPES.h"
#include"TWI_PRIV.h"
#include"MATH.h"
//#include"UART_INTERFACE.h"
#include"BIT_MATH.h"
//#include<util/delay.h>

void TWI_VidMasterInit(void)
{
	/* Bit Rate: 100000 Hz */
	TWBR=BITRATE(0x00);
	//TWSR=0x01;

}
void TWI_VidSlaveInit()
{
	/* Slave Address =1 , No General Call Response*/
	TWAR = 0xD0;
	TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);

}
void TWI_U8SlvRcv()
{
	while(!GET_BIT(TWCR,TWINT));
	u8 status=TWI_U8GetStatus();
	if(status==0x60)
	{
		TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);
	}
	while(!GET_BIT(TWCR,TWINT));
	//status=TWI_U8GetStatus();
	//if(status==0x80)
	//UART_VidSendData(TWDR);

}
void TWI_VidStartCheck(u8 address)
{
	u8 status;
	while (1)
	{
		TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
		while (!GET_BIT(TWCR,TWINT));
		status = TWI_U8GetStatus();
		if (status != 0x08)
			continue;
		TWI_VidSendByte(address);
		status = TWI_U8GetStatus();
		if (status != 0x18 )
		{
			TWI_VidStop();
			continue;
		}
		break;
	}

}
void TWI_VidStart(u8 address)
{
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);
	while (!GET_BIT(TWCR,TWINT));
	TWDR = address;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while(!GET_BIT(TWCR,TWINT));

}
void TWI_VidStop(void)
{
	/* Send Stop Condition */
	TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
	while(!GET_BIT(TWCR,TWSTO));
}
void TWI_VidSendByte(u8 data)
{
	/* Load Data To TWDR */
	TWDR = data;
	/* Send Data  */
	TWCR = (1 << TWEN) | (1 << TWINT);
	while(!GET_BIT(TWCR,TWINT));
	//UART_VidParseInt(TWI_U8GetStatus());
	//UART_VidPrintString("\n\r");

}
u8 TWI_U8ReadACK(void)
{
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);    /* enable Ack */

	while(!GET_BIT(TWCR,TWINT));
	/* Read Data */
	return TWDR;
}
u8 TWI_U8ReadNACK(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN);   /* disable Ack */

	while(!GET_BIT(TWCR,TWINT));
	/* Read Data */
	return TWDR;
}

u8 TWI_U8GetStatus(void)
{
	u8 status=TWSR & 0xF8;
	return status;
}


