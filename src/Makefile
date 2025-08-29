CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra

ifeq ($(shell uname),Linux)
	TEST_LIBS = -lcheck -lsubunit -lm
else
	TEST_LIBS = -lcheck
endif

GCOV_FLAGS = --coverage

.PHONY: all clean test s21_decimal.a gcov_report

all: s21_decimal.a

s21_decimal.a: s21_decimal.o
	ar rcs $@ $^

s21_decimal.o:
	$(CC) $(CFLAGS) -c s21_decimal.c -o $@

test: s21_test.c s21_decimal.a
	$(CC) $(CFLAGS) $^ -o s21_test $(TEST_LIBS)
	./s21_test

clean:
	rm -rf *.o *.a s21_test *.gc* *.info html_report

rebuild: clean all

gcov_report:
	rm -rf *.o *.a s21_test *.gc* *.info html_report
	$(CC) $(CFLAGS) $(GCOV_FLAGS) s21_decimal.c s21_test.c -o s21_test $(TEST_LIBS)
	./s21_test
	lcov -t "s21_test" -c -d . --no-external -o report.info
	genhtml -o html_report report.info

check_code:
	clang-format -n *.c *.h
	cppcheck --enable=all --check-level=exhaustive --suppress=missingIncludeSystem *.c *.h

stylize_code:
	clang-format -i *.c *.h