#ifndef _PBT_H_
#define _PBT_H_

/* By YZBruh */

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

/* add pre-function important */
char *out;
char *outdir;
char *my_out;
char *cust_cxt;
bool use_cust_cxt = false;
bool pbt_ab = false;
bool pbt_logical = false;

/* shorter error messages will be functional xd */
void error(const char *err_msg) {
    fprintf(stderr, ANSI_RED "%s" ANSI_RESET, err_msg);
    exit(EXIT_FAILURE);
}

/* check if the device is ab partitioned */
void check_psf() {
    /* true = ab | false = a */
    if (use_cust_cxt) {
        char cust_cxt_ckpath[150];
        sprintf(cust_cxt_ckpath, "%s/boot_a", cust_cxt);
        if (access(cust_cxt_ckpath, F_OK) != 0) {
            pbt_ab = false;
        } else {
            pbt_ab = true;
        }
    } else {
        if (access("/dev/block/by-name/boot_a", F_OK) != 0) {
            pbt_ab = false;
        } else {
            pbt_ab = true;
        }
    }
    
    /* true = logical | false = classic */
    if (use_cust_cxt) {
        char cust_cxt_cklpath[150];
        sprintf(cust_cxt_cklpath, "%s/super", cust_cxt);
        if (access(cust_cxt_cklpath, F_OK) != 0) {
            pbt_logical = false;
        } else {
            pbt_logical = true;
        }
    } else {
        if (access("/dev/block/by-name/super", F_OK) != 0) {
            pbt_logical = false;
        } else {
            pbt_logical = true;
        }
    }
}

/* list existing partitions */
void listpart() {
    if (use_cust_cxt) {
        printf("List of classic partitions (%s): \n", cust_cxt);
        char cust_cxt_path[150];
        sprintf(cust_cxt_path, "ls %s", cust_cxt);
        if (system(cust_cxt_path) != 0) {
            error("An error occurred when the partition list appears!\n");
        }
    } else {
        printf("List of classic partitions (/dev/block/by-name): \n");
        if (system("ls /dev/block/by-name") != 0) {
            error("An error occurred when the classic partition list appears!\n");
        }
    }
    
    if (pbt_logical) {
        printf("List of logical partitions (/dev/block/mapper): \n");
        if (system("ls /dev/block/mapper") != 0) {
            error("An error occurred when the logical partition list appears!\n");
        }
    }
    if (pbt_ab) {
        printf("%sWarning: device using A/B partition style.%s\n", ANSI_YELLOW, ANSI_RESET);
    }
    if (pbt_logical) {
        printf("%sWarning: device using logical partition type.%s\n", ANSI_YELLOW, ANSI_RESET);
    }
}

/* additional function to perform backup */
void backup(char *target_pt, char *pst) {
    char path[200];
    if (strstr(pst, "classic") != NULL) {
        if (use_cust_cxt) {
            sprintf(path, "%s/%s", cust_cxt, target_pt);
        } else {
            sprintf(path, "/dev/block/by-name/%s", target_pt);
        }
    } else if (strstr(pst, "logical") != NULL) {
        sprintf(path, "/dev/block/mapper/%s", target_pt);
    } else {
        error("İnvalid partition type!\n");
    }
    if (access(path, F_OK) == -1) {
        error("Partition not found!\n");
    } else {
        printf("Target partition: %s\nBackupping...\n", target_pt);
    }
    char cmd[256];
    if (my_out != NULL) {
        if (out != NULL) {
            sprintf(cmd, "dd if=%s of=%s/%s.img status=none", path, my_out, out);
        } else {
            sprintf(cmd, "dd if=%s of=%s/%s.img status=none", path, my_out, target_pt);
        }
    } else {
        if (out != NULL) {
            sprintf(cmd, "dd if=%s of=/storage/emulated/0/%s.img status=none", path, out);
        } else {
            sprintf(cmd, "dd if=%s of=/storage/emulated/0/%s.img status=none", path, target_pt);
        }
    }
    if (system(cmd) != 0) {
        error("Failed!\n");
    } else {
        if (my_out != NULL) {
            if (out != NULL) {
                printf("%sSuccess. Output: %s/%s.img%s\n", ANSI_GREEN, my_out, out, ANSI_RESET);
            } else {
                printf("%sSuccess. Output: %s/%s.img%s\n", ANSI_GREEN, my_out, target_pt, ANSI_RESET);
            }
        } else {
            if (out != NULL) {
                printf("%sSuccess. Output: /storage/emulated/0/%s.img%s\n", ANSI_GREEN, out, ANSI_RESET);
            } else {
                printf("%sSuccess. Output: /storage/emulated/0/%s.img%s\n", ANSI_GREEN, target_pt, ANSI_RESET);
            }
        }
    }
}

/* root checker function */
void verify_root() {
    // a quick, easy method to verify root :D
    if (chdir("/dev/block") != 0) {
        error("Root privileges could not be detected! Please run this binary with root.\n");
    }
}

/* end of code */

#endif