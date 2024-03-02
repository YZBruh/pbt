#ifndef _DOCUMENTATION_H_
#define _DOCUMENTATION_H_

/* By YZBruh */

/*
 * Copyright 2024 YZBruh - Partition Backupper
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

void licenses() {
    printf("Copyright 2024 YZBruh - Partition Backupper\n");
    printf("Licensed under the Apache License, Version 2.0 (the \"License\");\n");
    printf("you may not use this file except in compliance with the License.\n");
    printf("You may obtain a copy of the License at\n\n");
    printf("    http://www.apache.org/licenses/LICENSE-2.0\n\n");
    printf("Unless required by applicable law or agreed to in writing, software\n");
    printf("distributed under the License is distributed on an \"AS IS\" BASIS,\n");
    printf("WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n");
    printf("See the License for the specific language governing permissions and limitations under the License.\n");
}

void help() {
    printf("Kullanımı (argümanlar): \n");
    printf("   -p, --partition   yedeklenecek olan bölümün adı\n");
    printf("   -l, --logical     yedeklenecek olan bölüm eğer mantıksal ise bu bayrağı kullanın\n");
    printf("   -o, --out         yedeklenen bölümün dosya adını belirtin (varsayılan: bölüm adı)\n");
    printf("   -d, --outdir      yedeklenecek olan bölümün kaydedileceği dizin (varsayılan: /storage/emulated/0)\n");
    printf("   -c, --context     eğer özel bir /dev bağlamı kullanmak isterseniz bu argümanı kullanın. Sadece klasik bölümlerde kullanılabilir (varsayılan: /dev/block/by-name)\n");
    printf("   -D, --list        bölümleri listeler\n");
    printf("   -v, --version     versiyonu görüntüle\n");
    printf("   -h, --help        yardım mesajını görüntüle\n");
    printf("   -L, --license     lisanları görüntüle\n\n");
    printf("Örnek 1:\n");
    printf("   -p boot_a -o boot_slot_a_image -d /sdcard/backup -c /dev/block/platform/bootdevice/by-name\n\n");
    printf("Örnek 2:\n");
    printf("   -c /dev/block/platform/bootdevice/by-name --list\n\n");
    printf("Hataları bildirin: <xda-@YZBruh>\n");
}

/* kodun sonu */

#endif
