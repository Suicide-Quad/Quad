#include "communication.h"


/*___GLOBAL-VAR___*/

//ID of the ArUco
uint8_t ID = NULL;

//Local Position of ArUco (from the robot)
PositionCommand PositionArUco = NULL;

TIM_HandleTypeDef* ESP_TIM;



/*___FUNCTION___*/

void initCommunication(TIM_HandleTypeDef* htim)
{
	ESP_TIM = htim;
}

void sendRequest(char* request, int size)
{
	HAL_UART_Transmit(ESP_TIME,request, size, TIME_OUT);
	receiveRequest();
}

uint8_t receiveRequest()
{
	enum TypeFrame typeFram = RESPONSE_IMAGE;
    uint8_t recept[typeFram];
    HAL_UART_Receive(huart2, recept, SIZE_REQUEST((typeFram)), TIME_OUT);

	//Parse Recept
}

char* sendImage(uint32_t image[1600*1200])
{

}

uint8_t getId();
{

}

PositionCommand getPositionArUco()
{

}

void sendDebugPosition(uint32_t x, uint32_t y, uint32_t theta)
{

}

void sendAck()
{

}

uint8_t receiveAck()
{

}
