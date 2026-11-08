#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t length;
    size_t capacity;
} IntArray;

static void int_array_destroy(IntArray *array)
{
    if (array == NULL) {
        return;
    }

    free(array->items);
    array->items = NULL;
    array->length = 0U;
    array->capacity = 0U;
}

static bool int_array_reserve(IntArray *array, size_t required)
{
    if (array == NULL) {
        return false;
    }
    if (required <= array->capacity) {
        return true;
    }

    const size_t max_items = (size_t)-1 / sizeof *array->items;
    if (required > max_items) {
        return false;
    }

    size_t next_capacity = array->capacity == 0U ? 4U : array->capacity;
    while (next_capacity < required) {
        if (next_capacity > max_items / 2U) {
            next_capacity = required;
            break;
        }
        next_capacity *= 2U;
    }

    int *next_items = realloc(array->items,
                              next_capacity * sizeof *array->items);
    if (next_items == NULL) {
        return false;
    }

    array->items = next_items;
    array->capacity = next_capacity;
    return true;
}

static bool int_array_push(IntArray *array, int value)
{
    if (array == NULL || array->length == (size_t)-1) {
        return false;
    }
    if (!int_array_reserve(array, array->length + 1U)) {
        return false;
    }

    array->items[array->length++] = value;
    return true;
}

int main(void)
{
    IntArray array = {NULL, 0U, 0U};

    assert(array.length == 0U);
    assert(array.capacity == 0U);
    assert(int_array_push(&array, 7));
    assert(int_array_push(&array, 14));
    assert(int_array_push(&array, 21));
    assert(int_array_push(&array, 28));
    assert(int_array_push(&array, 35));

    assert(array.length == 5U);
    assert(array.capacity >= array.length);
    assert(array.items[0] == 7);
    assert(array.items[1] == 14);
    assert(array.items[2] == 21);
    assert(array.items[3] == 28);
    assert(array.items[4] == 35);

    assert(!int_array_push(NULL, 1));
    assert(!int_array_reserve(NULL, 10U));

    int_array_destroy(&array);
    assert(array.items == NULL);
    assert(array.length == 0U);
    assert(array.capacity == 0U);

    int_array_destroy(&array);
    return EXIT_SUCCESS;
}
