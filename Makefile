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

# özel belirteçler (sürüm vb işte)
VERSION := 1.4.0
VERSION_CODE := 140
SOURCE_DIR := binary
TARGET := pbt
ARCH := $(shell uname -m)

# kaynak listesi
OBJS= $(SOURCE_DIR)/pbt.o
SRCS := $(SOURCE_DIR)/pbt.c

# gcc bayrakları (hepsi değil)
LDFLAGS :=
LDLIBS := -lm

# ekran
all: 
	@printf "  --- Partition Backupper İnşa Senaryosu ---  \n"; \
	printf "Sürüm: $(VERSION)\n"; \
	printf "Sürüm kodu: $(VERSION_CODE)\n"; \
	printf " \n"; \
	printf " ------------------------------------- \n"; \
	printf " \n"; \
	printf "İnşa başlatılıyor... Lütfen bekleyin.\n"; \
	sleep 2; \
	printf "Make sessiz modda çalıştırılıyor...\n"; \
	make -s pbt; 

# inşa işlemi
.PHONY: $(TARGET)
$(TARGET): $(OBJS)
	$(LD) -o $@ $(LDFLAGS) $(OBJS) $(LIBS)
	@mkdir -p out; \
	mkdir -p out/binary; \
	mkdir -p out/package; \
	mv pbt out/binary; \
	printf "gzip paketi oluşturuluyor...\n"; \
	cp out/binary/pbt out/package; \
	gzip -f out/package/pbt; \
	mv out/package/pbt.gz out/package/pbt_$(ARCH).gz; \
	printf " \n"; \
	printf " ------------------------------------- \n";

# temizleyici özellikler
.PHONY: clean
clean:
	@printf "Temizleniyor (inşa edilmişler [.o uzantılı])...\n"; \
	sleep 2; \
	rm -rf $(OBJS); \
	printf "Başarılı\n";

.PHONY: clean-all
clean-all:
	@printf "Temizleniyor (inşa edilmişler [.o uzantılı] ve kitaplık)...\n"; \
	sleep 2; \
	rm -rf $(OBJS) out; \
	printf "Başarılı\n";

# yardım önemli
.PHONY: help
help:
	@printf " --------- Partition Backupper yardım ---------\n"; \
	printf " \n"; \
	printf " Komutlar;\n"; \
	printf "    make                 ==> Partition Backupper inşasını başlatın.\n"; \
	printf "    make clean           ==> Dosyaları temizle (İnşa edilmiş kitaplık silinmez)\n"; \
	printf "    make clean-all       ==> Dosyaları temizle (İnşa edilmiş kitaplık silinir)\n"; \
	printf "    make install-termux  ==> Eğer termux kullanıyor ve mimariniz uygun ise ptb'yi termux'a kurar.\n"; \
	printf "    make help            ==> Bu yardım mesajını göster.\n"; \
	printf " \n";

.PHONY: install-termux
install-termux:
	@arch=$$(uname -m); \
	if [ "$$arch" = "aarch64" ]; then \
		printf " ------------------------------------- \n"; \
		printf "            pbt kuruluyor            \n"; \
		printf " ------------------------------------- \n"; \
		cp out/binary/pbt /data/data/com.termux/files/usr/bin/pbt; \
		chmod 777 /data/data/com.termux/files/usr/bin/pbt; \
		printf " \n"; \
		printf "Başarılı.\n"; \
		printf " \n"; \
	elif [ "$$arch" = "armv7l" ]; then \
		printf " ------------------------------------- \n"; \
		printf "           pbt kuruluyor           \n"; \
		printf " ------------------------------------- \n"; \
		cp out/binary/pbt /data/data/com.termux/files/usr/bin/pbt; \
		chmod 777 /data/data/com.termux/files/usr/bin/pbt; \
		printf " \n"; \
		printf "Başarılı.\n"; \
		printf " \n"; \
	else \
		printf "Bu özellik sadece termux kullanan aarch64 (64-bit) ve armv7l (32-bit) mimarili cihazlarda kullanılabilir.\n"; \
	fi
