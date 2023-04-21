#include "utils.h"
#include "odometer.h"

MotorSpeed convertPolarSpeed(PolarSpeed speed)
{
    MotorSpeed motor;
    motor.left = speed.linear - (speed.angular * WHELL_GAPS / 2.0F);
    motor.right = speed.linear + (speed.angular * WHELL_GAPS / 2.0F);
    return motor;
}

PolarSpeed convertMotorSpeed(MotorSpeed speed)
{
    PolarSpeed polar;
    polar.linear = (speed.left - speed.right) / 2.0F;
    polar.angular = ((double)WHELL_GAPS / 2.0F) * (speed.right + speed.left) / (speed.right - speed.left);
    return polar;
}

