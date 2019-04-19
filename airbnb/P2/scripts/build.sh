#!/bin/bash

ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." && pwd )"

rm -rf ${ROOT}/build/
mkdir -p ${ROOT}/build/

cd build
source "../scritps/cmakit.sh"
