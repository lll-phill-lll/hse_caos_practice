# Сборка демо "интерпретация vs JIT" поверх LLVM.
# Все флаги берём из llvm-config, поэтому Makefile портируемый:
# одинаково работает на Arch Linux x86_64 и на macOS arm64.
#
#   make            — собрать ./jitdb
#   make run        — собрать и прогнать демо с дефолтным запросом
#   make clean

LLVM_CONFIG ?= llvm-config

CXX      ?= clang++
CXXFLAGS := $(shell $(LLVM_CONFIG) --cxxflags) -O2 -Wall -Wextra
LDFLAGS  := $(shell $(LLVM_CONFIG) --ldflags)
LIBS     := $(shell $(LLVM_CONFIG) --libs core orcjit native passes) \
            $(shell $(LLVM_CONFIG) --system-libs)

# dlopen/dlsym: на Linux нужен -ldl, на macOS он встроен в libc.
ifeq ($(shell uname -s),Linux)
  LIBS += -ldl
endif

SRC := main.cpp jit.cpp cppjit.cpp
BIN := jitdb

# Запрос и размер таблицы можно переопределить:  make run ROWS=20000000 Q='c0*c1 + c2'
ROWS ?= 30000000
Q    ?= (c0*c0 + c1*c1 < 5000) ? max(c0, c1) : c2 - c3

all: $(BIN)

$(BIN): $(SRC) expr.hpp interp.hpp jit.hpp cppjit.hpp
	$(CXX) $(CXXFLAGS) $(SRC) -o $(BIN) $(LDFLAGS) $(LIBS)

run: $(BIN)
	./$(BIN) --rows $(ROWS) "$(Q)"

clean:
	rm -f $(BIN)

.PHONY: all run clean
