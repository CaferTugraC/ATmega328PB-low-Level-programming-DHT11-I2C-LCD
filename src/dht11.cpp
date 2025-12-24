/**
 * @file dht11.cpp
 * @brief DHT11 sıcaklık ve nem sensöründen veri okuma fonksiyonlarının
 *        implementasyonunu içerir.
 */

#include "dht11.h"

/**
 * @brief DHT11 sensöründen sıcaklık ve nem değerlerini okur.
 *
 * Sensörle haberleşme için gerekli zamanlama dizisini uygular, 5 baytlık
 * veri paketini okur ve checksum kontrolü yapar. Hata veya zaman aşımı
 * durumunda 255 döndürür.
 *
 * @param[out] temp Okunan sıcaklık değeri (°C cinsinden).
 * @param[out] hum  Okunan bağıl nem değeri (% cinsinden).
 *
 * @return 0 okuma başarılı ise, 255 hata durumunda.
 */
int dht_read_data(int *temp, int *hum) {
  uint8_t data[5] = {0, 0, 0, 0, 0};
  uint8_t checksum = 0;
  unsigned long time = 0;

  DHT_PIN_OUTPUT();

  DHT_PIN_LOW();
  delayMicroseconds(18000);

  DHT_PIN_HIGH();
  delayMicroseconds(40);

  DHT_PIN_INPUT();
  time = micros();
  while (!(DHTPINREG & (1 << DHT11_PIN))) {
    if (micros() - time > 100) return 255; // 80us low - dth ölçüm için hazırlanıyor
  }

  time = micros();
  while ((DHTPINREG & (1 << DHT11_PIN))) {
    if (micros() - time > 100) return 255; // 80us high - dth veri göndermek için hazırlanıyor
  }
  
  for (int i = 0; i < 5; i++) {
    data[i] = dht_read_byte();
    if (data[i] == 255) return 255;
  }

  checksum = data[0] + data[1] + data[2] + data[3];
  if (data[4] == checksum) {
    *temp = data[2];
    *hum = data[0];
    return 0; // Başarılı okuma
  }

  return 255;
}

/**
 * @brief DHT11 sensöründen tek bir bayt okur.
 *
 * Sensörün gönderdiği 8 biti, darbe genişliklerine göre 0 veya 1 olarak
 * yorumlayarak geri döndürür. Herhangi bir bit okumasında zaman aşımı
 * oluşursa 255 döndürülür.
 *
 * @return Okunan bayt değeri veya hata durumunda 255.
 */
uint8_t dht_read_byte() {
  uint8_t byte = 0;
  unsigned long time = 0;

  for (int i = 0; i < 8; i++) {
    time = micros();
    while (!(DHTPINREG & (1 << DHT11_PIN))) {
      if (micros() - time > 100) return 255;
    }

    unsigned long responseTime = micros();
    while (DHTPINREG & (1 << DHT11_PIN)) {
      if (micros() - responseTime > 100) return 255;
    }

    if(micros() - responseTime > 40) {
      byte ^= (1 << (7 - i));
    }
  }

  return byte;
}
