#ifndef _ENCODER_MESSAGE_H
#define _ENCODER_MESSAGE_H

void sendData(TYPE REQUEST, uint8_t* payload);

uint32_t sizePayload(TYPE REQUEST);

#endif 
