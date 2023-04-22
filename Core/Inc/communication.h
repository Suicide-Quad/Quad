#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H



/*___INCLUDE___*/

#include "main.h"



/*___DEFINE___*/

#define START_REQUEST 0xFE
#define SIZE_START 8

#define SIZE_TYPEFRAME 8

#define SIZE_CHECKSUM 8

#define END_REQUEST 0x26 //=='&'
#define SIZE_END 8

#define SIZE_REQUEST(data) SIZE_START + SIZE_TYPEFRAME + (data) + SIZE_CHECKSUM + SIZE_END

#define TIME_OUT 1000



/*___Struct and Enum___*/

enum TypeFrame
{
	IMAGE = 65536,
	ACK = 1,
	RESPONSE_IMAGE = 24,
	DEBUG_POSITION = 16,
};

typedef struct PositionCommand
{
	uint8_t x;
	uint8_t y;
}positionCommand;



/*___FUNCTION___*/

void initCommunication(UART_HandleTypeDef* htim);

void sendRequest(char* request);

void receiveRequest();

//Build and send the request for send image to the esp32 put on huart2;
void sendImage(uint32_t image[1600*1200]);
//get the ID of the sended image, 255 if not receive response, and 254 if is not found ArUco on image
uint8_t getId();
//get the local position of the ArUCo (from the robot)
struct PositionCommand getPositionArUco();

// Build and send the request for send position and orientation of the robot to the esp32 put on huart2;
void sendDebugPosition(uint32_t x, uint32_t y, uint32_t theta);

//Send request for say "i have read your request"
void sendAck();

#endif 
