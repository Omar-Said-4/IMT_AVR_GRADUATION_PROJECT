/*
 * MPU_INTERFACE.h
 *
 *  Created on: Jun 18, 2023
 *      Author: saziz
 */
#include"STD_TYPES.h"
#ifndef MPU_INTERFACE_H_
#define MPU_INTERFACE_H_


void MPU_VidInit();
void MPU_VidGetReadings(f32*Accx,f32*Accy,f32*Accz,f32*temp,f32*gyrox,f32*gyroy,f32*gyroz);
#endif /* MPU_INTERFACE_H_ */
