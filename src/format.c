/* By YZBruh */

/*
 * Copyright 2024 Partition Manager
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
#include <sys/statvfs.h>
#include <string.h>
#include <stdbool.h>

#include "include/pmt.h"

extern char *format_fs;
extern char *cust_cxt;
extern bool pmt_use_cust_cxt;
extern bool pmt_force_mode;

void format(char *target_format_partition, char *format_partition_style)
{
    /* generate partition extn */
    static char ppath[100];
    if (strstr(format_partition_style, "classic") != NULL)
    {
        if (pmt_use_cust_cxt)
        {
            sprintf(ppath, "%s/%s", cust_cxt, target_format_partition);
        } else {
            sprintf(ppath, "/dev/block/by-name/%s", target_format_partition);
        }
    /* for logical */
    } else if (strstr(format_partition_style, "logical") != NULL)
    {
        sprintf(ppath, "/dev/block/mapper/%s", target_format_partition);
    } else {
        if (!pmt_force_mode)
        {
            error("İnvalid partition type!\n", 30);
        } else {
            exit(49);
        }
    }

    /* check partition */
    if (access(ppath, F_OK) == -1)
    {
        if (!pmt_force_mode)
        {
            error("Partition not found!\n", 31);
        } else {
            exit(31);
        }
    }

    /* get target partition block size */
    struct statvfs file_sys_inf;
    if (statvfs(ppath, &file_sys_inf) != 0)
    {
        if (!pmt_force_mode)
        {
            fprintf(stderr, "The partition block size could not be obtained!\n");
            exit(49);
        } else {
            exit(49);
        }
    }

    /* generate mke2fs command */
    static char formatter_cmd[200];
    sprintf(formatter_cmd, "mke2fs -Fq -t %s -b %lu %s", format_fs, file_sys_inf.f_bsize, ppath);

    /* run command */
    if (system(formatter_cmd) != 0)
    {
        if (!pmt_force_mode)
        {
            error("Formatting failed! There may be a chance that something has been damaged!\n", 71);
        } else {
            exit(71);
        }
    }
}

#ifdef __cplusplus
}
#endif

/* end of code */
