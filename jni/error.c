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
#endif /* __cplusplus */

#define INC_MAIN_LIBS

#include <pmt.h>

__noreturn void error(int __status, const char* _Nullable __fmt, ...)
{
    if (__fmt == NULL) exit(__status);

    va_list err_args;
    va_start(err_args, __fmt);
    fprintf(stderr, "%s: ", bin_name);
    vfprintf(stderr, __fmt, err_args);
    fprintf(stderr, "\n");
    va_end(err_args);
    exit(__status);
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */