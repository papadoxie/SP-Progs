#!/usr/bin/env bash

gcc -c sys/helloworld.c -o sys/helloworld.o
ar -rs sys/libhelloworld.a sys/helloworld.o
gcc test.c -o test -Lsys -lhelloworld