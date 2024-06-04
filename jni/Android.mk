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

LOCAL_PATH := $(call my-dir)
ENVCONF := $(LOCAL_PATH)/config/env.mk

include $(CLEAR_VARS)
include $(ENVCONF)

# configration
LOCAL_MODULE = pmt
LOCAL_SRC_FILES = \
    pmt.c \
    versioner.c \
    tools.c \
    partition_tool.c \
    root.c \
    listpart.c \
    docs.c

# include dirs
LOCAL_C_INCLUDES = $(LOCAL_PATH)/include

# compiler flags settings
ifeq ($(ENABLE_DEBUGGING), true)
    LOCAL_CFLAGS = -O3 -g -Wall -Wextra $(EXTRA_COMPILER_FLAGS)
else ifeq ($(ENABLE_DEBUGGING), false)
    LOCAL_CFLAGS = -O3 -Wall $(EXTRA_COMPILER_FLAGS)
else
    $(warning Unknown debugging flag: $(ENABLE_DEBUGGING). Please see: $(PREDIR)/config/env.mk. Using non-debugging flags)
    LOCAL_CFLAGS = -O3 -Wall $(EXTRA_COMPILER_FLAGS)
endif

include $(BUILD_EXECUTABLE)

# end