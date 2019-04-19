#!/bin/bash

ROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )/.." && pwd )"

mkdir -p xcode

args=(
"-DTEST=ON"
)

cd xcode
cmake ${args} -G Xcode -H"${ROOT}" -B"${ROOT}/xcode/"
