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
#define PACK_LANG     "en"

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

/* classic main function (C binary here xd) */
int main(int argc, char *argv[]) {
#   ifdef __aarch64__
        /* empty */
#   elif __armv8l__
        /* empty */
#   elif __aarch32__
        /* empty */
#   elif __armv7l__
        /* empty */
#   else
       error("Incompatible architecture was detected. This binary works with only arm (32-bit or 64-bit).\n");
#   endif
    /* a structure for long arguments... */
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
    /* control for each argument */
    while ((opt = getopt_long(argc, argv, "p:lo:d:c:DvhL", long_options, NULL)) != -1) {
        /* process arguments */
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
                    error("This device does not have logical partitions!\n");
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
                    fprintf(stderr, "%s: %s: no such file or directory.\n", argv[0], outdir);
                    exit(EXIT_FAILURE);
                } else {
                    if (S_ISDIR(out_info.st_mode)) {
                        my_out = outdir;
                    } else {
                        fprintf(stderr, "%s: %s: is a not directory.\n", argv[0], outdir);
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
                printf("Version: %s (code %s)\n", PACK_VER, PACK_VER_CODE);
#               ifdef __clang__
                printf("Compiled by clang version %s\n", __clang_version__);
#               endif
                printf("See licenses with -L argument.\n");
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
                printf("Try `%s --help' for more information.\n", argv[0]);
                exit(EXIT_FAILURE);
                break;
            default:
                printf("Usage: %s -p, --partition PARTITION [-l, --logical] [-o, --out] [-d, --outdir] [-D, --list] [-v, --version] [-h, --help] [-L, --license]\n", argv[0]);
        }
    }
    verify_root();
    check_psf();
    /* custom context checker */
    if (use_cust_cxt) {
        struct stat cxtinfo;
        printf("Checking custom context path...\n");
        if (stat(cust_cxt, &cxtinfo) == 0) {
            if (S_ISDIR(cxtinfo.st_mode)) {
                /* empty */
            } else {
                fprintf(stderr, "%s: %s: is a not directory.\n", argv[0], cust_cxt);
                exit(EXIT_FAILURE);
            }
        } else {
            error("The specified context was not found!\n");
        }
        if (strstr(cust_cxt, "/dev") != 0) {
            printf("%sThis custom context is strange...%s", ANSI_YELLOW, ANSI_RESET);
        }
    }
    if (use_argx_p) {
        if (use_logical) {
            backup(argx_target_p, "logical");
        } else {
            backup(argx_target_p, "classic");
        }
    } else {
        fprintf(stderr, "%s: required partition name.\nTry `%s --help' for more information.\n", argv[0], argv[0]);
        exit(EXIT_FAILURE);
    }
}

/* end of code */
