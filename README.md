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
## ⚡ Şaşırtıcı Derecede Sorunsuz Geliştirme Süreci
İlginç bir şekilde, proje geliştirme süreci oldukça sorunsuz ilerledi. Kapsamlı araştırma ve planlama aşaması önemli ölçüde fayda sağladı:
- DHT11 iletişim protokolünü ilk denemede doğru implemente edebildim
- Önemli hata ayıklama gerektirmeden stabil I2C iletişimi kurabildim
- Tüm bileşenleri minimum donanım sorunuyla entegre edebildim
- Geliştirme süreci boyunca temiz kod mimarisini koruyabildim
Bu beklenmedik sorunsuzluk şunların değerini gösterdi:
- Implementasyon öncesi kapsamlı veri sayfası çalışması
- Pin atamalarının ve kaynak tahsisinin dikkatli planlanması
- Her bileşenin bağımsız testine olanak sağlayan modüler kod tasarımı
- Implementasyondan önce temel kavramları anlama
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
## 🌟 Gelecek Geliştirmeler
Bu proje için potansiyel iyileştirmeler:
- Enerji verimliliği optimizasyonu
- Çoklu sensör desteği
- Veri kaydetme özellikleri
- Kablosuz iletişim entegrasyonu
- Uzaktan izleme için web arayüzü
## 📞 İletişim & Bağlantı
Gömülü sistemler, low-level programlama veya potansiyel işbirlikleri hakkında tartışmaları memnuniyetle karşılıyorum!
[![LinkedIn](https://img.shields.io/badge/LinkedIn-Bağlan-mavi)](https://linkedin.com/in/profiliniz)
[![Email](https://img.shields.io/badge/Eposta-Bana%20Ulaşın-kırmızı)](mailto:eposta@alanadiniz.com)
[![GitHub](https://img.shields.io/badge/GitHub-Takip%20Et-açıkgri)](https://github.com/kullaniciadiniz)
---
⭐ Bu projeyi faydalı veya ilginç bulursanız, lütfen yıldız vermeyi unutmayın!
