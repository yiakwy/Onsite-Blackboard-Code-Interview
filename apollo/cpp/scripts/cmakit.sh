#!/bin/bash

ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." && pwd )"

install_path=${ROOT}

args=(
"-DCMAKE_INSTALL_PREFIX:PATH=${install_path}"
"-DTEST=ON"
)

cd "${ROOT}/build"
if [ -f ~/ClangOverrides.txt ]; then
    cmake .. -DCMAKE_TOOLCHAIN_FILE=~/ClangOverrides.txt ${args}
else
    cmake .. ${args}
fi
