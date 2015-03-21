# balloc Makefile
#
# lib: build library (builds to LIB_OUT, or out/libballoc.a)
# test: run tests
# clean: spring cleaning

CC ?= gcc
FLAGS ?= -O2 -Wall -DBALLOC_SAFE

LIB_OUT ?= out/libballoc.a
OBJ = out/obj/balloc.o

# test (requires built library) is default
default: test

# build shared library
lib: out $(LIB_OUT)

out:
	-mkdir -p out/obj

# archive library to libballoc.a file
$(LIB_OUT): $(OBJ)
	ar rcs $(LIB_OUT) $(OBJ)

# build shared library object files
out/obj/%.o: src/%.c
	$(CC) $(FLAGS) -c -o $@ $^

# run tests
test: lib
	bash test/test.sh

test/%.c.o: test/%.c
	$(CC) $(LIB_OUT) -Isrc $(FLAGS) $< -o $@

# clean
clean:
	rm -rf out

.PHONY: test out lib clean