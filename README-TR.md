# Arduino Register Seviyesi DHT11 ve I2C LCD Projesi
##  Proje Amacı
Bu projeyi, DHT11 sensöründen sıcaklık verilerini okuyup LCD ekranda göstermenin yanı sıra, Arduino'yu register seviyesinde programlayarak low-level programlama becerilerimi geliştirmek ve I2C gibi protokollerin temelde nasıl çalıştığını anlamak için geliştirdim.
##  Proje Genel Bakış
Bu projeyle şunları deneyimledim:
- AVR mikrodenetleyicilerde direkt register manipülasyonu
- Kütüphane bağımlılığı olmadan low-level protokol implementasyonu
- Donanım etkileşimi ve zamanlama kritik programlama
##  Kullanılan Donanım Bileşenleri
- Arduino Uno
- DHT11 Sıcaklık/Nem Sensörü
- 16x2 I2C LCD Ekran
- DHT11 için 5kΩ direnç
- I2C için 2x 4kΩ çekme direnci
- Breadboard ve jumper kablolar
##  Teknik Implementasyon
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
### DTH Haberleşme Protokolü
DTH1'den sıcaklık ve nem verisini okyabilmek için datasheetinde bulununan protoklü implemente ettim:
-  MCU DATA pinini LOW yaparak başlatma sinyali gönderir (18ms)
-  MCU pinini HIGH yapar ve bekleme moduna geçer
-  DHT11 yanıt sinyali gönderir (LOW 80μs + HIGH 80μs)
-  40-bit veri gönderimi başlar (LOW 50μs + HIGH 26-70μs)
-   Her bit: LOW 50μs + HIGH uzunluğu (26μs = 0, 70μs = 1)

  Not : Daha fazla detay için DTH11 datashettini inceleyebilirsiniz.
##  Edinilen Önemli Beceriler
Bu projeyle şunları geliştirdim:
- AVR mimarisi ve register manipülasyonu konusunda **derin anlayış**
- Sensör iletişimi için **hassas zamanlama** becerileri
- Protokollerin temelde **nasıl çalıştığı** hakkında önemli bilgiler
- Hem kod analizi hem de donanım araçları kullanarak **hata ayıklama** deneyimi
- Çoklu bileşenler için **donanım entegrasyonu** becerileri
##  Proje Yapısı
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
##  Bağlantı Şeması

<img width="1454" height="1007" alt="Ekran görüntüsü 2025-08-23 133358" src="https://github.com/user-attachments/assets/8dfcf1d3-5013-457e-a3a5-8aae356b7644" />
## Not
- Bu şema EasyEDA kullanılarak tasarlanmıştır
- Eğitim/kişisel kullanım amaçlıdır
- [EasyEDA](https://easyeda.com/) - Ücretsiz elektronik tasarım aracı

---
 Bu projeyi faydalı veya ilginç bulursanız, lütfen yıldız vermeyi unutmayın!
