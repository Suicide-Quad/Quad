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
uint8_t computeCheckSum(enum TypeFrame size, uint8_t data[size])
{
	uint8_t sum = 0;
	for (enum TypeFrame i = 0; i < size ; i ++)
	{
		sum += data[size];
	}
	return sum % 256;
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
		uint8_t checksumCompute = computeCheckSum(RESPONSE_IMAGE/8, data);
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

void sendImage(uint32_t image[1600*1200])
{
	return ;
}

uint8_t getId()
{
	return IDArUco;
}

struct PositionCommand getPositionArUco()
{
	return PositionArUco;
}

void sendDebugPosition(uint32_t x, uint32_t y, uint32_t theta)
{
	return;
}

void sendAck()
{
	return;
}
