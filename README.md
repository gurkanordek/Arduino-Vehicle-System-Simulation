# 🚗 Arduino Car Control & Safety System Simulation

Bu proje, **Arduino Mega 2560** mikrodenetleyicisi kullanılarak geliştirilmiş kapsamlı bir **Araç Kontrol ve Güvenlik Sistemi Simülasyonudur**. Proteus üzerinde tasarlanan devre ve Arduino C++ kodu ile bir otomobilin temel elektronik fonksiyonlarını (motor kontrolü, farlar, klima, güvenlik sistemleri vb.) simüle eder.

## 🌟 Proje Hakkında

Bu simülasyon, modern araçlarda bulunan sensör tabanlı otomasyon ve güvenlik sistemlerinin çalışma mantığını göstermek amacıyla tasarlanmıştır. Sistem; sıcaklık, ışık seviyesi ve yakıt durumu gibi çevresel ve dahili faktörleri sürekli izleyerek sürücüye görsel/işitsel geri bildirim verir ve otomatik aksiyonlar alır.

### Temel Özellikler

* **Motor Kontrol Sistemi:** Emniyet kemeri takılı olmadan ve kapılar kapalı olmadan motorun çalışmasını engelleyen güvenlik kilidi.
* **Otomatik Far Sistemi:** LDR sensörü ile ortam ışığını algılayıp farları otomatik açıp kapatma.
* **Akıllı Klima Sistemi:** LM35 sıcaklık sensörü ile ortam sıcaklığını ölçerek belirli bir eşiğin (25°C) üzerinde klimayı otomatik devreye alma.
* **Yakıt Yönetim Sistemi:** Potansiyometre ile simüle edilen yakıt seviyesini LCD ekranda gösterme, düşük seviyelerde görsel ve yazılı uyarılar verme, yakıt bittiğinde motoru otomatik durdurma.
* **Kapı Güvenlik Sistemi:** Kapı açıldığında RGB LED ile görsel uyarı verme ve motoru durdurma.
* **LCD Bilgi Ekranı:** Anlık durum bilgilerini (Sıcaklık, Yakıt, Uyarılar) sürücüye aktaran 16x2 LCD ekran.

## 🛠️ Kullanılan Donanımlar (Simülasyon)

* **Mikrodenetleyici:** Arduino Mega 2560
* **Sensörler:** LM35 (Sıcaklık), LDR (Işık), Potansiyometre (Yakıt Seviyesi).
* **Aktüatörler:** DC Motorlar, 16x2 LCD Ekran, RGB LED, Standart LED'ler, Buzzer.
* **Sürücü:** BD139 Transistör.

## 🔌 Devre Şeması ve Kurulum

Projenin Proteus üzerindeki devre şeması `src` klasöründe bulunmaktadır.

![Devre Şeması](src/devre.png)

### Nasıl Çalıştırılır?

1.  Bu repoyu bilgisayarınıza indirin.
2.  `src/PROJE2A.ino` dosyasını Arduino IDE ile derleyin ve `.hex` dosyasını oluşturun.
3.  `simulation/PROJE2.pdsprj` dosyasını **Proteus** ile açın.
4.  Arduino Mega kartına çift tıklayıp oluşturduğunuz `.hex` dosyasını "Program File" kısmına yükleyin.
5.  Simülasyonu başlatın.

## 📂 Dosya Yapısı

```bash
.
├── simulation/
│   ├── PROJE2.pdsprj           # Proteus Proje Dosyası
│   ├── ArduinoMega25602TEP.LIB # Kütüphane Dosyası
│   └── ArduinoMega25602TEP.IDX # Index Dosyası
├── src/
│   ├── PROJE2A.ino             # Arduino Kaynak Kodu
│   └── devre.png               # Devre Görüntüsü
└── README.md                   # Proje Dokümantasyonu
```

## 📝 Kod Özeti
Proje kodu src/PROJE2A.ino içerisinde bulunmaktadır ve şu işlevleri yerine getirir:

* **Sensör Okuma:** Sıcaklık (LM35), Işık (LDR) ve Yakıt (Potansiyometre) verilerini analog pinlerden okur.

* **Güvenlik Kontrolü:** loop döngüsü içinde sürekli olarak kapı ve emniyet kemeri durumunu denetler (digitalRead).

* **LCD Yönetimi:** LiquidCrystal kütüphanesi ile anlık uyarıları ekrana yansıtır.

* **Aktüatör Kontrolü:** Koşullar sağlandığında motorları ve LED'leri tetikler.
