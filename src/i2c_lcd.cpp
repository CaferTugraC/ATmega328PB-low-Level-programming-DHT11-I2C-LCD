#include "i2c.h"
#include "i2c_lcd.h"

uint8_t lcd_send_data(uint8_t data, bool is_char) {

    uint8_t rs_config = (is_char ? RS_BIT : 0);
    // (data & 0xF0) -> high nibble, (data << 4) & 0xF0 -> low nibble

    // set high nibble packacge
    uint8_t package_high_en = ((data & 0xF0) | rs_config | BL_BIT | EN_BIT);
    uint8_t package_low_en = ((data & 0xF0) | rs_config | BL_BIT);

    // send high nibble
    i2c_send_byte(package_high_en); // send high nibble with en bit 1
    i2c_dly();
    if (i2c_wait_ack() == 0) {
      return 0;
    }

    i2c_send_byte(package_low_en); // send high nibble with en bit 0
    i2c_dly();
    if (i2c_wait_ack() == 0) {
      return 0;
    }

    // set low nibble packacge
    package_high_en = (((data << 4) & 0xF0) | rs_config | BL_BIT | EN_BIT);
    package_low_en = (((data << 4) & 0xF0) | rs_config | BL_BIT);
    // send low nibble
    i2c_send_byte(package_high_en); // send low nibble with en bit 1
    i2c_dly();
    if (i2c_wait_ack() == 0) {
      return 0;
    }

    i2c_send_byte(package_low_en); // send low nibble with en bit 0
    i2c_dly();
    if (i2c_wait_ack() == 0) {
      return 0;
    }

    return 1;
  }

  void lcd_init() {

    delay(50);
    i2c_send_byte(LCD_ADRESS << 1);
    if (i2c_wait_ack() == 0) {
      return;
    }
    i2c_dly();

    lcd_send_data(0x30, false); // 8-bit mod
    i2c_dly();
    lcd_send_data(0x30, false); // 8-bit mod
    i2c_dly();
    lcd_send_data(0x30, false); // 8-bit mod
    i2c_dly();
    lcd_send_data(0x20, false); // 4-bit mod
    i2c_dly();

    lcd_send_data(0x28, false); // Function Set: 4-bit, 2 lines, 5x8 dots
    delay(1);
    lcd_send_data(0x0C, false); // Display On, Cursor Off, Blink Off
    delay(1);
    lcd_send_data(0x06, false); // Entry Mode Set
    delay(1);
    lcd_send_data(0x01, false); // Clear Display
    delay(5);
  }

  void lcd_setCursor(uint8_t col, uint8_t row) {
    uint8_t address = (row == 0) ? 0x80 + col : 0xC0 + col;

    lcd_send_data(address, false);
  }

  void lcd_print(const char* str) {

    for (size_t i = 0; i < strlen(str); i++) {
        lcd_send_data(str[i], true);
    }
  }