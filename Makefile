CC ?= cc
CFLAGS ?= -std=c11 -O2 -Wall -Wextra -Wpedantic -Wconversion -Wshadow
CPPFLAGS ?= -I.
BUILD_DIR := build
EXAMPLE := $(BUILD_DIR)/dynamic_array
TEST := $(BUILD_DIR)/test_dynamic_array

.PHONY: all example test sanitize clean

all: example

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

example: $(EXAMPLE)

$(EXAMPLE): examples/dynamic_array.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@

$(TEST): tests/test_dynamic_array.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@

test: $(TEST)
	./$(TEST)

sanitize: CFLAGS += -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer
sanitize: clean test

clean:
	rm -rf $(BUILD_DIR)
