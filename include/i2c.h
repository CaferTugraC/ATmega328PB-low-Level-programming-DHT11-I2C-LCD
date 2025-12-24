/**
 * @file i2c.h
 * @brief Yazılımsal (bit-banged) I2C haberleşmesi için pin ve fonksiyon tanımları.
 */

#ifndef I2C_H
#define I2C_H

#include <Arduino.h>

#define I2CDDR      DDRC   ///< I2C hattı için DDR register'ı
#define I2CPORT     PORTC  ///< I2C hattı için PORT register'ı
#define I2CPINREG   PINC   ///< I2C hattı için PIN register'ı
#define SDA_PIN     4      ///< SDA veri hattı pini
#define SCL_PIN     5      ///< SCL saat hattı pini

/**
 * @brief SDA pinini çıkış moduna alır.
 */
#define I2C_SDA_OUTPUT()    { I2CDDR |= (1 << SDA_PIN); } 

/**
 * @brief SDA pinini giriş (yüzer) moda alır.
 */
#define I2C_SDA_INPUT()     { I2CDDR &= ~(1 << SDA_PIN); }

/**
 * @brief SDA pinini lojik 0 seviyesine çeker.
 */
#define I2C_SDA_LOW()       { I2CDDR |= (1 << SDA_PIN); I2CPORT &= ~(1 << SDA_PIN); }

/**
 * @brief SDA hattını bırakır (harici pull-up ile 1 olur).
 */
#define I2C_SDA_FLOAT()     { I2CDDR |= (1 << SDA_PIN); I2CDDR &= ~(1 << SDA_PIN); }

/**
 * @brief SCL pinini çıkış moduna alır.
 */
#define I2C_SCL_OUTPUT()    { I2CDDR |= (1 << SCL_PIN); }

/**
 * @brief SCL pinini lojik 0 seviyesine çeker.
 */
#define I2C_SCL_LOW()       { I2CDDR |= (1 << SCL_PIN); I2CPORT &= ~(1 << SCL_PIN); }

/**
 * @brief SCL hattını bırakır (harici pull-up ile 1 olur).
 */
#define I2C_SCL_FLOAT()     { I2CDDR &= ~(1 << SCL_PIN); }

/**
 * @brief I2C zamanlamasını sağlamak için kısa bir gecikme oluşturur.
 *
 * Yaklaşık 100 kHz I2C saat frekansını hedefler.
 */
void i2c_dly();

/**
 * @brief I2C başlangıç (START) koşulunu üretir.
 */
void i2c_start();

/**
 * @brief I2C durdurma (STOP) koşulunu üretir.
 */
void i2c_stop();

/**
 * @brief I2C hattı üzerinden bir bayt veri gönderir (MSB önce).
 *
 * @param byte Gönderilecek 8 bitlik veri.
 */
void i2c_send_byte(uint8_t byte);

/**
 * @brief Slave cihazdan ACK/NACK durumunu okur.
 *
 * @return 1 ACK alındıysa, 0 NACK veya hata durumunda.
 */
int i2c_wait_ack();

#endif