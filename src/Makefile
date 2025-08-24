CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra

ifeq ($(shell uname),Linux)
# CF = -lm
	TEST_LIBS = -lcheck -lsubunit -lm
else
# CF =
	TEST_LIBS = -lcheck
endif

GCOV_FLAGS = --coverage

PHONY: all clean test s21_decimal.a gcov_report

all: s21_decimal.a


s21_decimal.a: s21_decimal_arifmetics.o
	ar rcs $@ $^


s21_decimal_arifmetics.o:
	$(CC) $(CFLAGS) -c s21_decimal_arifmetics.c -o $@
# $(CF)


test: tests.c s21_decimal.a
	$(CC) $(CFLAGS) $^ -o s21_test $(TEST_LIBS)
	./s21_test


clean:
	rm -rf *.o *.a s21_test *.gc* *.info html_report


rebuild: clean all


gcov_report:
	rm -rf *.o *.a s21_test *.gc* *.info html_report
	$(CC) $(CFLAGS) $(GCOV_FLAGS) s21_decimal_arifmetics.c tests.c -o s21_test $(TEST_LIBS)
	./s21_test
	lcov -t "s21_test" -c -d . --no-external -o report.info
	genhtml -o html_report report.info


check_code:
	clang-format -n *.c *.h
	cppcheck --enable=all --check-level=exhaustive --suppress=missingIncludeSystem *.c *.h
