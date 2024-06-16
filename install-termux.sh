#!/data/data/com.termux/files/usr/bin/bash
#
# By YZBruh
#

set -e

UNAME="$(uname -m)"

if [[ "${UNAME}" = "aarch64" ]] || [[ "${UNAME}" = "armv8a" ]] || [[ "${UNAME}" = "armv8" ]]; then
    ARCH="aarch64"
else if [[ "${UNAME}" = "aarch32" ]] || [[ "${UNAME}" = "armv7a" ]] || [[ "${UNAME}" = "armv7" ]]; then
    ARCH="armv7a"
else
    echo "  - Unsupported arch: ${UNAME}!"
    exit 1
fi

VERSION="2.1.0"
REL_LINK="https://github.com/YZBruh/pbt/releseases/download/${VERSION}/pmt-${ARCH}-linux-android.xz"
CUR_DIR="$(pwd)"
TMP_DIR=${CUR_DIR}/tempinstall
TERMUX_BIN_PREFIX="/data/data/com.termux/files/usr/bin"

echo " ------------ pmt installer ------------"

if [ -f ${TERMUX_BIN_PREFIX}/pmt ]; then
    read -p "  - pmt already installed. Are you trying to update etc? (y/n) " state
    if [ "${state}" = "y" ]; then
        echo "  - Uninstalling..."
        rm ${TERMUX_BIN_PREFIX}/pmt
    else if [ "${state}" = "n" ]; then
        echo "  - Okay..."
        exit
    else
        echo "${0}: unexpected: ${state}"
        exit 1
    fi
fi

if [ ! -f ${TERMUX_BIN_PREFIX}/wget ]; then
    echo "  - İnstalling wget..."
    pkg update
    pkg install wget
fi

echo "  - Downloading latest version of package..."

mkdir -p ${TMP_DIR}
wget -q -P ${TMP_DIR} ${REL_LINK}

echo "  - Extracting downloaded package..."

cd ${TMP_DIR}
xz -d *.xz
rm *.xz
cd ${CUR_DIR}

echo "  - İnstalling..."

cp ${TMP_DIR}/* ${TERMUX_BIN_PREFIX}/pmt
chmod 777 ${TERMUX_BIN_PREFIX}/pmt

echo -e "  - Success.\n"

# end of script
