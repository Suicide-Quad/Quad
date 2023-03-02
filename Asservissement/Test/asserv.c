
#include "asserv.h"


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
#define getDistance(rotary) PI*WHEEL_DIAG*rotary

//macro for phase of movement
#define ACCELERATE 1
#define STABLE 2
#define DECELERATE 3





/*_____Global Variable_____*/

//const Math
const float PI = 3.14;

//Timer for make regular PID
float TIME_REG = 0.01;

//Motor Statistic
float MOTOR_LIMIT_MAX = 1000;  //in m/s
float MOTOR_LIMIT_MIN = -1000;   //in m/s

//Distancelimit for start freinage
float DISTANCE_START_FREINAGE = 0.5;  //in m
//Anglelimit for start freinage
float ANGLE_START_FREINAGE = PI/12;   //in rad

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

//Value  for choose direction to move
int FORWARD = 1;
int BACKWARD = (-1);

//Value for choose direction to rotate
int LEFT = (-1);
int RIGHT = 1;

//Global position and rotation
float posX = 0;
float posY = 0;
float rotation = 0;

/*_____Function_____*/

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





float move(float distance, int dir, /* args for testing ->*/ float timeNow, float nbTurnsLeft, float nbTurnsRight, float retour [2][6]) //move robot to the distance(m) and return the distance left in m, dir indicate the direction to move
{

	dir +=0; //at del
	

	//timer for regular pid in sec
	//int timeNow = 0; commente put for testing
	static float lastTime = 0;
	
	//for reset EncodeurVal
	//static float lastValEncodeurLeft = 0;
	//static float lastValEncodeurRight = 0;

	//distance initial
	static float distanceInit = 0;
	static int first = 0;
	if (!first)
	{
		distanceInit = distance;
		first = 1;
	}

	//phase of movement: accelerate, stable, decelerate
	static int phase = ACCELERATE;

	//distance do during acceleration 
	static float firstDistance = 0;

	//Commande to put at motors in m/s
	static float RightCommande = 0;
	static float LeftCommande = 0;

	if (timeNow - lastTime >= TIME_REG || timeNow == 0)  //for regular interval
	{
		//calcul number of turns since last tick and check if valEncodeur have overrun
		/*size_t valEncodeurLeft = abs(0);   //get encodeur left
		if (lastValEncodeurLeft > valEncodeurLeft)
		{
			size_t max = sizeof(int);
			size_t nbTurnsLeft = max-lastValEncodeurLeft+valEncodeurLeft;
		}
		else
		{
			size_t nbTurnsLeft = valEncodeurLeft - lastValEncodeurLeft;
		}
		lastValEncodeurLeft = valEncodeurLeft;
		size_t valEncodeurRight = abs(0);  //get encodeur right
		if (lastValEncodeurRight > valEncodeurRight)
		{
			size_t max = sizeof(int);
			size_t nbTurnsRight = max-lastValEncodeurRight+valEncodeurRight;
		}
		else
		{
			size_t nbTurnsRight = valEncodeurRight - lastValEncodeurRight;
		}
		lastValEncodeurRight = valEncodeurRight;*/

		//calcul error 
		float distanceLeft = PI*WHEEL_DIAG*nbTurnsLeft; //getDistance(nbTurnsLeft);
		float distanceRight = PI*WHEEL_DIAG*nbTurnsRight; //getDistance(nbTurnsRight);
		float speedLeft = distanceLeft/TIME_REG;
		float speedRight = distanceRight/TIME_REG;
		float errorRight = VITESSE_NOW-speedRight;
		float errorLeft = VITESSE_NOW-speedLeft;

		//comput both pid9/*+*
		RightCommande += computePID(errorRight,speedRight, PID_RIGHT, SET);
		LeftCommande += computePID(errorLeft,speedLeft, PID_LEFT, SET);

		//give commande to both motor
		//not forget to do Commande*dir for motor

        

		//change distance at do
		distance -= (distanceLeft+distanceRight)/2;
		//calculated coord
		if (rotation == 0)
			posX+=dir*(distanceLeft+distanceRight)/2;
		else if (rotation == PI || rotation == -PI)
			posX-=dir*(distanceLeft+distanceRight)/2;
		else if (rotation == PI/2)
			posY+=dir*(distanceLeft+distanceRight)/2;
		else if (rotation == - PI/2)
			posY-=dir*(distanceLeft+distanceRight)/2;
		else
		{
			posX+=dir*cosf(rotation)*((distanceLeft+distanceRight)/2);
			posY+=dir*sinf(rotation)*((distanceLeft+distanceRight)/2);
		}
		//manage all phase of movement
		if (distance <= 0) //completly stop and restore PID
		{
			//commande motor for stop them


			//reset val
			computePID(0, 0, PID_LEFT, RESET);
			computePID(0, 0, PID_RIGHT, RESET);
			VITESSE_LIMIT = VITESSE_INIT;
			lastTime = 0;
			RightCommande = 0;
			LeftCommande = 0;
			//lastValEncodeurRight = 0;
			//lastValEncodeurLeft = 0;
			distanceInit = 0;
			firstDistance = 0;
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

		//retour is for testing
		retour[0][0] = nbTurnsLeft;
		retour[0][1] = distanceLeft;
		retour[0][2] = speedLeft;
		retour[0][3] = errorLeft;
		retour[0][4] = LeftCommande;
		retour[0][5] = distance;
		retour[1][0] = nbTurnsRight;
		retour[1][1] = distanceRight;
		retour[1][2] = speedRight;
		retour[1][3] = errorRight;
		retour[1][4] = RightCommande;
		retour[1][5] = VITESSE_NOW;
	}

	return distance;
}





float rotate(float angle, int dir,/* args for testing ->*/ float timeNow, float nbTurnsLeft, float nbTurnsRight, float retour [2][6]) //rotate robot in angle(rad) and return the angle left in rad
{
	dir +=0; //at del
	

	//timer for regular pid in sec
	//int timeNow = 0; commente put for testing
	static float lastTime = 0;
	
	//for reset EncodeurVal
	//static float lastValEncodeurLeft = 0;
	//static float lastValEncodeurRight = 0;

	//distance initial
	static float angleInit = 0;
	static int first = 0;
	if (!first)
	{
		angleInit = angle;
		first = 1;
	}

	//phase of movement: accelerate, stable, decelerate
	static int phase = ACCELERATE;

	//distance do during acceleration 
	static float firstAngle = 0;

	//Commande to put at motors in m/s
	static float RightCommande = 0;
	static float LeftCommande = 0;

	if (timeNow - lastTime >= TIME_REG || timeNow == 0)  //for regular interval
	{
		//calcul number of turns since last tick and check if valEncodeur have overrun
		/*size_t valEncodeurLeft = abs(0);   //get encodeur left
		if (lastValEncodeurLeft > valEncodeurLeft)
		{
			size_t max = sizeof(int);
			size_t nbTurnsLeft = max-lastValEncodeurLeft+valEncodeurLeft;
		}
		else
		{
			size_t nbTurnsLeft = valEncodeurLeft - lastValEncodeurLeft;
		}
		lastValEncodeurLeft = valEncodeurLeft;
		size_t valEncodeurRight = abs(0);  //get encodeur right
		if (lastValEncodeurRight > valEncodeurRight)
		{
			size_t max = sizeof(int);
			size_t nbTurnsRight = max-lastValEncodeurRight+valEncodeurRight;
		}
		else
		{
			size_t nbTurnsRight = valEncodeurRight - lastValEncodeurRight;
		}
		lastValEncodeurRight = valEncodeurRight;*/

		//calcul error 
		float distanceLeft = PI*WHEEL_DIAG*nbTurnsLeft; //getDistance(nbTurnsLeft);
		float distanceRight = PI*WHEEL_DIAG*nbTurnsRight; //getDistance(nbTurnsRight);
		float speedLeft = distanceLeft/TIME_REG;
		float speedRight = distanceRight/TIME_REG;
		float errorRight = VITESSE_ROTATE_NOW-speedRight;
		float errorLeft = VITESSE_ROTATE_NOW-speedLeft;

		//comput both pid9/*+*
		RightCommande += computePID(errorRight,speedRight, PID_RIGHT, SET);
		LeftCommande += computePID(errorLeft,speedLeft, PID_LEFT, SET);

		//give commande to both motor
		//not forget to do Commande*dir for motorleft and Commande*-dir for motorright



		//change angle at do and calculate relatif rotation
		if (dir == LEFT)
		{
			angle -= 2*distanceRight/ENTRAXE;
			rotation -= (2*distanceRight/ENTRAXE);
		}
		else
		{
			angle -= 2*distanceLeft/ENTRAXE;
			rotation += (2*distanceLeft/ENTRAXE);
		}
		//manage all phase of movement
		if (angle <= 0) //completly stop and restore PID
		{
			//commande motor for stop them


			//reset val
			computePID(0, 0, PID_LEFT, RESET);
			computePID(0, 0, PID_RIGHT, RESET);
			VITESSE_ROTATE_LIMIT = VITESSE_ROTATE_INIT;
			lastTime = 0;
			RightCommande = 0;
			LeftCommande = 0;
			//lastValEncodeurRight = 0;
			//lastValEncodeurLeft = 0;
			angleInit = 0;
			firstAngle = 0;
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

		//retour is for testing
		retour[0][0] = nbTurnsLeft;
		retour[0][1] = distanceLeft;
		retour[0][2] = speedLeft;
		retour[0][3] = errorLeft;
		retour[0][4] = LeftCommande;
		retour[0][5] = angle;
		retour[1][0] = nbTurnsRight;
		retour[1][1] = distanceRight;
		retour[1][2] = speedRight;
		retour[1][3] = errorRight;
		retour[1][4] = RightCommande;
		retour[1][5] = VITESSE_ROTATE_NOW;
	}


	return angle;
}
