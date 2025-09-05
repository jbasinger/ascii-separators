#!/bin/bash

set -e

export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$(pwd)/lib"

./build.sh
gcc -Wall -Werror -o bin/test_app -I./ test/main.c -Llib/ -lsep

bin/test_app