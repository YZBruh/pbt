include mka/config.mk

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

# speficy
VERSION := 1.5.0
VERSION_CODE := 150
SOURCE_DIR := binary
TARGET := pbt
ARCH := $(shell uname -m)

# code list
OBJS= $(SOURCE_DIR)/pbt.o
SRCS := $(SOURCE_DIR)/pbt.c

# gcc flags
LDFLAGS :=
LDLIBS := -lm

# display
all: 
	@printf "  --- Building Partition Backupper ---  \n"; \
	printf "Version: $(VERSION)\n"; \
	printf "Version code: $(VERSION_CODE)\n"; \
	printf " \n"; \
	printf " ------------------------------------- \n"; \
	printf " \n"; \
	printf "Starting build... Please waith.\n"; \
	sleep 2; \
	printf "Make running with silent mode...\n"; \
	make -s pbt; 

# build progress
.PHONY: $(TARGET)
$(TARGET): $(OBJS)
	$(LD) -o $@ $(LDFLAGS) $(OBJS) $(LIBS)
	@mkdir -p out; \
	mkdir -p out/binary; \
	mkdir -p out/package; \
	mv pbt out/binary; \
	printf "Generating gzip package...\n"; \
	cp out/binary/pbt out/package; \
	gzip -f out/package/pbt; \
	mv out/package/pbt.gz out/package/pbt-$(ARCH)-en.gz; \
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
	rm -rf $(OBJS) out; \
	printf "Success\n";

# helper function
.PHONY: help
help:
	@printf " --------- Partition Backupper help ---------\n"; \
	printf " \n"; \
	printf " Commands;\n"; \
	printf "    make                 ==> Build Partition Backupper\n"; \
	printf "    make clean           ==> Clear files (Builded binaries are not deleted)\n"; \
	printf "    make clean-all       ==> Clear files (Builded binaries are deleted)\n"; \
	printf "    make install-termux  ==> If you are using termux, it installs the compiled pbt into termux. So it allows you to use it like a normal command.\n"; \
	printf "    make help            ==> Display help message\n"; \
	printf " \n";

.PHONY: install-termux
install-termux:
	@arch=$$(uname -m); \
	if [ "$$arch" = "aarch64" ]; then \
		printf " ------------------------------------- \n"; \
		printf "            pbt installer            \n"; \
		printf " ------------------------------------- \n"; \
		cp out/binary/pbt /data/data/com.termux/files/usr/bin/pbt; \
		chmod 777 /data/data/com.termux/files/usr/bin/pbt; \
		printf " \n"; \
		printf "Success.\n"; \
		printf " \n"; \
	elif [ "$$arch" = "armv7l" ]; then \
		printf " ------------------------------------- \n"; \
		printf "           ptb installer           \n"; \
		printf " ------------------------------------- \n"; \
		cp out/pbt /data/data/com.termux/files/usr/bin/pbt; \
		chmod 777 /data/data/com.termux/files/usr/bin/pbt; \
		printf " \n"; \
		printf "Success.\n"; \
		printf " \n"; \
	else \
		printf "This function is only available on Termux Android devices using aarch64 (64-bit) and armv7l (32-bit)\n"; \
	fi
