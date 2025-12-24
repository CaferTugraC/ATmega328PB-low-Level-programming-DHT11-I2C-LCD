#include <Arduino.h>
#include <avr/io.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "i2c.h"
#include "dht11.h"
#include "i2c_lcd.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Ready.");
  i2c_start();
  i2c_send_byte(LCD_ADRESS << 1);
  if (i2c_wait_ack() == 0) {
    Serial.println("eror: can not connect to lcd");
    i2c_stop();
    return;
  }
  i2c_dly();
  lcd_init();
  i2c_dly();
  lcd_send_data(0x01, false); // Clear Display
  i2c_dly();
  lcd_setCursor(0, 0);
  i2c_dly();
}

void loop() {
  int humidity, temperature;
  if (dht_read_data(&temperature, &humidity) == 0) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  } else {
    Serial.println("Failed to read from DHT11");
  }
  char temp_str[16];
  snprintf(temp_str, sizeof(temp_str), "Temp : %d C", temperature);
  char hum_str[16];
  snprintf(hum_str, sizeof(hum_str), "Hum : %d %%", humidity);
  lcd_setCursor(0, 0);
  i2c_dly();
  lcd_print(temp_str);
  i2c_dly();
  lcd_setCursor(0, 2);
  i2c_dly();
  lcd_print(hum_str);

  delay(1000); // wait for 1 seconds before next read
}

