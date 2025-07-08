CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
OBJECTS = s21_cat

s21_cat : 
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat -lm

test : s21_cat
	bash s21_cat_TESTS.sh

clear :
	rm $(OBJECTS)

rebuild : clear s21_cat
