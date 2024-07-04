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

#####
# sub-make for building package
#####

THIS_IS = src

include ../Makefile.inc

ifeq ($(INC_OLDENV),true)
	include ../config/oldenv.mk
endif

define make_obj
	$(eval OBJ := $(1:.c=.o))
	$(call m_stat,`basename $(SOURCE_DIR)`/`basename $(OBJ)`)
	$(CC) $(CFLAGS) -c $1 || exit 1;
endef

define make_executable
	printf " - Making executable file...\n"; \
	$(CC) $(CFLAGS) -L$(SOURCE_DIR) -lpmt_root -lpmt_lister -lpmt_partitiontool -o $(TARGET) pmt.o error.o docs.o versioner.o lang_tools.o languages.o || exit 1;
endef

define make_staticlib
	$(call m_stat,$(1))
	$(AR) rcs "$1" "$2" || exit 1;
endef

# all target for building
all:
	@rm -f ../config/oldenv.mk; \
	printf " ---- Partition Manager Builder ---- \n\n"; \
	printf " - Version: $(VERSION)\n"; \
	printf " - Version code: $(VERSION_CODE)\n\n"; \
	printf "   --------------------------------   \n\n"; \
	abort_build() { \
		if [ -d "$(PACKAGE_DIR)" ]; then \
			rm -rf "$(PACKAGE_DIR)"; \
		fi; \
		if [ -d "$(BINARY_DIR)" ]; then \
			rm -rf "$(BINARY_DIR)"; \
		fi; \
		if [ -d "$(STATICLIB_DIR)" ]; then \
			rm -rf "$(STATICLIB_DIR)"; \
		fi; \
		exit 1; \
	}; \
	if [ -f $(SOURCE_DIR)/docs.o ]; then \
		printf " - Please clean up before you build it.\n\n"; \
		printf " ----------------------------------- \n"; \
		exit 1; \
	fi; \
	printf " - Building objects...\n"; \
	sleep 2; \
	$(foreach csrc,$(SRCS),$(call make_obj, $(csrc)))
	$(call mdir,$(OUT_DIR))
	$(call mdir,$(BINARY_DIR))
	$(call mdir,$(PACKAGE_DIR))
	$(call mdir,$(STATICLIB_DIR))
	printf " - Building static libraries...\n";
	$(call make_staticlib,libpmt_root.a,root.o)
	$(call make_staticlib,libpmt_lister.a,listpart.o)
	$(call make_staticlib,libpmt_partitiontool.a,partition_tool.o)
	sleep 1;
	$(call make_executable)
	sleep 1;
	mv pmt $(BINARY_DIR) || abort_build; \
	mv *.a $(STATICLIB_DIR) || abort_build; \
	printf " - Generating xz package...\n"; \
	cp $(BINARY_DIR)/pmt $(PACKAGE_DIR) || abort_build; \
	xz $(PACKAGE_DIR)/pmt || abort_build; \
	sleep 1; \
	mv $(PACKAGE_DIR)/pmt.xz $(PACKAGE_DIR)/pmt-$(ARCH).xz || abort_build; \
	printf " - Success\n\n"; \
	sleep 1; \
	printf " ----------------------------------- \n"

.PHONY: clean
clean:
	$(eval STATICLIBS = $(wildcard $(SOURCE_DIR)/*.a))
	$(eval OBJS = $(wildcard $(SOURCE_DIR)/*.o))
	$(info Cleaning files...)
	$(foreach obj,$(OBJS), $(call m_stat_nn,src/$(shell basename $(obj))) $(call erase,$(obj)))
	$(foreach lib,$(STATICLIBS),$(call m_stat_nn,src/$(shell basename $(lib))) $(call erase,$(lib)))

# end