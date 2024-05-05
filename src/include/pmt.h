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

/* check compiler system */
#ifdef _WIN32
    #error "it can only be compiled in linux or android environment. but current system windows (_WIN32 defined)"
#elif ! __linux__ || __android__
    #error "unknown compiler system founded"
#endif

/* compiler architecture if arm is not 32-bit or 64-bit, the compilation is stopped */
#if ! __SIZEOF_POINTER__ == 4 || ! __SIZEOF_POINTER__ == 8
    #error "only 32-bit or 64-bit arm compilers can be used"
#endif

#ifndef _PMT_H
#define _PMT_H

/* color definations */
#define ANSI_RED          "\033[31m"
#define ANSI_YELLOW       "\033[33m"
#define ANSI_GREEN        "\033[32m"
#define ANSI_RESET        "\033[0m"

/* info */
#define PMT_VERSION          "1.8.0"
#define PMT_VERSION_CODE     "180"
#define PMT_PACKAGE_NAME     "Partition Manager"
#define PMT_PACKAGE_LANG     "en"

/* variable definations */
extern char *out;
extern char *outdir;
extern char *cust_cxt;
extern char *target_partition;
extern char *target_flash_file;
extern char *format_fs;
extern bool pmt_use_logical;
extern bool pmt_use_cust_cxt;
extern bool pmt_ab;
extern bool pmt_logical;
extern bool pmt_flash;
extern bool pmt_backup;
extern bool pmt_format;
extern bool pmt_force_mode;

/* function definations */
void listpart();
void error(const char *err_msg, uint32_t errcode);
void check_psf();
void check_root();
void backup(char *target_backup_partition, char *backup_partition_style);
void flash(char *target_flash_partition, char *target_file, char *flash_partition_style);
void format(char *target_format_partition, char *format_partition_style);
void help();
void licenses();

#endif /* _PMT_H */

#ifdef __cplusplus
}
#endif

/* end of code */