# Makefile

# compilers for C
CC := g++

# compile flags for C
FLAGS := -Wall -Wextra -O2 -std=c++11

OBJECT_LIST = sandbox.o namespace.o

static_lib : $(OBJECT_LIST)
	ar rcs libssandbox.a $(OBJECT_LIST)

sandbox_c : sandbox.c
	$(CC) $(FLAGS) -c sandbox.cc -o sandbox.o

.PHONY clean:
	rm -f *.o *.out