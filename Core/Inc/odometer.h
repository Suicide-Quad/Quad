#ifndef _ODOMETER_H
#define _ODOMETER_H
#include "encoder.h"
#define WHEEL_DIAMETER 0.0588
#define WHEEL_RADIUS ((WHEEL_DIAMETER)/2)
#define FREQUENCY_ENCODER 50
#define WHELL_GAPS 0.235

double computeSpeed(enum Encoder encoder, uint32_t encoderVal);

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
