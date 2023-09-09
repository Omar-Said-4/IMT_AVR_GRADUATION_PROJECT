/*
 * LINE_FOLLOW.h
 *
 *  Created on: Jul 24, 2023
 *      Author: saziz
 */

#ifndef LINE_FOLLOW_H_
#define LINE_FOLLOW_H_


void LF_VidInit();
feedback LF_VidGetState();
feedback LF_BoolObstacle();
void LF_VidFindPath();
void LF_VidProcess(u8 mode);
void LF_VidProcess2();
#endif /* LINE_FOLLOW_H_ */
