#include "utils.h"
#include "odometer.h"

uint8_t equalThreeshold(Location first, Location second, double threeshold)
{
    if (first.x - threeshold < second.x && first.y + threeshold > second.y)
        return 1;
    return 0;
}

double computeLinearDistance(Location my, Location dst)
{
    double x = dst.x - my.x;
    double y = dst.y - my.y;
    return sqrt(x*x + y*y);
}

double computeAngularDistance(Location my, Location dst)
{
    double x = dst.x - my.x;
    double y = dst.y - my.y;
    return asin((x*x + y*y) / y);
}

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

