#ifndef _UTILS_H
#define _UTILS_H
#include "odometer.h"
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) < (b) ? (b) : (a))
#define CLAMP(a,c,b) MIN(MAX((a),(c)), (b))


MotorSpeed convertPolarSpeed(PolarSpeed speed);
PolarSpeed convertMotorSpeed(MotorSpeed speed);
#endif 
