#ifndef _COMMON_H_
#define _COMMON_H_

/* By YZBruh */

/*
 *         _      _   
 *        | |    | |  
 *  _ __  | |__  | |_ 
 * | '_ \ | '_ \ | __|
 * | |_) || |_) || |_ 
 * | .__/ |_.__/  \__|
 * | |                
 * |_|                
 *
 */

/*
 * Copyright 2024 YZBruh - Partition Packupper
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

/* funcs */
void error(const char *err_msg);
void check_psf();
void check_root();
void listpart();
void backup(char *target_pt, char *pst);
void flash(char *target_flash_part, char *target_flash_fpart);

/* macros */
#define ANSI_RED      "\033[31m"
#define ANSI_YELLOW   "\033[33m"
#define ANSI_GREEN    "\033[32m"
#define ANSI_RESET    "\033[0m"

#define PACK_VER      "1.5.0"
#define PACK_VER_CODE "150"
#define PACK_NAME     "Partition Backupper"
#define PACK_LANG     "en"

/* variables */
extern char *argx_target_p;
extern char *out;
extern char *outdir;
extern char *my_out;
extern char *cust_cxt;
extern char target_flash_f[300];
extern char cust_cxt_path[150];
extern char cust_cxt_ckpath[150];
extern char cust_cxt_cklpath[150];
extern char path[300];
extern char cmd[256];
extern bool use_argx_p;
extern bool use_logical;
extern bool use_cust_cxt;
extern bool pbt_ab;
extern bool pbt_logical;
extern bool pbt_flash_mode;

/* end of code */

#endif
