# C Pro

A practical C programming skill for writing efficient, memory-safe, and maintainable systems code.

## Overview

C Pro guides C implementation and review with a focus on memory ownership, pointer safety, POSIX interfaces, embedded constraints, concurrency, debugging, and measured performance. It targets C99 and C11 projects unless the target project specifies otherwise.

## Capabilities

- Heap allocation, ownership, lifetimes, and leak prevention.
- Pointer arithmetic, buffers, data structures, and bounds checking.
- POSIX system calls, file descriptors, and error handling.
- Embedded and resource-constrained development.
- Pthreads and synchronization fundamentals.
- Debugging with GDB and Valgrind.
- Static analysis and compiler diagnostics.
- Performance profiling and benchmarking.

## Repository structure

```text
.
├── SKILL.md
├── README.md
├── LICENSE
├── .gitignore
├── Makefile
├── examples/
│   └── dynamic_array.c
├── references/
│   ├── memory-and-ownership.md
│   └── systems-programming-checklist.md
└── tests/
    └── test_dynamic_array.c
```

## Use the skill

Place `SKILL.md` in the skill directory recognized by your agent environment. The file contains the activation description, workflow, coding requirements, and links to the supporting references.

The repository's examples are standalone learning resources. They are not required runtime dependencies of the skill.

## Build the examples and tests

Requirements:
- A C compiler such as GCC or Clang.
- GNU Make or a compatible make implementation.
- A POSIX-like shell for the provided Makefile commands.

Build the example:

```bash
make example
./build/dynamic_array
```

Run the test program:

```bash
make test
```

Run a warning-enabled build:

```bash
make
```

Run sanitizer checks when supported by the compiler:

```bash
make sanitize
```

Remove generated files:

```bash
make clean
```

## Compiler flags

The Makefile defaults to C11 with `-Wall -Wextra -Wpedantic -Wconversion -Wshadow`. Override the compiler or flags when needed:

```bash
make CC=clang
make CFLAGS="-std=c99 -O2 -Wall -Wextra -Wpedantic"
```

Sanitizer support depends on the compiler and platform. Valgrind and clang-tidy are optional tools and are not required to build the examples.

## Validation

The included test covers dynamic-array initialization, growth, indexed access, and cleanup. The repository does not claim a test or sanitizer run has passed unless it has actually been executed in the target environment.

## License

MIT. See [LICENSE](LICENSE).
