#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

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

/* flasher func */
void flash(char *target_flash_partition, char *target_file, char *flash_partition_style)
{
    static char flasher_path[200];
    /* determine device block */
    /* for classic */
    if (strstr(flash_partition_style, "classic") != NULL) {
        if (use_cust_cxt) {
            sprintf(flasher_path, "%s/%s", cust_cxt, target_flash_partition);
        } else {
            sprintf(flasher_path, "/dev/block/by-name/%s", target_flash_partition);
        }
    /* for logical */
    } else if (strstr(flash_partition_style, "logical") != NULL) {
        sprintf(flasher_path, "/dev/block/mapper/%s", target_flash_partition);
    } else {
        error("İnvalid partition type!\n");
    }

    /* check partition */
    if (access(flasher_path, F_OK) == -1) {
        error("Partition not found!\n");
    } else {
        printf("Target partition: %s\nFlashing...\n", target_flash_partition);
    }

    /* setting up */
    static char flasher_cmd[256];
    sprintf(flasher_cmd, "dd if=%s of=%s status=none", target_file, flasher_path);

    /* start flash */
    if (system(flasher_cmd) != 0) {
        error("Failed!\n");
    } else {
        printf("%sSuccess.%s\n", ANSI_GREEN, ANSI_RESET);
    }
}

/* end of code */
