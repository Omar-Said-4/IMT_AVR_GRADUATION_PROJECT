#ifndef MOTORS_CONFIG_H
#define	MOTORS_CONFIG_H

/* Port used for Motors' Directional Pins */
#define MOTORS_PORT Port_A
/* 4 Directional Pins from Port A for the 2 Motors */
#define IN1 Pin_0
#define IN2 Pin_1
#define IN3 Pin_2
#define IN4 Pin_4

/* 2 Pins for Motors' PWM *
 * Pin 3 of Port B for Motor A (TIMER_0)
 * Pin 7 of Port D for Motor B (TIMER_2)
 */
#define ENA Pin_3
#define ENB Pin_7

#endif
