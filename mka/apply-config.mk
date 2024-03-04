# By YZBruh

#         _      _   
#        | |    | |  
#  _ __  | |__  | |_ 
# | '_ \ | '_ \ | __|
# | |_) || |_) || |_ 
# | .__/ |_.__/  \__|
# | |                
# |_|                
#

# Copyright 2024 YZBruh - Partition Backupper
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# gcc setting
ifeq ($(USE_CUST_GCC), true)
	CC := $(CUST_GCC)
	LD := $(CUST_GCC)
else
	CC := gcc
	LD := gcc
endif

# gcc flag settings
CFLAGS := -O3 -g -Wno-unused-parameter -Wall -Wextra -static $(EXTRA_GCC_FLAGS)

# end of code
