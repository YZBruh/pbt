#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "include/common.h"

/* By YZBruh */

/*
 *         _      _   
 *        | |    | |  
 *  _ __  | |__  | |_ 
 * | '_ \ | '_ \ | __|
 * | |_) || |_) || |_ 
 * | .__/ |_.__/  \__|
 * | |                
 * |_|                
 *
 */

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

void backup(char *target_pt, char *pst)
{
    if (strstr(pst, "classic") != NULL) {
        if (use_cust_cxt) {
            sprintf(path, "%s/%s", cust_cxt, target_pt);
        } else {
            sprintf(path, "/dev/block/by-name/%s", target_pt);
        }
    } else if (strstr(pst, "logical") != NULL) {
        sprintf(path, "/dev/block/mapper/%s", target_pt);
    } else {
        error("İnvalid partition type!\n");
    }
    if (access(path, F_OK) == -1) {
        error("Partition not found!\n");
    } else {
        printf("Target partition: %s\nBackupping...\n", target_pt);
    }
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
                printf("%sSuccess. Output: %s/%s.img%s\n", ANSI_GREEN, my_out, out, ANSI_RESET);
            } else {
                printf("%sSuccess. Output: %s/%s.img%s\n", ANSI_GREEN, my_out, target_pt, ANSI_RESET);
            }
        } else {
            if (out != NULL) {
                printf("%sSuccess. Output: /storage/emulated/0/%s.img%s\n", ANSI_GREEN, out, ANSI_RESET);
            } else {
                printf("%sSuccess. Output: /storage/emulated/0/%s.img%s\n", ANSI_GREEN, target_pt, ANSI_RESET);
            }
        }
    }
}
