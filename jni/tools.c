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
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <errno.h>
#include <err.h>
#include <sysexits.h>
#include <fcntl.h>
#include <pmt.h>

#define BFSIZE 1024

extern char* out;
extern char* format_fs;
extern char* cust_cxt;
extern char* target_partition;
extern char* target_flash_file;
extern char* partition_type;
extern bool pmt_use_logical;
extern bool pmt_use_cust_cxt;
extern bool pmt_logical;
extern bool pmt_flash;
extern bool pmt_backup;
extern bool pmt_silent;
extern bool pmt_force_mode;

/**
 *    if progress_code is a
 * 1 = backup mode 
 * 
 * 2 = flash mode 
 * 
 * 3 = format mode
 */

/**
 * it is meant to calculate the size of the quickly given file. 
 * its purpose is for rapid processing
 */
static double
calc_flsz(const char* _Nonnull filepath)
{
    static int calc_flsz_file;
    calc_flsz_file = open(filepath, O_RDONLY);
    if (calc_flsz_file == -1) return calc_flsz_file;

    static off_t flsz;
    flsz = lseek(calc_flsz_file, 0, SEEK_END);
    close(calc_flsz_file);

    if (flsz == (off_t)-1) return -1;

    return (double)flsz / (1024 * 1024);
}

/**
 * error that the partition is not found. 
 * It's for quick action.
 */
static int
partition_not_found()
{
    if (!pmt_silent) errx(EX_OSFILE, "partition not found!");
    else return EX_OSFILE;
}

/**
 * unknown partition type error. 
 * It's for quick action.
 */
static int
invalid_partition_type()
{
    if (!pmt_silent) errx(EX_USAGE, "invalid partition type!");
    else exit(EX_USAGE);

    return 0;
}

/* to stop use of function type */
#define partition_not_found partition_not_found()
#define invalid_partition_type invalid_partition_type()

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

/* the partitions are meant to quickly find. */
static void
search_partition(const char* _Nonnull partition)
{
    static int partition_results = 0;
    partition_results = search_stat(partition, "blk");

    if (partition_results == 1) partition_not_found;
    else if (partition_results == -1 && !pmt_silent) errx(EX_OSFILE, "the specified partition is not the block. I mean, it's not actually an episode (disc). I'm sure it needs to applaud those mistakes.");
    else exit(EX_OSFILE);
}

