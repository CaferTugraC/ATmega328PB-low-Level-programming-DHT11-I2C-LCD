#include "i2c.h"

void i2c_dly() {
    // I2C SCL speed 100kHz
    delayMicroseconds(5);
}

void i2c_start() {
  I2C_SDA_OUTPUT();
  I2C_SCL_OUTPUT();

  I2C_SDA_LOW();
  i2c_dly();

  I2C_SCL_LOW();
  i2c_dly();

//    I2CPORT |= (1 << SCL_PIN | 1 << SDA_PIN);
//    i2c_dly();
}

void i2c_stop() {

  I2C_SDA_OUTPUT();
  I2C_SCL_OUTPUT();

  I2C_SDA_LOW();
  i2c_dly();

  I2C_SCL_FLOAT();
  i2c_dly();

  I2C_SDA_FLOAT();
}

void i2c_send_byte(uint8_t byte) {
    
    for (int i = 7; i >= 0; i--) {
      if ((byte & (1 << i)) == 0) {
        I2C_SDA_LOW(); // send 0 bit
        i2c_dly();
        I2C_SCL_FLOAT();
        i2c_dly();
        I2C_SCL_LOW();
      }
      else {
        I2C_SDA_FLOAT();
        i2c_dly();
        I2C_SCL_FLOAT();
        i2c_dly();
        I2C_SCL_LOW();  
      }
    }
  }

int i2c_wait_ack() {

    I2C_SDA_INPUT();
    
    I2C_SCL_FLOAT();
    i2c_dly();

    int ack = !(I2CPINREG & (1 << SDA_PIN));

    I2C_SCL_LOW();
    i2c_dly();

    I2C_SDA_OUTPUT();

    return ack;
} 