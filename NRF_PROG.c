/*
 * NRF_PROG.c
 *
 *  Created on: Jun 22, 2023
 *      Author: saziz
 */

#include"NRF_PRIVATE.h"
#include"SPI_INTEFACE.h"
#include"DIO_INTERFACE.h"
#include <util/delay.h>
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"EXIT_INTERFACE.h"
static u8 rx_address[5] = { 0xe7, 0xe7, 0xe7, 0xe7, 0xe7 };	// Read pipe address
static u8 tx_address[5] = { 0xe7, 0xe7, 0xe7, 0xe7, 0xe7 };	// Write pipe address
u8 NRF_U8send_spi(u8 register_address, void *data, u32 bytes)
{
	u8 status;
	DIO_VidSetPinValue(CSN,0);
	status=SPI_U8Transaction(register_address);
	for(u32 i=0;i<bytes;i++)
	{
		((u8 *)data)[i]=SPI_U8Transaction(((u8 *)data)[i]);
	}
	DIO_VidSetPinValue(CSN,1);
	return status;

}
u8 NRF_U8Write(u8 register_address, void *data, u32 bytes)
{
	return NRF_U8send_spi(register_address,data,bytes);
}
void NRF_VidInit(void)
{

	EXIT_VidInit(INT0,Falling);

	/* Standby Mode */
	DIO_VidSetPinDirection(CE,1);
	DIO_VidSetPinDirection(CSN,1);
	DIO_VidSetPinValue(CE,0);
	DIO_VidSetPinValue(CSN,1);

	/* SPI Init */
	SPI_VidMasterInit();
	_delay_ms(100);

	u8 data =
			(!(RX_INTERRUPT) << MASK_RX_DR) |	/* IRQ interrupt on RX (0 = enabled) */
			(!(TX_INTERRUPT) << MASK_TX_DS) |	/* IRQ interrupt on TX (0 = enabled) */
			(!(RT_INTERRUPT) << MASK_MAX_RT) |	/* IRQ interrupt on auto retransmit counter overflow (0 = enabled) */
			(1 << EN_CRC) |						/* CRC enable */
			(1 << CRC0) |						/* CRC scheme 2 bytes */
			(1 << PWR_UP) |						/* Power up  */
			(1 << PRIM_RX);
	NRF_U8Write(CONFIG,&data,1);


	data =
			(AUTO_ACK << ENAA_P5) |
			(AUTO_ACK << ENAA_P4) |
			(AUTO_ACK << ENAA_P3) |
			(AUTO_ACK << ENAA_P2) |
			(AUTO_ACK << ENAA_P1) |
			(AUTO_ACK << ENAA_P0);
	NRF_U8Write(EN_AA,&data,1);


	data = 0xF0;				/* Delay 4000us with 1 re-try (will be added in settings) */
	NRF_U8Write(SETUP_RETR,&data,1);


	/* Disable RX addresses */
	data = 0;
	NRF_U8Write(EN_RXADDR, &data, 1);

	/* Set channel */
	data = CHANNEL;
	NRF_U8Write(RF_CH,&data,1);

	data =
			(CONTINUOUS << CONT_WAVE) |					/* Continuous carrier transmit */
			((DATARATE >> RF_DR_HIGH) << RF_DR_HIGH) |	/* Data rate */
			((POWER >> RF_PWR) << RF_PWR);				/* PA level */
	NRF_U8Write(RF_SETUP,&data,1);

	/* Status Clear */
	data =
			(1 << RX_DR) |
			(1 << TX_DS) |
			(1 << MAX_RT);
	NRF_U8Write(STATUS,&data,1);

	/* Dynamic payload on all pipes */
	data =
			(DYN_PAYLOAD << DPL_P0) |
			(DYN_PAYLOAD << DPL_P1) |
			(DYN_PAYLOAD << DPL_P2) |
			(DYN_PAYLOAD << DPL_P3) |
			(DYN_PAYLOAD << DPL_P4) |
			(DYN_PAYLOAD << DPL_P5);
	NRF_U8Write(DYNPD, &data,1);

	/* Enable dynamic payload */
	data =
			(DYN_PAYLOAD << EN_DPL) |
			(AUTO_ACK << EN_ACK_PAY) |
			(AUTO_ACK << EN_DYN_ACK);
	NRF_U8Write(FEATURE,&data,1);
	/* flush tx,rx */
	NRF_U8Write(FLUSH_RX,0,0);
	NRF_U8Write(FLUSH_TX,0,0);


	/* open pipes */
	NRF_U8Write(RX_ADDR_P0 + READ_PIPE,rx_address,5);
	NRF_U8Write(TX_ADDR,tx_address,5);

	/* Enable Pipe */
	data = (1 << READ_PIPE);
	NRF_U8Write(EN_RXADDR,&data,1);
}
u8 NRF_U8Read(u8 register_address, u8 *data, u32 bytes)
{
	return NRF_U8send_spi(R_REGISTER | register_address, data, bytes);

}
void NRF_VidState(u8 state)
{
	u8 config_register,data;
	NRF_U8Read(CONFIG,&config_register,1);
	switch (state)
	{
	case POWERUP:
		data = config_register | (1 << PWR_UP);
		NRF_U8Write(CONFIG,&data,1);
		_delay_ms(2);
		break;
	case POWERDOWN:
		data = config_register & ~(1 << PWR_UP);
		NRF_U8Write(CONFIG,&data,1);
		break;
	case RECEIVE:
		data = config_register | (1 << PRIM_RX);
		NRF_U8Write(CONFIG,&data,1);
		data = (1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT);
		NRF_U8Write(STATUS,&data,1);
		break;
	case TRANSMIT:
		data = config_register & ~(1 << PRIM_RX);
		NRF_U8Write(CONFIG,&data,1);
		break;
	case STANDBY1:
		DIO_VidSetPinValue(CE,0);
		break;
	case STANDBY2:
		data = config_register & ~(1 << PRIM_RX);
		NRF_U8Write(CONFIG,&data,1);
		DIO_VidSetPinDirection(CE,1);
		_delay_us(150);
		break;
	}

}
void NRF_VidStartListening(void)
{
	NRF_VidState(RECEIVE);				// Receive mode
	//if (AUTO_ACK) nrf24_write_ack();	// Write acknowledgment
	DIO_VidSetPinValue(CE,1);
	_delay_us(150);						// Settling time
}
bool NRF_VidAvailable(void)
{
	u8 config_register;
	NRF_U8Read(FIFO_STATUS,&config_register,1);
	if (!(config_register & (1 << RX_EMPTY))) return true;
	return false;
}
void NRF_VidWriteAck(void)
{
	const void *ack = "A";
	u8 length = 1;
	DIO_VidSetPinValue(CSN,0);
	SPI_U8Transaction(W_ACK_PAYLOAD);
	while (length--) SPI_U8Transaction(*(uint8_t *)ack++);
	DIO_VidSetPinValue(CSN,1);
}
bool NRF_U8SendMessage(const void *tx_message,u8 length)
{
	NRF_VidState(TRANSMIT);
	NRF_U8Write(FLUSH_RX,0,0);
	NRF_U8Write(FLUSH_TX,0,0);
	u8 data = (1 << TX_DS);
	NRF_U8Write(STATUS,&data,1);

	/* Disable interrupt on RX */
	NRF_U8Read(CONFIG,&data,1);
	data |= (1 << MASK_RX_DR);
	NRF_U8Write(CONFIG,&data,1);

	DIO_VidSetPinValue(CSN,0);
	if (AUTO_ACK) SPI_U8Transaction(W_TX_PAYLOAD);
	else SPI_U8Transaction(W_TX_PAYLOAD_NOACK);
	while (length--) SPI_U8Transaction(*(uint8_t *)tx_message++);
	SPI_U8Transaction(0);
	DIO_VidSetPinValue(CSN,1);

	DIO_VidSetPinValue(CE,1);
	_delay_us(15);
	DIO_VidSetPinValue(CE,0);

	NRF_U8Read(STATUS,&data,1);
	while(!(data & (1 << TX_DS))) NRF_U8Read(STATUS,&data,1);

	NRF_U8Read(CONFIG,&data,1);
	data &= ~(1 << MASK_RX_DR);
	NRF_U8Write(CONFIG,&data,1);

	NRF_VidStartListening();

	return true;
}
const char * NRF_VidReadMessage(void)
{
	static char rx_message[32];
	for(u8 i=0;i<32;i++)rx_message[i]=0;
	if (AUTO_ACK) NRF_VidWriteAck();

	u8 data;
	NRF_U8Read(R_RX_PL_WID,&data,1);
	if (data > 0) NRF_U8send_spi(R_RX_PAYLOAD,&rx_message,data+1);

	u8 strlen=0;
	for(u8 i=0;rx_message[i]!=0;i++)
		strlen++;
	if (strlen > 0)
	{
		// Clear RX interrupt
		data = (1 << RX_DR);
		NRF_U8Read(STATUS,&data,1);

		return rx_message;
	}
	data = (1 << RX_DR);
	NRF_U8Read(STATUS,&data,1);

	return "failed";

}
