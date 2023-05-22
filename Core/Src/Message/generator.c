#include "Message/generator.h"
#include "main.h"

void getBytesFromInt(uint8_t payload, uint8_t index, int val)
{
	char* valCut = (char*) val;
	for(int i = 0; i < sizeof(int); i++)
	{
		*(payload+i+index) = *(valCut+i);
	}
}

void sendDebugInt(int val, char id);
{
	uint8_t payload [5];

	getBytesFromInt(playload, 0, val);
	payload[4] = id;

	//call encode
}

void sendDebugDouble(double val, char id)
{
	uint8_t payload [9];

	int vp = trunc(val);
	int vn = trunc(val*FLOAT_PRECISION)-vp*FLOAT_PRECISON;

	getBytesFromInt(payload,0,vp);
	getBytesFromInt(payload,4,vn);

	payload[8] = id;

	//call encode
}

void sendDebugPosition(double x, double y, char id)
{
	uint8_t payload [17];

	int vxp = trunc(x);
	int vxn = trunc(x*FLOAT_PRECISION)-vxp*FLOAT_PRECISON;

	getBytesFromInt(payload,0,vxp);
	getBytesFromInt(payload,4,vxn);

	int vyp = trunc(y);
	int vyn = trunc(y*FLOAT_PRECISION)-vyp*FLOAT_PRECISON;

	getBytesFromInt(payload,8,vyp);
	getBytesFromInt(payload,12,vyn);

	payload[16] = id;

	//call encode
}

void sendAskPosition()
{
	uint8_t payload [1];

	payload[0] = 0;

	//call encode
}

void sendResponsePosition(PositionCommande commande, uint8_t id)
{
	uint8_t payload [9];

	getBytesFromInt(payload, 0, commande.x);
	getBytesFromInt(payload, 4, commande.y);

	payload[8] = id;

	//call encode
}

void sendAck()
{
	uint8_t playload [1];

	payload[0] = 1;
}
