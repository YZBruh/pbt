#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdint.h>
#include <stddef.h>

#include "include/common.h"
#include "include/documentation.h"

/* By YZBruh */

/*
 * Copyright 2024 YZBruh - Partition Manager
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

char *out = NULL;
char *outdir = NULL;
char *cust_cxt = NULL;
char *target_partition = NULL;
char *target_flash_file = NULL;
bool use_logical = NULL;
bool use_cust_cxt = NULL;
bool pmt_ab = false;
bool pmt_logical = false;
bool pmt_flash = false;
bool pmt_backup = false;

/* klasik main fonksiyonu (C kitaplığı işte xd) */
int main(int argc, char *argv[])
{
    /* toplam argüman sayısını kontrol et */
    if (argc < 2) {
        printf("Kullanımı: %s [-b, --backup] [-f, --flash FILE] [-p, --partition PARTITION] [-l, --logical] [-o, --out OUTNAME] [-d, --outdir OUTDIR] [-D, --list] [-v, --version] [-h, --help] [-L, --license]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* uzun kullanımlı argümanlar için bir struct... */
    struct option long_options[] = {
        {"backup", no_argument, 0, 'b'},
        {"flash", required_argument, 0, 'f'},
        {"partition", required_argument, 0, 'p'},
        {"logical", no_argument, 0, 'l'},
        {"out", required_argument, 0, 'o'},
        {"outdir", required_argument, 0, 'd'},
        {"context", required_argument, 0, 'c'},
        {"list", no_argument, 0, 'D'},
        {"version", no_argument, 0, 'v'},
        {"help", no_argument, 0, 'h'},
        {"license", no_argument, 0, 'L'},
        {0, 0, 0, 0}
    };

    static char *opt_symbol = "-";
    static char *common_symbol_rule;
    common_symbol_rule = "Bir seçeneğin ekleşik argümanını girerken başka bir seçenek tipinde argüman kullanılamaz. Kısacası kural: ekleşik argüman başında '-' olamaz.\n";
    int opt;
    /* tüm argümanları kontrol et */
    while ((opt = getopt_long(argc, argv, "bf:p:lo:d:c:DvhL", long_options, NULL)) != -1) {
        /* argümanları işlemeye al */
        switch (opt) {
            case 'b':
                pmt_backup = true;
                break;
            case 'f':
                target_flash_file = strdup(optarg);
                if (strncmp(target_flash_file, opt_symbol, 1) == 0) {
                    error(common_symbol_rule);
                }
                pmt_flash = true;
                check_root();
                check_psf();
                struct stat flashf_info;
                if (stat(target_flash_file, &flashf_info) != 0) {
                    fprintf(stderr, "%s: %s: dosya veya dizin yok.\n", argv[0], target_flash_file);
                    exit(EXIT_FAILURE);
                } else {
                    if (!S_ISREG(flashf_info.st_mode)) {
                        fprintf(stderr, "%s: %s: bu bir dosya değil.\n", argv[0], target_flash_file);
                        exit(EXIT_FAILURE);
                    }
                }
                break;
            case 'p':
                target_partition = strdup(optarg);
                if (strncmp(target_partition, opt_symbol, 1) == 0) {
                    error(common_symbol_rule);
                }
                break;
            case 'l':
                check_root();
                check_psf();
                if (pmt_logical) {
                    use_logical = true;
                } else {
                    error("Bu cihaz mantıksal bölümlere sahip değil!\n");
                }
                break;
            case 'o':
                out = strdup(optarg);
                if (strncmp(out, opt_symbol, 1) == 0) {
                    error(common_symbol_rule);
                }
                break;
            case 'd':
                outdir = strdup(optarg);
                if (strncmp(outdir, opt_symbol, 1) == 0) {
                    error(common_symbol_rule);
                }
                check_root();
                check_psf();
                struct stat out_info;
                if (stat(outdir, &out_info) != 0) {
                    fprintf(stderr, "%s: %s: dosya veya dizin yok.\n", argv[0], outdir);
                    exit(EXIT_FAILURE);
                } else {
                    if (!S_ISDIR(out_info.st_mode)) {
                        fprintf(stderr, "%s: %s: bu bir dizin değil.\n", argv[0], outdir);
                        exit(EXIT_FAILURE);
                    }
                }
                break;
            case 'c':
                use_cust_cxt = true;
                cust_cxt = strdup(optarg);
                if (strncmp(cust_cxt, opt_symbol, 1) == 0) {
                    error(common_symbol_rule);
                }
                break;
            case 'D':
                check_root();
                listpart();
                exit(EXIT_SUCCESS);
                break;
            case 'v':
                printf("Versiyon: %s (kod %s)\n", PACK_VER, PACK_VER_CODE);
#               ifdef __clang__
                    printf("Derleyici: clang %s", __clang_version__);
#               endif
#               ifdef __GNUC__
                    printf("(GNUC %d.%d.%d)\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#               else
                    printf("\n");
#               endif
                printf("-L argümanını kullanarak lisansları görüntüleyebilirsiniz.\n");
                exit(EXIT_SUCCESS);
                break;
            case 'h':
                help();
                exit(EXIT_SUCCESS);
                break;
            case 'L':
                licenses();
                exit(EXIT_SUCCESS);
                break;
            case '?':
                printf("`%s --help' komutu ile daha fazla bilgi edinebilirsiniz.\n", argv[0]);
                exit(EXIT_FAILURE);
                break;
            default:
                printf("Kullanımı: %s [-b, --backup] [-f, --flash FILE] [-p, --partition PARTITION] [-l, --logical] [-o, --out OUTNAME] [-d, --outdir OUTDIR] [-D, --list] [-v, --version] [-h, --help] [-L, --license]\n", argv[0]);
        }
    }

    /* ufak bir denetleme */
    if (!pmt_backup && !pmt_flash) {
        fprintf(stderr, "%s: hedef yok (yedek veya flaş).\n`%s --help` komutu ile daha fazla bilgi edinebilisiniz.\n", argv[0], argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pmt_backup && pmt_flash) {
        error("Yedek ve flaş işlemleri aynı anda kullanılamaz\n");
    }

    /* kontroller */
    check_root();
    check_psf();

    /* özel bağlam kontrolcüsü */
    if (use_cust_cxt) {
        struct stat cxtinfo;
        if (stat(cust_cxt, &cxtinfo) == 0) {
            if (S_ISDIR(cxtinfo.st_mode)) {
                /* boş.. */
            } else {
                fprintf(stderr, "%s: özel bağlam: %s: bu bir dizin değil.\n", argv[0], cust_cxt);
                exit(EXIT_FAILURE);
            }
        } else {
            error("Belirtilen özel bağlam bulunamadı!\n");
        }
        if (strstr(cust_cxt, "/dev") == NULL) {
            printf("%sBu özel bağlam biraz tuhaf...%s\n", ANSI_YELLOW, ANSI_RESET);
        }
    }

    if (target_partition == NULL) {
        fprintf(stderr, "%s: bölüm adı gerekiyor.\n`%s --help` komutu ile daha fazla bilgi edinebilisiniz.\n", argv[0], argv[0]);
        exit(EXIT_FAILURE);
    } else {
        if (pmt_backup) {
            if (use_logical) {
                backup(target_partition, "logical");
                exit(EXIT_SUCCESS);
            } else {
                backup(target_partition, "classic");
                exit(EXIT_SUCCESS);
            }
        } else if (pmt_flash) {
            if (use_logical) {
                flash(target_partition, target_flash_file, "logical");
                exit(EXIT_SUCCESS);
            } else {
                flash(target_partition, target_flash_file, "classic");
                exit(EXIT_SUCCESS);
            }
        } else {
            fprintf(stderr, "%s: hedef yok (yedek veya flaş).\n`%s --help` komutu ile daha fazla bilgi edinebilisiniz.\n", argv[0], argv[0]);
            exit(EXIT_FAILURE);
        }
    }
}

/* kodun sonu */
