/* By YZBruh */

/**
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

#if defined(__cplusplus)
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <err.h>
#include <sysexits.h>
#include <dirent.h>
#include <string.h>
#include <pmt.h>

extern bool pmt_use_cust_cxt;
extern bool pmt_ab;
extern bool pmt_logical;
extern bool pmt_silent;
extern bool pmt_force_mode;
extern char* cust_cxt;
extern char* bin_name;

/* list existing partitions */
int listpart(void) {
    DIR *dir;
    struct dirent *entry;

    if (pmt_use_cust_cxt)
    {
        dir = opendir(cust_cxt);
        if (dir == NULL)
        {
            if (!pmt_force_mode) errx(EX_OSFILE, "could not open: `%s': %s", cust_cxt, strerror(errno));
            else return EX_OSFILE;
        }
    }
    else
    {
        dir = opendir("/dev/block/by-name");
        if (dir == NULL)
        {
            if (!pmt_force_mode) errx(EX_OSFILE, "could not open: `/dev/block/by-name': %s", strerror(errno));
            else return EX_OSFILE;
        }
    }

    while ((entry = readdir(dir)) != NULL) printf("%s\n", entry->d_name);

    closedir(dir);

    if (pmt_logical)
    {
        dir = opendir("/dev/block/mapper");

        if (dir == NULL) 
        {
            if (!pmt_silent) errx(EX_OSFILE, "could not open: `/dev/block/mapper': %s", strerror(errno));
            else return EX_OSFILE;
        }
        else printf("List of logical partitions (`/dev/block/mapper'):\n");
    }

    while ((entry = readdir(dir)) != NULL) printf("%s\n", entry->d_name);

    closedir(dir);

    if (pmt_ab && !pmt_silent) warnx(ANSI_YELLOW "warning: device using A/B partition style." ANSI_RESET);

    if (pmt_logical && !pmt_silent) warnx(ANSI_YELLOW "warning: device using logical partition type." ANSI_RESET);

    return EX_OK;
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* end of code */