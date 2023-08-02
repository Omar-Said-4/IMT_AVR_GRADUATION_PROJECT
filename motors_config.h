#ifndef MOTORS_CONFIG_H
#define	MOTORS_CONFIG_
/* Port used for Motors' Directional Pins */
#define MOTORS_PORT 0
/* 4 Directional Pins from Port A for the 2 Motors */
#define IN1 0
#define IN2 1
#define IN3 2
#define IN4 3

/* 2 Pins for Motors' PWM *
 * Pin 3 of Port B for Motor A (TIMER_0)
 * Pin 7 of Port D for Motor B (TIMER_2)
 */
#define ENA 3
#define ENB 7

#endif
