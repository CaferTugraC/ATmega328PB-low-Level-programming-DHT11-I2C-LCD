#include "i2c.h"

void i2c_dly() {
    // I2C SCL speed 100kHz
    delayMicroseconds(5);
}

void i2c_start() {
    I2CDDR |= (1 << SDA_PIN | 1 << SCL_PIN); // set sda as output

    I2CPORT |= (1 << SCL_PIN | 1 << SDA_PIN);
    i2c_dly();

    I2CPORT &= ~(1 << SDA_PIN); // sda line as low
    i2c_dly();

    I2CPORT &= ~(1 << SCL_PIN); // scl line as low
    i2c_dly();
}

void i2c_stop() {

    I2CDDR |= (1 << SDA_PIN | 1 << SCL_PIN); // set sda as output

    I2CPORT &= ~(1 << SDA_PIN);
    i2c_dly();

    I2CPORT |= (1 << SCL_PIN);
    i2c_dly();
  
    I2CPORT |= (1 << SDA_PIN);
}

void i2c_send_byte(uint8_t byte) {
    
    for (int i = 7; i >= 0; i--) {
      if ((byte & (1 << i)) == 0) {
        I2CPORT &= ~(1 << SDA_PIN); // send 0 bit
        i2c_dly();
        I2CPORT |= (1 << SCL_PIN);
        i2c_dly();
        I2CPORT &= ~(1 << SCL_PIN);
      }
      else {
        I2CPORT |= (1 << SDA_PIN); // send 1 bit
        i2c_dly();
        I2CPORT |= (1 << SCL_PIN);
        i2c_dly();
        I2CPORT &= ~(1 << SCL_PIN);
      }
    }
  }

int i2c_wait_ack() {

    I2CDDR &= ~(1 << SDA_PIN); // sda set as input
    
    I2CPORT |= (1 << SCL_PIN); // scl high
    i2c_dly();

    int ack = !(I2CPINREG & (1 << SDA_PIN));

    I2CPORT &= ~(1 << SCL_PIN); // scl low again
    i2c_dly();

    I2CDDR |= (1 << SDA_PIN); // sda set as output again

    return ack;
} 