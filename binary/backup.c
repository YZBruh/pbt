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

extern char *out;
extern char *outdir;
extern char *cust_cxt;
extern bool use_logical;
extern bool use_cust_cxt;

/* backupper func */
void backup(char *target_backup_partition, char *backup_partition_style)
{
    static char backupper_path[200];
    if (strstr(backup_partition_style, "classic") != NULL) {
        if (use_cust_cxt) {
            sprintf(backupper_path, "%s/%s", cust_cxt, target_backup_partition);
        } else {
            sprintf(backupper_path, "/dev/block/by-name/%s", target_backup_partition);
        }
    } else if (strstr(backup_partition_style, "logical") != NULL) {
        sprintf(backupper_path, "/dev/block/mapper/%s", target_backup_partition);
    } else {
        error("İnvalid partition type!\n");
    }

    if (access(backupper_path, F_OK) == -1) {
        error("Partition not found!\n");
    } else {
        printf("Target partition: %s\nBackupping...\n", target_backup_partition);
    }

    static char backupper_cmd[256];
    if (outdir != NULL) {
        if (out != NULL) {
            sprintf(backupper_cmd, "dd if=%s of=%s/%s.img status=none", backupper_path, outdir, out);
        } else {
            sprintf(backupper_cmd, "dd if=%s of=%s/%s.img status=none", backupper_path, outdir, target_backup_partition);
        }
    } else {
        if (out != NULL) {
            sprintf(backupper_cmd, "dd if=%s of=/storage/emulated/0/%s.img status=none", backupper_path, out);
        } else {
            sprintf(backupper_cmd, "dd if=%s of=/storage/emulated/0/%s.img status=none", backupper_path, target_backup_partition);
        }
    }

    if (system(backupper_cmd) != 0) {
        error("Failed!\n");
    } else {
        if (outdir != NULL) {
            if (out != NULL) {
                printf("%sSuccess. Output: %s/%s.img%s\n", ANSI_GREEN, outdir, out, ANSI_RESET);
            } else {
                printf("%sSuccess. Output: %s/%s.img%s\n", ANSI_GREEN, outdir, target_backup_partition, ANSI_RESET);
            }
        } else {
            if (out != NULL) {
                printf("%sSuccess. Output: /storage/emulated/0/%s.img%s\n", ANSI_GREEN, out, ANSI_RESET);
            } else {
                printf("%sSuccess. Output: /storage/emulated/0/%s.img%s\n", ANSI_GREEN, target_backup_partition, ANSI_RESET);
            }
        }
        
    }
}

/* end of code */
