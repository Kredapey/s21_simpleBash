CC = gcc
CFLAGS = -c -Wall -Werror -Wextra
CFLAGS_WC = -Wall -Werror -Wextra
all: s21_grep test

s21_grep: s21_grep.o grep.o
	$(CC) $(CFLAGS_WC) s21_grep.o grep.o -o s21_grep

s21_grep.o:
	$(CC) $(CFLAGS) s21_grep.c

grep.o:
	$(CC) $(CFLAGS) grep.c

test:
	sh test_func_grep.sh

clean:
	rm -rf *.o *.out s21_grep

rebuild: clean all