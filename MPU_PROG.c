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
	TWI_VidStart();
	TWI_VidSendByte(MPU_WRITE_ADDR);
	TWI_VidSendByte(MPU_SMPRT_DIV);
	/* 1khz*/
	TWI_VidSendByte(0x07);
	TWI_VidStop();

	TWI_VidStart();
	TWI_VidSendByte(MPU_WRITE_ADDR);
	TWI_VidSendByte(MPU_PWR_MGMT_1);
    /* X axis Gyroscope reference freq */
	TWI_VidSendByte(0x01);
	TWI_VidStop();

	TWI_VidStart();
	TWI_VidSendByte(MPU_WRITE_ADDR);
	TWI_VidSendByte(MPU_CONFIG);
	/* Disable Input  non prescaled Sample rate =8khz */
	TWI_VidSendByte(0x00);
	TWI_VidStop();

	TWI_VidStart();
	TWI_VidSendByte(MPU_WRITE_ADDR);
	TWI_VidSendByte(MPU_GYRO_CONFIG);
	/* Full Scale Gyro */
	TWI_VidSendByte(0x18);
	TWI_VidStop();

	TWI_VidStart();
	TWI_VidSendByte(MPU_WRITE_ADDR);
	TWI_VidSendByte(MPU_INT_EN);
	/* Enable data ready interrupt */
	TWI_VidSendByte(0x01);
	TWI_VidStop();

}
void MPU_VidGetReadings(f32*Accx,f32*Accy,f32*Accz,f32*temp,f32*gyrox,f32*gyroy,f32*gyroz)
{
	TWI_VidStart();
	TWI_VidSendByte(MPU_WRITE_ADDR);
	TWI_VidSendByte(ACCEL_XOUT_H);
    TWI_VidStart();
    TWI_VidSendByte(MPU_READ_ADDR);
	*(Accx)=(((u32)TWI_U8ReadACK()<<8)|((u32)TWI_U8ReadACK()<<8));
	*(Accy)=(((u32)TWI_U8ReadACK()<<8)|((u32)TWI_U8ReadACK()<<8))/16384.0;
	*(Accz)=(((u32)TWI_U8ReadACK()<<8)|((u32)TWI_U8ReadACK()<<8))/16384.0;
	*(temp)=(((u32)TWI_U8ReadACK()<<8)|((u32)TWI_U8ReadACK()<<8))/340.0+36.53;
	*(gyrox)=(((u32)TWI_U8ReadACK()<<8)|((u32)TWI_U8ReadACK()<<8))/16.4;
	*(gyroy)=(((u32)TWI_U8ReadACK()<<8)|((u32)TWI_U8ReadACK()<<8))/16.4;
	*(gyroz)=(((u32)TWI_U8ReadACK()<<8)|((u32)TWI_U8ReadACK()<<8))/16.4;
	TWI_VidStop();
}
