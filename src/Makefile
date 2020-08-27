# Makefile

# compilers for C++
CC = clang++

# compile flags for C++
FLAGS = -Wall -Wextra -O2 -std=c++17

OBJECT_LIST = sandbox.o containerfs.o userns.o

static_lib : $(OBJECT_LIST)
	ar rcs libssandbox.a $(OBJECT_LIST)

sandbox.o : sandbox.cc
	$(CC) $(FLAGS) -c sandbox.cc -o sandbox.o

containerfs.o : containerfs.cc
	$(CC) $(FLAGS) -c containerfs.cc -o containerfs.o

userns.o : userns.cc
	$(CC) $(FLAGS) -c userns.cc -o userns.o

.PHONY clean:
	rm -f *.o *.out