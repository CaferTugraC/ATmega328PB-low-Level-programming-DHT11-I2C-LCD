#ifndef I2C_H
#define I2C_H

#include <Arduino.h>

#define I2CDDR      DDRC 
#define I2CPORT     PORTC 
#define I2CPINREG   PINC 
#define SDA_PIN     4 
#define SCL_PIN     5 

#define I2C_SDA_OUTPUT()    { I2CDDR |= (1 << SDA_PIN); } 
#define I2C_SDA_INPUT()     { I2CDDR &= ~(1 << SDA_PIN); }
#define I2C_SDA_LOW()       { I2CDDR |= (1 << SDA_PIN); I2CPORT &= ~(1 << SDA_PIN); }
#define I2C_SDA_FLOAT()     { I2CDDR |= (1 << SDA_PIN); I2CDDR &= ~(1 << SDA_PIN); }

#define I2C_SCL_OUTPUT()    { I2CDDR |= (1 << SCL_PIN); }
#define I2C_SCL_LOW()       { I2CDDR |= (1 << SCL_PIN); I2CPORT &= ~(1 << SCL_PIN); }
#define I2C_SCL_FLOAT()     { I2CDDR &= ~(1 << SCL_PIN); }

void i2c_dly();
void i2c_start();
void i2c_stop();
void i2c_send_byte(uint8_t byte);
int i2c_wait_ack();

#endif