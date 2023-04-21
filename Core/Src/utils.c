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

