#include "dth11.h"

int dth_read_data(int *temp, int *hum) {
  uint8_t data[5] = {0, 0, 0, 0, 0};
  uint8_t checksum = 0;
  unsigned long time = 0;

  DTHDDR |= (1 << DTH11_PIN); // DTH pinini çıkık olarak ayarla

  DTHPORT &= ~(1 << DTH11_PIN); // DTH pinin low yap - dthye hazırlan sinyali ver
  delayMicroseconds(18000);

  DTHPORT |= (1 << DTH11_PIN); // DTH pinini High yap - dthye veriyi gönder sinyali ver
  delayMicroseconds(40);

  DTHDDR &= ~(1 << DTH11_PIN); // DTH pinini giriş olarak ayarla - dthden veri almak için input yap

  time = micros();
  while (!(DTHPINREG & (1 << DTH11_PIN))) {
    if (micros() - time > 100) return 255; // 80us low - dth ölçüm için hazırlanıyor
  }

  time = micros();
  while ((DTHPINREG & (1 << DTH11_PIN))) {
    if (micros() - time > 100) return 255; // 80us high - dth veri göndermek için hazırlanıyor
  }
  
  for (int i = 0; i < 5; i++) {
    data[i] = dth_read_byte();
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

uint8_t dth_read_byte() {
  uint8_t byte = 0;
  unsigned long time = 0;

  for (int i = 0; i < 8; i++) {
    time = micros();
    while (!(DTHPINREG & (1 << DTH11_PIN))) {
      if (micros() - time > 100) return 255;
    }

    unsigned long responseTime = micros();
    while (DTHPINREG & (1 << DTH11_PIN)) {
      if (micros() - responseTime > 100) return 255;
    }

    if(micros() - responseTime > 40) {
      byte ^= (1 << (7 - i));
    }
  }

  return byte;
}
