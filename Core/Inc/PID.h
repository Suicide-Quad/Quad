#ifndef ASSERV_H
#define ASSERV_H
#include <math.h>

enum Direction
{
    FORWARD = 0,
    BACKWARD = 2,
    LEFT = 1,
    RIGHT = 3
};

float move(float distance, int dir); //move robot to the distance(m) and return the distance left in m, dir is BACKWARD or FORWARD 

float rotate(float angle, int dir); //rotate robot in angle(rad) and return the angle left in rad, dir is LEFT or RIGHT

#endif
