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
#include <android/ndk-version.h>
#include <pmt-versioning.h>

extern char* bin_name;

void version(void)
{
    printf("%s version %d.%d.%d (code %d%d%d) ", bin_name, PMT_MAJOR, PMT_MINOR, PMT_PATCHLEVEL, PMT_MAJOR, PMT_MINOR, PMT_PATCHLEVEL);

    #if __SIZEOF_POINTER__ == 4
        printf("32-bit binary\n");
    #elif __SIZEOF_POINTER__ == 8
        printf("64-bit binary\n");
    #else
        printf("<unknown> binary\n");
    #endif

    #if defined(__clang__)
        printf("Compiler: clang %d.%d.%d (NDK major r%d)\n", __clang_major__, __clang_minor__, __clang_patchlevel__, __NDK_MAJOR__);
    #endif

    printf("See licenses with -L argument.\n");
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* end of code */
