/**
 * @file i2c_lcd.cpp
 * @brief I2C üzerinden HD44780 uyumlu karakter LCD sürücüsünün implementasyonu.
 */

#include "i2c.h"
#include "i2c_lcd.h"

/**
 * @brief LCD'ye tek bir komut veya veri (karakter) baytı gönderir.
 *
 * Veriyi 4-bit modda iki nibble'a bölerek I2C üzerinden iletir ve her gönderim
 * sonrasında ACK kontrolü yapar.
 *
 * @param data    Gönderilecek komut veya karakter verisi.
 * @param is_char true ise karakter verisi, false ise komut gönderilir.
 *
 * @return 1 başarı, 0 ACK alınamadığında hata.
 */
uint8_t lcd_send_data(uint8_t data, bool is_char) {

    uint8_t rs_config = (is_char ? RS_BIT : 0);
    // (data & 0xF0) -> high nibble, (data << 4) & 0xF0 -> low nibble

    // Set high nibble package
    uint8_t package_high_en = ((data & 0xF0) | rs_config | BL_BIT | EN_BIT);
    uint8_t package_low_en = ((data & 0xF0) | rs_config | BL_BIT);

    // Send high nibble
    i2c_send_byte(package_high_en); // High nibble with EN = 1
    i2c_dly();
    if (i2c_wait_ack() == 0) {
      return 0;
    }

    i2c_send_byte(package_low_en); // High nibble with EN = 0
    i2c_dly();
    if (i2c_wait_ack() == 0) {
      return 0;
    }

    // Prepare low nibble package
    package_high_en = (((data << 4) & 0xF0) | rs_config | BL_BIT | EN_BIT);
    package_low_en = (((data << 4) & 0xF0) | rs_config | BL_BIT);
    // Send low nibble
    i2c_send_byte(package_high_en); // Low nibble with EN = 1
    i2c_dly();
    if (i2c_wait_ack() == 0) {
      return 0;
    }

    i2c_send_byte(package_low_en); // Low nibble with EN = 0
    i2c_dly();
    if (i2c_wait_ack() == 0) {
      return 0;
    }

    return 1;
  }

  /**
   * @brief LCD ekranı 4-bit çalışma moduna göre ilklendirir.
   *
   * Güç verildikten sonra gerekli bekleme ve fonksiyon set, display control,
   * entry mode ve ekran temizleme komutlarını sırasıyla gönderir.
   */
  void lcd_init() {

    delay(50);
    i2c_send_byte(LCD_ADRESS << 1);
    if (i2c_wait_ack() == 0) {
      return;
    }
    i2c_dly();

    lcd_send_data(0x30, false); // 8-bit mode
    i2c_dly();
    lcd_send_data(0x30, false); // 8-bit mode
    i2c_dly();
    lcd_send_data(0x30, false); // 8-bit mode
    i2c_dly();
    lcd_send_data(0x20, false); // Switch to 4-bit mode
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

  /**
   * @brief LCD imlecini istenen sütun ve satıra konumlandırır.
   *
   * @param col Sütun numarası (0 tabanlı).
   * @param row Satır numarası (0: birinci satır, 1: ikinci satır).
   */
  void lcd_setCursor(uint8_t col, uint8_t row) {
    uint8_t address = (row == 0) ? 0x80 + col : 0xC0 + col;

    lcd_send_data(address, false);
  }

  /**
   * @brief Verilen C-string'i LCD'ye karakter karakter yazar.
   *
   * @param str Yazdırılacak null-sonlandırılmış karakter dizisi.
   */
  void lcd_print(const char* str) {

    for (size_t i = 0; i < strlen(str); i++) {
        lcd_send_data(str[i], true);
    }
  }