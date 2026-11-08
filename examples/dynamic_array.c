#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
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

    array->items[array->length] = value;
    array->length += 1U;
    return true;
}

int main(void)
{
    IntArray values = {NULL, 0U, 0U};

    for (int value = 1; value <= 5; ++value) {
        if (!int_array_push(&values, value * 10)) {
            (void)fprintf(stderr, "Could not append value %d\n", value);
            int_array_destroy(&values);
            return EXIT_FAILURE;
        }
    }

    for (size_t index = 0U; index < values.length; ++index) {
        (void)printf("%d%c", values.items[index],
                     index + 1U == values.length ? '\n' : ' ');
    }

    int_array_destroy(&values);
    return EXIT_SUCCESS;
}
