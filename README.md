# claude-c-pro-skill

A Claude Code skill for writing, reviewing, debugging, and optimizing reliable C programs with disciplined memory and systems programming practices.

## Overview

This skill focuses on C development where correctness, resource ownership, performance, and predictable failure behavior matter. It supports application code, low-level interfaces, embedded environments, POSIX programming, and performance-sensitive components.

## Core Topics

### Memory and Ownership

- Heap allocation and deallocation.
- Ownership transfer and object lifetime.
- Buffer sizing and bounds validation.
- Stack lifetime and pointer validity.
- Memory leaks, use-after-free, and double-free prevention.
- Allocation failure handling.

### Pointers and Data Structures

- Pointer arithmetic and array boundaries.
- Aliasing and alignment.
- Struct layout and data representation.
- Dynamic arrays, linked structures, and ownership rules.
- Invariants for safe mutation.

### Systems Programming

- POSIX APIs and system calls.
- File descriptors and resource cleanup.
- Processes, signals, and pipes.
- Correct handling of return values and `errno`.
- Portability and platform assumptions.

### Concurrency

- Thread lifecycle and synchronization.
- Mutexes and condition variables.
- Shared-state ownership.
- Data race and deadlock prevention.
- Safe shutdown and cleanup.

### Diagnostics and Performance

- Compiler warnings and strict build flags.
- Address and undefined-behavior sanitizers.
- GDB and Valgrind workflows.
- Static analysis and profiling.
- Measuring performance before optimizing.

## Installation

```bash
git clone https://github.com/Brajesh31/claude-c-pro-skill.git ~/.claude/skills/c-pro
```

## Usage

Invoke the skill for C-specific engineering tasks:

```text
/c-pro
```

Include the compiler, target platform, build system, expected behavior, and any memory or performance constraints.

## Recommended Workflow

1. Inspect the existing project conventions and build configuration.
2. Define ownership and lifetime for every allocated resource.
3. Check bounds and validate external input.
4. Implement explicit error handling and cleanup paths.
5. Compile with useful warnings enabled.
6. Run tests and relevant sanitizers.
7. Use profiling tools to locate actual performance bottlenecks.
8. Review portability and concurrency assumptions.

## Example Build

```bash
cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow \
  -g -O1 -fsanitize=address,undefined \
  -o app src/main.c
```

Adjust compiler flags and source paths to the target project. Sanitizers are development tools and should be configured appropriately for the deployment environment.

## Repository Contents

- `SKILL.md`: Main C engineering instructions.
- `Makefile`: Build and test entry points where configured.
- `examples/`: Focused implementation examples.
- `references/`: Memory ownership and systems programming guidance.
- `tests/`: Test cases for included examples.

## Code Quality Checklist

- Every allocation has a clear owner and release path.
- Buffer operations are bounds-checked.
- Return values are checked where failure is possible.
- File descriptors and other resources are closed on every path.
- Integer conversions and arithmetic overflow are considered.
- Shared state is synchronized correctly.
- Compiler warnings are addressed rather than suppressed blindly.
- Tests cover error paths as well as normal behavior.

## Important Principle

Readable, explicit C is usually safer than clever C. Optimize only after measuring, and never trade memory safety or clear ownership for a speculative performance gain.
