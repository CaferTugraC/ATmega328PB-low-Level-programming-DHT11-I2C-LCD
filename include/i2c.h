/**
 * @file i2c.h
 * @brief Software (bit-banged) I2C interface pin and function definitions.
 */

#ifndef I2C_H
#define I2C_H

#include <Arduino.h>

#define I2CDDR      DDRC   ///< DDR register used for the I2C pins
#define I2CPORT     PORTC  ///< PORT register used for the I2C pins
#define I2CPINREG   PINC   ///< PIN register used for the I2C pins
#define SDA_PIN     4      ///< SDA (data) line pin
#define SCL_PIN     5      ///< SCL (clock) line pin

/**
 * @brief Configure SDA pin as output.
 */
#define I2C_SDA_OUTPUT()    { I2CDDR |= (1 << SDA_PIN); } 

/**
 * @brief Configure SDA pin as input (high‑impedance).
 */
#define I2C_SDA_INPUT()     { I2CDDR &= ~(1 << SDA_PIN); }

/**
 * @brief Drive SDA line low (logic 0).
 */
#define I2C_SDA_LOW()       { I2CDDR |= (1 << SDA_PIN); I2CPORT &= ~(1 << SDA_PIN); }

/**
 * @brief Release SDA line (external pull‑up pulls it high).
 */
#define I2C_SDA_FLOAT()     { I2CDDR |= (1 << SDA_PIN); I2CDDR &= ~(1 << SDA_PIN); }

/**
 * @brief Configure SCL pin as output.
 */
#define I2C_SCL_OUTPUT()    { I2CDDR |= (1 << SCL_PIN); }

/**
 * @brief Drive SCL line low (logic 0).
 */
#define I2C_SCL_LOW()       { I2CDDR |= (1 << SCL_PIN); I2CPORT &= ~(1 << SCL_PIN); }

/**
 * @brief Release SCL line (external pull‑up pulls it high).
 */
#define I2C_SCL_FLOAT()     { I2CDDR &= ~(1 << SCL_PIN); }

/**
 * @brief Small delay used to shape the I2C timing.
 *
 * Target is roughly a 100 kHz I2C clock.
 */
void i2c_dly();

/**
 * @brief Generate an I2C START condition.
 */
void i2c_start();

/**
 * @brief Generate an I2C STOP condition.
 */
void i2c_stop();

/**
 * @brief Send one byte over the I2C bus (MSB first).
 *
 * @param byte 8‑bit value to send.
 */
void i2c_send_byte(uint8_t byte);

/**
 * @brief Read ACK/NACK from the slave device.
 *
 * @return 1 if ACK received, 0 on NACK or error.
 */
int i2c_wait_ack();

#endif