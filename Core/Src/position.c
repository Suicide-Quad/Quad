#include "position.h"
#include "utils.h"
#include "odometer.h"
#include "servo.h"

Location myPosition;
Location destinationPosition;
TrajectoryState state = Idle;
double currentTime = 0;
double distanceLin = 0;
double distanceTheta = 0;
double ghostLin = 0;
double ghostAng = 0;
double T_a;
double T_c;

void initMouvement(Location current, Location destination)
{
    destinationPosition = destination;
    myPosition = current;
    state = Idle;
}

void computeGhostAngularMouvement()
{
    if (T_a > currentTime)
    {
        // Acceleration
        ghostAng += LIN_ACCELERATION_MAX;
    }
    else if (T_c > currentTime)
    {
        // Constant
        ghostAng = LIN_VITESSE_MAX;
    }
    else if (T_c + T_a > currentTime)
    {
        // Freinage
        ghostAng -= LIN_DECELERATION_MAX; 
    }
    else 
    {
        state = Idle;
        return ;
    }
    ghostAng = SIGN_FLOAT(ghostAng) * MIN(LIN_VITESSE_MAX, ghostAng);
    PolarSpeed order = {0, ghostAng};
    servo(computeOdometer(), order);
}

void computeGhostLinearMouvement()
{
    if (T_a > currentTime)
    {
        // Acceleration
        ghostLin += LIN_ACCELERATION_MAX;
    }
    else if (T_c > currentTime)
    {
        // Constant
        ghostLin = LIN_VITESSE_MAX;
    }
    else if (T_c + T_a > currentTime)
    {
        // Freinage
        ghostLin -= LIN_DECELERATION_MAX; 
    }
    else 
    {
        state = Angular;
    }
    ghostLin = MIN(LIN_VITESSE_MAX, ghostLin);
    PolarSpeed order = {ghostLin, 0};
    servo(computeOdometer(), order);
}


void applyGhostMouvement()
{
    switch(state)
    {
        case Linear:
            computeGhostLinearMouvement();
            break;
        case Angular:
            computeGhostAngularMouvement();
            break;
        default:
            break;
    }
}

void computeGhostMouvement()
{
    currentTime = HAL_GetTick();
    distanceLin = computeLinearDistance(myPosition, destinationPosition);
    distanceTheta = computeAngularDistance(myPosition, destinationPosition);
    T_a = LIN_VITESSE_MAX / LIN_ACCELERATION_MAX;
    T_c = distanceLin / LIN_VITESSE_MAX;
}
