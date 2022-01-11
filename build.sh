#!/bin/bash

mkdir -p build
cc -std=c99 -Wall src/main.c src/mpc.c -ledit -lm -o build/minilisp