## Partition Manager (pmt)

Bu ikili statik C kitaplığı android cihazların bölümlerini kontrol etmek içindir.
Bir çok seçenek sunar. Bunlara aşşağıda yer vereceğim. Ama önce işleyişten bahsedeyim...

```
1. Bölüm adı elde edilir (-p veya --partition argümanı ile)
2. Diğer argümanlar (kullanılmış ise) işlenir.
3. DD kullanarak yedeklenir. İlerleyiş sorun olmaz ise verilmez (DD)
```

#### Sunulan argümanlar (seçenekler)

```
Kullanımı (argümanlar):
   -b, --backup      yedek modu
   -f, --flash       flaş modu
   -p, --partition   yedeklenecek olan bölümün adı
   -l, --logical     yedeklenecek olan bölüm eğer mantıksal ise bu bayrağı kullanın
   -o, --out         yedeklenen bölümün dosya adını belirtin (varsayılan: bölüm adı)
   -d, --outdir      yedeklenecek olan bölümün kaydedileceği dizin (varsayılan: /storage/emulated/0)
   -c, --context     eğer özel bir /dev bağlamı kullanmak isterseniz bu argümanı kullanın. Sadece klasik bölümlerde kullanılabilir (varsayılan: /dev/block/by-name)
   -D, --list        bölümleri listeler
   -v, --version     versiyonu görüntüle
   -h, --help        yardım mesajını görüntüle
   -L, --license     lisanları görüntüle

Örnek 1:
   -b --partition boot_a -o boot_slot_a_image -d /sdcard/backup -c /dev/block/platform/bootdevice/by-name

Örnek 2:
   --flash /sdcard/twrp/boot.img -p boot_a -c /dev/block/platform/bootdevice/by-name

Örnek 3:
   -c /dev/block/platform/bootdevice/by-name --list

Hataları bildirin: <xda-@YZBruh>
```

#### Bazı notlar
- İstediğiniz soruları sormaktan çekinmeyin.
- Paketler yayınlarda mevcuttur.
- `-b` | `--backup` veya `-f` | `--flash` ve `-p` | `--partition` argümanlarının kullanılması zorunludur. Sonuçta, ilerleme olması için bir bölüm adı ve ilerleme türü gerekir.
- Eğer mantıksal bölüm bayrağı kullanılmaz ise varsayılan olarak klasik bir bölûm ile çalışılır.
- [Özel sürüm değişikliklerini görmek için tıklayın](https://github.com/YZBruh/pbt/blob/1.5.0-tr/CHANGELOG.md)
- Önerilerinizi bildirin!

### Nasıl inşa edilir?

pmt'yi inşa etmek için termux bile yeterlidir. Veya isterseniz linux ile derleyebilirsiniz. NOT: Derlemek istediğiniz mimariye göre özel bir gcc kullanın.

Eğer bir şeyleri değiştirmek istiyorsanız konfigrasyona göz atın. Onu değiştirebilirsiniz.
`mka` klasörü içinde bulunur. Adı `config.mk`. Dosya içinde bilgileri verdim. Daha fazlasını sorabilirsiniz.

İnşa etmek için;
```
make
```

Özel `make` komutları (pmt sunar :) ;
```
--------- Partition Manager yardım ---------

 Komutlar;
    make                 ==> Partition Backupper inşasını başlatın.
    make clean           ==> Dosyaları temizle (İnşa edilmiş kitaplık silinmez)
    make clean-all       ==> Dosyaları temizle (İnşa edilmiş kitaplık silinir)
    make install-termux  ==> Eğer termux kullanıyor ve mimariniz uygun ise pmt'yi termux'a kurar.
    make help            ==> Bu yardım mesajını göster.
```

Ben termux ile derledim :D. Neden uğraşayımki... `GCC 17.0.6` ile derledim. Sürüm görme seçeneği ile bakabilirsiniz :)
