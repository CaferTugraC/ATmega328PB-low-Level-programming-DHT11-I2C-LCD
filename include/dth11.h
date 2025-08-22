#ifndef DTH11_H
#define DTH11_H 

#include <Arduino.h>

#define DTH11_PIN 2 
#define DTHPORT PORTD 
#define DTHDDR DDRD 
#define DTHPINREG PIND


int dth_read_data(int *temperature, int* humidity);
uint8_t dth_read_byte();

#endif