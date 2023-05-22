#include "Message/proccesor.h" 
#include "utils.h" 
#include "main.h" 

//fonction pour avoir taille getSize()

void processMessage(TypeRequest *request, uint8_t* payload){
    uint8_t size = getSize(request);
    if (request == NULL) return;
    if (*request == RESPONSE_POSITION){
        id = payload[2];
        SwitchId(id); 
    }
}


