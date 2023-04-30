#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H



/*___INCLUDE___*/

#include "main.h"
#include "dma.h"


/*___DEFINE___*/

#define START_REQUEST 0xFE
#define SIZE_START 8

#define SIZE_TYPEFRAME 8

#define SIZE_CHECKSUM 8

#define SIZE_REQUEST(data) (SIZE_START + SIZE_TYPEFRAME + (data) + SIZE_CHECKSUM )/8

#define TIME_OUT 1000



/*___Struct and Enum___*/

int SizeTypeFrame [6] = {65536,8,24,16,32,64};
enum TypeFrame
{
	NONE = -1,
	IMAGE = 0,
	ACK = 1,
	RESPONSE_IMAGE = 2,
	DEBUG_POSITION = 3,
	DEBUG_INT = 4,
	DEBUG_FLOAT = 5,
};

typedef struct PositionCommand
{
	uint8_t x;
	uint8_t y;
}positionCommand;



/*___FUNCTION___*/

//init communication
void initCommunication(UART_HandleTypeDef* htim);


//receive request and manage all
void receiveRequest();


//send the request request of the type type
void sendRequest(uint8_t* request, enum TypeFrame type);

//Build and send the request for send image to the esp32 put on huart2;
void sendImage(uint32_t image[1600*1200]);

//Send request for say "i have read your request"
void sendAck();

// Build and send the request for send position and orientation of the robot to the esp32 put on huart2;
void sendDebugPosition(uint8_t x, uint8_t y);

//Build and send the request for debug float
void sendDebugFloat(float value);

//Build and send the request for debug int
void sendDebugInt(uint32_t value);


//get the ID of the sended image, 255 if not receive response, and 254 if is not found ArUco on image
uint8_t getId();
//get the local position of the ArUCo (from the robot)
struct PositionCommand getPositionArUco();

#endif 
