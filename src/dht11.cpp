/**
 * @file dht11.cpp
 * @brief Implementation of DHT11 temperature and humidity sensor read functions.
 */

#include "dht11.h"

/**
 * @brief Read temperature and humidity values from the DHT11 sensor.
 *
 * Performs the required timing sequence, reads the 5‑byte data frame
 * and verifies the checksum. Returns 255 on timeout or protocol error.
 *
 * @param[out] temp Measured temperature in degrees Celsius.
 * @param[out] hum  Measured relative humidity in percent.
 *
 * @return 0 on success, 255 on error.
 */
int dht_read_data(int *temp, int *hum) {
  uint8_t data[5] = {0, 0, 0, 0, 0};
  uint8_t checksum = 0;
  unsigned long time = 0;

  DHT_PIN_OUTPUT();

  DHT_PIN_LOW();
  delayMicroseconds(18000);

  DHT_PIN_HIGH();
  delayMicroseconds(40);

  DHT_PIN_INPUT();
  time = micros();
  while (!(DHTPINREG & (1 << DHT11_PIN))) {
    if (micros() - time > 100) return 255;
  }

  time = micros();
  while ((DHTPINREG & (1 << DHT11_PIN))) {
    if (micros() - time > 100) return 255;
  }
  
  for (int i = 0; i < 5; i++) {
    data[i] = dht_read_byte();
    if (data[i] == 255) return 255;
  }

  checksum = data[0] + data[1] + data[2] + data[3];
  if (data[4] == checksum) {
    *temp = data[2];
    *hum = data[0];
    return 0;
  }

  return 255;
}

/**
 * @brief Read a single byte from the DHT11 sensor.
 *
 * Interprets the duration of high pulses as 0/1 bits and assembles
 * them into a single byte. Returns 255 if any bit read times out.
 *
 * @return The received byte value, or 255 on timeout/error.
 */
uint8_t dht_read_byte() {
  uint8_t byte = 0;
  unsigned long time = 0;

  for (int i = 0; i < 8; i++) {
    time = micros();
    while (!(DHTPINREG & (1 << DHT11_PIN))) {
      if (micros() - time > 100) return 255;
    }

    unsigned long responseTime = micros();
    while (DHTPINREG & (1 << DHT11_PIN)) {
      if (micros() - responseTime > 100) return 255;
    }

    if(micros() - responseTime > 40) {
      byte ^= (1 << (7 - i));
    }
  }

  return byte;
}
