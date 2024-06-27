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

#define BFSIZE 1024
#define INC_MAIN_LIBS
#define INC_STAT
#define INC_DEBUGERS
#define INC_TOOLS_REQS

#include <pmt.h>

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

extern struct pmt_langdb_general* current;
extern struct pmt_langdb_general en;
extern struct pmt_langdb_general tr;

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
partition_not_found(void)
{
    if (!pmt_silent) error(1, "%s", current->part_not_found);
    else return 1;
}

/* to stop use of function type */
#define partition_not_found partition_not_found()

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

    return 2;
}

/* the partitions are meant to quickly find. */
static void
search_partition(const char* _Nonnull partition)
{
    static int partition_results = 0;
    partition_results = search_stat(partition, "blk");

    if (partition_results == 1) partition_not_found;
    else if (partition_results == -1 && !pmt_silent) error(1, "%s", current->not_block);
    else exit(1);
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

        search_partition(backupper_path);

        if (calc_flsz(backupper_path) != -1 && !pmt_silent) printf("%s: %.2f\n", current->part_disk_sz, calc_flsz(backupper_path));
        else if (!pmt_silent) warning("%s", current->part_disk_sz_fail);

        srcf = open(backupper_path, O_RDONLY);
        if (srcf == -1)
        {
            if (!pmt_silent) error(1, "%s: %s: %s", current->not_read, backupper_path, strerror(errno));
            else return 1;
        }

        /* determine output */
        if (strcmp(out, target_partition) == 0)
        {
            sprintf(outf, "%s.img", target_partition);
            if (!pmt_silent) warning("%s: %s", current->out_not_spec, outf);
        }
        else sprintf(outf, "%s", target_partition);

        targetf = open(outf, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (targetf == -1)
        {
            if (!pmt_silent) error(1, "%s: %s: %s", current->not_gen, outf, strerror(errno));
            else return 1;
        }

        /* start writing */
        while ((readed_data = read(srcf, buffer, BFSIZE)) > 0 && copied_data < count)
        {
            ssize_t writed_data = write(targetf, buffer, readed_data);
            if (writed_data != readed_data)
            {
                if (!pmt_silent) warning("%s: %s: %s", current->not_write, backupper_path, strerror(errno));
                close(srcf);
                close(targetf);
                if (search_stat(outf, "file") == 0) remove(outf);
                return 1;
            }

            copied_data += writed_data;
        }

        /* close files */
        close(srcf);
        close(targetf);

        if (!pmt_silent) printf("%s: %s\n", current->success_backup, outf);
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

        /* check partition */
        search_partition(flasher_path);

        if (calc_flsz(target_flash_file) != -1 && !pmt_force_mode) printf("%s: %.2f\n", current->flash_file_sz, calc_flsz(target_flash_file));
        else warning("%s", current->flash_file_sz_fail);

        if (calc_flsz(target_partition) != -1 && !pmt_force_mode) printf("%s: %.2f\n", current->part_disk_sz, calc_flsz(target_partition));
        else warning("%s", current->part_disk_sz_fail);

        if (calc_flsz(target_flash_file) > calc_flsz(target_partition) && !pmt_silent) error(1, "%s", current->ffile_more_part);
        else return 1;

        srcf = open(target_flash_file, O_RDONLY);
        if (srcf == -1)
        {
            if (!pmt_force_mode) error(1, "%s: %s: %s", current->not_read, target_flash_file, strerror(errno));
            else return 1;
        }

        targetf = open(target_partition, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (targetf == -1)
        {
            if (!pmt_force_mode) error(1, "%s: %s: %s", current->not_read, target_partition, strerror(errno));
            else return 1;
        }

        /* start writing */
        while ((readed_data = read(srcf, buffer, BFSIZE)) > 0 && copied_data < count)
        {
            ssize_t writed_data = write(targetf, buffer, readed_data);
            if (writed_data != readed_data)
            {
                warning("%s: %s: %s", current->not_write, backupper_path, strerror(errno));
                close(srcf);
                close(targetf);
                return 1;
            }

            copied_data += writed_data;
        }

        close(srcf);
        close(targetf);

        if (!pmt_force_mode) printf("%s.\n", current->success_flash);
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

        /* check partition */
        search_partition(ppath);

        /* get target partition block size */
        struct statvfs file_sys_inf;
        if (statvfs(ppath, &file_sys_inf) != 0)
        {
            if (!pmt_force_mode) error(1, "%s", current->cannot_get_bsz);
            else return 1;
        }

        /* generate mke2fs command */
        sprintf(formatter_cmd, "mke2fs -Fq -t %s -b %lu %s", format_fs, file_sys_inf.f_bsize, ppath);

        /* run command */
        if (system(formatter_cmd) != 0)
        {
            if (!pmt_force_mode) error(1, "%s", current->format_fail);
            else return 1;
        }
    }

    return 0;
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* end of code */
