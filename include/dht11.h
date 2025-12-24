/**
 * @file dht11.h
 * @brief Low-level (register level) driver macros and functions
 *        for the DHT11 temperature and humidity sensor.
 */

#ifndef DHT11_H
#define DHT11_H 

#include <Arduino.h>

#define DHT11_PIN 2           ///< DHT11 data pin (PD2 on Arduino Uno)
#define DHTPORT   PORTD       ///< Port register used by the DHT11 pin
#define DHTDDR    DDRD        ///< DDR register used to configure the DHT11 pin direction
#define DHTPINREG PIND        ///< PIN register used to read the DHT11 pin state

/**
 * @brief Configure DHT11 pin as output.
 */
#define DHT_PIN_OUTPUT() { DHTDDR |= (1 << DHT11_PIN);}

/**
 * @brief Drive DHT11 pin low (logic 0).
 */
#define DHT_PIN_LOW() { DHTPORT &= ~(1 << DHT11_PIN);}

/**
 * @brief Drive DHT11 pin high (logic 1).
 */
#define DHT_PIN_HIGH() { DHTPORT |= (1 << DHT11_PIN);}

/**
 * @brief Configure DHT11 pin as input.
 */
#define DHT_PIN_INPUT() { DHTDDR &= ~(1 << DHT11_PIN);}


/**
 * @brief Read temperature and humidity values from the DHT11 sensor.
 *
 * Performs the required timing sequence, reads the 5‑byte data frame
 * from the sensor, verifies the checksum and returns the results.
 *
 * @param[out] temperature Measured temperature in degrees Celsius.
 * @param[out] humidity    Measured relative humidity in percent.
 *
 * @return 0 on success, 255 on timeout or communication error.
 */
int dht_read_data(int *temperature, int* humidity);

/**
 * @brief Read a single byte from the DHT11 sensor.
 *
 * Interprets the width of the pulses sent by the sensor as 0/1 bits
 * and assembles them into one byte.
 *
 * @return The received byte value, or 255 on timeout/error.
 */
uint8_t dht_read_byte();

#endif