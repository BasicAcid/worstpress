CC := gcc

CFLAGS := -O2 \
          -Wall \
          -Wextra \
          -Wformat=2 \
          -Wformat-overflow \
          -Wformat-truncation \
          -Wshadow \
          -Wdouble-promotion \
          -Wundef \
          -fno-common \
          -z noexecstack \
          -Wconversion \
          -g

SRC := worstpress.c
TARGET := bin/worstpress

.PHONY: build

build: create_dir $(TARGET)

create_dir:
	mkdir -p bin

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

run: build
	$(TARGET)

cppcheck:
	cppcheck --enable=all --inconclusive --force --suppress=unusedFunction .

valgrind:
	 valgrind --tool=memcheck --leak-check=full --show-reachable=yes --num-callers=20 -s --track-fds=yes  --track-origins=yes ./bin/worstpress
