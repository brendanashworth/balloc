# balloc

> Mostly comprehensive C memory allocation library. Has equivalents for `free(3)`, `malloc(3)`, and `realloc(3)`.

### Features

* Memory safe mode (on by default, `-DBALLOC_SAFE`) that resets (to `NULL`) the memory when newly-allocated and free'd, rather than junk memory.
* Resets free'd pointers, preventing double-`free()` errors and vulnerabilities.
* Keeps track of allocated memory, able to be retrieved at any time with `ba_size()`.
* Errors on a failed allocation, rather than a hard to trace `NULL` pointer reference.

### Documentation
Read through [`balloc.h`](./src/balloc.h) for the documentation and forward declarations. When in doubt, [read the source code](./src/balloc.c). For examples, take a look at the [tests](./test/).

### Building
Building balloc requires:

* bash
* C compiler (gcc by default, change with `make CC=...`)
* file archiver (ar by default)

```sh
$ make
```

This will build a shared library file (which can be compiled against) to `out/libballoc.a` and will then run the tests.

#### Build shared library
You can specify a location to build the shared library to like so:

```sh
$ make LIB_OUT=/my/custom/dir/libballoc.a
```

#### Run tests
Tests will be run by the [`test.sh`](./test/test.sh) file. Run tests only like so:

```sh
$ make test
```

### License
[MIT licensed](./LICENSE). Enjoy :)