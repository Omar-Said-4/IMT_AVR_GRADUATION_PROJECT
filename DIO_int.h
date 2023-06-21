/***************************************************************************/
/**************SWC      : DIO Driver****************************************/
/**************BY       : Mahmoud Essam*************************************/
/**************Date     : 27Aug22*******************************************/
/**************Version  : 1.0***********************************************/
/***************************************************************************/

#ifndef DIO_INT_H
#define DIO_INT_H

typedef enum {
	
	Port_A,
	Port_B,
	Port_C,
	Port_D
	
	
	
} et_Port;

typedef enum {
	Pin_0,
	Pin_1,
	Pin_2,
	Pin_3,
	Pin_4,
	Pin_5,
	Pin_6,
	Pin_7
	
	
}et_Pin;

typedef enum{
	
	Input,
	Output
	
}et_Direction;

typedef enum {
	
	PinLow,
	PinHigh
}et_Status;

/* Setting Pin Direction */

void DIO_VidSetPinDirection (u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction);

/* Setting Pin Value */

void DIO_VidSetPinValue (u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value);

/* Getting Pin Value */

void DIO_VidGetPinValue (u8 Copy_u8Port, u8 Copy_u8Pin, u8 *pu8Data);

/* Setting Port Direction */                          // matensash t-copy el fo2 hena zay el pin lel port 
/* Setting Port(port register) Value */               // han-copy lel port bas fel arguments nesheel el pin
/* Getting Port(pin register) Value */

/* Setting Pin Direction */
/* Setting Pin Value */
/* Getting Pin Value */

void DIO_VidSetPortDirection(u8 Copy_u8Port, u8 Copy_u8DirectionValue);
void DIO_VidSetPortValue(u8 Copy_u8Port, u8 Copy_u8PortValue);
void DIO_VidGetPortValue(u8 Copy_u8Port, u8 *pu8Data);





#endif
