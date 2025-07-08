#ifndef S21_STRING_H
#define S21_STRING_H
#endif
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

#if defined(__GNUC__) || defined(__clang__)
#define S21_SCANF_ATTR(format_idx, arg_idx) \
  __attribute__((format(scanf, format_idx, arg_idx)))
#define S21_FORMAT_ATTR(format_idx, arg_idx) \
  __attribute__((format(printf, format_idx, arg_idx)))
#else
#define S21_SCANF_ATTR(format_idx, arg_idx)
#endif

#define S21_NULL ((void *)0)
typedef unsigned long s21_size_t;
typedef int s21_wchar_t;

void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

int s21_sprintf(char *str, const char *format, ...) S21_FORMAT_ATTR(2, 3);

int s21_sscanf(const char *str, const char *format, ...) S21_SCANF_ATTR(2, 3);