#include "PID.h"
#include <math.h> 
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

/*_____Macro_____*/

//macro for calcul PID:
#define KP 0.7
#define KI 0.01
#define KD 0.25

//macro for call easly computePID
#define SET 1
#define RESET 0
#define PID_LEFT 1
#define PID_RIGHT 0

//macro at measured on robot
#define WHEEL_DIAG 0.12  //in m
#define ENTRAXE 0.45 //in m

//macro for phase of movement
#define ACCELERATE 1
#define STABLE 2
#define DECELERATE 3


/*_____Global Variable_____*/
//Timer for make regular PID
float TIM_REG = 0.01;  //in s


//last val encodeur for have same value in  rotation and move
static int lastTurnsLeft = 0;
static int lastTurnsRight = 0;

//Motor Statistic
float MOTOR_LIMIT_MAX = 100;  //in % of voltage
float MOTOR_LIMIT_MIN = 0;   //in % of voltage

//Distancelimit for start freinage
float DISTANCE_START_FREINAGE = 0.5;  //in m
//Anglelimit for start freinage
float ANGLE_START_FREINAGE = M_PI/12;   //in rad

//Speed for move and do copy
float VITESSE_LIMIT = 1;  //in m/s
float VITESSE_INIT = 1;
float VITESSE_NOW = 0.01;  //in m/s 

//Speed for rotate and do copy
float VITESSE_ROTATE_LIMIT = 1;  //in m/s
float VITESSE_ROTATE_INIT = 1;
float VITESSE_ROTATE_NOW = 0;   //in m/s

//The value to add at vitesse_distance_now at each time_reg
float VITESSE_DELTA = 0.01;
//The value to add at vitesse_angle_now at each time_reg
float VITESSE_ROTATE_DELTA = 0.01;

//Vitesse minimum for forward
float VITESSE_MIN = 0.03;
float VITESSE_ROTATE_MIN = 0.05;
//Coeff for decrease speed more quick than accelerate
float COEFF_DECELERATE = 1.05;
float COEFF_ROTATE_DECELERATE = 1.05;

int DIR_LEFT = 1;
int DIR_RIGHT = (-1);


float posX;
float posY;
float rotation;
/*_____Function_____*/

uint32_t crossProduct(float pourcentage)
{
	uint32_t maxprescaler = 65535;
	uint32_t ret = pourcentage*maxprescaler/100;
	return ret;
}

void setDuty(TIM_HandleTypeDef* tim,float pourcent)
{
	uint32_t newv = crossProduct(pourcent);
	tim->Init.Prescaler = newv;
}


float computePID(float error,float input, int direction, int reset)
{
	static float lastInput [2] = {0,0};
	static float sumError [2]= {0,0};

	if (!reset) //for reset PID
	{
		lastInput[direction] = 0;
		sumError[direction] = 0;
		return 0;
	}

	sumError[direction] += KI*error;

	float P = KP*error;
	float I = sumError[direction];
	float D = KD*(input-lastInput[direction]);

	lastInput[direction] = input;

	float output = P+I-D;


	//if the limit is rush, the pid make not good calcul
	if (output > MOTOR_LIMIT_MAX)
	{
		output = MOTOR_LIMIT_MAX;
		sumError[direction] -= KI*error;
	}
	else if (output < MOTOR_LIMIT_MIN)
	{
		output = MOTOR_LIMIT_MIN;
		sumError[direction] -= KI*error;
	}

	return output;
}

