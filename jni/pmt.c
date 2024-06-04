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

/* force use C std (if default is C++) */
#if defined(__cplusplus)
extern "C" {
#endif

/* include needed libs (headers) */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include <errno.h>
#include <err.h>
#include <sysexits.h>
#include <pmt.h>
#include <pmt-docs.h>

/* add value to variables that are added globally and are not worth */
char* out = NULL;
char* cust_cxt = NULL;
char* target_partition = NULL;
char* target_flash_file = NULL;
char* partition_type = NULL;
char* format_fs = NULL;
char* bin_name = NULL;
bool pmt_use_logical = NULL;
bool pmt_use_cust_cxt = NULL;
bool pmt_ab = false;
bool pmt_logical = false;
bool pmt_silent = false;
bool pmt_flash = false;
bool pmt_backup = false;
bool pmt_format = false;
bool pmt_force_mode = false;

/* variables for use in control of '-' expression */
static const char* opt_symbol = "-";
static const char* common_symbol_rule = "When entering the attached argument of an option, an argument of another option type cannot be used. In short, the rule is: there can be no '-' at the beginning of the attached argument.";

/**
 * He controls whether the '-' sign at 
 * the beginning of the given word
 */
static void
check_optsym(const char* _Nonnull mystring)
{
    if (strncmp(mystring, opt_symbol, 1) == 0)
    {
        if (!pmt_force_mode) errx(EX_USAGE, "%s", common_symbol_rule);
        else exit(EX_USAGE);
    }
}

/**
 * The target file is controlled by the stat function. 
 * Files, directories, links and blocks (disks) are for. 
 * If it is never found, it returns 1 value.
 * If he finds 0 value is returned. 
 * If the desired type is not in -1 value is returned.
 */
static int
search_stat(const char* _Nonnull filepath, const char* _Nonnull stype)
{
    struct stat search_stat;

    if (stat(filepath, &search_stat) != 0) return 1;

    if (strcmp(stype, "dir") == 0) 
    {
        if (S_ISDIR(search_stat.st_mode)) return 0;
        else return -1;
    }
    else if (strcmp(stype, "file") == 0)
    {
        if (S_ISREG(search_stat.st_mode)) return 0;
        else return -1;
    }
    else if (strcmp(stype, "blk") == 0)
    {
        if (S_ISBLK(search_stat.st_mode)) return 0;
        else return -1;
    }
    else if (strcmp(stype, "link") == 0)
    {
        if (S_ISLNK(search_stat.st_mode)) return 0;
        else return -1;
    }

    return 0;
}

/* classic main function (C binary here xd) */
int main(int argc, char* argv[])
{
    /* check argument total */
    if (argc < 2) errx(EX_USAGE, "missing operand\nTry `%s --help' for more information.", argv[0]);

    bin_name = argv[0];

    /* a structure for long arguments */
    struct option long_options[] = {
        {"logical", no_argument, 0, 'l'},
        {"context", required_argument, 0, 'c'},
        {"list", no_argument, 0, 'p'},
        {"silent", no_argument, 0, 's'},
        {"force", no_argument, 0, 'f'},
        {"version", no_argument, 0, 'v'},
        {"help", no_argument, 0, 0},
        {"license", no_argument, 0, 'L'},
        {0, 0, 0, 0}
    };

    /* boolean statements (only valid in this file) to distinguish. and pointer from a shortcut for the symbol rule */
    static bool wiew_help = false;
    static bool wiew_licenses = false;
    static bool wiew_version = false;
    static bool list_partitions = false;
    static bool combo_wiewers = false;
    static int search_result = 3;
    static int opt;

    /* control for each argument */
    while ((opt = getopt_long(argc, argv, "lc:psfvL", long_options, NULL)) != -1)
    {
        /* process arguments */
        switch (opt)
        {
            /* logical partitions option */
            case 'l':
                check_root();
                check_dev_point();
                if (pmt_logical) pmt_use_logical = true;
                else
                {
                    if (!pmt_force_mode) errx(EX_USAGE, "this device does not have logical partitions!");
                    else return EX_USAGE;
                }
                break;
            /* context selector option */
            case 'c':
                pmt_use_cust_cxt = true;
                cust_cxt = strdup(optarg);
                if (strncmp(cust_cxt, opt_symbol, 1) == 0)
                {
                    if (!pmt_force_mode) errx(EX_USAGE, "%s", common_symbol_rule);
                    else return EX_USAGE;
                }
                break;
            /* partition lister function */
            case 'p':
                list_partitions = true;
                /* check combo wiewer options and progress */
                if (wiew_version || wiew_help || wiew_licenses) combo_wiewers = true;
                break;
            /* force mode option */
            case 'f':
                pmt_force_mode = true;
                break;
            /* silent mode option */
            case 's':
                pmt_silent = true;
                break;
            /* version info option */
            case 'v':
                wiew_version = true;
                /* check combo wiewer options and progress */
                if (list_partitions || wiew_help || wiew_licenses) combo_wiewers = true;
                break;
            /* help message opption */
            case 0:
                wiew_help = true;
                /* check combo wiewer options and progress */
                if (wiew_version || list_partitions || wiew_licenses) combo_wiewers = true;
                break;
            /* license wiewer option */
            case 'L':
                wiew_licenses = true;
                /* check combo wiewer options and progress */
                if (wiew_version || wiew_help || list_partitions) combo_wiewers = true;
                break;
            /* for invalid options */
            case '?':
                printf("Try `%s --help' for more information.\n", argv[0]);
                return EX_USAGE;
                break;
            default:
                printf("Usage: %s [backup] flash] [format] [-l | --logical] [-c | --context] [-D | --list] [-v | --version] [--help] [-L | --license]\n", argv[0]);
                exit(EX_USAGE);
        }
    }

    /* stop the program if multiple viewer is used */
    if (combo_wiewers) errx(EX_USAGE, "multiple wiewers cannot be used at the same line.");

    /* controller to handle viewer */
    if (wiew_help)
    {
        help();
        return EX_OK;
    }
    else if (wiew_version)
    {
        version();
        return EX_OK;
    }
    else if (wiew_licenses)
    {
        licenses();
        return EX_OK;
    }
    else if (list_partitions)
    {
        check_root();
        return listpart();
    }

    /* detect target mode */
    static char arg1[20];
    sprintf(arg1, "%s", argv[1]);

    if (strcmp(arg1, "backup") == 0)
    {
        if (argc == 2)
        {
            if (!pmt_force_mode) errx(EX_USAGE, "expected backup argument 2, retrieved 0.");
            else return EX_USAGE;
        }

        target_partition = argv[2];
        if (argc != 4) out = target_partition;
        else out = argv[3];
        check_optsym(target_partition);
        check_optsym(out);

        pmt_backup = true;
    }
    else if (strcmp(arg1, "flash") == 0)
    {
        if (argc == 2)
        {
            if (!pmt_force_mode) errx(EX_USAGE, "expected flash argument 2, retrieved 0.");
            else return EX_USAGE;
        }

        if (argc == 3)
        {
            if (!pmt_force_mode) errx(EX_USAGE, "expected flash argument 2, retrieved 0.");
            else return EX_USAGE;
        }

        target_flash_file = argv[2];
        target_partition = argv[3];
        check_optsym(target_flash_file);
        check_optsym(target_partition);

        pmt_flash = true;
    }
    else if (strcmp(arg1, "format") == 0)
    {
        if (argc == 2)
        {
            if (!pmt_force_mode) errx(EX_USAGE, "expected format argument 2, retrieved 0.");
            else return EX_USAGE;
        }

        if (argc == 3)
        {
            if (!pmt_force_mode) errx(EX_USAGE, "expected format argument 2, retrieved 1.");
            else return EX_USAGE;
        }

        format_fs = argv[2];
        target_partition = argv[3];
        check_optsym(format_fs);
        check_optsym(target_partition);

        pmt_format = true;
    }

    /* target control is done */
    if (!pmt_backup && !pmt_flash && !pmt_format && !pmt_silent) errx(EX_USAGE, "missing operand.\nTry `%s --help` for more information.", argv[0]);
    else return EX_USAGE;

    /* prevent multiple mode use */
    if (pmt_backup && pmt_flash && pmt_format)
    {
        if (!pmt_force_mode) errx(EX_USAGE, "multi functions cannot be used in the same command.");
        else return EX_USAGE;
    }

    /* checks */
    check_root();
    check_dev_point();

    if (pmt_format)
    {
        if (strcmp(format_fs, "ext4") != 0 || strcmp(format_fs, "ext3") != 0 || strcmp(format_fs, "ext2") != 0)
        {
            if (!pmt_force_mode) errx(EX_USAGE, "formatter: unsupported filesystem: %s", format_fs);
            else return EX_USAGE;
        }
    }

    if (pmt_flash)
    {
        search_result = search_stat(target_flash_file, "file");

        if (search_result == 1)
        {
            if (!pmt_silent) errx(EX_UNAVAILABLE, "cannot stat `%s': %s", target_flash_file, strerror(errno));
            else return EX_UNAVAILABLE;
        }
        else if (search_result == -1)
        {
            if (!pmt_silent) errx(EX_USAGE, "`%s': is a not file.", target_flash_file);
            else return EX_USAGE;
        }
    }

    /* custom context checker */
    if (pmt_use_cust_cxt)
    {
        search_result = search_stat(cust_cxt, "dir");

        if (search_result == 1)
        {
            if (!pmt_silent) errx(EX_UNAVAILABLE, "cannot stat `%s': %s", cust_cxt, strerror(errno));
            else return EX_UNAVAILABLE;
        }
        else if (search_result == -1)
        {
            if (!pmt_silent) errx(EX_USAGE, "`%s': is a not directory.", cust_cxt);
            else return EX_USAGE;
        }

        if (strstr(cust_cxt, "/dev") == NULL && !pmt_force_mode) errx(EX_USAGE, ANSI_YELLOW "you're going through my wave? There's nothing about this /dev. Use force mode if you don't want this error." ANSI_RESET);
    }

    if (target_partition == NULL)
    {
        if (!pmt_force_mode)
        {
            if (!pmt_silent) errx(EX_USAGE, "required partition name.\nTry `%s --help' for more information.\n", argv[0]);
        }
        else return EX_USAGE;
    }
    else
    {
        /**
         * 1 = backup mode 
         * 
         * 2 = flash mode 
         * 
         * 3 = format
         */
        if (pmt_backup) return pmt(1);
        else if (pmt_flash) return pmt(2);
        else if (pmt_format) return pmt(3);
        else if (!pmt_silent) errx(EX_USAGE, "no target (backup or flash).\nTry `%s --help` for more information.\n", argv[0]);
    }
}

#if defined(__cplusplus)
}
#endif

/* end of code */