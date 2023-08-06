/*
 * DFS.h
 *
 *  Created on: Jul 7, 2023
 *      Author: saziz
 */
#define LED1 0,4
#define LED2 0,5
#define LED3 0,6
#define LED4 0,7

#ifndef DFS_H_
#define DFS_H_
typedef enum{
	Button1,
	Button2,
	Button3,
	Button4,
	None,
}Buttons;
typedef enum{
	front,
	back,
	right,
	left,
	stop
}Movs;
#endif /* DFS_H_ */
