/*
 * LINE_FOLLOW_DFS.h
 *
 *  Created on: Jul 24, 2023
 *      Author: saziz
 */

#ifndef LINE_FOLLOW_DFS_H_
#define LINE_FOLLOW_DFS_H_

#define SENSOR_1_PIN 0,4
#define SENSOR_2_PIN 0,5

typedef enum{
  sforward,
  sright,
  sleft,
  sstop,
  lfobstacle,
  fobstacle,
  snone
}feedback;

#endif /* LINE_FOLLOW_DFS_H_ */
