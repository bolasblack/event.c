CC ?= gcc
CFLAGS = -std=c99 -Ideps -Wall

SRC = $(wildcard src/*.c)
DEPS = $(wildcard deps/*/*.c)

test: test.c $(SRC) $(DEPS)
	@$(CC) $(CFLAGS) $^ -o $@
	@./$@

.PHONY: test
