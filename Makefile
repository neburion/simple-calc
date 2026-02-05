# Flags
RELEASE_FLAGS = -Iinclude -O2 -DNDEBUG
DEBUG_FLAGS = -Iinclude -fsanitize=undefined,address -g -Wall -Wextra -Wpedantic
# Directories
SRC = $(wildcard src/*.c)
RELEASE_OBJ = $(patsubst src/%.c, build/release/%.o, $(SRC))
DEBUG_OBJ = $(patsubst src/%.c, build/debug/%.o, $(SRC))
# Compiler
CC = gcc
# Binaries
EXEC = bin/calc #linux release
DEXEC = bin/calc-debug #linux debug

# Default compile
all: $(EXEC)
$(EXEC): $(RELEASE_OBJ)
	$(CC) $(RELEASE_OBJ) -o $(EXEC)
# Debug compile
dbg: $(DEBUG_OBJ)
	$(CC) $(DEBUG_OBJ) $(DEBUG_FLAGS) -o $(DEXEC)

# Patern rules
build/release/%.o: src/%.c | release-build
	$(CC) $(RELEASE_FLAGS) -c $< -o $@

build/debug/%.o: src/%.c | debug-build
	$(CC) $(DEBUG_FLAGS) -c $< -o $@

#Ensure all needed directory exist
$(RELEASE_OBJ): | release-build
$(DEBUG_OBJ): | debug-build
$(EXEC): | bin
$(DEXEC): | bin
release-build:
	mkdir -p build/release
debug-build:
	mkdir -p build/debug
bin:
	mkdir -p bin
