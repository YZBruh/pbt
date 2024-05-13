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

include config/env.mk
include config/vars.mk
include config/source.mk
-include config/INS_STAT.mk
-include config/UNINS_STAT.mk

# start build (if no custom target)
.PHONY: all
all:
	@printf " ---- Building Partition Manager ---- \n\n"; \
	printf " - Version: $(VERSION)\n"; \
	printf " - Version code: $(VERSION_CODE)\n\n"; \
	printf "   --------------------------------   \n\n"; \
	printf " - Building... Please waith.\n"; \
	sleep 2; \
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) || exit 1; \
	mkdir -p $(OUT_DIR); \
	mkdir -p $(BINARY_DIR); \
	mkdir -p $(PACKAGE_DIR); \
	mv pmt $(BINARY_DIR) || exit 1; \
	printf " - Generating xz package...\n"; \
	cp $(BINARY_DIR)/pmt $(PACKAGE_DIR) || exit 1; \
	xz $(PACKAGE_DIR)/pmt; \
	mv $(PACKAGE_DIR)/pmt.xz $(PACKAGE_DIR)/pmt-$(TARGET_ARCH)-$(LANG).xz || exit 1; \
	printf " - Success\n\n"; \
	printf " ------------------------------------ \n";

# cleaner functions
.PHONY: clean
clean:
	@printf "Cleaning with rm force mode (builded binary)...\n"; \
	sleep 1; \
	rm -rf $(OUT_DIR); \
	printf "Success\n";

# helper function
.PHONY: help
help:
	@printf " ------- Partition Manager help -------\n"; \
	printf " \n"; \
	printf " Commands;\n"; \
	printf "    make                   ==> Build Partition Manager\n"; \
	printf "    make deb               ==> Generate deb (debian) package (compatibility => termux)\n"; \
	printf "    make clean             ==> Clear builded binary.\n"; \
	printf "    make install           ==> If you are using termux, it installs the compiled pmt into termux. So it allows you to use it like a normal command.\n"; \
	printf "    make uninstall         ==> If you are using termux, it uninstalls the compiled pmt into termux. So it allows you to use it like a normal command.\n"; \
	printf "    make help              ==> Display help message\n\n";

# deb maker
.PHONY: deb
deb:
	@printf " --------- Making deb package ---------\n"; \
	printf " - Checking all files and directories (only neededs)...\n"; \
	if [ ! -d $(DEBUTILS_DIR) ]; then \
		printf " - Not found: $(DEBUTILS_DIR) \n"; \
		exit 1; \
	fi; \
	if [ ! -d $(DEBUTILS_DIR)/DEBIAN ]; then \
		printf " - Not found: $(DEBUTILS_DIR)/DEBIAN \n"; \
		exit 1; \
	fi; \
	if [ ! -d $(DEBUTILS_DIR)/mandoc ]; then \
		printf " - Not found: $(DEBUTILS_DIR)/mandoc \n"; \
		exit 1; \
	fi; \
	if [ ! -d $(DEBUTILS_DIR)/data/data/com.termux ]; then \
		printf " - Not found: $(DEBUTILS_DIR)/data/data/com.termux \n"; \
		exit 1; \
	fi; \
	if [ ! -d $(DEBUTILS_DIR)/data/data/com.termux/files/usr ]; then \
		printf " - Not found: $(DEBUTILS_DIR)/data/data/com.termux/files/usr \n"; \
		exit 1; \
	fi; \
	if [ ! -d $(DEBUTILS_DIR)/data/data/com.termux/files/usr/bin ]; then \
		printf " - Not found: $(DEBUTILS_DIR)/data/data/com.termux/files/usr/bin \n"; \
		exit 1; \
	fi; \
	if [ ! -d $(DEBUTILS_DIR)/data/data/com.termux/files/usr/share/man/man1 ]; then \
		printf " - Not found: $(DEBUTILS_DIR)/data/data/com.termux/files/usr/share/man/man1 \n"; \
		exit 1; \
	fi; \
	if [ ! -f $(DEBUTILS_DIR)/mandoc/pmt.1 ]; then \
		printf " - Not found: $(DEBUTILS_DIR)/mandoc/pmt.1 \n"; \
		exit 1; \
	fi; \
	if [ ! -f $(DEBUTILS_DIR)/DEBIAN/control_32 ]; then \
		printf " - Not found: $(DEBUTILS_DIR)/DEBIAN/control_32 \n"; \
		exit 1; \
	fi; \
	if [ ! -f $(DEBUTILS_DIR)/DEBIAN/control_64 ]; then \
		printf " - Not found: $(DEBUTILS_DIR)/DEBIAN/control_64 \n"; \
		exit 1; \
	fi; \
	if [ ! -f $(BINARY_DIR)/pmt ]; then \
		printf " - Package not builded! Please build package and try again \n"; \
		exit 1; \
	fi; \
	printf " - Generating template dir...\n"; \
	mkdir -p $(DEBUTILS_DIR)/temp; \
	printf " - Generating out dir...\n"; \
	mkdir -p $(DEB_DIR); \
	printf " - Copying files...\n"; \
	cp -r $(DEBUTILS_DIR)/data $(DEBUTILS_DIR)/temp || exit 1; \
	rm -f $(DEBTERMUX_USR)/share/man/man1/dummy; \
	rm -f $(DEBTERMUX_USR)/bin/dummy; \
	mkdir -p $(DEBUTILS_DIR)/temp/DEBIAN; \
	if [ "$(ARCH)" = "aarch64" ] || [ "$(ARCH)" = "armv8l" ]; then \
		printf " - Selected arm-64 package control file.\n"; \
		cp $(DEBUTILS_DIR)/DEBIAN/control_64 $(DEBUTILS_DIR)/temp/DEBIAN/control || exit 1; \
	elif [ "$(ARCH)" = "aarch32" ] || [ "$(ARCH)" = "armv7l" ]; then \
		printf " - Selected arm-32 package control file.\n"; \
		cp $(DEBUTILS_DIR)/DEBIAN/control_32 $(DEBUTILS_DIR)/temp/DEBIAN/control || exit 1; \
	fi; \
	cp $(DEBUTILS_DIR)/mandoc/pmt.1 $(DEBTERMUX_USR)/share/man/man1 || exit 1; \
	cp $(BINARY_DIR)/pmt $(DEBTERMUX_USR)/bin || exit 1; \
	printf " - Starting dpkg-deb...\n"; \
	sleep 2; \
	chmod -R 755 *; \
	dpkg-deb -b $(DEBUTILS_DIR)/temp $(DEB_DIR)/pmt-$(ARCH)-$(LANG).deb || exit 1; \
	rm -r $(DEBUTILS_DIR)/temp || exit 1; \
	printf " - Done! Package: $(DEB_DIR)/pmt-$(ARCH)-$(LANG).deb\n"

