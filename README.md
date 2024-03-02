## Partition Backupper (pbt)

Bu ikili statik C kitaplığı android cihazların bölümlerini yedeklemek içindir.
Bir çok seçenek sunar. Bunlara aşşağıda yer vereceğim. Ama önce işleyişten bahsedeyim...

```
1. Bölüm adı elde edilir (-p veya --partition argümanı ile)
2. Diğer argümanlar (kullanılmış ise) işlenir.
3. DD kullanarak yedeklenir. İlerleyiş sorun olmaz ise verilmez (DD)
```

#### Sunulan argümanlar (seçenekler)

```
Kullanımı (argümanlar):
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
   -p boot_a -o boot_slot_a_image -d /sdcard/backup -c /dev/block/platform/bootdevice/by-name

Örnek 2:
   -c /dev/block/platform/bootdevice/by-name --list

Hataları bildirin: <xda-@YZBruh>
```

Mesela `boot_a` bölümünü yedeklemek istersek: `pbt -p boot_a` (eğer farklı adda ise komutu düzenleyin).

#### Bazı notlar
- İstediğiniz soruları sormaktan çekinmeyin.
- Paketler yayınlarda mevcuttur.
- `-p` | `--partition` argümanını kullanmak zorunludur. Sonuçta yedeklenecek bir bölüm adı gerekli.
- Eğer mantıksal bölüm bayrağı kullanılmaz ise varsayılan olarak klasik bir bölûm yedeklenmeye çalışılır.
- Önerilerinizi bildirin!

### Nasıl inşa edilir?

pbt'yi inşa etmek için termux bile yeterlidir. Veya isterseniz linux ile derleyebilirsiniz. NOT: Derlemek istediğiniz mimariye göre özel bir gcc kullanın.

Eğer bir şeyleri değiştirmek istiyorsanız konfigrasyona göz atın. Onu değiştirebilirsiniz.
`mka` klasörü içinde bulunur. Adı `config.mk`. Dosya içinde bilgileri verdim. Daha fazlasını sorabilirsiniz.

İnşa etmek için;
```
make
```

Özel `make` komutları (pbt sunar :) ;
```
--------- Partition Backupper yardım ---------

 Komutlar;
    make                 ==> Partition Backupper inşasını başlatın.
    make clean           ==> Dosyaları temizle (İnşa edilmiş kitaplık silinmez)
    make clean-all       ==> Dosyaları temizle (İnşa edilmiş kitaplık silinir)
    make install-termux  ==> Eğer termux kullanıyor ve mimariniz uygun ise ptb'yi termux'a kurar.
    make help            ==> Bu yardım mesajını göster.
```

Ben termux ile derledim :D. Neden uğraşayımki... `GCC 17.0.6` ile derledim. Sürüm görme seçeneği ile bakabilirsiniz :)
