/**
 * @file i2c.cpp
 * @brief Yazılımsal (bit-banged) I2C fonksiyonlarının implementasyonu.
 */

#include "i2c.h"

/**
 * @brief Yaklaşık 100 kHz I2C saat frekansını sağlayacak kısa bir gecikme uygular.
 */
void i2c_dly() {
    // Hold time for ~100 kHz I2C clock
    delayMicroseconds(5);
}
 
/**
 * @brief I2C START koşulunu üretir.
 *
 * SDA hattını yüksek seviyeden düşük seviyeye çekerken SCL hattını yüksekten
 * düşüğe alarak standard I2C başlangıç sekansını oluşturur.
 */
void i2c_start() {
  I2C_SDA_OUTPUT();
  I2C_SCL_OUTPUT();

  I2C_SDA_LOW();
  i2c_dly();

  I2C_SCL_LOW();
  i2c_dly();

}

/**
 * @brief I2C STOP koşulunu üretir.
 *
 * SCL hattını serbest bırakıp (HIGH), ardından SDA hattını da serbest
 * bırakarak veri aktarımını sonlandırır.
 */
void i2c_stop() {

  I2C_SDA_OUTPUT();
  I2C_SCL_OUTPUT();

  I2C_SDA_LOW();
  i2c_dly();

  I2C_SCL_FLOAT();
  i2c_dly();

  I2C_SDA_FLOAT();
}

/**
 * @brief I2C veri hattı üzerinden tek bir bayt gönderir.
 *
 * MSB'den LSB'ye doğru 8 saat darbesi boyunca veri hattına bitleri yazar.
 *
 * @param byte Gönderilecek 8 bitlik değer.
 */
void i2c_send_byte(uint8_t byte) {
    
    for (int i = 7; i >= 0; i--) {
      if ((byte & (1 << i)) == 0) {
        I2C_SDA_LOW(); // Send logic 0
        i2c_dly();
        I2C_SCL_FLOAT();
        i2c_dly();
        I2C_SCL_LOW();
      }
      else {
        I2C_SDA_FLOAT();
        i2c_dly();
        I2C_SCL_FLOAT();
        i2c_dly();
        I2C_SCL_LOW();
      }
    }
  }

/**
 * @brief Slave cihazdan ACK/NACK bilgisini okur.
 *
 * SDA hattını girişe alıp, saat darbesi sırasında hattın çekilip çekilmediğini
 * kontrol eder.
 *
 * @return 1 ACK alındıysa, 0 NACK veya hata durumunda.
 */
int i2c_wait_ack() {

    I2C_SDA_INPUT();
    
    I2C_SCL_FLOAT();
    i2c_dly();

    int ack = !(I2CPINREG & (1 << SDA_PIN));

    I2C_SCL_LOW();
    i2c_dly();

    I2C_SDA_OUTPUT();

    return ack;
} 