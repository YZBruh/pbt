#!/usr/bin/bash
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

RED='\e[31m'
NC='\e[0m'

abort() {
    printf "${RED}$1${NC}"
    exit 1
}

case $1 in
    arm64-v8a)
        PREFIX="64"
    ;;
    armeabi-v7a)
        PREFIX="32"
    ;;
    *)
        abort " - Error: unknown architecture flag: $1. Avaiable: arm64-v8a & armeabi-v7a\n"
esac

VERSION="2.0.0"
CUR_DIR=$(pwd)
LIB_DIR=${CUR_DIR}/libs
ARMV8A_DIR=${OUT_DIR}/arm64-v8a
ARMV7A_DIR=${OUT_DIR}/armeabi-v7a
DEB_DIR=${OUT_DIR}/deb
DEBUTILS_DIR=${CUR_DIR}/debutils
DEBTERMUX_USR=${DEBUTILS_DIR}/data/data/com.termux/files/usr

chmod -R 755 *

printf " --------- Making pmt deb package ---------\n"; 
printf " - Checking all files and directories (only
eededs)...\n"; 
if [ ! -d ${DEBUTILS_DIR} ]; then 
    abort " - Not found: ${DEBUTILS_DIR}\n"
fi
if [ ! -d ${DEBUTILS_DIR}/DEBIAN ]; then 
    abort " - Not found: ${DEBUTILS_DIR}/DEBIAN\n"
fi
if [ ! -d ${DEBUTILS_DIR}/mandoc ]; then 
    abort " - Not found: ${DEBUTILS_DIR}/mandoc\n"
fi
if [ ! -d ${DEBUTILS_DIR}/data/data/com.termux ]; then 
    abort " - Not found: ${DEBUTILS_DIR}/data/data/com.termux\n"
fi
if [ ! -d ${DEBUTILS_DIR}/data/data/com.termux/files/usr ]; then 
    abort " - Not found: ${DEBUTILS_DIR}/data/data/com.termux/files/usr\n"
fi
if [ ! -d ${DEBUTILS_DIR}/data/data/com.termux/files/usr/bin ]; then 
    abort " - Not found: ${DEBUTILS_DIR}/data/data/com.termux/files/usr/bin\n"
fi
if [ ! -d ${DEBUTILS_DIR}/data/data/com.termux/files/usr/share/man/man1 ]; then 
    abort " - Not found: ${DEBUTILS_DIR}/data/data/com.termux/files/usr/share/man/man1\n"
fi
if [ ! -f ${DEBUTILS_DIR}/mandoc/pmt.1 ]; then 
    abort " - Not found: ${DEBUTILS_DIR}/mandoc/pmt.1\n"
fi
if [ ! -f ${DEBUTILS_DIR}/DEBIAN/control_32 ]; then 
    abort " - Not found: ${DEBUTILS_DIR}/DEBIAN/control_32\n"
fi
if [ ! -f ${DEBUTILS_DIR}/DEBIAN/control_64 ]; then 
    abort " - Not found: ${DEBUTILS_DIR}/DEBIAN/control_64\n"
fi
if [ ! -f ${ARMV8A_DIR}/pmt ]; then 
    abort " - Package not comptely builded! Please build package and try again\n"
elif [ ! -f ${ARMV7A_DIR}/pmt ]; then
    abort " - Package not comptely builded! Please build package and try again\n"
fi

printf " - Generating template dir...\n"
mkdir -p ${DEBUTILS_DIR}/temp

printf " - Generating out dir...\n"
mkdir -p ${DEB_DIR}

printf " - Copying files...\n"
cp -r ${DEBUTILS_DIR}/data ${DEBUTILS_DIR}/temp || exit 1
rm -f ${DEBTERMUX_USR}/share/man/man1/dummy
rm -f ${DEBTERMUX_USR}/bin/dummy
mkdir -p ${DEBUTILS_DIR}/temp/DEBIAN

printf " - Selected arm-${PREFIX} package control file.\n"
cp ${DEBUTILS_DIR}/DEBIAN/control_${PREFIX} ${DEBUTILS_DIR}/temp/DEBIAN/control || exit 1
cp ${DEBUTILS_DIR}/mandoc/pmt.1 ${DEBTERMUX_USR}/share/man/man1 || exit 1
if [ "${PREFIX}" = "64" ]; then
    cp ${ARMV8A_DIR}/pmt ${DEBTERMUX_USR}/bin || exit 1
elif [ "${PREFIX}" = "32" ]; then
    cp ${ARMV7A_DIR}/pmt ${DEBTERMUX_USR}/bin || exit 1
fi

printf " - Starting dpkg-deb...\n"
sleep 2
chmod -R 755 *
dpkg-deb -b ${DEBUTILS_DIR}/temp ${DEB_DIR}/pmt-${VERSION}-arm${PREFIX}.deb || exit 1; 
rm -rf ${DEBUTILS_DIR}/temp || exit 1;

printf " - Done! Package: ${DEB_DIR}/pmt-${VERSION}.deb\n"

# end of script