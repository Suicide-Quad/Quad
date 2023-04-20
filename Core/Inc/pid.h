#ifndef PID
#define PID

struct pidController 
{
    double Kp;
    double Ki;
    double Kd;
    double errorLast;
    double errorTotal;
}

// Retourne la correction neccesaire
pidController* initPid(double Kp, double Ki, double Kd);

double pidCorrection(double measure, double order, pidController* controller);

#endif 
