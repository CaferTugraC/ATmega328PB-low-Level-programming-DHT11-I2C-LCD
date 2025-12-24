/**
 * @file i2c_lcd.cpp
 * @brief Implementation of an HD44780‑compatible character LCD driver over I2C.
 */

#include "i2c.h"
#include "i2c_lcd.h"

/**
 * @brief Send a single command or data (character) byte to the LCD.
 *
 * Splits the byte into two 4‑bit nibbles and transfers them over I2C,
 * checking for ACK after each step.
 *
 * @param data    Command or character byte to send.
 * @param is_char True to send character data, false to send a command.
 *
 * @return 1 on success, 0 if ACK is not received.
 */
uint8_t lcd_send_data(uint8_t data, bool is_char) {

    uint8_t rs_config = (is_char ? RS_BIT : 0);

    uint8_t package_high_en = ((data & 0xF0) | rs_config | BL_BIT | EN_BIT);
    uint8_t package_low_en = ((data & 0xF0) | rs_config | BL_BIT);

    i2c_send_byte(package_high_en);
    i2c_dly();
    if (i2c_wait_ack() == 0) {
      return 0;
    }

    i2c_send_byte(package_low_en);
    i2c_dly();
    if (i2c_wait_ack() == 0) {
      return 0;
    }

    package_high_en = (((data << 4) & 0xF0) | rs_config | BL_BIT | EN_BIT);
    package_low_en = (((data << 4) & 0xF0) | rs_config | BL_BIT);
    i2c_send_byte(package_high_en);
    i2c_dly();
    if (i2c_wait_ack() == 0) {
      return 0;
    }

    i2c_send_byte(package_low_en);
    i2c_dly();
    if (i2c_wait_ack() == 0) {
      return 0;
    }

    return 1;
  }

  /**
   * @brief Initialize the LCD to operate in 4‑bit mode.
   *
   * After power‑up delay, sends function set, display control,
   * entry mode and clear display commands in sequence.
   */
  void lcd_init() {

    delay(50);
    i2c_send_byte(LCD_ADRESS << 1);
    if (i2c_wait_ack() == 0) {
      return;
    }
    i2c_dly();

    lcd_send_data(0x30, false);
    i2c_dly();
    lcd_send_data(0x30, false);
    i2c_dly();
    lcd_send_data(0x30, false);
    i2c_dly();
    lcd_send_data(0x20, false);
    i2c_dly();

    lcd_send_data(0x28, false);
    delay(1);
    lcd_send_data(0x0C, false);
    delay(1);
    lcd_send_data(0x06, false);
    delay(1);
    lcd_send_data(0x01, false);
    delay(5);
  }

  /**
   * @brief Position the LCD cursor at the requested column and row.
   *
   * @param col Column index (0‑based).
   * @param row Row index (0: first line, 1: second line, etc.).
   */
  void lcd_setCursor(uint8_t col, uint8_t row) {
    uint8_t address = (row == 0) ? 0x80 + col : 0xC0 + col;

    lcd_send_data(address, false);
  }

  /**
   * @brief Write the given C‑string to the LCD character by character.
   *
   * @param str Null‑terminated string to write.
   */
  void lcd_print(const char* str) {

    for (size_t i = 0; i < strlen(str); i++) {
        lcd_send_data(str[i], true);
    }
  }