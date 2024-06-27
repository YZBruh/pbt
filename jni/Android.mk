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

include $(LOCAL_PATH)/config/env.mk

ifeq ($(ENABLE_DEBUGGING), true)
    PMT_CFLAGS := -O3 -g -Wall -Wextra $(EXTRA_COMPILER_FLAGS)
else ifeq ($(ENABLE_DEBUGGING), false)
    PMT_CFLAGS := -O3 -Wall $(EXTRA_COMPILER_FLAGS)
else
    $(warning Unknown debugging flag: $(ENABLE_DEBUGGING). Please see: $(PREDIR)/config/env.mk. Using non-debugging flags)
    PMT_CFLAGS := -O3 -Wall $(EXTRA_COMPILER_FLAGS)
endif

include $(CLEAR_VARS)

LOCAL_MODULE := libpmt_root
LOCAL_SRC_FILES := root.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_CFLAGS := $(PMT_CFLAGS)

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := libpmt_partitiontool
LOCAL_SRC_FILES := partition_tool.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_CFLAGS := $(PMT_CFLAGS)

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := libpmt_list
LOCAL_SRC_FILES := listpart.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_CFLAGS := $(PMT_CFLAGS)

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := pmt
LOCAL_SRC_FILES := \
    pmt.c \
    versioner.c \
    tools.c \
    error.c \
    lang_tools.c \
    languages.c \
    docs.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_STATIC_LIBRARIES := \
    libpmt_root \
    libpmt_partitiontool \
    libpmt_list
LOCAL_CFLAGS := $(PMT_CFLAGS)

include $(BUILD_EXECUTABLE)

# end
