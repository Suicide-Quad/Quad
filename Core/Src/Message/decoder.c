#include "Message/decoder.h" 
#include "utils.h" 
#include "main.h" 

StateReceive actualStatement = WAITING;
uint8_t payload[BUFF_SIZE];
TypeRequest actualType;

void receiveByte(uint8_t byte)
{
}


