#!/bin/bash

rm -rf bin/
mkdir -p bin/

rm -rf lib/
mkdir -p lib/

gcc -Wall -Werror -fPIC -shared -o lib/libsep.so sep.c

gcc -Wall -Werror -o bin/ascii main.c