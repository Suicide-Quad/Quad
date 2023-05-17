#include "position.h"
#include "utils.h"

Location myPosition;
Location destinationPosition;
Location ghostPosition;
TrajectoryState state = Idle;

void initMouvement(Location current, Location destination)
{
    destinationPosition = destination;
    myPosition = current;
    state = Idle;
}

void computeGhostAngularMouvement()
{
}

void computeGhostLinearMouvement()
{
}

void computeGhostMouvement()
{
    if (state == Idle)
        return;
    if (!equal_threeshold(myPosition, destinationPosition, LIN_THREESHOLD) && state == Linear)
    {
        computeGhostLinearMouvement();
    } 
    else if (!equal_threeshold(myPosition, destinationPosition, ANG_THREESHOLD) && state == Angular)
    {
        computeGhostAngularMouvement();
    }
}
