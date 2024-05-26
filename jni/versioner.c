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
#include <pmt-versioning.h>

void version()
{
    printf("Version: %d.%d.%d (code %d%d%d) ", PMT_MAJOR, PMT_LEVEL, PMT_PATCH, PMT_MAJOR, PMT_LEVEL, PMT_PATCH);

    #if __SIZEOF_POINTER__ == 4
        printf("32-bit binary\n");
    #elif __SIZEOF_POINTER__ == 8
        printf("64-bit binary\n");
    #else
        printf("\n");
    #endif

    #if defined(__clang__)
        printf("Compiler: clang %s\n", __clang_version__);
    #elif defined(__gcc__)
        printf("Compiler: gcc %s\n", __gcc_version__)
    #endif

    printf("See licenses with -L argument.\n");
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* end of code */
