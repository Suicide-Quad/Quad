#ifndef _UTILS_H
#define _UTILS_H
#include "odometer.h"
#include "position.h"
#include <math.h>
#define ABS(a) ((a) < 0 ? -(a) : (a))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MINABS(a,b) (ABS(a) < ABS(b) ? (a) : (b))
#define MAXABS(a,b) (ABS(a) < ABS(b) ? (b) : (a))
#define MAX(a,b) ((a) < (b) ? (b) : (a))
#define CLAMP(a,c,b) MIN(MAX((a),(c)), (b))
#define DEG_TO_RAD(x) ((x)*M_PI / 180.0F)
#define RAD_TO_DEG(x) ((x)*180.0F / M_PI)
#define MOD_BY_ANG(x,y) (((x) - (y) % 2*PI) + (y))
#define SIGN_FLOAT(x) ((x) < 0.0 ? (-1) : 1)
#define SIGN(x) ((x) < 0 ? (-1) : 1)
uint8_t equal_threeshold(Location first, Location second, double threeshold);
uint8_t checksum(char* msg);
double computeLinearDistance(Location my, Location dst);
double computeAngularDistance(Location my, Location dst);
MotorSpeed convertPolarSpeed(PolarSpeed speed);
PolarSpeed convertMotorSpeed(MotorSpeed speed);
#endif 
