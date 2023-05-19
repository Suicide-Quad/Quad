#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

/*___INCLUDE___*/

#include "main.h"
#include "dma.h"
#include <math.h>
#include <string.h>


/*___DEFINE___*/

#define START_REQUEST 0xFE

#define SIZE_START 8

#define SIZE_TYPEFRAME 8

#define SIZE_CHECKSUM 8

#define SIZE_REQUEST(data) ((SIZE_START) + (SIZE_TYPEFRAME) + (data) + (SIZE_CHECKSUM) )/8

#define TIME_OUT 100

#define FINISH 1

#define NOT_FINISH 0

#define FLOAT_PRECISION 1000000


/*___Struct and Enum___*/

enum TypeFrame
{
	NONE = -1,
	ASK_POSITION = 6,
	ACK = 1,
	RESPONSE_POSITION = 2,
	DEBUG_POSITION = 3,
	DEBUG_INT = 4,
	DEBUG_FLOAT = 5,
};

typedef struct PositionCommand
{
	uint8_t x;
	uint8_t y;
}positionCommand;


/*___USEFUL_FUNCTION___*/

//init communication
void initCommunication(UART_HandleTypeDef* htim);

//receive request and manage all
void receiveRequest();

//Build and send the request for send image to the esp32 put on huart2;
void sendAskPosition();

// Build and send the request for send position and orientation of the robot
void sendDebugPosition(uint8_t x, uint8_t y, char id);

//Build and send the request for debug int
void sendDebugInt(uint32_t value, char id);

//Build and send the request for debug float
void sendDebugFloat(float value, char id);

//get the ID of the sended image, 255 if not receive response, and 254 if is not found ArUco on image
uint8_t getId();

//get the local position of the ArUCo (from the robot)
struct PositionCommand getPositionArUco();


/*___BACKEND_FUNCTION___*/

void initCommunication(UART_HandleTypeDef* htim);

int getSizeTypeFrame (enum TypeFrame type);

uint8_t computeCheckSum(int size, uint8_t data[size]);

void receiveStartBlock(uint8_t* start, char buffer[], uint8_t* pointBuffer);

void receiveType(uint8_t data[], enum TypeFrame type);

uint8_t receiveData(enum TypeFrame type, uint8_t* pointBuffer, uint8_t* sizeReadBuffer, char buffer[]);

void sendRequest(uint8_t* msg, enum TypeFrame type);

void computeRequestGeneric(enum TypeFrame type, uint8_t* request);

#endif
