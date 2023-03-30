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

float move(float distance, int dir); //move robot to the distance(m) and return the distance left in m, dir is BACKWARD or FORWARD 

float rotate(float angle, int dir); //rotate robot in angle(rad) and return the angle left in rad, dir is LEFT or RIGHT

#endif
