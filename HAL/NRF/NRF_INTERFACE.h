/*
 * NRF_INTERFACE.h
 *
 *  Created on: Jun 22, 2023
 *      Author: saziz
 */

#ifndef NRF_INTERFACE_H_
#define NRF_INTERFACE_H_
#include"STD_TYPES.h"
#include"BIT_MATH.h"


void NRF_VidInit(void);
u8 NRF_U8send_spi(u8 register_address, void *data, u32 bytes);
u8 NRF_U8Write(u8 register_address, void *data, u32 byte);
void NRF_VidState(u8 state);
u8 NRF_U8Read(u8 register_address, u8 *data, u32 bytes);
void NRF_VidStartListening(void);
u8 NRF_VidAvailable(void);
bool NRF_U8SendMessage(const void *tx_message,u8 length);
const char * NRF_VidReadMessage(void);
void NRF_VidPrintConfig(void);
#endif /* NRF_INTERFACE_H_ */
