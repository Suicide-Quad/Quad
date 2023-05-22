#ifndef _DECODER_H
#define _DECODER_H


typedef enum 
{
    WAITING,
    SOF,
    TYPE,
    PAYLOAD,
    SUM
} StateReceive;

void receiveByte(uint8_t byte);

#endif
