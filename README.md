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

#### Bazı notlar
- İstediğiniz soruları sormaktan çekinmeyin.
- `-p` | `--partition` argümanını kullanmak zorunludur. Sonuçta yedeklenecek bir bölüm adı gerekli.
- Eğer mantıksal bölüm bayrağı kullanılmaz ise varsayılan olarak klasik bir bölûm yedeklenmeye çalışılır.
- Önerilerinizi bildirin!
