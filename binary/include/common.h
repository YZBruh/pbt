#define _COMMON_H_

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

/* color definations */
#define ANSI_RED      "\033[31m"
#define ANSI_YELLOW   "\033[33m"
#define ANSI_GREEN    "\033[32m"
#define ANSI_RESET    "\033[0m"

/* info */
#define PACK_VER      "1.5.0"
#define PACK_VER_CODE "150"
#define PACK_NAME     "Partition Manager"
#define PACK_LANG     "en"

/* variable definations */
extern char *out;
extern char *outdir;
extern char *cust_cxt;
extern char *target_partition;
extern char *target_flash_file;
extern bool use_logical;
extern bool use_cust_cxt;
extern bool pmt_ab;
extern bool pmt_logical;
extern bool pmt_flash;
extern bool pmt_backup;

/* function definations */
void listpart();
void error(const char *err_msg);
void check_psf();
void check_root();
void backup(char *target_backup_partition, char *backup_partition_style);
void flash(char *target_flash_partition, char *target_file, char *flash_partition_style);
