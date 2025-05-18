CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -Wextra

SRC_DIR = .
TEST_DIR = ./tests/
OUT_TEST = $(TEST_DIR)test.out

# Файлы исходников
SRC_FILES = $(wildcard $(SRC_DIR)/s21_*/*.cpp)
OBJ_FILES = $(SRC_FILES:.cpp=.o)

# Файлы тестов
TEST_FILES = $(wildcard $(TEST_DIR)*.cpp)

# Имя библиотеки
LIB_NAME = s21_containers.a

OS := $(shell uname -s)

ifeq ($(OS),Linux)
    OPEN_CMD = xdg-open
    TEST_LIBS = -lgtest -lsubunit -lrt -lm -pthread
endif
ifeq ($(OS),Darwin)
    OPEN_CMD = open
    TEST_LIBS = -L/usr/local/lib -lgtest -pthread
endif

all: clean $(LIB_NAME)

$(LIB_NAME): $(OBJ_FILES)
	ar rcs $(LIB_NAME) $(OBJ_FILES)
	ranlib $(LIB_NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: build
	$(OUT_TEST)

build: clean
	$(CXX) $(CXXFLAGS) -o $(OUT_TEST) $(SRC_FILES) $(TEST_FILES) $(TEST_LIBS)

gcov_report: clean
	$(CXX) $(CXXFLAGS) --coverage -o $(TEST_DIR)gtest_test $(SRC_FILES) $(TEST_FILES) $(TEST_LIBS)
	chmod +x $(TEST_DIR)gtest_test
	$(TEST_DIR)gtest_test
	lcov --capture --branch-coverage --directory . --output-file $(TEST_DIR)coverage.info --no-external  --ignore-errors inconsistent,mismatch
	lcov --list $(TEST_DIR)coverage.info
	genhtml $(TEST_DIR)coverage.info --output-directory $(TEST_DIR)coverage_report
	$(OPEN_CMD) $(TEST_DIR)coverage_report/index.html

style_test:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -n $(SRC_FILES) $(TEST_FILES)
	rm -rf .clang-format

format_style:
	cp ../../materials/linters/.clang-format .clang-format
	clang-format -i $(SRC_FILES) $(TEST_FILES)
	rm -rf .clang-format

clean: clean_test
	rm -rf $(SRC_DIR)*/*.o $(LIB_NAME) $(TEST_DIR)*.out

clean_test:
	rm -rf $(TEST_DIR)*.gc*  $(TEST_DIR)*.dSYM $(TEST_DIR)*.info $(TEST_DIR)gtest_test $(TEST_DIR)coverage_report $(TEST_DIR)*.out $(TEST_DIR)*.out.* *.out

rebuild: clean build