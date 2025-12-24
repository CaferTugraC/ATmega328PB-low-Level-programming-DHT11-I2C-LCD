#ifndef DHT11_H
#define DHT11_H 

#include <Arduino.h>

#define DHT11_PIN 2 
#define DHTPORT PORTD 
#define DHTDDR DDRD 
#define DHTPINREG PIND

#define DHT_PIN_OUTPUT() { DHTDDR |= (1 << DHT11_PIN);}
#define DHT_PIN_LOW() { DHTPORT &= ~(1 << DHT11_PIN);}
#define DHT_PIN_HIGH() { DHTPORT |= (1 << DHT11_PIN);}
#define DHT_PIN_INPUT() { DHTDDR &= ~(1 << DHT11_PIN);}


int dht_read_data(int *temperature, int* humidity);
uint8_t dht_read_byte();

#endif