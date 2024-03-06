# By YZBruh

# Copyright 2024 YZBruh - Partition Manager
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
else ifeq ($(USE_CUST_GCC), false)
	CC := gcc
	LD := gcc
else
	$(error İnvalid custom gcc config flag: $(USE_CUST_GCC))
endif

# gcc flag settings
CFLAGS := -O3 -g -Wno-unused-parameter -Wall -Wextra -static $(EXTRA_GCC_FLAGS)

# end of code
