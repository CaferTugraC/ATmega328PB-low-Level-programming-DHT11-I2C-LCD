/**
 * @file i2c_lcd.h
 * @brief Driver for HD44780‑compatible character LCD over an I2C expander.
 */

#ifndef I2C_LCD_H
#define I2C_LCD_H

#include <Arduino.h>

#define I2CDDR  DDRC  ///< DDR register for the I2C port used by the LCD backpack
#define I2CPORT PORTC ///< PORT register for the I2C port used by the LCD backpack
#define I2CPINREG PINC///< PIN register for the I2C port used by the LCD backpack

#define LCD_ADRESS 0x27 ///< I2C address of the PCF8574‑based LCD backpack

/// RS bit: 0 = command, 1 = data (character).
const uint8_t RS_BIT = 0b00000001;
/// RW bit: 0 = write, 1 = read (always 0 in this project).
const uint8_t RW_BIT = 0b00000010;
/// EN bit: LCD enable line to latch the data.
const uint8_t EN_BIT = 0b00000100;
/// BL bit: Backlight control.
const uint8_t BL_BIT = 0b00001000;

/**
 * @brief Send a single byte to the LCD (command or data).
 *
 * In 4‑bit mode, the byte is split into two nibbles and transferred via I2C.
 *
 * @param data   Command/data byte to send.
 * @param isChar If true, sends character data; if false, sends a command.
 *
 * @return 1 on success, 0 if I2C ACK is not received.
 */
uint8_t lcd_send_data(uint8_t data, bool isChar);

/**
 * @brief Initialize the LCD to operate in 4‑bit mode.
 *
 * Sends function set, display control, entry mode and clear display commands.
 */
void lcd_init();

/**
 * @brief Move the cursor to the requested column and row.
 *
 * @param col Column index (0‑based).
 * @param row Row index (0: first line, 1: second line, etc.).
 */
void lcd_setCursor(uint8_t col, uint8_t row);

/**
 * @brief Print a null‑terminated C string to the LCD character by character.
 *
 * @param str Null‑terminated string to print.
 */
void lcd_print(const char* str);

#endif