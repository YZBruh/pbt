#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "include/common.h"

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

extern char *cust_cxt;
extern bool use_cust_cxt;
extern bool pmt_ab;
extern bool pmt_logical;

/* mevcut bölümleri yazdır */
void listpart() {
    if (use_cust_cxt) {
        printf("Klasik bölümlerin listesi (%s): \n", cust_cxt);
        static char cust_cxt_path[150];
        sprintf(cust_cxt_path, "ls %s", cust_cxt);
        if (system(cust_cxt_path) != 0) {
            error("Bölümler listelenirken bir hata oluştu!\n");
        }
    } else {
        printf("Klasik bölümlerin listesi (/dev/block/by-name): \n");
        if (system("ls /dev/block/by-name") != 0) {
            error("Bölümler listelenirken bir hata oluştu!\n");
        }
    }

    if (pmt_logical) {
        printf("Mantıksal bölümlerin listesi (/dev/block/mapper): \n");
        if (system("ls /dev/block/mapper") != 0) {
            error("Bölümler listelenirken bir hata oluştu!\n");
        }
    }

    if (pmt_ab) {
        printf("%sUyarı: cihaz A/B bölüm stilini kullanıyor.%s\n", ANSI_YELLOW, ANSI_RESET);
    }

    if (pmt_logical) {
        printf("%sUyarı: cihaz mantıksal bölüm tipini kullanıyor.%s\n", ANSI_YELLOW, ANSI_RESET);
    }
}

/* end of code */
