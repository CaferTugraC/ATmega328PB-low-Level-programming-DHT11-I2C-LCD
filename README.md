# Arduino Register Seviyesi DHT11 ve I2C LCD Projesi
## 🎯 Proje Amacı
Bu projeyi, DHT11 sensöründen sıcaklık verilerini okuyup LCD ekranda göstermenin yanı sıra, Arduino'yu register seviyesinde programlayarak low-level programlama becerilerimi geliştirmek ve I2C gibi protokollerin temelde nasıl çalıştığını anlamak için geliştirdim.
## 📋 Proje Genel Bakış
Bu projeyle şunları deneyimledim:
- AVR mikrodenetleyicilerde direkt register manipülasyonu
- Kütüphane bağımlılığı olmadan low-level protokol implementasyonu
- Donanım etkileşimi ve zamanlama kritik programlama
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
// I2C haberleşmeyi başlatan donksiyon
void i2c_start() {
    I2CDDR |= (1 << SDA_PIN | 1 << SCL_PIN);

    I2CPORT |= (1 << SCL_PIN | 1 << SDA_PIN);
    i2c_dly();

    I2CPORT &= ~(1 << SDA_PIN);
    i2c_dly();

    I2CPORT &= ~(1 << SCL_PIN);
    i2c_dly();
}
```
### I2C Protokol Implementasyonu
I2C protokolünü sıfırdan implemente ettim:
- Başlatma/durdurma koşulu oluşturma
- Veri iletimi ve alımı
- ACK/NACK işleme
- Saat esnetme desteği
## 💡 Edinilen Önemli Beceriler
Bu projeyle şunları geliştirdim:
- AVR mimarisi ve register manipülasyonu konusunda **derin anlayış**
- Sensör iletişimi için **hassas zamanlama** becerileri
- Kütüphane bağımlılığı olmadan **protokol implementasyonu** yetenekleri
- Hem kod analizi hem de donanım araçları kullanarak **hata ayıklama** uzmanlığı
- Çoklu bileşenler için **donanım entegrasyonu** becerileri
## 🚀 Proje Yapısı
```
├── include/
│   ├── dth11.h    # DHT11 register tanımlamaları
│   ├── i2c.h      # I2C protokol fonksiyonları
│   └── i2c_lcd.h  # LCD kontrol fonksiyonları
├── src/
│   ├── main.cpp   # Ana uygulama
│   ├── dth11.cpp  # DHT11 implementasyonu
│   ├── i2c.cpp    # I2C iletişimi
│   └── i2c_lcd.cpp # LCD kontrol implementasyonu
└── platformio.ini # Derleme yapılandırması
```
## 📊 Bağlantı Şeması
*(Buraya kendi bağlantı şemanızı ekleyebilirsiniz)*

---
⭐ Bu projeyi faydalı veya ilginç bulursanız, lütfen yıldız vermeyi unutmayın!
