#ifndef ASSERV_H
#define ASSERV_H
#include <math.h>

int FORWARD;
int BACKWARD;
int LEFT;
int RIGHT;
float posX;
float posY;
float rotation;

/*for call need to do:
  float distance = x ; //(in m and >0)
  while(1)
  		distance = move(distance, DIR); //(DIR == BACKWARD or FORWARD)
*/
float move (float distance, int dir); //move robot to the distance(m) and return the distance left in m, dir is BACKWARD or FORWARD 

/*for call need to do:
  float angle = y ; //(in rad and >0)
  while(1)
  		angle = rotate(angle, DIR); //(DIR == LEFT or RIGHT)
*/
float rotate(float angle, int dir); //rotate robot in angle(rad) and return the angle left in rad, dir is LEFT or RIGHT

#endif
