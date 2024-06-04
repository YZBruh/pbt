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

#if !defined(__PMT_H_)
#define __PMT_H_

/* some definations */
#define ANSI_RED             "\033[31m"
#define ANSI_YELLOW          "\033[33m"
#define ANSI_GREEN           "\033[32m"
#define ANSI_RESET           "\033[0m"

#define PMT_PACKAGE_NAME     "Partition Manager"

/* variable definations */
extern char* out;
extern char* cust_cxt;
extern char* target_partition;
extern char* target_flash_file;
extern char* format_fs;
extern char* partition_type;
extern char* bin_name;
extern bool pmt_use_logical;
extern bool pmt_use_cust_cxt;
extern bool pmt_ab;
extern bool pmt_logical;
extern bool pmt_silent;
extern bool pmt_flash;
extern bool pmt_backup;
extern bool pmt_format;
extern bool pmt_force_mode;

/* function definations */
int listpart();
void check_dev_point();
void check_root();
int pmt(unsigned short progress_code);
void version();

#endif /* __PMT_H_ */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* end of code */
