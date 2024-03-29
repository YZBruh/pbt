#define _DOCUMENTATION_H_

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

void licenses()
{
    printf("Copyright 2024 YZBruh - Partition Manager\n");
    printf("Licensed under the Apache License, Version 2.0 (the \"License\");\n");
    printf("you may not use this file except in compliance with the License.\n");
    printf("You may obtain a copy of the License at\n\n");
    printf("    http://www.apache.org/licenses/LICENSE-2.0\n\n");
    printf("Unless required by applicable law or agreed to in writing, software\n");
    printf("distributed under the License is distributed on an \"AS IS\" BASIS,\n");
    printf("WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n");
    printf("See the License for the specific language governing permissions and limitations under the License.\n");
}

void help()
{
    printf("Usage (arguments): \n");
    printf("   -b, --backup      backup mode\n");
    printf("   -f, --flash       flash mode\n");
    printf("   -p, --partition   name of the partition to be backed up\n");
    printf("   -l, --logical     know that the partition that will be backed up is logical\n");
    printf("   -o, --out         (only backups) the output name of the backed-up partition (default: partition name)\n");
    printf("   -d, --outdir      (only backups) directory where the backup partition will be saved (default: /storage/emulated/0)\n");
    printf("   -c, --context     it is meant to specify a custom /dev context. Only classic partitions (default: /dev/block/by-name)\n");
    printf("   -D, --list        list partitions\n");
    printf("   -v, --version     see version\n");
    printf("   -h, --help        see help message\n");
    printf("   -L, --license     see license\n\n");
    printf("Example 1:\n");
    printf("   -b --partition boot_a -o boot_slot_a_image -d /sdcard/backup -c /dev/block/platform/bootdevice/by-name\n\n");
    printf("Example 2:\n");
    printf("   --flash /sdcard/twrp/boot.img -p boot_a -c /dev/block/platform/bootdevice/by-name\n\n");
    printf("Example 3:\n");
    printf("   -c /dev/block/platform/bootdevice/by-name --list\n\n");
    printf("Report bugs to <xda-@YZBruh>\n");
}

/* end of code */