# installer
.PHONY: install
install:
	@if [ -f $(TERMUX_BIN)/termux-open ]; then \
		printf " ------------ pmt installer ------------ \n"; \
		if [ -f $(TERMUX_BIN)/pmt ]; then \
			printf " - pmt already installed\n"; \
			exit; \
		fi; \
		if [ ! "$(INSTALL_SUCCESS)" = "true" ] && [ ! "$(INSTALL_SUCCESS)" = "" ]; then \
			printf " - Warning: a previously-stayed failed installation process found\n"; \
		fi; \
		printf " - Checking files...\n"; \
		if [ ! -f $(BINARY_DIR)/pmt ]; then \
			printf " - Package not builded! Please build package and try again \n"; \
			echo "INSTALL_SUCCESS := false" > $(CUR_DIR)/config/INS_STAT.mk; \
			exit 1; \
		fi; \
		printf " - Copying files...\n"; \
		if [ "`cp $(BINARY_DIR)/pmt /data/data/com.termux/files/usr/bin/pmt`" = "" ]; then \
			printf " - Setting up permissions...\n"; \
		else \
			echo "INSTALL_SUCCESS := false" > $(CUR_DIR)/config/INS_STAT.mk; \
			exit 1; \
		fi; \
		if [ "`chmod 777 $(TERMUX_BIN)/pmt`" = "" ]; then \
			printf " - Saving current status...\n"; \
			echo "INSTALL_SUCCESS := true" > $(CUR_DIR)/config/INS_STAT.mk; \
		else \
			echo "INSTALL_SUCCESS := false" > $(CUR_DIR)/config/INS_STAT.mk; \
			exit 1; \
		fi; \
		printf " - Success.\n\n"; \
		echo "INSTALL_SUCCESS := true" > $(CUR_DIR)/config/INS_STAT.mk; \
		echo "UNINSTALLED_SUCCESS := " > $(CUR_DIR)/config/UNINS_STAT.mk; \
	else \
		printf " - This function is only available on Termux.\n"; \
	fi

# uninstaller
.PHONY: uninstall
uninstall:
	@if [ -f $(TERMUX_BIN)/termux-open ]; then \
		printf " ----------- pmt uninstaller ----------- \n"; \
		if [ ! -f $(TERMUX_BIN)/pmt ]; then \
			printf " - pmt already uninstalled\n"; \
			exit; \
		fi; \
		if [ ! "$(UNINSTALL_SUCCESS)" = "true" ] && [ ! "$(UNINSTALL_SUCCESS)" = "" ]; then \
			printf " - Warning: a previously-stayed failed uninstallation process found\n"; \
		fi; \
		if [ -f $(TERMUX_USR)/share/man/man1/pmt.1 ]; then \
			printf " - It was found to be established by pmt's deb pack. It's removed with apt...\n"; \
			apt remove -y pmt || exit 1; \
			printf " - Success.\n\n"; \
			echo "UNINSTALLED_SUCCESS := true" > $(CUR_DIR)/config/UNINS_STAT.mk; \
			echo "INSTALL_SUCCESS := " > $(CUR_DIR)/config/INS_STAT.mk; \
		else \
			printf " - It was found that pmt was manually established (with this makefile or copying). Manually removed...\n"; \
			if [ "`rm $(TERMUX_BIN)/pmt`" = "" ]; then \
				printf " - Success.\n\n"; \
				echo "UNINSTALLED_SUCCESS := true" > $(CUR_DIR)/config/UNINS_STAT.mk; \
				echo "INSTALL_SUCCESS := " > $(CUR_DIR)/config/INS_STAT.mk; \
			else \
				echo "UNINSTALLED_SUCCESS := false" > $(CUR_DIR)/config/UNINS_STAT.mk; \
				exit 1; \
			fi; \
		fi; \
	else \
		printf "This function is only available on Termux.\n"; \
	fi

# end
