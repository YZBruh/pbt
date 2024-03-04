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

void error(const char *err_msg);
void check_psf();
void check_root();
void listpart();
void backup(char *target_pt, char *pst);
void flash();

/* end of code */

#endif
