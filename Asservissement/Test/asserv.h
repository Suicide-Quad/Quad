#ifndef ASSERV_H
#define ASSERV_H

float TIME_REG;
float VITESSE_LIMIT;
int FORWARD;
int BACKWARD;
int LEFT;
int RIGHT;
//float move (float distance, int dir); //move robot to the distance(m) and return the distance left in m
//float rotate(float angle, int dir); //rotate robot in angle(rad) and return the angle left in rad
float move(float distance, int dir, /* args for testing ->*/ float timeNow, float valEncodeurLeft, float valEncodeurRight, float retour [2][6]); //move robot to the distance(m) and return the distance left in m
float rotate(float angle, int dir,/* args for testing ->*/ float timeNow, float nbTurnsLeft, float nbTurnsRight, float retour [2][6]); //rotate robot in angle(rad) and return the angle left in rad

#endif