int pmt(unsigned short progress_code)
{
    /* required variables */
    static int srcf, targetf;
    static char backupper_path[512];
    static char ppath[100];
    static char formatter_cmd[200];
    static char outf[512];
    static char flasher_path[512];
    static char buffer[BFSIZE];
    static ssize_t readed_data;
    static unsigned long long copied_data = 0;
    static unsigned long long count = 1024 * 1024 * 1024;

    if (progress_code == 1)
    {
        if (!pmt_use_logical)
        {
            if (pmt_use_cust_cxt) sprintf(backupper_path, "%s/%s", cust_cxt, target_partition);
            else sprintf(backupper_path, "/dev/block/by-name/%s", target_partition);
        }
        else if (pmt_use_logical) sprintf(backupper_path, "/dev/block/mapper/%s", target_partition);
        else return invalid_partition_type;

        search_partition(backupper_path);

        if (calc_flsz(backupper_path) != -1 && !pmt_silent) printf("Disk size of the partition to be backed up: %.2f\n", calc_flsz(backupper_path));
        else warnx(ANSI_YELLOW "failed to get target partition disk size" ANSI_RESET);

        srcf = open(backupper_path, O_RDONLY);
        if (srcf == -1)
        {
            if (!pmt_silent) errx(EX_OSFILE, "couldn't read: %s: %s", backupper_path, strerror(errno));
            else return EX_IOERR;
        }

        /* determine output */
        if (strcmp(out, target_partition) == 0)
        {
            sprintf(outf, "%s.img", target_partition);
            if (!pmt_silent) warnx(ANSI_YELLOW "warning: The output file name was not specified. The output file name will be: %s" ANSI_RESET, outf);
        }
        else sprintf(outf, "%s", target_partition);

        targetf = open(outf, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (targetf == -1)
        {
            if (!pmt_silent) errx(EX_CANTCREAT, "couldn't generate: %s: %s", outf, strerror(errno));
            else return EX_CANTCREAT;
        }

        /* start writing */
        while ((readed_data = read(srcf, buffer, BFSIZE)) > 0 && copied_data < count)
        {
            ssize_t writed_data = write(targetf, buffer, readed_data);
            if (writed_data != readed_data)
            {
                if (!pmt_silent) warnx("couldn't write: %s: %s", backupper_path, strerror(errno));
                close(srcf);
                close(targetf);
                if (search_stat(outf, "file") == 0) remove(outf);
                return EX_IOERR;
            }

            copied_data += writed_data;
        }

        /* close files */
        close(srcf);
        close(targetf);

        if (!pmt_silent) printf("%sSuccess. Output: %s%s\n", ANSI_GREEN, outf, ANSI_RESET);
    }
    else if (progress_code == 2)
    {
        /* determine device block */
        /* for classic */
        if (!pmt_use_logical)
        {
            if (pmt_use_cust_cxt) sprintf(flasher_path, "%s/%s", cust_cxt, target_partition);
            else sprintf(flasher_path, "/dev/block/by-name/%s", target_partition);
        /* for logical */
        }
        else if (pmt_use_logical) sprintf(flasher_path, "/dev/block/mapper/%s", target_partition);
        else return invalid_partition_type;

        /* check partition */
        search_partition(flasher_path);

        if (calc_flsz(target_flash_file) != -1 && !pmt_force_mode) printf("Size of flash file: %.2f\n", calc_flsz(target_flash_file));
        else warnx(ANSI_YELLOW "failed to get flash file size" ANSI_RESET);

        if (calc_flsz(target_partition) != -1 && !pmt_force_mode) printf("Disk size of the target partition: %.2f\n", calc_flsz(target_partition));
        else warnx(ANSI_YELLOW "failed to get target partition disk size" ANSI_RESET);

        if (calc_flsz(target_flash_file) > calc_flsz(target_partition) && !pmt_silent) errx(EX__BASE, "size of the file to flash more than the partition size.");
        else return EX__BASE;

        srcf = open(target_flash_file, O_RDONLY);
        if (srcf == -1)
        {
            if (!pmt_force_mode) errx(EX_NOINPUT, "couldn't read: %s: %s", target_flash_file, strerror(errno));
            else return EX_IOERR;
        }

        targetf = open(target_partition, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (targetf == -1)
        {
            if (!pmt_force_mode) errx(EX_OSFILE, "couldn't read: %s: %s", target_partition, strerror(errno));
            else return EX_IOERR;
        }

        /* start writing */
        while ((readed_data = read(srcf, buffer, BFSIZE)) > 0 && copied_data < count)
        {
            ssize_t writed_data = write(targetf, buffer, readed_data);
            if (writed_data != readed_data)
            {
                warnx("couldn't write: %s: %s", backupper_path, strerror(errno));
                close(srcf);
                close(targetf);
                return EX_IOERR;
            }

            copied_data += writed_data;
        }

        close(srcf);
        close(targetf);

        if (!pmt_force_mode) printf("%sSuccess.%s\n", ANSI_GREEN, ANSI_RESET);
    }
    else if (progress_code == 3)
    {
        /* generate partition extn */
        if (!pmt_use_logical)
        {
            if (pmt_use_cust_cxt) sprintf(ppath, "%s/%s", cust_cxt, target_partition);
            else sprintf(ppath, "/dev/block/by-name/%s", target_partition);
        /* for logical */
        }
        else if (pmt_use_logical) sprintf(ppath, "/dev/block/mapper/%s", target_partition);
        else return invalid_partition_type;

        /* check partition */
        search_partition(ppath);

        /* get target partition block size */
        struct statvfs file_sys_inf;
        if (statvfs(ppath, &file_sys_inf) != 0)
        {
            if (!pmt_force_mode) errx(EX_TEMPFAIL, "the partition block size could not be obtained!");
            else return EX_TEMPFAIL;
        }

        /* generate mke2fs command */
        sprintf(formatter_cmd, "mke2fs -Fq -t %s -b %lu %s", format_fs, file_sys_inf.f_bsize, ppath);

        /* run command */
        if (system(formatter_cmd) != 0)
        {
            if (!pmt_force_mode) errx(EX_TEMPFAIL, "formatting failed! There may be a chance that something has been damaged!");
            else return EX_TEMPFAIL;
        }
    }
    return 0;
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* end of code */
