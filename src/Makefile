SHELL=/bin/sh
OS := $(shell uname -s)
GCC = gcc
GXX = g++
CFLAGS = -std=c11 -Wall -Werror -Wextra -lncurses
CXXFLAGS = -std=c++17 -Wall -Werror -Wextra -lncurses
T_FLAGS = -lcheck -lm -lncurses
BACK_DIR = brick_game/tetris
SNAKE_DIR = brick_game/snake
FRONT_DIR = gui/cli
DESK_DIR = gui/desktop/*
TEST_DIR = test
CLANG_FORMAT_PATH = ../materials/linters/.clang-format
BACK_SRCS = $(wildcard $(BACK_DIR)/*.c)
SNAKE_SRCS = $(wildcard $(SNAKE_DIR)/*.cpp) $(wildcard $(SNAKE_DIR)/*.c)
FRONT_SRCS = $(wildcard $(FRONT_DIR)/*.c) $(wildcard $(FRONT_DIR)/*.cpp)
FRONT_DESK = $(wildcard $(DESK_DIR)/*.cpp)
MAIN_SRC = gui/cli/main.cpp  # Новый файл с main функцией
CHECK = checkmk 
CHECK_SRSC = $(wildcard $(TEST_DIR)/*.check)
NAME = BrickGame
VERSION = _v0.1
DELETE = rm -rf

TEST_TARGET = $(TEST_DIR)/gtest_test
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)  # Исходные файлы тестов
TEST_LIBS = -L/usr/local/lib -lgtest -pthread

ifeq ($(OS),Linux)
    OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
    OPEN_CMD = open
endif

# Директория для выходных файлов
OUTPUT_DIR = $(NAME)

# Целевой исполняемый файл с указанием директории
TARGET_PATH = $(OUTPUT_DIR)/$(NAME)$(VERSION)

# Цели для десктопных версий
SNAKE_TARGET = $(OUTPUT_DIR)/SnakeDesktop
TETRIS_TARGET = $(OUTPUT_DIR)/TetrisDesktop

.PHONY: all install start ds dt clang clang_test test dvi dist uninstall clean gcov_report

all: install start

install: $(TARGET_PATH)

# Компиляция C файлов
$(BACK_DIR)/%.o: $(BACK_DIR)/%.c
	$(GCC) $(CFLAGS) -c $< -o $@

# Компиляция C++ файлов
$(SNAKE_DIR)/%.o: $(SNAKE_DIR)/%.cpp
	$(GXX) $(CXXFLAGS) -c $< -o $@

$(FRONT_DIR)/%.o: $(FRONT_DIR)/%.cpp
	$(GXX) $(CXXFLAGS) -c $< -o $@

# Компиляция main.cpp
$(FRONT_DIR)/main.o: $(MAIN_SRC)
	$(GXX) $(CXXFLAGS) -c $< -o $@

$(TARGET_PATH): $(BACK_SRCS:.c=.o) $(SNAKE_SRCS:.cpp=.o) $(FRONT_SRCS:.cpp=.o) $(FRONT_DIR)/main.o | $(OUTPUT_DIR)
	$(GXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

start: install
	./$(TARGET_PATH)

ds:
	$(DELETE) -rf temp
	mkdir -p temp && cd temp && qmake ../gui/desktop/S21_snake/S21_snake.pro
	cd temp && make
	mv temp/S21_snake.app/Contents/MacOS/S21_snake $(SNAKE_TARGET)
	$(DELETE) -rf temp
	./$(SNAKE_TARGET)

dt:
	$(DELETE) -rf temp
	mkdir -p temp && cd temp && qmake ../gui/desktop/S21_tetris/S21_tetris.pro
	cd temp && make
	mv temp/S21_tetris.app/Contents/MacOS/S21_tetris $(TETRIS_TARGET)
	$(DELETE) -rf temp
	./$(TETRIS_TARGET)


clang:
	cp "$(CLANG_FORMAT_PATH)" .clang-format
	clang-format -i $(BACK_SRCS) $(SNAKE_SRCS) $(FRONT_SRCS) $(FRONT_DESK)
	$(DELETE) .clang-format

clang_test:
	cp "$(CLANG_FORMAT_PATH)" .clang-format
	clang-format -n $(BACK_SRCS) $(SNAKE_SRCS) $(FRONT_SRCS) $(FRONT_DESK)
	$(DELETE) .clang-format

test: $(TEST_TARGET)
	$(TEST_TARGET)

$(TEST_TARGET): $(BACK_SRCS) $(SNAKE_SRCS) $(TEST_SRCS)
	$(GXX) $(CXXFLAGS) -pthread $^ $(TEST_LIBS) -o $@

gcov_report: clean
	$(GXX) $(CXXFLAGS) --coverage -pthread $(BACK_SRCS) $(SNAKE_SRCS) $(TEST_SRCS) $(TEST_LIBS) -o $(TEST_TARGET)
	$(TEST_TARGET)
	lcov --capture --branch-coverage --directory . --output-file $(TEST_DIR)/coverage.info --no-external --ignore-errors inconsistent,mismatch
	lcov --list $(TEST_DIR)/coverage.info
	genhtml $(TEST_DIR)/coverage.info --output-directory $(TEST_DIR)/coverage_report
	$(OPEN_CMD) $(TEST_DIR)/coverage_report/index.html
	rm -rf test/*.info test/*.gcno test/*.gcda test/gtest_test

dvi:
	@echo "Building HTML documentation..."
	@if [ ! -f "misc/docs.html" ]; then \
		echo "No such file!"; \
	else \
		if [ ! -d "docs" ]; then mkdir docs; fi; \
		cp misc/docs.html docs/docs.html; \
		echo "HTML documentation copied successfully."; \
		open docs/docs.html;  \
	fi

dist: clean
	@echo "Creating distribution package..."
	mkdir -p dist
	cp -r brick_game gui test Makefile misc dist/
	tar -czf $(NAME)$(VERSION).tar.gz dist
	$(DELETE) dist
	@echo "Distribution package created: $(NAME)$(VERSION).tar.gz"

uninstall:
	$(DELETE) "$(TARGET_PATH)"

clean:
	$(DELETE) -rf $(OUTPUT_DIR) *.o *.txt dist test_file *.gcno *.gcda *.gcov *.info report docs *.gz test/test.c test/coverage_report
	$(DELETE) $(SNAKE_DIR)/*.o $(BACK_DIR)/*.o $(FRONT_DIR)/*.o test/*.info test/*.gcno test/*.gcda 
