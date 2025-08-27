OS := $(shell uname -s)
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
TEST_LIBS = -lcheck -lm -lpthread -lsubunit
OBJECTS = s21_decimal.o
SOURSES = s21_decimal.c
GCOVFLAGS = -fprofile-arcs -ftest-coverage

ifeq ($(OS), Darwin)
 FLAGS_PLATFORM = -lcheck
else
 FLAGS_PLATFORM = -lcheck -lsubunit -lrt -lm -lpthread
endif

all: clean s21_decimal.a test

s21_decimal.a: s21_decimal.o
	$(CC) $(CFLAGS) -g -c  $(SOURSES)
	ar rcs s21_decimal.a $(OBJECTS)

test: s21_test.c s21_decimal.a
	$(CC) $(CFLAGS) -c s21_test.c $(FLAGS_PLATFORM) -o s21_test.o
	$(CC) $(CFLAGS) -g s21_test.o s21_decimal.a $(FLAGS_PLATFORM) -o s21_test

gcov_report: s21_decimal.a
	$(CC) $(CFLAGS) --coverage s21_test.c s21_decimal.c s21_decimal.a $(FLAGS_PLATFORM) -o gcov_test
	chmod +x *
	./gcov_test
	lcov -t s21_test -o s21_test.info -c -d .
	genhtml -o report s21_test.info

rebuild: clean all

clean:
	rm -rf ./*.o ./*.a ./a.out gcov_test *.html *.css ./GcovReport ./*.gcno ./*.gcda ./report ./*.info ./s21_decimal.so ./*.dSYM ./s21_decimal_test s21_test

