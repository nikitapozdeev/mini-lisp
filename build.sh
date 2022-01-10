#!/bin/bash

mkdir -p build
cc -std=c99 -Wall src/main.c -o build/minilisp.o