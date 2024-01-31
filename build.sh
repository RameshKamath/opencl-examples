#!/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
rm -rf ${SCRIPT_DIR}/Build
mkdir -p ${SCRIPT_DIR}/Build
cmake -B ${SCRIPT_DIR}/Build -S ${SCRIPT_DIR}
cmake --build ${SCRIPT_DIR}/Build