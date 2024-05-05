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

# speficy
VERSION := 1.9.0
VERSION_CODE := 190
TARGET := pmt
LANG := en

# device arch info
ARCH := $(shell uname -m)

# current directory
CUR_DIR := $(shell pwd)

# others needed important variables
SOURCE_DIR ?= $(CUR_DIR)/src
OUT_DIR := $(CUR_DIR)/out
BINARY_DIR := $(OUT_DIR)/binary
PACKAGE_DIR := $(OUT_DIR)/package
DEB_DIR := $(OUT_DIR)/deb
DEBUTILS_DIR := $(CUR_DIR)/debutils
DEBTERMUX_USR := $(DEBUTILS_DIR)/temp/data/data/com.termux/files/usr
TERMUX_BIN := /data/data/com.termux/files/usr/bin
TERMUX_USR := /data/data/com.termux/files/usr
