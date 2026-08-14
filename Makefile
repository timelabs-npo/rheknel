CC ?= cc
CMAKE ?= cmake
BUILD_DIR ?= build
STRICT_CFLAGS ?= -O2 -std=c99 -Wall -Wextra -Wpedantic -Werror
SOURCES = src/rhea.c src/omnia_bus.c src/platform.c src/sha256.c

.PHONY: all build test sanitize openbsd-test embed-check clean

all: build

build:
	$(CMAKE) -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Release
	$(CMAKE) --build $(BUILD_DIR) --config Release

test: build
	ctest --test-dir $(BUILD_DIR) --build-config Release --output-on-failure

sanitize:
	$(CMAKE) -S . -B $(BUILD_DIR)-sanitize -DCMAKE_BUILD_TYPE=Debug -DRHEKNEL_SANITIZE=ON
	$(CMAKE) --build $(BUILD_DIR)-sanitize
	ctest --test-dir $(BUILD_DIR)-sanitize --output-on-failure

openbsd-test:
	mkdir -p $(BUILD_DIR)/openbsd
	$(CC) $(STRICT_CFLAGS) -Iinclude -Isrc -Itests $(SOURCES) tests/test_omnia_bus.c -DOMNIA_FIXTURE_DIR='"tests/fixtures"' -o $(BUILD_DIR)/openbsd/omnia_bus_tests
	$(BUILD_DIR)/openbsd/omnia_bus_tests
	$(CC) $(STRICT_CFLAGS) -Iinclude -Isrc $(SOURCES) kernel.c -o $(BUILD_DIR)/openbsd/rhea
	$(BUILD_DIR)/openbsd/rhea tests/fixtures/omnia-dns-macos.omnb 1786665600

embed-check:
	mkdir -p $(BUILD_DIR)
	python3 tools/embed_omnia.py tests/fixtures/omnia-dns-macos.omnb $(BUILD_DIR)/omnia-dns-macos.h --symbol omnia_dns_macos
	cmp $(BUILD_DIR)/omnia-dns-macos.h tests/fixtures/omnia-dns-macos.h

clean:
	rm -rf $(BUILD_DIR) $(BUILD_DIR)-sanitize
