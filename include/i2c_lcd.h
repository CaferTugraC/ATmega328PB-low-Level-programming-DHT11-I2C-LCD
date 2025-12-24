/**
 * @file i2c_lcd.h
 * @brief I2C arayüzlü karakter LCD (HD44780 uyumlu) ekran sürücüsü.
 */

#ifndef I2C_LCD_H
#define I2C_LCD_H

#include <Arduino.h>

#define I2CDDR  DDRC  ///< LCD'nin bağlı olduğu I2C portu için DDR register'ı
#define I2CPORT PORTC ///< LCD'nin bağlı olduğu I2C portu için PORT register'ı
#define I2CPINREG PINC///< LCD'nin bağlı olduğu I2C portu için PIN register'ı

#define LCD_ADRESS 0x27 ///< PCF8574 tabanlı I2C LCD modülünün I2C adresi

/// RS biti: 0 = komut, 1 = veri (karakter).
const uint8_t RS_BIT = 0b00000001;
/// RW biti: 0 = yazma, 1 = okuma (bu projede her zaman 0).
const uint8_t RW_BIT = 0b00000010;
/// EN biti: LCD'ye veriyi kilitlemek için enable hattı.
const uint8_t EN_BIT = 0b00000100;
/// BL biti: Arka aydınlatmayı kontrol eden bit.
const uint8_t BL_BIT = 0b00001000;

/**
 * @brief LCD'ye tek bir bayt gönderir (komut veya veri).
 *
 * 4-bit modda, baytı iki nibble şeklinde I2C üzerinden aktarır.
 *
 * @param data   Gönderilecek komut/veri baytı.
 * @param isChar true ise veri (karakter), false ise komut gönderilir.
 *
 * @return 1 başarı, 0 ise I2C ACK alınamadığında hata.
 */
uint8_t lcd_send_data(uint8_t data, bool isChar);

/**
 * @brief LCD ekranı 4-bit modda çalışacak şekilde ilklendirir.
 *
 * Fonksiyon set, display control, entry mode ve clear display komutlarını gönderir.
 */
void lcd_init();

/**
 * @brief İmleci istenen sütun ve satıra taşır.
 *
 * @param col Sütun numarası (0'dan başlar).
 * @param row Satır numarası (0: birinci satır, 1: ikinci satır vb.).
 */
void lcd_setCursor(uint8_t col, uint8_t row);

/**
 * @brief Verilen C-string'i LCD'ye karakter karakter yazar.
 *
 * @param str Yazdırılacak null-sonlandırılmış karakter dizisi.
 */
void lcd_print(const char* str);

#endif