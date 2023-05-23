#ifndef PID
#define PID

typedef struct pidControllerStruct
{
    double Kp;
    double Ki;
    double Kd;
    double errorLast;
    double errorTotal;

} pidController;

// Retourne la command neccesaire
pidController initPid(double Kp, double Ki, double Kd);

double computePid(double measure, double order, pidController* controller);

#endif 
