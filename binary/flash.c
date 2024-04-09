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

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>

#include "include/pmt.h"

extern char *cust_cxt;
extern bool pmt_use_cust_cxt;
extern bool pmt_force_mode;

/* flasher func */
void flash(char *target_flash_partition, char *target_file, char *flash_partition_style)
{
    static char flasher_path[200];
    /* determine device block */
    /* for classic */
    if (strstr(flash_partition_style, "classic") != NULL) {
        if (pmt_use_cust_cxt) {
            sprintf(flasher_path, "%s/%s", cust_cxt, target_flash_partition);
        } else {
            sprintf(flasher_path, "/dev/block/by-name/%s", target_flash_partition);
        }
    /* for logical */
    } else if (strstr(flash_partition_style, "logical") != NULL) {
        sprintf(flasher_path, "/dev/block/mapper/%s", target_flash_partition);
    } else {
        if (!pmt_force_mode) {
            error("İnvalid partition type!\n", 30);
        } else {
            exit(30);
        }
    }

    /* check partition */
    if (access(flasher_path, F_OK) == -1) {
        if (!pmt_force_mode) {
            error("Partition not found!\n", 31);
        } else {
            exit(31);
        }
    }

    /* setting up */
    static char flasher_cmd[256];
    sprintf(flasher_cmd, "dd if=%s of=%s status=none", target_file, flasher_path);

    /* start flash */
    if (system(flasher_cmd) != 0) {
        if (!pmt_force_mode) {
            error("Failed!\n", 98);
        } else {
            exit(98);
        }
    }
}

#ifdef __cplusplus
}
#endif

/* end of code */
