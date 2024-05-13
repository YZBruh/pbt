# By YZBruh

# Copyright 2024 Partition Manager
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

#########################################
#                                       #
#          Configuration Flags          #
#                                       #
#         Warning: you can edit         #
#                                       #
#########################################

# addionital gcc flags
EXTRA_GCC_FLAGS ?= 

# arch config. 32-bit = armv7a | 64-bit = aarch64 | default = aarch64
TARGET_BUILD_ARCH ?= aarch64

# debugging mode (binary)
ENABLE_BINARY_DEBUGGING ?= false

#########################################
#########################################

#########################################
#                                       #
#          Apply Configuration          #
#                                       #
#      Warning: please do not edit      #
#                                       #
#########################################

# gcc flag settings
ifeq ($(ENABLE_BINARY_DEBUGGING), true)
	CFLAGS ?= -O3 -g -Wall -Wextra $(EXTRA_GCC_FLAGS)
else ifeq ($(ENABLE_BINARY_DEBUGGING), false)
	CFLAGS ?= -O3 -Wall $(EXTRA_GCC_FLAGS)
endif

#########################################
#########################################
