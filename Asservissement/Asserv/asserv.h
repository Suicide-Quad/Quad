#ifndef ASSERV_H
#define ASSERV_H
#include <math.h>
float posX;
float posY;
float rotation;
//float move (float distance, int dir); //move robot to the distance(m) and return the distance left in m
//float rotate(float angle, int dir); //rotate robot in angle(rad) and return the angle left in rad
float move(float distance); //move robot to the distance(m) and return the distance left in m
float rotate(float angle, int dir); //rotate robot in angle(rad) and return the angle left in rad

#endif
