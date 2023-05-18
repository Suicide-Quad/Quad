#include "communication.h"


/*___DEFINE___*/

#define FINISH 1
#define NOT_FINISH 0



/*___GLOBAL-VAR___*/

//ID of the ArUco
uint8_t IDArUco;

//Local Position of ArUco (from the robot)
struct PositionCommand PositionArUco;

UART_HandleTypeDef* ESP_TIM = NULL;

uint8_t Ack = 0;



/*___FUNCTION___*/


void initCommunication(UART_HandleTypeDef* htim)
{
	ESP_TIM = htim;
}



int getSizeTypeFrame (enum TypeFrame type)
{
	if (type == NONE)
		return 0;
	return SizeTypeFrame[type];
}

uint8_t computeCheckSum(int size, uint8_t data[size])
{
	uint8_t sum = 0;
	for (int i = 0; i < size ; i ++)
	{
		sum += data[i];
	}
	return sum % 256;
}



void receiveStartBlock(uint8_t* start, char buffer[], uint8_t* pointBuffer)
{
	while (!*start && *pointBuffer < BUFF_SIZE)
	{
		if (buffer[*pointBuffer] == START_REQUEST)
		{
			*start = 1;
		}
		(*pointBuffer) ++;
	}
}

void receiveType(uint8_t data[], enum TypeFrame type)
{
	if (type == RESPONSE_POSITION)
	{
		IDArUco = data[0];
		PositionArUco.x = data[1];
		PositionArUco.y = data[2];
	}
	else if (type == ACK)
	{
		Ack = 1;
	}
}

//catch data and compute things to do
uint8_t receiveData(enum TypeFrame type, uint8_t* pointBuffer, uint8_t* sizeReadBuffer, char buffer[])
{
	uint64_t sizeType = getSizeTypeFrame(type);
	static uint8_t data[BUFF_SIZE];
	static uint8_t goodSum = 0;
	static uint8_t startBuffer = 0;
	static uint8_t first = 1;
	if (first)
	{
		startBuffer = *pointBuffer;
		first = 0;
	}

	//received data of the request
	while(*sizeReadBuffer < sizeType/8 && *pointBuffer < BUFF_SIZE)
	{
		data[*pointBuffer-startBuffer] = buffer[*pointBuffer];
		(*sizeReadBuffer) += 8;
		(*pointBuffer) ++;
	}
	//verify checksum
	if (*sizeReadBuffer == sizeType/8 && *pointBuffer < BUFF_SIZE)
	{
		uint8_t checksumRequest = buffer[*pointBuffer];
		(*pointBuffer) ++;
		(*sizeReadBuffer) ++;
		uint8_t checksumCompute = computeCheckSum(sizeType/8, data);
		if(checksumCompute == checksumRequest)
			goodSum = 1;
		if (goodSum == 1)
		{
			receiveType(data, type);
		}
		goodSum = 0;
		first = 1;
		return FINISH;
	}
	return NOT_FINISH;
}

void receiveRequest()
{
	static uint8_t start = 0;
	static enum TypeFrame type = NONE;
	static uint8_t sizeReadData = 0; //in bytes calculted in the start of data

	char buffer[BUFF_SIZE];
	getFromDMA(buffer, BUFF_SIZE);

	uint8_t pointBuffer = 0;

	if (!start)
	{
		receiveStartBlock(&start, buffer, &pointBuffer);
	}
	if (start && type == NONE && pointBuffer < BUFF_SIZE)
	{
		type = buffer[pointBuffer];
		pointBuffer ++;
	}
	if (start && pointBuffer < BUFF_SIZE)
	{
		uint8_t finish = receiveData(type, &pointBuffer, &sizeReadData, buffer);
		if (finish)
		{
			start = 0;
			type = NONE;
			sizeReadData = 0;
		}
	}
}



void sendRequest(uint8_t* msg, enum TypeFrame type)
{
	HAL_UART_Transmit(ESP_TIM,msg, type/8, TIME_OUT);
}

void sendAskPosition()
{
	enum TypeFrame type = ASK_POSITION;
	int sizeRequest = SIZE_REQUEST(getSizeTypeFrame(type));
	uint8_t request [sizeRequest];

	request[0] = START_REQUEST;
	request[1] = type;

	sendRequest(request, sizeRequest);
}

void sendDebugPosition(uint8_t x, uint8_t y)
{
	enum TypeFrame type = DEBUG_POSITION;
	uint8_t sizeType = getSizeTypeFrame(type);
	int sizeRequest = SIZE_REQUEST(sizeType);
	uint8_t request [sizeRequest];

	request[0] = START_REQUEST;
	request[1] = type;
	request[2] = x;
	request[3] = y;

	uint8_t sum = computeCheckSum(sizeType/8, &request[2]);

	request[4] = sum;

	sendRequest(request, sizeRequest);
}

void sendAck()
{
	enum TypeFrame type = ACK;
	uint8_t sizeType = getSizeTypeFrame(type);
	int sizeRequest = SIZE_REQUEST(sizeType);
	uint8_t request [sizeRequest];


	request[0] = START_REQUEST;
	request[1] = type;
	request[2] = 1;

	uint8_t sum = computeCheckSum(sizeType/8, &request[2]);

	request[4] = sum;

	sendRequest(request, sizeRequest);
}

void sendDebugInt(uint32_t value)
{
	enum TypeFrame type = DEBUG_INT;
	uint8_t sizeType = getSizeTypeFrame(type);
	int sizeRequest = SIZE_REQUEST(sizeType);
	uint8_t request [sizeRequest];


	request[0] = START_REQUEST;
	request[1] = type;
	
	request[2] = value >> 24;
	request[3] = value >> 16;
	request[4] = value >> 8;
	request[5] = value;

	uint8_t sum = computeCheckSum(sizeType/8, &request[2]);

	request[4] = sum;

	sendRequest(request, sizeRequest);
}

void sendDebugFloat(float value)
{
	uint32_t valueInt = value;
	uint32_t valueFloat = value*100000 - valueInt*100000;
	enum TypeFrame type = DEBUG_FLOAT;
	uint8_t sizeType = getSizeTypeFrame(type);
	int sizeRequest = SIZE_REQUEST(sizeType);
	uint8_t request [sizeRequest];


	request[0] = START_REQUEST;
	request[1] = type;
	
	request[2] = valueInt >> 24;
	request[3] = valueInt >> 16;
	request[4] = valueInt >> 8;
	request[5] = valueInt;

	request[6] = valueFloat >> 24;
	request[7] = valueFloat >> 16;
	request[8] = valueFloat >> 8;
	request[9] = valueFloat;

	uint8_t sum = computeCheckSum(sizeType/8, &request[2]);

	request[10] = sum;

	sendRequest(request, sizeRequest);
}



uint8_t getId()
{
	return IDArUco;
}

struct PositionCommand getPositionArUco()
{
	return PositionArUco;
}
