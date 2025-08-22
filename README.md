# Arduino Register Seviyesi DHT11 ve I2C LCD Projesi

## 🎯 Proje Amacı
Bu projeyi, DHT11 sensöründen sıcaklık verilerini okuyup LCD ekranda göstermenin yanı sıra, Arduino'yu register seviyesinde programlayarak low-level programlama becerilerimi geliştirmek ve I2C gibi protokollerin temelde nasıl çalıştığını anlamak için geliştirdim.

## 📋 Proje Genel Bakış
Bu projeyle şunları deneyimledim:
- AVR mikrodenetleyicilerde direkt register manipülasyonu
- Kütüphane bağımlılığı olmadan low-level protokol implementasyonu
- Donanım etkileşimi ve zamanlama kritik programlama
- Gömülü sistem geliştirme en iyi uygulamaları

## 🛠 Kullanılan Donanım Bileşenleri
- Arduino Uno
- DHT11 Sıcaklık/Nem Sensörü
- 16x2 I2C LCD Ekran
- DHT11 için 5kΩ direnç
- I2C için 2x 4kΩ çekme direnci
- Breadboard ve jumper kablolar

## 🔧 Teknik Implementasyon

### Register Seviyesinde Programlama
```cpp
// Direkt port manipülasyon örnekleri
#define DTHPORT PORTD
#define DTHDDR DDRD
#define DTHPINREG PIND

// Özel mikrosaniye gecikme fonksiyonu
void delayMicrosec(uint16_t us) {
    uint16_t loops = us * 4;
    while (loops--) {
        asm("nop");
    } 
}
