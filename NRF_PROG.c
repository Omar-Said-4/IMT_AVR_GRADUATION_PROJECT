/*
 * NRF_PROG.c
 *
 *  Created on: Jun 22, 2023
 *      Author: saziz
 */

#include"NRF_PRIVATE.h"
#include"SPI_INTEFACE.h"
#include"DIO_INTERFACE.h"
#include"NRF_INTERFACE.h"
#include"UART_INTERFACE.h"
#include <util/delay.h>
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"EXIT_INTERFACE.h"
static u8 rx_address[5] = { 0xe7, 0xe7, 0xe7, 0xe7, 0xe7 };	/* Read pipe address */
static u8 tx_address[5] = { 0xe7, 0xe7, 0xe7, 0xe7, 0xe7 };	/* Write pipe address */
u8 NRF_U8send_spi(u8 register_address, void *data, u32 bytes)
{
	u8 status;
	DIO_VidSetPinValue(CSN,0);
	status = SPI_U8Transaction(register_address);
	for (unsigned int i = 0; i < bytes; i++)
		((u8*)data)[i] = SPI_U8Transaction(((u8*)data)[i]);
	DIO_VidSetPinValue(CSN,1);
	return status;

}
u8 NRF_U8Write(u8 register_address, void *data, u32 bytes)
{
	return NRF_U8send_spi(W_REGISTER | register_address, data, bytes);

}
void NRF_VidInit(void)
{

	/* Standby Mode */
	DIO_VidSetPinDirection(CE,1);
	DIO_VidSetPinDirection(CSN,1);
	DIO_VidSetPinValue(CE,0);
	DIO_VidSetPinValue(CSN,1);

	/* SPI Init */
	SPI_VidMasterInit();
	_delay_ms(100);
	u8 check;
	u8 data =
			(!(RX_INTERRUPT) << MASK_RX_DR) |	/* IRQ interrupt on RX (0 = enabled) */
			(!(TX_INTERRUPT) << MASK_TX_DS) |	/* IRQ interrupt on TX (0 = enabled) */
			(!(RT_INTERRUPT) << MASK_MAX_RT) |	/* IRQ interrupt on auto retransmit counter overflow (0 = enabled) */
			(1 << EN_CRC) |						/* CRC enable */
			(1 << CRC0) |						/* CRC scheme 2 bytes */
			(1 << PWR_UP) |						/* Power up  */
			(1 << PRIM_RX);
	UART_VidPrintString("CONFIG1: ");
	UART_VidParseInt(data);
	UART_VidPrintString("\n\r");
	NRF_U8Write(CONFIG,&data,1);
	NRF_U8Read(CONFIG,&check,1);
	UART_VidPrintString("CONFIG: ");
	UART_VidParseInt(check);
	UART_VidPrintString("\n\r");
	data =
			(AUTO_ACK << ENAA_P5) |
			(AUTO_ACK << ENAA_P4) |
			(AUTO_ACK << ENAA_P3) |
			(AUTO_ACK << ENAA_P2) |
			(AUTO_ACK << ENAA_P1) |
			(AUTO_ACK << ENAA_P0);
	UART_VidPrintString("EN_AA1: ");
	UART_VidParseInt(data);
	UART_VidPrintString("\n\r");
	NRF_U8Write(EN_AA,&data,1);
	NRF_U8Read(EN_AA,&check,1);
	UART_VidPrintString("EN_AA: ");
	UART_VidParseInt(check);
	UART_VidPrintString("\n\r");


	data = 0xF0;		/* Delay 4000us with 1 retry */
	UART_VidPrintString("SETUP_RETR1: ");
	UART_VidParseInt(data);
	UART_VidPrintString("\n\r");
	NRF_U8Write(SETUP_RETR,&data,1);
	NRF_U8Read(SETUP_RETR,&check,1);
	UART_VidPrintString("SETUP_RETR: ");
	UART_VidParseInt(check);
	UART_VidPrintString("\n\r");


	/* Disable RX addresses */
	data = 0;
	UART_VidPrintString("EN_RXADDR1: ");
	UART_VidParseInt(data);
	UART_VidPrintString("\n\r");
	NRF_U8Write(EN_RXADDR,&data,1);
	NRF_U8Read(EN_RXADDR,&check,1);
	UART_VidPrintString("EN_RXADDR: ");
	UART_VidParseInt(check);
	UART_VidPrintString("\n\r");


	/* Set channel */
	data = CHANNEL;
	UART_VidPrintString("RF_CH1: ");
	UART_VidParseInt(data);
	UART_VidPrintString("\n\r");
	NRF_U8Write(RF_CH,&data,1);
	NRF_U8Read(RF_CH,&check,1);
	UART_VidPrintString("RF_CH: ");
	UART_VidParseInt(check);
	UART_VidPrintString("\n\r");

	data =
			(CONTINUOUS << CONT_WAVE) |					/* Continuous carrier transmit */
			((DATARATE >> RF_DR_HIGH) << RF_DR_HIGH) |	/* Data rate */
			((POWER >> RF_PWR) << RF_PWR);				/* PA level */

	UART_VidPrintString("RF_SETUP1: ");
	UART_VidParseInt(data);
	UART_VidPrintString("\n\r");
	NRF_U8Write(RF_SETUP,&data,1);
	NRF_U8Read(RF_SETUP,&check,1);
	UART_VidPrintString("RF_SETUP: ");
	UART_VidParseInt(check);
	UART_VidPrintString("\n\r");


	/* Status Clear */
	data =
			(1 << RX_DR) |
			(1 << TX_DS) |
			(1 << MAX_RT);

	UART_VidPrintString("STATUS1: ");
	UART_VidParseInt(data);
	UART_VidPrintString("\n\r");
	NRF_U8Write(STATUS,&data,1);
	NRF_U8Read(STATUS,&check,1);
	UART_VidPrintString("STATUS: ");
	UART_VidParseInt(check);
	UART_VidPrintString("\n\r");


	/* Dynamic payload on all pipes */
	data =
			(DYN_PAYLOAD << DPL_P0) |
			(DYN_PAYLOAD << DPL_P1) |
			(DYN_PAYLOAD << DPL_P2) |
			(DYN_PAYLOAD << DPL_P3) |
			(DYN_PAYLOAD << DPL_P4) |
			(DYN_PAYLOAD << DPL_P5);

	UART_VidPrintString("DYNPD1: ");
	UART_VidParseInt(data);
	UART_VidPrintString("\n\r");
	NRF_U8Write(DYNPD,&data,1);
	NRF_U8Read(DYNPD,&check,1);
	UART_VidPrintString("DYNPD: ");
	UART_VidParseInt(check);
	UART_VidPrintString("\n\r");



    NRF_U8send_spi(ACTIVATE,0,0);
    NRF_U8send_spi(POSTACTIVATE,0,0);
	/* Enable dynamic payload */
	data =
			(DYN_PAYLOAD << EN_DPL) |
			(AUTO_ACK << EN_ACK_PAY) |
			(!AUTO_ACK << EN_DYN_ACK);

	UART_VidPrintString("FEATURE1: ");
	UART_VidParseInt(data);
	UART_VidPrintString("\n\r");
	NRF_U8Write(FEATURE,&data,1);
	NRF_U8Read(FEATURE,&check,1);
	UART_VidPrintString("FEATURE: ");
	UART_VidParseInt(check);
	UART_VidPrintString("\n\r");

	/* flush tx,rx */
	NRF_U8Write(FLUSH_RX,0,0);
	NRF_U8Write(FLUSH_TX,0,0);


	/* open pipes */
	NRF_U8Write(RX_ADDR_P0 + READ_PIPE,rx_address,5);
	NRF_U8Write(TX_ADDR,tx_address,5);
	NRF_U8Write(EN_RXADDR,&data,1);
	/* Enable Pipe */
	data = (1 << READ_PIPE);

	UART_VidPrintString("EN_RXADDR1: ");
	UART_VidParseInt(data);
	UART_VidPrintString("\n\r");
	NRF_U8Write(EN_RXADDR,&data,1);
	NRF_U8Read(EN_RXADDR,&check,1);
	UART_VidPrintString("EN_RXADDR: ");
	UART_VidParseInt(check);
	UART_VidPrintString("\n\r");
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
	NRF_VidState(RECEIVE);				/* Receive mode */
	DIO_VidSetPinValue(CE,1);
	_delay_us(150);
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
    UART_VidPrintString(rx_message);
    UART_VidPrintString("\n\r");
	u8 strlen=0;
	for(u8 i=0;rx_message[i]!=0;i++)
		strlen++;
	if (strlen > 0)
	{
		// Clear RX interrupt
		data = (1 << RX_DR);
		NRF_U8Write(STATUS,&data,1);

		if(data==4){

			return rx_message;
		}
	}
	data = (1 << RX_DR);
	NRF_U8Read(STATUS,&data,1);

	return "failed";

}
void NRF_VidPrintConfig(void)
{
	uint8_t data;
	UART_VidPrintString("Startup successful\n\r");
	printf("-------------------------------------------\n\r");
	NRF_U8Read(CONFIG,&data,1);
	UART_VidPrintString("CONFIG: ");
	UART_VidParseInt(data);
	NRF_U8Read(EN_AA,&data,1);
	UART_VidPrintString("-------------------------------------------\n\r");
	UART_VidPrintString("EN_AA: ");
	UART_VidParseInt(data);
	UART_VidPrintString("-------------------------------------------\n\r");
	NRF_U8Read(EN_RXADDR,&data,1);
	UART_VidPrintString("EN_RXADDR: ");
	UART_VidParseInt(data);
	UART_VidPrintString("-------------------------------------------\n\r");
	NRF_U8Read(SETUP_RETR,&data,1);
	UART_VidPrintString("SETUP_RETR: ");
	UART_VidParseInt(data);
	UART_VidPrintString("-------------------------------------------\n\r");
	NRF_U8Read(RF_CH,&data,1);
	UART_VidPrintString("RF_CH: ");
	UART_VidParseInt(data);
	UART_VidPrintString("-------------------------------------------\n\r");
	NRF_U8Read(RF_SETUP,&data,1);
	UART_VidPrintString("RF_SETUP: ");
	UART_VidParseInt(data);
	UART_VidPrintString("-------------------------------------------\n\r");
	NRF_U8Read(STATUS,&data,1);
	UART_VidPrintString("STATUS: ");
	UART_VidParseInt(data);
	UART_VidPrintString("-------------------------------------------\n\r");
	NRF_U8Read(FEATURE,&data,1);
	UART_VidPrintString("FEATURE: ");
	UART_VidParseInt(data);

	UART_VidPrintString("-------------------------------------------\n\r");
}

