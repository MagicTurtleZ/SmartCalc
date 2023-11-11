CC=gcc
FLAGS= -g -Wall -Werror -Wextra -std=c11
COVFLAGS = -fprofile-arcs -ftest-coverage
APP=./Application/SmartCalc.app
all: open

calc.a: calc.o
		ar rc calc.a calc.o
		ranlib calc.a
		rm *.o

calc.o: back_calc.c back.h
		$(CC) $(FLAGS) -c back_calc.c -o calc.o

test: calc.a
		$(CC) $(CFLAGS) test_calc.c -lcheck $(COVFLAGS) back_calc.c -o test_calc
		./test_calc
		make clean

gcov_report:
		$(CC) $(CFLAGS) test_calc.c -lcheck $(COVFLAGS) back_calc.c -o test_calc
		./test_calc
		lcov -t "Calc_tests" -o test_calc.info -c -d .
		genhtml -o report test_calc.info
		rm *.gcda *.gcno *.info
		open report/index.html
		make clean

clean:
		rm -rf *.a
		rm -rf *.dSYM
		rm -rf *.gcda
		rm -rf *.gcno

install:
	mkdir -p build && mkdir -p Application \
	&& cd build && cmake -DEXECUTABLE_OUTPUT_PATH="../Application" ../SmartCalc && cmake --build .

uninstall:
	rm -rf Application

open: install
		open $(APP)