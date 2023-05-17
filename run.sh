#!/bin/bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c tests/main.c -o hsh && valgrind ./hsh && rm hsh
