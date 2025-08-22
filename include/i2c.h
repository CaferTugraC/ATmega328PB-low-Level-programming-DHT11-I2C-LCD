#ifndef I2C_H
#define I2C_H

#include <Arduino.h>

#define I2CDDR DDRC 
#define I2CPORT PORTC 
#define I2CPINREG PINC 
#define SDA_PIN 4 
#define SCL_PIN 5 

void i2c_dly();
void i2c_start();
void i2c_stop();
void i2c_send_byte(uint8_t byte);
int i2c_wait_ack();

#endif