#include "utils.h"
#include "encoder.h"
#include "odometer.h"

double lastEncoderLeft = 0.0F;
double lastEncoderRight = 0.0F;

double computeSpeed(enum Encoder encoder, double encoderVal)
{
    if (encoder == ENCODER_LEFT)
        return (encoderVal - lastEncoderLeft) * ((double)FREQUENCY_ENCODER);
    else 
        return (encoderVal - lastEncoderRight) * ((double)FREQUENCY_ENCODER);
}

PolarSpeed computeOdometer()
{
    double encoderRight = getEncoderRad(ENCODER_RIGHT);
    double encoderLeft = getEncoderRad(ENCODER_LEFT);

    // Matrice
    MotorSpeed motorSpeed;
    motorSpeed.left = computeSpeed(ENCODER_LEFT, encoderLeft);
    motorSpeed.right = computeSpeed(ENCODER_RIGHT, encoderRight);
    PolarSpeed polarSpeed = convertMotorSpeed(motorSpeed);
    lastEncoderLeft = encoderLeft;
    lastEncoderRight = encoderRight; 
    return polarSpeed;
}
