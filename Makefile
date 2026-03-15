# ==============================================================================
# Compiler & Flags
# ==============================================================================
CC      = gcc
LIBS    =
INCLUDE = -Iinclude

RELEASE_FLAGS = $(INCLUDE) -O2 -DNDEBUG
DEBUG_FLAGS   = $(INCLUDE) -g -Wall -Wextra -Wpedantic -fsanitize=undefined,address

# ==============================================================================
# Files
# ==============================================================================
SRC         = $(wildcard src/*.c)
TEST_SRC    = $(filter-out src/main.c, $(wildcard src/*.c))
RELEASE_OBJ = $(patsubst src/%.c, build/release/%.o, $(SRC))
DEBUG_OBJ   = $(patsubst src/%.c, build/debug/%.o, $(SRC))
TEST_OBJ    = $(patsubst src/%.c, build/test/%.o, $(TEST_SRC))

EXEC  = bin/calc
DEXEC = bin/dbg-calc
TEXEC = bin/test-calc

# ==============================================================================
# Targets
# ==============================================================================
.PHONY: all dbg test clean clean-release clean-debug

all: $(EXEC)

dbg: $(DEXEC)

test: $(TEXEC)

# ==============================================================================
# Binaries
# ==============================================================================
$(EXEC): $(RELEASE_OBJ) | bin
	$(CC) $(RELEASE_OBJ) -o $@ $(LIBS)

$(DEXEC): $(DEBUG_OBJ) | bin
	$(CC) $(DEBUG_OBJ) -o $@ $(LIBS) $(DEBUG_FLAGS)

$(TEXEC): $(TEST_OBJ) | bin
	$(CC) $(DEBUG_FLAGS) tests/test.c $(TEST_OBJ) -o $@ $(LIBS)

# ==============================================================================
# Object Files
# ==============================================================================
build/release/%.o: src/%.c | build/release
	$(CC) $(RELEASE_FLAGS) -c $< -o $@

build/debug/%.o: src/%.c | build/debug
	$(CC) $(DEBUG_FLAGS) -c $< -o $@

build/test/%.o: src/%.c | build/test
	$(CC) $(DEBUG_FLAGS) -c $< -o $@

# ==============================================================================
# Directories
# ==============================================================================
bin build/release build/debug build/test:
	mkdir -p $@

# ==============================================================================
# Clean
# ==============================================================================
clean:
	rm -rf build/ bin/

clean-release:
	rm -rf build/release/ $(EXEC)

clean-debug:
	rm -rf build/debug/ $(DEXEC)
