# Systems Programming Checklist

Use this checklist when implementing or reviewing POSIX-facing C code.

## System-call discipline

- Check every return value according to that API's contract.
- Consult `errno` only when the API indicates it is meaningful.
- Handle interrupted operations where the API requires retrying after `EINTR`.
- Handle short reads and writes. A successful call may process fewer bytes than requested.
- Close file descriptors on every exit path.
- Do not retry an operation blindly when retrying could duplicate side effects.
- Preserve useful error context for callers.

## File descriptors and I/O

- Track descriptor ownership and close responsibility.
- Treat descriptor value zero as valid.
- Avoid assuming a read fills the requested buffer.
- Avoid assuming input is null-terminated.
- Check conversions between signed return values and unsigned sizes.
- Define behavior for nonblocking descriptors and partial progress.

## Threads

- Check pthread function return codes. They generally return an error number directly rather than using `errno`.
- Pair mutex lock/unlock operations on all paths.
- Define which thread owns and destroys each synchronization object.
- Avoid holding locks while calling unknown callbacks or performing slow I/O.
- Use condition variables with a predicate loop.
- Join or detach created threads according to a documented lifecycle.
- Protect shared mutable state consistently.

## Embedded and constrained targets

- Establish RAM, flash, and stack budgets.
- Avoid large automatic arrays when stack size is constrained.
- Prefer bounded buffers and explicit capacity limits.
- Decide whether dynamic allocation is permitted.
- Define timeout and failure behavior for hardware-facing operations.
- Avoid unbounded loops in real-time or watchdog-sensitive paths.
- Keep platform-specific code behind narrow interfaces.

## Build and diagnostics

- Enable `-Wall -Wextra -Wpedantic` and address warnings.
- Select the intended C standard explicitly.
- Use debug symbols for development builds.
- Run static analysis where available.
- Use sanitizers on supported host builds.
- Use GDB for state and control-flow inspection.
- Use Valgrind on supported platforms for leak and invalid-access checks.
- Profile representative workloads before optimization.

## Review questions

1. What happens if each allocation or system call fails?
2. Who owns each resource, and where is it released?
3. Can a size calculation overflow?
4. Can another thread observe partially updated state?
5. Are all buffers bounded and correctly terminated where required?
6. Are platform and compiler assumptions documented?
7. Are tests exercising error paths and boundary conditions?
