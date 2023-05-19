#ifndef _POSITION_H
#define _POSITION_H

// --- Linear ---
#define LIN_ACCELERATION_MAX 1.0 
#define LIN_DECELERATION_MAX (LIN_ACCELERATION_MAX) 
#define LIN_VITESSE_MAX 1.0 
#define LIN_THREESHOLD 1.0
// --- Angular ---
#define ANG_ACCELERATION_MAX 1.0 
#define ANG_DECELERATION_MAX (ANG_ACCELERATION_MAX)
#define ANG_VITESSE_MAX 1.0 
#define ANG_THREESHOLD 1.0

#define SAMPLING_FREQUENCY 50.0
#define SAMPLING_PERIOD (1.0/SAMPLING_FREQUENCY)


typedef struct LocationStruct
{
    double x;
    double y;
    double theta;
} Location;


typedef enum TrajectoryStateEnum
{
    Idle,
    Angular,
    Linear,
} TrajectoryState;

void initMouvement(Location current, Location command);

void computeGhostLinearMouvement();
void computeGhostAngularMouvement();
void applyGhostMouvement();
void computeGhostMouvement();
#endif

