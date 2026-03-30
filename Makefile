CC = gcc
CFLAGS = -Wall -Wextra -I./include -lm
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests

VECTOR_SRC = $(SRC_DIR)/vector.c
MATRIX_SRC = $(SRC_DIR)/matrix.c
TEST_SRC = $(TEST_DIR)/test.c

all: test

test: $(VECTOR_SRC) $(MATRIX_SRC) $(TEST_SRC)
	$(CC) $(CFLAGS) $^ -o test

clean:
	rm -f test

.PHONY: all clean test
