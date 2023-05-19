#include "pid.h"
#include "debug.h"
#include "math.h"


pidController initPid(double Kp, double Ki, double Kd)
{
    pidController controller;
    controller.Kp = Kp;
    controller.Ki = Ki;
    controller.Kd = Kd;
    controller.errorTotal = 0.0F;
    controller.errorLast = 0.0F;
    return controller;
}

double computePid(double measure, double order, pidController* controller)
{
    double error = order - measure;
    controller->errorTotal += error;
    double derivative = error - controller->errorLast;
    double command = (controller->Kp * error) + (controller->Ki * controller->errorTotal) + (controller->Kd * derivative);
    controller->errorLast = error;
    return command;
}
