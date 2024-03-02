#ifndef _PBT_H_
#define _PBT_H_

/* By YZBruh */

/*
 * Copyright 2024 YZBruh - Partition Packupper
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

/* fonksiyonları eklemeden önce gerekli değişkenleri belirt */
char *out;
char *outdir;
char *my_out;
char *cust_cxt;
bool use_cust_cxt = false;
bool pbt_ab = false;
bool pbt_logical = false;

/* hızlı ve basit hata mesajları önemli xd */
void error(const char *err_msg) {
    fprintf(stderr, ANSI_RED "%s" ANSI_RESET, err_msg);
    exit(EXIT_FAILURE);
}

/* cihazın ab ve mantıksal bölümlere sahip olup olmadığını kontrol et */
void check_psf() {
    /* true = ab | false = a */
    if (use_cust_cxt) {
        char cust_cxt_ckpath[150];
        sprintf(cust_cxt_ckpath, "%s/boot_a", cust_cxt);
        if (access(cust_cxt_ckpath, F_OK) != 0) {
            pbt_ab = false;
        } else {
            pbt_ab = true;
        }
    } else {
        if (access("/dev/block/by-name/boot_a", F_OK) != 0) {
            pbt_ab = false;
        } else {
            pbt_ab = true;
        }
    }
    
    /* true = mantıksal | false = klasik */
    if (use_cust_cxt) {
        char cust_cxt_cklpath[150];
        sprintf(cust_cxt_cklpath, "%s/super", cust_cxt);
        if (access(cust_cxt_cklpath, F_OK) != 0) {
            pbt_logical = false;
        } else {
            pbt_logical = true;
        }
    } else {
        if (access("/dev/block/by-name/super", F_OK) != 0) {
            pbt_logical = false;
        } else {
            pbt_logical = true;
        }
    }
}

/* bölüm listeleme özelliği */
void listpart() {
    if (use_cust_cxt) {
        printf("Klasik bölümlerin listesi (%s): \n", cust_cxt);
        char cust_cxt_path[150];
        sprintf(cust_cxt_path, "ls %s", cust_cxt);
        if (system(cust_cxt_path) != 0) {
            error("Klasik bölümlerin listesi görüntülenirken bir hata oluştu!\n");
        }
    } else {
        printf("Klasik bölümlerin listesi (/dev/block/by-name): \n");
        if (system("ls /dev/block/by-name") != 0) {
            error("Klasik bölümlerin listesi görüntülenirken bir hata oluştu!\n");
        }
    }
    
    if (pbt_logical) {
        printf("Mantıksal bölümlerin listesi (/dev/block/mapper): \n");
        if (system("ls /dev/block/mapper") != 0) {
            error("Mantıksal bölümlerin listesi görüntülenirken bir hata oluştu!\n");
        }
    }
    if (pbt_ab) {
        printf("%sUyarı: cihaz A/B bölüm stili kullanıyor.%s\n", ANSI_YELLOW, ANSI_RESET);
    }
    if (pbt_logical) {
        printf("%sUyarı: cihaz mantıksal bölüm tipine sahip.%s\n", ANSI_YELLOW, ANSI_RESET);
    }
}

/* düzgün ve sorunsuz yedek için özentili bir fonksiyon ;) */
void backup(char *target_pt, char *pst) {
    char path[200];
    if (strstr(pst, "classic") != NULL) {
        if (use_cust_cxt) {
            sprintf(path, "%s/%s", cust_cxt, target_pt);
        } else {
            sprintf(path, "/dev/block/by-name/%s", target_pt);
        }
    } else if (strstr(pst, "logical") != NULL) {
        sprintf(path, "/dev/block/mapper/%s", target_pt);
    } else {
        error("Bilinmeyen bölüm stili (mantıksal veya klasik değil)!\n");
    }
    if (access(path, F_OK) == -1) {
        error("Bölüm bulunamadı!\n");
    } else {
        printf("Hedef bölüm: %s\nYedekleniyor...\n", target_pt);
    }
    char cmd[256];
    if (my_out != NULL) {
        if (out != NULL) {
            sprintf(cmd, "dd if=%s of=%s/%s.img status=none", path, my_out, out);
        } else {
            sprintf(cmd, "dd if=%s of=%s/%s.img status=none", path, my_out, target_pt);
        }
    } else {
        if (out != NULL) {
            sprintf(cmd, "dd if=%s of=/storage/emulated/0/%s.img status=none", path, out);
        } else {
            sprintf(cmd, "dd if=%s of=/storage/emulated/0/%s.img status=none", path, target_pt);
        }
    }
    if (system(cmd) != 0) {
        error("Failed!\n");
    } else {
        if (my_out != NULL) {
            if (out != NULL) {
                printf("%sBaşarılı. Çıktı: %s/%s.img%s\n", ANSI_GREEN, my_out, out, ANSI_RESET);
            } else {
                printf("%sBaşarılı. Çıktı: %s/%s.img%s\n", ANSI_GREEN, my_out, target_pt, ANSI_RESET);
            }
        } else {
            if (out != NULL) {
                printf("%sBaşarılı. Çıktı: /storage/emulated/0/%s.img%s\n", ANSI_GREEN, out, ANSI_RESET);
            } else {
                printf("%sBaşarılı. Çıktı: /storage/emulated/0/%s.img%s\n", ANSI_GREEN, target_pt, ANSI_RESET);
            }
        }
    }
}

/* root erişimini doğrulamazsak olmaz */
void verify_root() {
    // sadece disklere erişmeyi denemek yeter bence :D
    if (chdir("/dev/block") != 0) {
        error("Root privileges could not be detected! Please run this binary with root.\n");
    }
}

/* kod sonu */

#endif