float move(float distance, TIM_HandleTypeDef* htim1, TIM_HandleTypeDef* htim8, TIM_HandleTypeDef* htim2, TIM_HandleTypeDef* htim5) //move robot to the distance(m) and return the distance left in m
{
	//distance initial and lastTime
	static float distanceInit = 0;
	static int first = 0;
	static uint32_t lastTime = 0;
	if (!first)
	{
		lastTime = HAL_GetTick();
		distanceInit = distance;
		first = 1;
	}

	//timer for regular pid in sec
	uint32_t timeSinceStart = HAL_GetTick();
	uint32_t timeNow = timeSinceStart - lastTime;


	//phase of movement: accelerate, stable, decelerate
	static int phase = ACCELERATE;

	//distance do during acceleration 
	static float firstDistance = 0;

	//Commande to put at motors in m/s
	static float RightCommande = 0;
	static float LeftCommande = 0;

	if (timeNow - lastTime >= TIM_REG || timeNow == 0)  //for regular interval
	{
		//manage encodeur
		int valEncodeurLeft = (TIM2->CNT)>>2;
		int valEncodeurRight = (TIM5->CNT)>>2;

		int nbTurnsLeft = 0;
		int nbTurnsRight = 0;

		if (valEncodeurLeft<0 && lastTurnsLeft > 0)
		{
			nbTurnsLeft = (INT_MAX-lastTurnsLeft)+(valEncodeurLeft-INT_MIN);
		}
		else
		{
			nbTurnsLeft = valEncodeurLeft-lastTurnsLeft;
		}
		if (valEncodeurRight<0 && lastTurnsRight > 0)
		{
			nbTurnsRight = (INT_MAX-lastTurnsRight)+(valEncodeurRight-INT_MIN);
		}
		else
		{
			nbTurnsRight = valEncodeurRight-lastTurnsRight;
		}
		lastTurnsLeft = valEncodeurLeft;
		lastTurnsRight = valEncodeurRight;

		//calcul error 
		float distanceLeft = M_PI*WHEEL_DIAG*nbTurnsLeft; //getDistance(nbTurnsLeft);
		float distanceRight = M_PI*WHEEL_DIAG*nbTurnsRight; //getDistance(nbTurnsRight);
		float speedLeft = distanceLeft/TIM_REG;
		float speedRight = distanceRight/TIM_REG;
		float errorRight = VITESSE_NOW-speedRight;
		float errorLeft = VITESSE_NOW-speedLeft;

		//comput both pid
		RightCommande += computePID(errorRight,speedRight, PID_RIGHT, SET);
		LeftCommande += computePID(errorLeft,speedLeft, PID_LEFT, SET);

		//give commande to both motor
		setDuty(htim1,LeftCommande);
		setDuty(htim8,RightCommande);

		//change distance at do
		distance -= (distanceLeft+distanceRight)/2;
		//calculated coord
		if (rotation == 0)
			posY+=(distanceLeft+distanceRight)/2;
		else if (rotation == M_PI || rotation == -M_PI)
			posY-=(distanceLeft+distanceRight)/2;
		else if (rotation == M_PI/2)
			posX+=(distanceLeft+distanceRight)/2;
		else if (rotation == - M_PI/2)
			posX-=(distanceLeft+distanceRight)/2;
		else
		{
			posY+=cosf(rotation)*((distanceLeft+distanceRight)/2);
			posX+=sinf(rotation)*((distanceLeft+distanceRight)/2);
		}
		//manage all phase of movement
		if (distance <= 0) //completly stop and restore PID
		{
			//commande motor for stop them
			setDuty(htim1,0);
			setDuty(htim8,0);

			//reset val
			computePID(0, 0, PID_LEFT, RESET);
			computePID(0, 0, PID_RIGHT, RESET);
			VITESSE_LIMIT = VITESSE_INIT;
			lastTime = 0;
			RightCommande = 0;
			LeftCommande = 0;
			distanceInit = 0;
			firstDistance = 0;
			first = 0;
		}
		else if (phase == ACCELERATE)
		{
			if (distance <= distanceInit/2)  //not need stable phase
			{
				phase = DECELERATE;
				VITESSE_NOW -= VITESSE_DELTA;
			}
			else if (VITESSE_NOW >= VITESSE_LIMIT) //need stable phase
			{
				phase = STABLE;
				firstDistance = distance;
			}
			else             // accelerate
			{
				VITESSE_NOW += VITESSE_DELTA;
			}
		}
		else if (phase == STABLE)
		{
			if (distance <= distanceInit - firstDistance)  //need to decelerate now
			{
				phase = DECELERATE;
				VITESSE_NOW -= VITESSE_DELTA;
			}
		}
		else if (phase == DECELERATE)  
		{
			VITESSE_NOW = (VITESSE_NOW-COEFF_DECELERATE*VITESSE_DELTA <= VITESSE_MIN? VITESSE_MIN : VITESSE_NOW-COEFF_DECELERATE*VITESSE_DELTA);  //for not stop motor if target not rush
		}

		lastTime = timeNow;
	}

	return distance;
}





