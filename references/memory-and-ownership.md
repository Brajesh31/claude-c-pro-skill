# Memory Ownership and Safe Allocation

This reference is a practical review guide for C code that allocates or manages memory.

## Define ownership

For every pointer, decide which of these contracts applies:

- **Owning:** the holder is responsible for releasing the allocation exactly once.
- **Borrowed:** the holder may use the object but must not free it.
- **Transferred:** ownership moves to another function or object.
- **Shared:** multiple users access the object under an explicit lifetime and synchronization policy.

Document the contract in API comments. Avoid APIs where callers cannot tell whether they must free a returned pointer.

## Allocation rules

- Check the result of every allocation before dereferencing it.
- Use `sizeof *ptr` rather than repeating the pointed-to type.
- Check size calculations before multiplication or addition.
- Do not overwrite the only owning pointer with a failed `realloc` result.
- Initialize structures before a cleanup function can see them.
- Match allocation and deallocation strategies. Do not mix incompatible allocators.

Example of overflow-safe array allocation:

```c
#include <stdint.h>
#include <stdlib.h>

int allocate_items(size_t count, size_t item_size, void **out)
{
    if (out == NULL || item_size == 0U) {
        return -1;
    }

    *out = NULL;
    if (count > SIZE_MAX / item_size) {
        return -1;
    }

    void *memory = calloc(count, item_size);
    if (memory == NULL && count != 0U) {
        return -1;
    }

    *out = memory;
    return 0;
}
```

## Safe reallocation

Keep the original pointer until reallocation succeeds:

```c
void *next = realloc(buffer, new_size);
if (next == NULL) {
    /* buffer remains valid and still belongs to the caller */
    return -1;
}
buffer = next;
```

For a zero-size request, define behavior explicitly rather than relying on implementation-specific or historically varying `realloc(ptr, 0)` behavior.

## Cleanup paths

Use one clear cleanup path when a function acquires multiple resources. Track which resources were successfully acquired, release them in reverse order, and preserve the original error when cleanup itself can fail.

## Common defects to look for

- Memory leaks and double frees.
- Use-after-free and dangling pointers.
- Out-of-bounds reads and writes.
- Uninitialized memory.
- Integer overflow in allocation sizes.
- Incorrect assumptions about null termination.
- Returning addresses of local variables.
- Freeing borrowed or static storage.
- Losing an owning pointer after failed `realloc`.

## Verification

Use compiler warnings first. Add AddressSanitizer and UndefinedBehaviorSanitizer when available. Use Valgrind where supported. Tests should cover empty input, maximum or boundary sizes, allocation failures where injectable, and repeated create/destroy cycles.
