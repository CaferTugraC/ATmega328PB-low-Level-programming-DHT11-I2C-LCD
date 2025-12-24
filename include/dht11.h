/**
 * @file dht11.h
 * @brief DHT11 sıcaklık ve nem sensörünün düşük seviye (register seviyesinde)
 *        sürülmesi için fonksiyon ve makroları içerir.
 */

#ifndef DHT11_H
#define DHT11_H 

#include <Arduino.h>

#define DHT11_PIN 2           ///< DHT11 veri pini (Arduino'da PD2)
#define DHTPORT   PORTD       ///< DHT11'in bağlı olduğu port register'ı
#define DHTDDR    DDRD        ///< DHT11 pininin yönünü ayarlayan DDR register'ı
#define DHTPINREG PIND        ///< DHT11 pininin giriş değerini okuyan pin register'ı

/**
 * @brief DHT11 pinini çıkış moduna alır.
 */
#define DHT_PIN_OUTPUT() { DHTDDR |= (1 << DHT11_PIN);}

/**
 * @brief DHT11 pinini lojik 0 seviyesine çeker.
 */
#define DHT_PIN_LOW() { DHTPORT &= ~(1 << DHT11_PIN);}

/**
 * @brief DHT11 pinini lojik 1 seviyesine çeker.
 */
#define DHT_PIN_HIGH() { DHTPORT |= (1 << DHT11_PIN);}

/**
 * @brief DHT11 pinini giriş moduna alır.
 */
#define DHT_PIN_INPUT() { DHTDDR &= ~(1 << DHT11_PIN);}


/**
 * @brief DHT11 sensöründen sıcaklık ve nem değerlerini okur.
 *
 * Sensörle gerekli zamanlamaları sağlayarak 5 baytlık veri paketi okur,
 * checksum kontrolü yapar ve sonuçları kullanıcıya döndürür.
 *
 * @param[out] temperature Okunan sıcaklık değeri (°C cinsinden, tam sayı).
 * @param[out] humidity    Okunan bağıl nem değeri (% cinsinden, tam sayı).
 *
 * @return 0 okuma başarılıysa, 255 ise zaman aşımı/iletişim hatası durumda.
 */
int dht_read_data(int *temperature, int* humidity);

/**
 * @brief DHT11 sensöründen tek bayt veri okur.
 *
 * Sensörün gönderdiği 8 biti zamanlamaya göre yorumlayarak bir bayta çevirir.
 *
 * @return Okunan bayt değeri, ya da hata durumunda 255.
 */
uint8_t dht_read_byte();

#endif