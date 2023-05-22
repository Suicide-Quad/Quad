#include "communication.h"
#include "math.h" 

/*___GLOBAL-VAR___*/

//ID of the ArUco
uint8_t IDArUco;

//Local Position of ArUco (from the robot)
struct PositionCommand PositionArUco;

UART_HandleTypeDef* htimESP = NULL;
UART_HandleTypeDef* htimUSB = NULL;

int SizeTypeFrame[7] = {0,1,3,17,5,9,1};



/*___FUNCTION___*/

void initCommunication(UART_HandleTypeDef* htim, UART_HandleTypeDef* htim2)
{
	htimESP = htim;
    htimUSB = htim2;
	IDArUco = 255;
}


int getSizeTypeFrame (enum TypeFrame type)
{
	if (type == NONE)
		return 0;
	return SizeTypeFrame[type];
}

// TODO : Merge with utils 
uint8_t computeCheckSum(int size, uint8_t data[size])
{
	uint8_t sum = 0;
	for (int i = 0; i < size ; i ++)
	{
		sum += data[i];
	}
	return sum % 255 ; 
}


void receiveStartBlock(uint8_t* start, char buffer[], uint8_t* pointBuffer)
{
	while (!*start && *pointBuffer < BUFF_SIZE)
	{
        // sendDebugInt(buffer[*pointBuffer],'s');
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
		IDArUco = data[2];
		PositionArUco.x = data[0];
		PositionArUco.y = data[1];
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
	while(*sizeReadBuffer < sizeType && *pointBuffer < BUFF_SIZE)
	{
		data[*pointBuffer-startBuffer] = buffer[*pointBuffer];
		(*sizeReadBuffer) += 1;
		(*pointBuffer) ++;
	}
	//verify checksum
	if (*sizeReadBuffer == sizeType && *pointBuffer < BUFF_SIZE)
	{
		uint8_t checksumRequest = buffer[*pointBuffer];
		(*pointBuffer) ++;
		(*sizeReadBuffer) ++;
		uint8_t checksumCompute = computeCheckSum(sizeType, data);
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
    // Lire la dma 
    // Enregistrer l'etat 
    // fin de trame fait l'action
}


void sendRequest(uint8_t* msg, uint8_t size)
{
    
    if (htimESP != NULL)
	    HAL_UART_Transmit_IT(htimESP, msg, size); 
    if (htimUSB != NULL)
	    HAL_UART_Transmit_IT(htimUSB, msg, size);
}

void computeRequestGeneric(enum TypeFrame type, uint8_t* request)
{
	uint8_t sizeType = getSizeTypeFrame(type);
	uint8_t sizeRequest = SIZE_REQUEST(sizeType);

	request[0] = START_REQUEST;

	request[1] = type;

	uint8_t sum = computeCheckSum(sizeType, &request[2]);
	request[sizeRequest-1] = sum;
	
	sendRequest(request, sizeRequest);
}

void sendAskPosition()
{
	enum TypeFrame type = ASK_POSITION;
	uint8_t request [SIZE_REQUEST(getSizeTypeFrame(type))];

	request[2] = 10;

	computeRequestGeneric(type,request);
}

void sendDebugPosition(double x,double y, char id)
{
	enum TypeFrame type = DEBUG_POSITION;
	uint8_t request [SIZE_REQUEST(getSizeTypeFrame(type))];

	int vxp = trunc(x);
	int vxn = trunc(x*FLOAT_PRECISION)-vxp*FLOAT_PRECISION;
	memcpy(&request[2],&vxp,4);
	memcpy(&request[6],&vxn,4);

	int vyp = trunc(y);
	int vyn = trunc(y*FLOAT_PRECISION)-vyp*FLOAT_PRECISION;
	memcpy(&request[10],&vyp,4);
	memcpy(&request[14],&vyn,4);

	request[18] = id;

	computeRequestGeneric(type,request);
}

void sendDebugInt(uint32_t value, char id)
{

	enum TypeFrame type = DEBUG_INT;
	uint8_t request [SIZE_REQUEST(getSizeTypeFrame(type))];

	memcpy(&request[2],&value,4);

	request[6] = id;

	computeRequestGeneric(type,request);
}

void sendDebugFloat(float value, char id)
{
	enum TypeFrame type = DEBUG_POSITION;
	uint8_t request [SIZE_REQUEST(getSizeTypeFrame(type))];

	int vp = trunc(value);
	int vn = trunc(value*FLOAT_PRECISION)-value*FLOAT_PRECISION;
	memcpy(&request[2],&vp,4);
	memcpy(&request[6],&vn,4);

	request[10] = id;

	computeRequestGeneric(type,request);
}


uint8_t getId()
{
	return IDArUco;
}

struct PositionCommand getPositionArUco()
{
	return PositionArUco;
}
