#ifndef _COMMUNICATION_H
#define _COMMUNICATION_H

#define START_REQUEST 0xFE
#define SIZE_START 8

#define SIZE_COMFLAGS 8

#define SIZE_DATA pow(2,255)

#define SIZE_CHECKSUM 8

#define END_REQUEST 0x26 //=='&'
#define SIZE_END 8

#define SIZE_REQUEST SIZE_START+SIZE_COMFLAGS+SIZE_DATA+SIZE_CHECKSUM+SIZE_END

enum ComFlags
{
	Image = 0;
	Ack = 0;
	Response_Image = 0;
	Position = 0;
}

//Build and send the request for send image to the esp32 put on huart2;
void send_image(uint32_t image[1600*1200]);
//Read the request of image and put in the pointeur of the image and return true if it's a image request
uint8_t receive_image(char request [SIZE_REQUEST], uint32_t* image[1600*1200]);

////Build and send the request for send position and orientation of the robot to the esp32 put on huart2;
void send_position(uint32_t x, uint32_t y, uint32_t theta);
//READ the request of position and orientation and put this on the table position[x,y,theta] and return true if it's a position request
uint8_t receive_position(char request [SIZE_REQUEST], uint32_t position [3]);

//Send request for say "i have read your request"
void send_ack();
//Read the request who say "i have read the request" and return true if it's a ack request
void receive_ack();
