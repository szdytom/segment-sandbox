# Makefile

# compilers for C
CC := gcc

# compile flags for C
FLAGS := -Wall -Wextra -O2

OBJECT_LIST = sandbox.o namespace.o

static_lib : $(OBJECT_LIST)
	ar rcs libssandbox.a $(OBJECT_LIST)

sandbox_c : sandbox.c
	$(CC) $(FLAGS) -c sandbox.c -o sandbox.o

namespace_c : namespace.c
	$(CC) $(FLAGS) -c namespace.c -o namespace.o


.PHONY clean:
	rm -f *.o *.out