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

extern bool use_cust_cxt;
extern bool pmt_ab;
extern bool pmt_logical;
extern char *cust_cxt;

/* check parts */
void check_psf()
{
    /* true = ab | false = a */
    if (use_cust_cxt) {
        static char cust_cxt_ck_path[150];
        sprintf(cust_cxt_ck_path, "%s/boot_a", cust_cxt);
        if (access(cust_cxt_ck_path, F_OK) != 0) {
            pmt_ab = false;
        } else {
            pmt_ab = true;
        }
    } else {
        if (access("/dev/block/by-name/boot_a", F_OK) != 0) {
            pmt_ab = false;
        } else {
            pmt_ab = true;
        }
    }
    
    /* true = logical | false = classic */
    if (use_cust_cxt) {
        static char cust_cxt_ckl_path[150];
        sprintf(cust_cxt_ckl_path, "%s/super", cust_cxt);
        if (access(cust_cxt_ckl_path, F_OK) != 0) {
            pmt_logical = false;
        } else {
            pmt_logical = true;
        }
    } else {
        if (access("/dev/block/by-name/super", F_OK) != 0) {
            pmt_logical = false;
        } else {
            pmt_logical = true;
        }
    }
}

/* root checker function */
void check_root()
{
    /* a quick, easy method to verify root :D */
    if (chdir("/dev/block") != 0) {
        error("Root privileges could not be detected! Please run this binary with root.\n");
    }
}

/* end of code */
