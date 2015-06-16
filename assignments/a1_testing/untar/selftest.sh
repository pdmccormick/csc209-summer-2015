#!/bin/bash

usage() {
    echo "usage: $0 your-untar-bin"
    exit -1
}

UNTAR_BIN=$1

if [[ -z "${UNTAR_BIN}" ]]; then
    usage
fi

if [[ ! -f "${UNTAR_BIN}" ]]; then
    echo "ERROR: ${UNTAR_BIN} does not exist"
    usage
fi

if [[ ! -x "${UNTAR_BIN}" ]]; then
    echo "ERROR: ${UNTAR_BIN} is NOT an executable file!"
    usage
fi

START_DIR=`pwd`
cd `dirname $0`
BASE_DIR=`pwd`

cd "${BASE_DIR}"

INPUTS="inputs/*"

for ARCHIVE in $INPUTS; do
    NAME="`basename $ARCHIVE`"
    NAME="${NAME%.tar}"

    ARCHIVE_PATH="${BASE_DIR}/${ARCHIVE}"

    echo "${NAME}:"

    OUTPUT_GNU_PATH="outputs/gnu-tar/${NAME}"
    OUTPUT_UNTAR_PATH="outputs/untar/${NAME}"

    # If they exist, delete old directories to clear their contents
    cd "${BASE_DIR}"
    [[ -d "${OUTPUT_GNU_PATH}" ]] && rm -rf "${OUTPUT_GNU_PATH}"
    [[ -d "${OUTPUT_UNTAR_PATH}" ]] && rm -rf "${OUTPUT_UNTAR_PATH}"

    # Use GNU tar(1) to extract the archive
    cd "${BASE_DIR}"
    mkdir -p "${OUTPUT_GNU_PATH}"
    cd "${OUTPUT_GNU_PATH}"
    tar xf "${ARCHIVE_PATH}"

    # Use provided untar binary to extract
    cd "${BASE_DIR}"
    mkdir -p "${OUTPUT_UNTAR_PATH}"
    cd "${OUTPUT_UNTAR_PATH}"
    "${UNTAR_BIN}" "${ARCHIVE_PATH}"

    # Use diff(1) to spot differences in resultant directory structures
    cd "${BASE_DIR}"
    diff -ru "${OUTPUT_GNU_PATH}" "${OUTPUT_UNTAR_PATH}"

    echo
done

echo "Self test completed."
