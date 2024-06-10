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

#if defined(__cplusplus)
extern "C" {
#endif

#include <stdio.h>
#include <pmt-docs.h>

extern char* bin_name;

void licenses(void)
{
    printf("Copyright 2024 Partition Manager\n");
    printf("Licensed under the Apache License, Version 2.0 (the \"License\");\n");
    printf("you may not use this file except in compliance with the License.\n");
    printf("You may obtain a copy of the License at\n\n");
    printf("    http://www.apache.org/licenses/LICENSE-2.0\n\n");
    printf("Unless required by applicable law or agreed to in writing, software\n");
    printf("distributed under the License is distributed on an \"AS IS\" BASIS,\n");
    printf("WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n");
    printf("See the License for the specific language governing permissions and limitations under the License.\n");
}

void help(void)
{
    printf("Usage: \n");
    printf("   %s backup PARTITION [OUTPUT] [OPTIONS]...\n", bin_name);
    printf("   %s flash FILE PARTITION [OPTIONS]...\n", bin_name);
    printf("   %s format FILE_SYSTEM[ext/2/3/4] PARTITION [OPTIONS]...\n\n", bin_name);
    printf("Options: \n");
    printf("   -l | --logical     it is meant to determine whether the target partition is logical\n");
    printf("   -c | --context     it is meant to specify a custom /dev context. Only classic partitions (default: /dev/block/by-name)\n");
    printf("   -p | --list        list partitions\n");
    printf("   -s | --silent      information and warning messages are silenced in normal work.\n");
    printf("   -f | --force       force mode. Error messages are silenced and some things are ignored.\n");
    printf("   -v | --version     see version\n");
    printf("        --help        see help message\n");
    printf("   -L | --license     see license\n\n");
    printf("Examples:\n");
    printf("   %s backup boot_a -c /dev/block/platform/bootdevice/by-name\n", bin_name);
    printf("   %s flash /sdcard/twrp/boot.img boot_a -c /dev/block/platform/bootdevice/by-name\n", bin_name);
    printf("   %s format ext4 system_a --logical\n", bin_name);
    printf("   %s -c /dev/block/platform/bootdevice/by-name --list\n\n", bin_name);
    printf("Report bugs to <t.me/YZBruh>\n");
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* end of code */
