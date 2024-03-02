#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdint.h>
#include <stddef.h>

#define ANSI_RED      "\033[31m"
#define ANSI_YELLOW   "\033[33m"
#define ANSI_GREEN    "\033[32m"
#define ANSI_RESET    "\033[0m"

#define PACK_VER      "1.4.0"
#define PACK_VER_CODE "140"
#define PACK_NAME     "Partition Backupper"
#define PACK_LANG     "tr"

#include "include/pbt.h"
#include "include/documentation.h"

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

/* klasik main fonksiyonu (C kitaplığı işte xd) */
int main(int argc, char *argv[]) {
#   ifdef __aarch64__
        /* boş... */
#   elif __armv8l__
        /* boş... */
#   elif __aarch32__
        /* boş... */
#   elif __armv7l__
        /* boş... */
#   else
       error("Uyumsuz mimari tespit edildi. Bu kitaplık sadece arm (32-bit yada 64-bit) mimarilerde kullanılabilir.\n");
#   endif
    /* uzun kullanımlı argümanlar için bir struct... */
    struct option long_options[] = {
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
    char *argx_target_p;
    bool use_argx_p = false;
    bool use_logical = false;
    int opt;
    /* tüm argümanları kontrol et */
    while ((opt = getopt_long(argc, argv, "p:lo:d:c:DvhL", long_options, NULL)) != -1) {
        /* argümanları işlemeye al */
        switch (opt) {
            case 'p':
                argx_target_p = strdup(optarg);
                use_argx_p = true;
                break;
            case 'l':
                verify_root();
                check_psf();
                if (pbt_logical) {
                    use_logical = true;
                } else {
                    error("Bu cihaz mantıksal bölümlere sahip değil!\n");
                }
                break;
            case 'o':
                out = strdup(optarg);
                break;
            case 'd':
                verify_root();
                check_psf();
                outdir = strdup(optarg);
                struct stat out_info;
                if (stat(outdir, &out_info) != 0) {
                    fprintf(stderr, "%s: %s: dosya veya dizin yok.\n", argv[0], outdir);
                    exit(EXIT_FAILURE);
                } else {
                    if (S_ISDIR(out_info.st_mode)) {
                        my_out = outdir;
                    } else {
                        fprintf(stderr, "%s: %s: dizin değil.\n", argv[0], outdir);
                        exit(EXIT_FAILURE);
                    }
                }
                break;
            case 'c':
                use_cust_cxt = true;
                cust_cxt = strdup(optarg);
                break;
            case 'D':
                listpart();
                exit(EXIT_SUCCESS);
                break;
            case 'v':
                printf("Sürüm: %s (kod %s)\n", PACK_VER, PACK_VER_CODE);
#               ifdef __clang__
                printf("clang %ssürümü ile derlendi.\n", __clang_version__);
#               endif
                printf("Lisansı görmek için -L seçeneğini kullanın.\n");
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
                printf("Bilgi için `%s --help' komutunu deneyin.\n", argv[0]);
                exit(EXIT_FAILURE);
                break;
            default:
                printf("Kullanım: %s -p, --partition PARTITION [-l, --logical] [-o, --out] [-d, --outdir] [-D, --list] [-v, --version] [-h, --help] [-L, --license]\n", argv[0]);
        }
    }
    verify_root();
    check_psf();
    /* özel bağlam kontrolcüsü */
    if (use_cust_cxt) {
        struct stat cxtinfo;
        printf("Özel bağlam kontrol ediliyor...\n");
        if (stat(cust_cxt, &cxtinfo) == 0) {
            if (S_ISDIR(cxtinfo.st_mode)) {
                /* boş... */
            } else {
                fprintf(stderr, "%s: %s: dizin değil.\n", argv[0], cust_cxt);
                exit(EXIT_FAILURE);
            }
        } else {
            error("Belirtilen bağlam bulunamadı!\n");
        }
        if (strstr(cust_cxt, "/dev") != 0) {
            printf("%sBu özel bağlam bir tuhaf...%s", ANSI_YELLOW, ANSI_RESET);
        }
    }
    if (use_argx_p) {
        if (use_logical) {
            backup(argx_target_p, "logical");
        } else {
            backup(argx_target_p, "classic");
        }
    } else {
        fprintf(stderr, "%s: bölüm adı gerekiyor.\nBilgi için `%s --help' komutunu deneyin.\n", argv[0], argv[0]);
        exit(EXIT_FAILURE);
    }
}

/* kodun sonu */
