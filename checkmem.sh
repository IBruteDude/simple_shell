#!/bin/bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh \
	&&valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s \
	./hsh $* && rm hsh
