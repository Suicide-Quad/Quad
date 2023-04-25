#include "communication.h"


/*___GLOBAL-VAR___*/

//ID of the ArUco
uint8_t IDArUco;

//Local Position of ArUco (from the robot)
struct PositionCommand PositionArUco;

UART_HandleTypeDef* ESP_TIM = NULL;



/*___FUNCTION___*/

void initCommunication(UART_HandleTypeDef* htim)
{
	ESP_TIM = htim;
}



uint8_t computeCheckSum(enum TypeFrame type, uint8_t data[type/8])
{
	uint8_t sum = 0;
	for (enum TypeFrame i = 0; i < type/8 ; i ++)
	{
		sum += data[i];
	}
	return sum % 256;
}



void receiveStartBlock()
{
	uint8_t startBlock[1];
	HAL_UART_Receive(ESP_TIM, startBlock, 1, TIME_OUT);
	while (startBlock[0] != START_REQUEST)
	{
		HAL_UART_Receive(ESP_TIM, startBlock, 1, TIME_OUT);
	}
}

enum TypeFrame receiveTypeBlock()
{
	uint8_t typeBlock[1];
	HAL_UART_Receive(ESP_TIM, typeBlock, 1, TIME_OUT);
	while(typeBlock[0] == START_REQUEST)
	{
		HAL_UART_Receive(ESP_TIM, typeBlock, 1, TIME_OUT);
	}
	enum TypeFrame type= typeBlock[0];
	return type;
}

//catch data and verify and return if request is_valide
unsigned char receiveData(enum TypeFrame type)
{
	unsigned char isValide = 0;
	if (type == ACK)
	{
		uint8_t data [ACK];
		HAL_UART_Receive(ESP_TIM, data, ACK, TIME_OUT);
		uint8_t checksumCompute = computeCheckSum(ACK, data);
		uint8_t checksumFind [1];
		HAL_UART_Receive(ESP_TIM, checksumFind, 1, TIME_OUT);
		if((data[0] == 1) && (checksumCompute == checksumFind[0]))
			isValide = 1;
	}
	else if (type == RESPONSE_IMAGE)
	{
		uint8_t data [RESPONSE_IMAGE/8];
		HAL_UART_Receive(ESP_TIM, data, RESPONSE_IMAGE/8, TIME_OUT);
		uint8_t checksumCompute = computeCheckSum(RESPONSE_IMAGE, data);
		uint8_t checksumFind [1];
		HAL_UART_Receive(ESP_TIM, checksumFind, 1, TIME_OUT);
		if (checksumCompute == checksumFind[0])
		{
			IDArUco = data[0];
			PositionArUco.x = data[1];
			PositionArUco.y = data[2];
			isValide = 1;
		}
	}
	return isValide;
}

void receiveRequest()
{
	unsigned char isValide = 0;

	while(!isValide)
	{
		receiveStartBlock();
		enum TypeFrame type = receiveTypeBlock();
		isValide = receiveData(type);
	}
}



void sendRequest(uint8_t* msg, enum TypeFrame type)
{
	HAL_UART_Transmit(ESP_TIM,msg, type/8, TIME_OUT);
}

void sendImage(uint32_t image[1600*1200])
{
	return;
}

void sendDebugPosition(uint8_t x, uint8_t y)
{
	enum TypeFrame type = DEBUG_POSITION;
	uint8_t request [SIZE_REQUEST(type)];

	request[0] = START_REQUEST;
	request[1] = type;
	request[2] = x;
	request[3] = y;

	uint8_t sum = computeCheckSum(type, &request[2]);

	request[4] = sum;
	request[5] = END_REQUEST;

	sendRequest(request, SIZE_REQUEST(type));
}

void sendAck()
{
	enum TypeFrame type = ACK;
	uint8_t request [SIZE_REQUEST(type)];

	request[0] = START_REQUEST;
	request[1] = type;
	request[2] = 1;

	uint8_t sum = computeCheckSum(type, &request[2]);

	request[4] = sum;
	request[5] = END_REQUEST;

	sendRequest(request, SIZE_REQUEST(type));
}

void sendDebugInt(uint32_t value)
{
	enum TypeFrame type = DEBUG_INT;
	uint8_t request [SIZE_REQUEST(type)];

	request[0] = START_REQUEST;
	request[1] = type;
	
	request[2] = value >> 24;
	request[3] = value >> 16;
	request[4] = value >> 8;
	request[5] = value;

	uint8_t sum = computeCheckSum(type, &request[2]);

	request[4] = sum;
	request[5] = END_REQUEST;

	sendRequest(request, SIZE_REQUEST(type));
}

void sendDebugFloat(float value)
{
	uint32_t valueInt = value;
	uint32_t valueFloat = value*100000 - valueInt*100000;
	enum TypeFrame type = DEBUG_FLOAT;
	uint8_t request [SIZE_REQUEST(type)];

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

	uint8_t sum = computeCheckSum(type, &request[2]);

	request[10] = sum;
	request[11] = END_REQUEST;

	sendRequest(request, SIZE_REQUEST(type));
}



uint8_t getId()
{
	return IDArUco;
}

struct PositionCommand getPositionArUco()
{
	return PositionArUco;
}
