#!/bin/bash

## Script to build the example deployment
##
## This script just calls fprime-util generate
## and fprime-util build

set -e

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

cd ${SCRIPT_DIR}/MathOpsExampleDeployment
rm -fr build-*

fprime-util generate -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
fprime-util build --jobs $(nproc)
