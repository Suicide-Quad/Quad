#include "Message/proccesor.h" 
#include "utils.h" 
#include "main.h" 

//fonction pour avoir taille getSize()

uint8_t x = 0;
uint8_t y = 0;
uint8_t id = 0;

void processMessage(TypeRequest *request, uint8_t* payload){
    uint8_t size = getSize(request);
    if (request == NULL) return;
    if (request == RESPONSE_POSITION){
        x = payload[0];
        y = payload[1];
        id = payload[2];
        SwitchId(id); 
    }
}


