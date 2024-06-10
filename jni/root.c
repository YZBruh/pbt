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
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <err.h>
#include <sysexits.h>
#include <pmt.h>

/* root checker function */
void check_root(void)
{
    /* a quick, easy method to verify root */
    if (getuid() != 0)
    {
        if (!pmt_force_mode) errx(EX_NOPERM, "root access could not be detected! Please run this binary with root.");
        else exit(EX_NOPERM);
    }
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* end of code */
