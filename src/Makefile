# Makefile

# compilers for C
CC := g++

# compile flags for C
FLAGS := -Wall -Wextra -O2 -std=c++17

OBJECT_LIST = sandbox.o containerfs.o

static_lib : $(OBJECT_LIST)
	ar rcs libssandbox.a $(OBJECT_LIST)

sandbox_cc : sandbox.cc
	$(CC) $(FLAGS) -c sandbox.cc -o sandbox.o

containerfs_cc : containerfs.cc
	$(CC) $(FLAGS) -c containerfs.cc -o containerfs.o

.PHONY clean:
	rm -f *.o *.out