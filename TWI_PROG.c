/*
 * TWI_PROG.c
 *
 *  Created on: Jun 18, 2023
 *      Author: saziz
 */


#include"TWI_INTERFACE.h"
#include"STD_TYPES.h"
#include"BIT_MATH.h"

void TWI_VidInit(void)
{
   /* Bit Rate: 400.000 kHz */
   TWBR=123;
   CLR_BIT(TWSR,1);
   SET_BIT(TWSR,0);
  /* Slave Address =1 , No General Call Response*/
   TWAR = 0x02;
  /*Allow acknowledge, No interrupt , Start Peripheral*/
   SET_BIT(TWCR,6);
   CLR_BIT(TWCR,0);
   SET_BIT(TWCR,2);
}

void TWI_VidStart(void)
{
	/* Send Start Condition */
	TWCR = (1 << 7) | (1 << 5) | (1 << 2);
    while(!GET_BIT(TWCR,7));

}
void TWI_VidStop(void)
{
	/* Send Stop Condition */
	TWCR = (1 << 7) | (1 << 4) | (1 << 2);
	while(TWCR&(1<<4));
}
void TWI_VidSendByte(u8 data)
{
	/* Load Data To TWDR */
	TWDR = data;
	/* Send Data  */
	 TWCR = (1 << 7) | (1 << 2);
	  while(!GET_BIT(TWCR,7));
}
u8 TWI_U8ReadACK(void)
{
	TWCR = (1 << 7) | (1 << 2) | (1 << 6);    /* enable Ack */

	  while(!GET_BIT(TWCR,7));

	  /* Read Data */
	  return TWDR;
}
u8 TWI_U8ReadNACK(void)
{
	TWCR = (1 << 7) | (1 << 2);   /* disable Ack */

    while(!GET_BIT(TWCR,7));

	/* Read Data */
	return TWDR;
}

u8 TWI_U8GetStatus(void)
{
	u8 status=TWSR & 0xF8;
	return status;
}


