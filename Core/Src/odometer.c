#include "utils.h"
#include "encoder.h"
#include "odometer.h"
#include "communication.h"

uint32_t lastEncoderLeft = 0;
uint32_t lastEncoderRight = 0;

double computeSpeed(enum Encoder encoder, uint32_t encoderVal)
{
    uint32_t last;
    if (encoder == ENCODER_LEFT)
        last = lastEncoderLeft;
    else 
        last = lastEncoderRight;
    int32_t delta = (encoderVal + HIGH_VALUE/2 - last) % HIGH_VALUE - HIGH_VALUE/2;
    return ((double)delta/(double)HIGH_VALUE)*(2.0*M_PI*(double)FREQUENCY_ENCODER);
}

PolarSpeed computeOdometer()
{
    uint32_t encoderRight = getEncoder(ENCODER_RIGHT);
    uint32_t encoderLeft = getEncoder(ENCODER_LEFT);

    // Matrice
    MotorSpeed motorSpeed;
    motorSpeed.left = -computeSpeed(ENCODER_LEFT, encoderLeft);
    motorSpeed.right = computeSpeed(ENCODER_RIGHT, encoderRight);
    PolarSpeed polarSpeed = convertMotorSpeed(motorSpeed);
    //sendInt("linea", (int)(RAD_TO_DEG(motorSpeed.right)*100));
    //sendFloatDebug("line", polarSpeed.linear,100);
    lastEncoderLeft = encoderLeft;
    lastEncoderRight = encoderRight; 
    //sendFloatDebug("linea", (polarSpeed.linear),100);
    //sendFloatDebug("angul", RAD_TO_DEG(polarSpeed.angular),1);
    return polarSpeed;
}
