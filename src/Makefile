CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -Wextra

C_FILES = s21_matrix_oop.cpp
H_FILES = s21_matrix_oop.h

TEST_DIR = ./tests/
TEST_FILES = $(wildcard $(TEST_DIR)*.cpp)
OUT_TEST = $(TEST_DIR)test.out
OS := $(shell uname -s)

ifeq ($(OS),Linux)
    OPEN_CMD = xdg-open
    TEST_LIBS = -lgtest -lsubunit -lrt -lm -pthread -lstdc++
endif
ifeq ($(OS),Darwin)
    OPEN_CMD = open
	TEST_LIBS = -L/usr/local/lib -lgtest -pthread -lstdc++
endif

all: clean s21_matrix_oop.a

s21_matrix_oop.a: $(C_FILES) $(H_FILES)
	$(CXX) $(CXXFLAGS) -c $(C_FILES)
	ar rcs s21_matrix_oop.a s21_matrix_oop.o
	ranlib s21_matrix_oop.a
	rm -f *.o
test: rebuild
	$(OUT_TEST)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build: clean
	$(CXX) $(CXXFLAGS) -o $(OUT_TEST) $(C_FILES) $(TEST_FILES) $(TEST_LIBS)

gcov_report: clean
	$(CXX) $(CXXFLAGS) --coverage -o $(TEST_DIR)gtest_test $(C_FILES) $(TEST_FILES) $(TEST_LIBS)
	chmod +x $(TEST_DIR)gtest_test
	$(TEST_DIR)gtest_test
	lcov --capture --branch-coverage --directory . --output-file $(TEST_DIR)coverage.info --ignore-errors mismatch --no-external --ignore-errors inconsistent,inconsistent
	lcov --list $(TEST_DIR)coverage.info
	genhtml $(TEST_DIR)coverage.info --output-directory $(TEST_DIR)coverage_report
	$(OPEN_CMD) $(TEST_DIR)coverage_report/index.html

style_test:
	cp ../../materials/linters/.clang-format .clang-format 
	clang-format -n $(H_FILES) $(C_FILES) $(TEST_FILES) t_func.cpp
	rm -rf .clang-format

format_style:
	cp ../../materials/linters/.clang-format .clang-format 
	clang-format -i $(H_FILES) $(C_FILES) $(TEST_FILES) t_func.cpp
	rm -rf .clang-format

clean: clean_test
	rm -rf *.o s21_matrix_oop.a *.out report test.out

clean_test:
	rm -rf $(TEST_DIR)*.gc* $(TEST_DIR)*.info $(TEST_DIR)gtest_test $(TEST_DIR)coverage_report $(TEST_DIR)*.out $(TEST_DIR)*.out.*

rebuild: clean build