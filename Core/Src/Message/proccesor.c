#include "Message/proccesor.h" 
#include "utils.h" 
#include "main.h" 

//fonction pour avoir taille getSize()

void processMessage(TypeRequest *request, uint8_t* payload){
    if (request == NULL) return;
    if (request == RESPONSE_POSITION){
        uint8_t x = payload[0];
        uint8_t y = payload[1];
        uint8_t id = payload[2];

        SwitchId(id); 
    }
}

