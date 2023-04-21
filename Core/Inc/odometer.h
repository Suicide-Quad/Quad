#ifndef _ODOMETER_H
#define _ODOMETER_H
#include "encoder.h"
#define WHEEL_DIAMETER 5.88
#define FREQUENCY_ENCODER 50
#define WHELL_GAPS 23.5

double computeSpeed(enum Encoder encoder, double encoderVal);

typedef struct PolarSpeedStruct
{
    double linear;
    double angular;
} PolarSpeed;

typedef struct MotorSpeedStruct
{
    double left;
    double right;
} MotorSpeed;

PolarSpeed computeOdometer();

#endif
