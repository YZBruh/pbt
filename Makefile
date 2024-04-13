# By YZBruh

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

include config/env.mk

# speficy {version}
VERSION := 1.7.0
VERSION_CODE := 170
SOURCE_DIR := binary
TARGET := pmt
LANG := en
ARCH := $(shell uname -m)
CUR_DIR := $(shell pwd)

# sources
SRCS := $(SOURCE_DIR)/$(TARGET).c
SRCS += $(SOURCE_DIR)/error.c
SRCS += $(SOURCE_DIR)/checkers.c
SRCS += $(SOURCE_DIR)/listpart.c
SRCS += $(SOURCE_DIR)/flash.c
SRCS += $(SOURCE_DIR)/backup.c
SRCS += $(SOURCE_DIR)/docs.c

# objects
OBJS := $(SOURCE_DIR)/$(TARGET).o
OBJS += $(SOURCE_DIR)/error.o
OBJS += $(SOURCE_DIR)/checkers.o
OBJS += $(SOURCE_DIR)/listpart.o
OBJS += $(SOURCE_DIR)/flash.o
OBJS += $(SOURCE_DIR)/backup.o
OBJS += $(SOURCE_DIR)/docs.o

OUT_DIR := $(CUR_DIR)/out
BINARY_DIR := $(OUT_DIR)/binary
PACKAGE_DIR := $(OUT_DIR)/package

# display
all:
	@printf "  --- Building Partition Manager ---  \n"; \
	printf "Version: $(VERSION)\n"; \
	printf "Version code: $(VERSION_CODE)\n\n"; \
	printf " ------------------------------------- \n\n"; \
	printf "Starting build... Please waith.\n"; \
	sleep 2; \
	printf "Make running with silent mode...\n"; \
	make -s pmt; 

# build progress
.PHONY: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	@mkdir -p $(OUT_DIR); \
	mkdir -p $(BINARY_DIR); \
	mkdir -p $(PACKAGE_DIR); \
	mv pmt $(BINARY_DIR); \
	printf "Generating gzip package...\n"; \
	cp $(BINARY_DIR)/pmt $(PACKAGE_DIR); \
	gzip -f $(PACKAGE_DIR)/pmt; \
	mv $(PACKAGE_DIR)/pmt.gz $(PACKAGE_DIR)/pmt-$(ARCH)-$(LANG).gz; \
	printf " \n"; \
	printf " ------------------------------------- \n";

# cleaner functions
.PHONY: clean
clean:
	@printf "Cleaning (builded files [.o extended])...\n"; \
	sleep 2; \
	rm -rf $(OBJS); \
	printf "Success\n";

.PHONY: clean-all
clean-all:
	@printf "Cleaning (builded files [.o extended] and binary)...\n"; \
	sleep 2; \
	rm -rf $(OBJS) $(OUT_DIR); \
	printf "Success\n";

# helper function
.PHONY: help
help:
	@printf " --------- Partition Manager help ---------\n"; \
	printf " \n"; \
	printf " Commands;\n"; \
	printf "    make                   ==> Build Partition Manager\n"; \
	printf "    make clean             ==> Clear files (Builded binaries are not deleted)\n"; \
	printf "    make clean-all         ==> Clear files (Builded binaries are deleted)\n"; \
	printf "    make install-termux    ==> If you are using termux, it installs the compiled pmt into termux. So it allows you to use it like a normal command.\n"; \
	printf "    make uninstall-termux  ==> If you are using termux, it uninstalls the compiled pmt into termux.\n"; \
	printf "    make help              ==> Display help message\n"; \
	printf " \n";

# installer
.PHONY: install-termux
install-termux:
	@if [ -f /data/data/com.termux/files/usr/bin/termux-open ]; then \
		printf " ------------------------------------- \n"; \
		printf "            pmt installer            \n"; \
		printf " ------------------------------------- \n"; \
		cp $(BINARY_DIR)/pmt /data/data/com.termux/files/usr/bin/pmt || exit 1; \
		chmod 777 /data/data/com.termux/files/usr/bin/pmt || exit 1; \
		printf " \n"; \
		printf "Success.\n\n"; \
	else \
		printf "This function is only available on Termux Android devices using aarch64 (64-bit) and armv7l (32-bit)\n"; \
	fi

# uninstaller
.PHONY: uninstall-termux
uninstall-termux:
	@if [ -f /data/data/com.termux/files/usr/bin/termux-open ]; then \
		printf " ------------------------------------- \n"; \
		printf "            pmt uninstaller          \n"; \
		printf " ------------------------------------- \n"; \
		rm /data/data/com.termux/files/usr/bin/pmt || exit 1; \
		printf " \n"; \
		printf "Success.\n\n"; \
	else \
		printf "This function is only available on Termux Android devices using aarch64 (64-bit) and armv7l (32-bit)\n"; \
	fi
