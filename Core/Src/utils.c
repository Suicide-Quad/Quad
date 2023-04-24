#include "utils.h"
#include "odometer.h"

uint8_t checksum(char* msg)
{
	uint8_t sum = 0;
	for (int i = 0; *(msg+i) != 0; i ++)
	{
		sum += *(msg+i);
	}
	return sum % 256;
}

MotorSpeed convertPolarSpeed(PolarSpeed speed)
{
    MotorSpeed motor;
    motor.left = speed.linear/WHEEL_RADIUS - speed.angular * (WHELL_GAPS/2*(1/WHEEL_RADIUS));
    motor.right = speed.linear/WHEEL_RADIUS + speed.angular * (WHELL_GAPS/2*(1/WHEEL_RADIUS));
    return motor;
}

PolarSpeed convertMotorSpeed(MotorSpeed speed)
{
    PolarSpeed polar;
    polar.linear = (WHEEL_RADIUS*(speed.left + speed.right) / 2.0F);
    // FIX : MAYBE NOT RADIUS
    polar.angular = (speed.right - speed.left)* (WHEEL_RADIUS/WHELL_GAPS);
    return polar;
}

