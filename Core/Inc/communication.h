#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H


/*___DEFINE___*/

#define START_REQUEST 0xFE
#define SIZE_START 8

#define SIZE_TYPEFRAME 8

#define SIZE_CHECKSUM 8

#define END_REQUEST 0x26 //=='&'
#define SIZE_END 8

#define SIZE_REQUEST((data)) SIZE_START + SIZE_TYPEFRAME + (data) + SIZE_CHECKSUM + SIZE_END

#define TIME_OUT 1000



/*___Struct and Enum___*/

enum TypeFrame
{
	IMAGE = 2**16;
	ACK = 1;
	RESPONSE_IMAGE = 24;
	DEBUG_POSITION = 16;
}

struct PositionCommand
{
	uint8_t x;
	uint8_t y;
}



/*___FUNCTION___*/

void initCommunication(TIM_HandleTypeDef* htim);

void sendRequest(char* request);

uint8_t receiveRequest();

//Build and send the request for send image to the esp32 put on huart2;
void sendImage(uint32_t image[1600*1200]);
//get the ID of the sended image, NULL if not receive response, and 255 if is not found ArUco on image
uint8_t getId();
//get the local position of the ArUCo (from the robot)
PositionCommand getPositionArUco()

// Build and send the request for send position and orientation of the robot to the esp32 put on huart2;
void sendDebugPosition(uint32_t x, uint32_t y, uint32_t theta);

//Send request for say "i have read your request"
void sendAck();

#endif 
