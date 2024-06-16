#!/data/data/com.termux/files/usr/bin/env bash
#
# By YZBruh
#

set -ex

VERSION="2.1.0"
CUR_DIR="$(pwd)"
TMP_DIR="${CUR_DIR}/tempinstall"
TERMUX_BIN_PREFIX="/data/data/com.termux/files/usr/bin"
UNAME="$(uname -m)"

abort()
{
    rm -rf "${TMP_DIR}"
    exit 1
}

echo " ------------ pmt installer ------------"

if [[ "${UNAME}" == "aarch64" ]] || [[ "${UNAME}" == "armv8a" ]]; then
    ARCH="aarch64"
elif [[ "${UNAME}" == "aarch32" ]] || [[ "${UNAME}" == "armv7a" ]]; then
    ARCH="armv7a"
    SUB_PREF="eabi"
else
    echo "  - Unsupported arch: ${UNAME}!"
    abort
fi

REL_LINK="https://github.com/YZBruh/pbt/releases/download/${VERSION}/pmt-${ARCH}-linux-android${SUB_PREF}.xz"

if [ -f "${TERMUX_BIN_PREFIX}/pmt" ]; then
    read -p "  - pmt already installed. Are you trying to update etc? (y/n) " state
    if [ "${state}" == "y" ]; then
        echo "  - Uninstalling..."
        rm "${TERMUX_BIN_PREFIX}/pmt"
    elif [ "${state}" == "n" ]; then
        echo "  - Okay..."
        exit
    else
        echo "${0}: unexpected: ${state}"
        abort
    fi
fi

if [ ! -f "${TERMUX_BIN_PREFIX}/wget" ]; then
    echo "  - Installing wget..."
    pkg update
    pkg install wget
fi

echo "  - Downloading latest version of package..."

mkdir -p "${TMP_DIR}"
wget -q -P "${TMP_DIR}" "${REL_LINK}"

echo "  - Extracting downloaded package..."

cd "${TMP_DIR}"
xz -d *.xz
cd "${CUR_DIR}"

echo "  - Installing..."

cp "${TMP_DIR}/*" "${TERMUX_BIN_PREFIX}/pmt"
chmod 777 "${TERMUX_BIN_PREFIX}/pmt"
rm -rf "${TMP_DIR}"

echo -e "  - Success.\n"

# end of script
