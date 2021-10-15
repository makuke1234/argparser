CXX=g++

CDEFFLAGS=-std=c++20 -Wall -Wextra -Wpedantic -Wconversion
CDEBFLAGS=-g -O0
CFLAGS=-O3 -Wl,--strip-all,--build-id=none,--gc-sections -fno-ident

default: test

test: test.cpp
	$(CXX) $(CDEFFLAGS) $^ -o $@.exe $(CFLAGS)
	$@.exe
