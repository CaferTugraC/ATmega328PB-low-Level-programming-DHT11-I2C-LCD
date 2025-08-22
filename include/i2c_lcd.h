#ifndef I2C_LCD_H
#define I2C_LCD_H

#include <Arduino.h>

#define I2CDDR DDRC 
#define I2CPORT PORTC 
#define I2CPINREG PINC 

#define LCD_ADRESS 0x27

const uint8_t RS_BIT = 0b00000001;
const uint8_t RW_BIT = 0b00000010; // Yazma için 0 olarak bırakılacak
const uint8_t EN_BIT = 0b00000100;
const uint8_t BL_BIT = 0b00001000;

uint8_t lcd_send_data(uint8_t data, bool isChar);
void lcd_init();
void lcd_setCursor(uint8_t col, uint8_t row);
void lcd_print(const char* str);

#endif