/*
 * MOU_PROG.c
 *
 *  Created on: Jun 18, 2023
 *      Author: saziz
 */

#include"MPU_INTERFACE.h"
#include"MPU_PRIV.h"
#include<util/delay.h>
#include"TWI_INTERFACE.h"
void MPU_VidInit()
{
	_delay_ms(150);
	TWI_VidStartCheck(MPU_WRITE_ADDR);
	TWI_VidSendByte(SMPLRT_DIV);
	/* 1khz*/
	TWI_VidSendByte(0x07);
	TWI_VidStop();

	TWI_VidStartCheck(MPU_WRITE_ADDR);
	TWI_VidSendByte(PWR_MGMT_1);
	/* X axis Gyroscope reference freq */
	TWI_VidSendByte(0x01);
	TWI_VidStop();

	TWI_VidStartCheck(MPU_WRITE_ADDR);
	TWI_VidSendByte(CONFIG);
	/* Disable Input  non prescaled Sample rate =8khz */
	TWI_VidSendByte(0x00);
	TWI_VidStop();

	TWI_VidStartCheck(MPU_WRITE_ADDR);
	TWI_VidSendByte(GYRO_CONFIG);
	/* Full Scale Gyro */
	TWI_VidSendByte(0x18);
	TWI_VidStop();

	TWI_VidStartCheck(MPU_WRITE_ADDR);
	TWI_VidSendByte(INT_ENABLE);
	/* Enable data ready interrupt */
	TWI_VidSendByte(0x01);
	TWI_VidStop();

}

void MPU_VidGetReadings(f32*Accx,f32*Accy,f32*Accz,f32*temp,f32*gyrox,f32*gyroy,f32*gyroz)
{
	/* start address of the first register to read from (ACCEL_XOUT_H) */
	TWI_VidStartCheck(MPU_WRITE_ADDR);
	TWI_VidSendByte(ACCEL_XOUT_H);
	TWI_VidStart(MPU_READ_ADDR);
	*(Accx)=(((s16)TWI_U8ReadACK()<<8)|(((s16)TWI_U8ReadACK())));
	*(Accy)=(((s16)TWI_U8ReadACK()<<8)|(((s16)TWI_U8ReadACK())));
	*(Accz)=(((s16)TWI_U8ReadACK()<<8)|(((s16)TWI_U8ReadACK())));
	*(temp)=(((s16)TWI_U8ReadACK()<<8)|(((s16)TWI_U8ReadACK())));
	*(gyrox)=(((s16)TWI_U8ReadACK()<<8)|(((s16)TWI_U8ReadACK())));
	*(gyroy)=(((s16)TWI_U8ReadACK()<<8)|(((s16)TWI_U8ReadACK())));
	*(gyroz)=(((s16)TWI_U8ReadACK()<<8)|(((s16)TWI_U8ReadNACK())));
	TWI_VidStop();
	*(Accx)/=16384.0;
	*(Accy)/=16384.0;
	*(Accz)/=16384.0;
	*(temp)=*(temp)/340.0+36.53;
	*(gyrox)/=16.4;
	*(gyroy)/=16.4;
	*(gyroz)/=16.4;

}

