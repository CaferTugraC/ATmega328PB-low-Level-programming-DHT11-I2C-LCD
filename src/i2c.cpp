/**
 * @file i2c.cpp
 * @brief Implementation of software (bit‑banged) I2C functions.
 */

#include "i2c.h"

/**
 * @brief Apply a short delay to achieve roughly a 100 kHz I2C clock.
 */
void i2c_dly() {
    delayMicroseconds(5);
}
 
/**
 * @brief Generate the I2C START condition.
 *
 * Drives SDA from high to low while SCL is high, then pulls SCL low to
 * begin the transfer, matching the standard I2C start sequence.
 */
void i2c_start() {
  I2C_SDA_OUTPUT();
  I2C_SCL_OUTPUT();

  I2C_SDA_LOW();
  i2c_dly();

  I2C_SCL_LOW();
  i2c_dly();

}

/**
 * @brief Generate the I2C STOP condition.
 *
 * Releases SCL (high) and then SDA (high) to terminate the transfer.
 */
void i2c_stop() {

  I2C_SDA_OUTPUT();
  I2C_SCL_OUTPUT();

  I2C_SDA_LOW();
  i2c_dly();

  I2C_SCL_FLOAT();
  i2c_dly();

  I2C_SDA_FLOAT();
}

/**
 * @brief Send a single byte over the I2C data line.
 *
 * Writes bits from MSB to LSB over 8 clock cycles.
 *
 * @param byte 8‑bit value to send.
 */
void i2c_send_byte(uint8_t byte) {
    
    for (int i = 7; i >= 0; i--) {
      if ((byte & (1 << i)) == 0) {
        I2C_SDA_LOW();
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

/**
 * @brief Read the ACK/NACK response from the slave.
 *
 * Sets SDA as input and samples it while SCL is high.
 *
 * @return 1 if ACK received, 0 on NACK or error.
 */
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