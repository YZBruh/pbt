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

/* list existing partitions */
void listpart() {
    if (use_cust_cxt) {
        printf("List of classic partitions (%s): \n", cust_cxt);
        static char cust_cxt_path[150];
        sprintf(cust_cxt_path, "ls %s", cust_cxt);
        if (system(cust_cxt_path) != 0) {
            error("An error occurred when the partition list appears!\n");
        }
    } else {
        printf("List of classic partitions (/dev/block/by-name): \n");
        if (system("ls /dev/block/by-name") != 0) {
            error("An error occurred when the classic partition list appears!\n");
        }
    }

    if (pmt_logical) {
        printf("List of logical partitions (/dev/block/mapper): \n");
        if (system("ls /dev/block/mapper") != 0) {
            error("An error occurred when the logical partition list appears!\n");
        }
    }

    if (pmt_ab) {
        printf("%sWarning: device using A/B partition style.%s\n", ANSI_YELLOW, ANSI_RESET);
    }

    if (pmt_logical) {
        printf("%sWarning: device using logical partition type.%s\n", ANSI_YELLOW, ANSI_RESET);
    }
}

/* end of code */
