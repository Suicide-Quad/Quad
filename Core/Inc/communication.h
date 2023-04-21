#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

#define START_REQUEST 0xFE
#define SIZE_START 8

#define SIZE_TYPEFRAME 8

#define SIZE_CHECKSUM 8

#define END_REQUEST 0x26 //=='&'
#define SIZE_END 8

#define SIZE_REQUEST((data)) SIZE_START + SIZE_TYPEFRAME + (data) + SIZE_CHECKSUM + SIZE_END

enum TypeFrame
{
	IMAGE = 2**16;
	ACK = 1;
	RESPONSE_IMAGE = 24;
	DEBUG_POSITION = 16;
}

void initCommunication(TIM_HandleTypeDef* htim);

void sendRequest(char request);

uint8_t receiveRequest();

//Build and send the request for send image to the esp32 put on huart2;
void sendImage(uint32_t image[1600*1200]);
//Read the request of image and put in the pointeur of the image and return true if it's a image request
uint8_t getId();

// TODO : Struct PositionCommand 
// PositionCommand getCommand();

// Build and send the request for send position and orientation of the robot to the esp32 put on huart2;
void sendDebugPosition(uint32_t x, uint32_t y, uint32_t theta);

//Send request for say "i have read your request"
void sendAck();
//Read the request who say "i have read the request" and return true if it's a ack request
uint8_t receiveAck();
#endif 