float rotate(float angle, TIM_HandleTypeDef* htim1, TIM_HandleTypeDef* htim8, TIM_HandleTypeDef* htim2, TIM_HandleTypeDef* htim5) //rotate robot in angle(rad) and return the angle left in rad
{
	//distance initial
	int dir = (angle < 0 ? DIR_RIGHT : DIR_LEFT);
	angle = abs(angle);
	static float angleInit = 0;
	static uint32_t lastTime = 0;
    static int first = 0;
	if (!first)
	{
		lastTime = HAL_GetTick();
		angleInit = angle;
		first = 1;
	}

	//timer for regular pid in sec
	uint32_t timeSinceStart = HAL_GetTick();
	uint32_t timeNow = timeSinceStart - lastTime;

	//phase of movement: accelerate, stable, decelerate
	static int phase = ACCELERATE;

	//distance do during acceleration 
	static float firstAngle = 0;

	//Commande to put at motors in m/s
	static float RightCommande = 0;
	static float LeftCommande = 0;

	if (timeNow - lastTime >= TIM_REG || timeNow == 0)  //for regular interval
	{
		//manage encodeur
		int valEncodeurLeft = (TIM2->CNT)>>2;
		int valEncodeurRight = (TIM5->CNT)>>2;

		int nbTurnsLeft = 0;
		int nbTurnsRight = 0;

		if (valEncodeurLeft<0 && lastTurnsLeft > 0)
		{
			nbTurnsLeft = abs((INT_MAX-lastTurnsLeft)+(valEncodeurLeft-INT_MIN));
		}
		else
		{
			nbTurnsLeft = abs(valEncodeurLeft-lastTurnsLeft);
		}
		if (valEncodeurRight<0 && lastTurnsRight > 0)
		{
			nbTurnsRight = abs((INT_MAX-lastTurnsRight)+(valEncodeurRight-INT_MIN));
		}
		else
		{
			nbTurnsRight = abs(valEncodeurRight-lastTurnsRight);
		}
		lastTurnsLeft = valEncodeurLeft;
		lastTurnsRight = valEncodeurRight;

		//calcul error
		float distanceLeft = M_PI*WHEEL_DIAG*nbTurnsLeft;
		float distanceRight = M_PI*WHEEL_DIAG*nbTurnsRight;
		float speedLeft = distanceLeft/TIM_REG;
		float speedRight = distanceRight/TIM_REG;
		float errorRight = VITESSE_ROTATE_NOW-speedRight;
		float errorLeft = VITESSE_ROTATE_NOW-speedLeft;

		//comput both pid
		RightCommande += computePID(errorRight,speedRight, PID_RIGHT, SET);
		LeftCommande += computePID(errorLeft,speedLeft, PID_LEFT, SET);

		//change angle at do and calculate relatif rotation
		if (dir == DIR_LEFT)
		{
			//give commande to both motor
			setDuty(htim1,-LeftCommande);
			setDuty(htim8,RightCommande);
			angle -= 2*distanceRight/ENTRAXE;
			rotation -= (2*distanceRight/ENTRAXE);
		}
		else
		{
			//give commande to both motor
			setDuty(htim1,LeftCommande);
			setDuty(htim8,-RightCommande);
			angle -= 2*distanceLeft/ENTRAXE;
			rotation += (2*distanceLeft/ENTRAXE);
		}
		//manage all phase of movement
		if (angle <= 0) //completly stop and restore PID
		{
			//commande motor for stop them
			setDuty(htim1,0);
			setDuty(htim8,0);

			//reset val
			computePID(0, 0, PID_LEFT, RESET);
			computePID(0, 0, PID_RIGHT, RESET);
			VITESSE_ROTATE_LIMIT = VITESSE_ROTATE_INIT;
			lastTime = 0;
			RightCommande = 0;
			LeftCommande = 0;
			angleInit = 0;
			firstAngle = 0;
			first = 0;
		}
		else if (phase == ACCELERATE)
		{
			if (angle <= angleInit/2)  //not need stable phase
			{
				phase = DECELERATE;
				VITESSE_ROTATE_NOW -= VITESSE_ROTATE_DELTA;
			}
			else if (VITESSE_ROTATE_NOW >= VITESSE_ROTATE_LIMIT) //need stable phase
			{
				phase = STABLE;
				firstAngle = angle;
			}
			else             // accelerate
			{
				VITESSE_ROTATE_NOW += VITESSE_ROTATE_DELTA;
			}
		}
		else if (phase == STABLE)
		{
			if (angle <= angleInit - firstAngle)  //need to decelerate now
			{
				phase = DECELERATE;
				VITESSE_ROTATE_NOW -= VITESSE_ROTATE_DELTA;
			}
		}
		else if (phase == DECELERATE)  
		{
			VITESSE_ROTATE_NOW = (VITESSE_ROTATE_NOW-COEFF_ROTATE_DECELERATE*VITESSE_ROTATE_DELTA <= VITESSE_ROTATE_MIN? VITESSE_ROTATE_MIN : VITESSE_ROTATE_NOW-COEFF_ROTATE_DECELERATE*VITESSE_ROTATE_DELTA);  //for not stop motor if target not rush
		}
		lastTime = timeNow;
	}

	return dir*angle;
}

