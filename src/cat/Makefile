CC = gcc
CFLAGS = -c -Wall -Werror -Wextra
CFLAGS_WC = -Wall -Werror -Wextra
all: s21_cat test

s21_cat: s21_cat.o cat.o
	$(CC) $(CFLAGS_WC) s21_cat.o cat.o -o s21_cat

s21_cat.o:
	$(CC) $(CFLAGS) s21_cat.c

cat.o:
	$(CC) $(CFLAGS) cat.c

test:
	sh test_func_cat.sh

clean:
	rm -rf *.o *.out s21_cat

rebuild: clean all