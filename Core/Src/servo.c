#include "servo.h"
#include <stdio.h>
#include <string.h>
#include "pwm.h"
#include "encoder.h"
#include "pid.h"
#include "odometer.h"
#include "utils.h"

/*
 * | V1 |    | X | 
 * |    | =  |   | X Matrice 
 * | V2 |    | O | 
 */


pidController servoLinear;
pidController servoAngular;

void initServo()
{
    // Kp, Ki, Kd
    servoLinear = initPid(0.0F, 0.0F, 0.0F);
    servoAngular = initPid(0.0F, 0.0F, 0.0F);
}

void servo(double measureLinear, double measureAngular, double orderLinear, double orderAngular)
{
    // TODO : double to struct 
    PolarSpeed polarSpeed;
    //TODO : Polar to command 
    polarSpeed.linear = computePid(measureLinear, orderLinear, &servoLinear);
    polarSpeed.angular = computePid(measureAngular, orderAngular, &servoAngular);   

    MotorSpeed motorSpeed = convertPolarSpeed(polarSpeed);

    setPWM(RIGHT, motorSpeed.right);
    setPWM(LEFT, motorSpeed.left);
}
    





