CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
OBJECTS = s21_grep

s21_grep :
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep -lpcre

test : s21_grep
	bash s21_grep_TESTS.sh

clear :
	rm $(OBJECTS)

rebuild : clear s21_grep
