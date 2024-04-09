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
#include <getopt.h>
#include <errno.h>

#include "include/pmt.h"

char *out = NULL;
char *outdir = NULL;
char *cust_cxt = NULL;
char *target_partition = NULL;
char *target_flash_file = NULL;
bool pmt_use_logical = NULL;
bool pmt_use_cust_cxt = NULL;
bool pmt_ab = false;
bool pmt_logical = false;
bool pmt_flash = false;
bool pmt_backup = false;
bool pmt_force_mode = false;

/* classic main function (C binary here xd) */
int main(int argc, char *argv[])
{
    /* check argument total */
    if (argc < 2) {
        fprintf(stderr, "%s: missing operand\nTry `%s --help` for more information.\n", argv[0], argv[0]);
        exit(44);
    }

    /* a structure for long arguments... */
    struct option long_options[] = {
        {"backup", no_argument, 0, 'b'},
        {"flash", required_argument, 0, 'F'},
        {"partition", required_argument, 0, 'p'},
        {"logical", no_argument, 0, 'l'},
        {"out", required_argument, 0, 'o'},
        {"outdir", required_argument, 0, 'd'},
        {"context", required_argument, 0, 'c'},
        {"list", no_argument, 0, 'D'},
        {"force", no_argument, 0, 'f'},
        {"version", no_argument, 0, 'v'},
        {"help", no_argument, 0, 0},
        {"license", no_argument, 0, 'L'},
        {0, 0, 0, 0}
    };

    static char *opt_symbol = "-";
    static char *common_symbol_rule;
    common_symbol_rule = "When entering the attached argument of an option, an argument of another option type cannot be used. In short, the rule is: there can be no '-' at the beginning of the attached argument.\n";
    int opt;
    /* control for each argument */
    while ((opt = getopt_long(argc, argv, "bF:p:lo:d:c:DfvL", long_options, NULL)) != -1) {
        /* process arguments */
        switch (opt) {
            case 'b':
                pmt_backup = true;
                break;
            case 'F':
                target_flash_file = strdup(optarg);
                if (strncmp(target_flash_file, opt_symbol, 1) == 0) {
                    if (!pmt_force_mode) {
                        error(common_symbol_rule, 19);
                    } else {
                        exit(19);
                    }
                }
                pmt_flash = true;
                check_root();
                check_psf();
                struct stat flashf_info;
                if (stat(target_flash_file, &flashf_info) != 0) {
                    if (!pmt_force_mode) {
                        fprintf(stderr, "%s: %s: %s\n", argv[0], target_flash_file, strerror(errno));
                        exit(15);
                    } else {
                        exit(15);
                    }
                } else {
                    if (!S_ISREG(flashf_info.st_mode)) {
                        if (!pmt_force_mode) {
                            fprintf(stderr, "%s: %s: is a not file.\n", argv[0], target_flash_file);
                            exit(16);
                        } else {
                            exit(16);
                        }
                    }
                }
                break;
            case 'p':
                target_partition = strdup(optarg);
                if (strncmp(target_partition, opt_symbol, 1) == 0) {
                    if (!pmt_force_mode) {
                        error(common_symbol_rule, 19);
                    } else {
                        exit(19);
                    }
                }
                break;
            case 'l':
                check_root();
                check_psf();
                if (pmt_logical) {
                    pmt_use_logical = true;
                } else {
                    if (!pmt_force_mode) {
                        error("This device does not have logical partitions!\n", 17);
                    } else {
                        exit(17);
                    }
                }
                break;
            case 'o':
                out = strdup(optarg);
                if (strncmp(out, opt_symbol, 1) == 0) {
                    if (!pmt_force_mode) {
                        error(common_symbol_rule, 19);
                    } else {
                        exit(19);
                    }
                }
                break;
            case 'd':
                outdir = strdup(optarg);
                if (strncmp(outdir, opt_symbol, 1) == 0) {
                    if (!pmt_force_mode) {
                        error(common_symbol_rule, 19);
                    } else {
                        exit(19);
                    }
                }
                check_root();
                check_psf();
                struct stat out_info;
                if (stat(outdir, &out_info) != 0) {
                    if (!pmt_force_mode) {
                        fprintf(stderr, "%s: %s: %s\n", argv[0], outdir, strerror(errno));
                        exit(18);
                    } else {
                        exit(18);
                    }
                } else {
                    if (!S_ISDIR(out_info.st_mode)) {
                        if (!pmt_force_mode) {
                            fprintf(stderr, "%s: %s: is a not directory.\n", argv[0], outdir);
                            exit(20);
                        } else {
                            exit(20);
                        }
                    }
                }
                break;
            case 'c':
                pmt_use_cust_cxt = true;
                cust_cxt = strdup(optarg);
                if (strncmp(cust_cxt, opt_symbol, 1) == 0) {
                    if (!pmt_force_mode) {
                        error(common_symbol_rule, 19);
                    } else {
                        exit(19);
                    }
                }
                break;
            case 'D':
                check_root();
                listpart();
                exit(EXIT_SUCCESS);
                break;
            case 'f':
                pmt_force_mode = true;
                break;
            case 'v':
                printf("Version: %s (code %s)\n", PMT_VERSION, PMT_VERSION_CODE);
                #ifdef __clang__
                    printf("Compiler: clang %s", __clang_version__);
                #endif
                #ifdef __GNUC__
                    printf("(GNUC %d.%d.%d)\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
                #else
                    printf("\n");
                #endif
                printf("See licenses with -L argument.\n");
                exit(EXIT_SUCCESS);
                break;
            case 0:
                help();
                exit(EXIT_SUCCESS);
                break;
            case 'L':
                licenses();
                exit(EXIT_SUCCESS);
                break;
            case '?':
                printf("Try `%s --help' for more information.\n", argv[0]);
                exit(43);
                break;
            default:
                printf("Usage: %s [-b | --backup] [-f | --flash FILE] [-p | --partition PARTITION] [-l | --logical] [-o | --out OUTNAME] [-d | --outdir OUTDIR] [-c | --context] [-D | --list] [-v | --version] [--help] [-L | --license]\n", argv[0]);
                exit(44);
        }
    }

    /* minor checks */
    if (!pmt_backup && !pmt_flash) {
        fprintf(stderr, "%s: missing operand.\nTry `%s --help` for more information.\n", argv[0], argv[0]);
        exit(3);
    }

    if (pmt_backup && pmt_flash) {
        if (!pmt_force_mode) {
            error("Backup and flash functions cannot be used in the same command\n", 9);
        } else {
            exit(9);
        }
    }

    /* checks */
    check_root();
    check_psf();

    /* custom context checker */
    if (pmt_use_cust_cxt) {
        struct stat cxtinfo;
        if (stat(cust_cxt, &cxtinfo) == 0) {
            if (!S_ISREG(cxtinfo.st_mode)) {
                if (!pmt_force_mode) {
                    fprintf(stderr, "%s: %s: is a not directory.\n", argv[0], cust_cxt);
                    exit(8);
                } else {
                    exit(8);
                }
            }
        } else {
            if (!pmt_force_mode) {
                fprintf(stderr, "%s: %s: %s\n", argv[0], cust_cxt, strerror(errno));
                exit(6);
            } else {
                exit(6);
            }
        }
        if (strstr(cust_cxt, "/dev") == NULL && !pmt_force_mode) {
            printf("%sThis custom context is strange...%s\n", ANSI_YELLOW, ANSI_RESET);
        }
    }

    if (target_partition == NULL) {
        if (!pmt_force_mode) {
            fprintf(stderr, "%s: required partition name.\nTry `%s --help' for more information.\n", argv[0], argv[0]);
            exit(5);
        } else {
            exit(5);
        }
    } else {
        if (pmt_backup) {
            if (pmt_use_logical) {
                backup(target_partition, "logical");
                exit(EXIT_SUCCESS);
            } else {
                backup(target_partition, "classic");
                exit(EXIT_SUCCESS);
            }
        } else if (pmt_flash) {
            if (pmt_use_logical) {
                flash(target_partition, target_flash_file, "logical");
                exit(EXIT_SUCCESS);
            } else {
                flash(target_partition, target_flash_file, "classic");
                exit(EXIT_SUCCESS);
            }
        } else {
            fprintf(stderr, "%s: no target (backup or flash).\nTry `%s --help` for more information.\n", argv[0], argv[0]);
            exit(3);
        }
    }
}

#ifdef __cplusplus
}
#endif

/* end of code */
