CC = g++
CFLAGS = -g -std=c++17 -Wall -Wextra -Werror
GCOVFLAGS = -fprofile-arcs -ftest-coverage

DIRINC = include

DIRFILES = files
CCFILES = $(DIRFILES)/s21_matrix_oop.cc
OBJ = $(CCFILES:.cc=.o)

TESTLIB = unit_tests
TESTFILES = $(TESTLIB)/test.cc
TESTAPP = $(TESTFILES:.cc=.app)

OS := $(shell uname -s)
ifeq ($(OS), Linux)
	MEMLEAKAGE = CK_FORK=no valgrind --leak-check=full --track-origins=yes -s ./$(TESTAPP)
else
	MEMLEAKAGE = leaks -atExit -- ./$(TESTAPP) | grep LEAK:
endif

LIB = s21_matrix_oop.a

all : $(LIB)

$(LIB) :
	$(CC) $(CFLAGS) -c $(TESTFILES) -o $(OBJ)
	ar rc $(LIB) $(OBJ)

clean :
	rm -rf $(DIRFILES)/*.o *.a $(TESTLIB)/*.app $(TESTLIB)/*.gcno $(TESTLIB)/*gcda gcov_report html.info

test :
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(TESTFILES) $(CCFILES) -o $(TESTAPP) -lgtest
	./$(TESTAPP)

gcov_report : test
	$(foreach file, $(wildcard $(GCNOTESTFILES)), gcov $(file);)
	lcov --capture --directory . --output-file html.info --no-external
	genhtml -o gcov_report html.info
	echo "Code coverage report generated in gcov_report directory."
	open gcov_report/index.html

style :
	clang-format -i -style=Google $(shell find . -name '*.cc') $(shell find . -name '*.h')

checking : test
	clear
	clang-format -n -style=Google $(DIRINC)/*.h $(CCFILES) $(TESTFILES)
	echo "\n\n"; $(MEMLEAKAGE)
	echo "\n\n"; cppcheck --enable=all --suppress=missingIncludeSystem $(CCFILES) $(TESTFILES)
	make clean
