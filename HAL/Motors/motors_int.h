#ifndef MOTORS_INT_H
#define	MOTORS_INT_H
void MOTORS_VidInit(void);
void MOTORS_VidMoveForward (void);
void MOTORS_VidMoveBackward (void);
void MOTORS_VidMoveRight (void);
void MOTORS_VidMoveLeft (void);
void MOTORS_VidStop (void);
void MOTORS_SetSpeed (u8 Copy_u8MotorSpeed);
void RIGHT_MOTOR_SetSpeed (u8 Copy_u8MotorSpeed);
void LEFT_MOTOR_SetSpeed (u8 Copy_u8MotorSpeed);

#endif
