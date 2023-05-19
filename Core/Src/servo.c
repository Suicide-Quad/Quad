#include "servo.h"
#include <stdio.h>
#include <string.h>
#include "pwm.h"
#include "encoder.h"
#include "pid.h"
#include "utils.h"

/*
 * | V1 |    | X | 
 * |    | =  |   | X Matrice 
 * | V2 |    | O | 
 */

pidController servoLeft;
pidController servoRight;

void initServo()
{
    // Kp, Ki, Kd
    servoLeft = initPid(0.0F, 0.0F, 0.0F);
    servoRight = initPid(1.0F, 0.0F, 0.0F);
}

void servo(PolarSpeed measurePolar, PolarSpeed orderPolar)
{
    MotorSpeed measureMotor = convertPolarSpeed(measurePolar);
    MotorSpeed orderMotor = convertPolarSpeed(orderPolar);

    double left = computePid(measureMotor.left, orderMotor.left, &servoLeft);
    double right = computePid(measureMotor.right, orderMotor.right , &servoRight);

    setPWM(RIGHT, right);
    setPWM(LEFT, left);
}
    




