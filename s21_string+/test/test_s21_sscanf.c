#include "s21_test.h"

#define GEN_SCANF_TEST(buf, fmt, var1, var2)                                 \
  res21 = s21_sscanf(buf, fmt, &var1);                                       \
  restd = sscanf(buf, fmt, &var2);                                           \
  ck_assert_msg(                                                             \
      res21 == restd,                                                        \
      "\nTest case failed (res) for input: \"%s\" with format \"%s\"\n"      \
      "Return value mismatch:\n"                                             \
      "s21_sscanf returned %d\n"                                             \
      "   sscanf returned %d",                                               \
      buf, fmt, res21, restd);                                               \
  ck_assert_msg(var1 == var2,                                                \
                "\nTest case failed for input: \"%s\" with format \"%s\"\n", \
                buf, fmt);

#define GEN_SCANF_STR_TEST(buf, fmt, var1, var2)                             \
  res21 = s21_sscanf(buf, fmt, var1);                                        \
  restd = sscanf(buf, fmt, var2);                                            \
  ck_assert_msg(                                                             \
      res21 == restd,                                                        \
      "\nTest case failed (res) for input: \"%s\" with format \"%s\"\n"      \
      "Return value mismatch:\n"                                             \
      "s21_sscanf returned %d\n"                                             \
      "   sscanf returned %d",                                               \
      buf, fmt, res21, restd);                                               \
  ck_assert_msg(strcmp(var1, var2) == 0,                                     \
                "\nTest case failed for input: \"%s\" with format \"%s\"\n", \
                buf, fmt);

#define GEN_SCANF_FLOAT_TEST(buf, fmt, var1, var2)                           \
  res21 = s21_sscanf(buf, fmt, &var1);                                       \
  restd = sscanf(buf, fmt, &var2);                                           \
  ck_assert_msg(                                                             \
      res21 == restd,                                                        \
      "\nTest case failed (res) for input: \"%s\" with format \"%s\"\n"      \
      "Return value mismatch:\n"                                             \
      "s21_sscanf returned %d\n"                                             \
      "   sscanf returned %d",                                               \
      buf, fmt, res21, restd);                                               \
  ck_assert_msg(fabs((double)(var1 - var2)) <= 1e-20,                        \
                "\nTest case failed for input: \"%s\" with format \"%s\"\n", \
                buf, fmt);

#define GEN_SCANF_MAX_LFLOAT_TEST(buf, fmt, var1, var2)                      \
  res21 = s21_sscanf(buf, fmt, &var1);                                       \
  restd = sscanf(buf, fmt, &var2);                                           \
  ck_assert_msg(                                                             \
      res21 == restd,                                                        \
      "\nTest case failed (res) for input: \"%s\" with format \"%s\"\n"      \
      "Return value mismatch:\n"                                             \
      "s21_sscanf returned %d\n"                                             \
      "   sscanf returned %d",                                               \
      buf, fmt, res21, restd);                                               \
  sprintf(bufs21, "%Lf", var1);                                              \
  sprintf(bufstd, "%Lf", var2);                                              \
  ck_assert_msg(strncmp(bufstd, bufs21, 20) == 0,                            \
                "\nTest case failed for input: \"%s\" with format \"%s\"\n", \
                buf, fmt);

#define GEN_SCANF_MAX_lFLOAT_TEST(buf, fmt, var1, var2)                      \
  res21 = s21_sscanf(buf, fmt, &var1);                                       \
  restd = sscanf(buf, fmt, &var2);                                           \
  ck_assert_msg(                                                             \
      res21 == restd,                                                        \
      "\nTest case failed (res) for input: \"%s\" with format \"%s\"\n"      \
      "Return value mismatch:\n"                                             \
      "s21_sscanf returned %d\n"                                             \
      "   sscanf returned %d",                                               \
      buf, fmt, res21, restd);                                               \
  sprintf(bufs21, "%lf", var1);                                              \
  sprintf(bufstd, "%lf", var2);                                              \
  ck_assert_msg(strncmp(bufstd, bufs21, 20) == 0,                            \
                "\nTest case failed for input: \"%s\" with format \"%s\"\n", \
                buf, fmt);

#define GEN_SCANF_MAX_FLOAT_TEST(buf, fmt, var1, var2)                  \
  res21 = s21_sscanf(buf, fmt, &var1);                                  \
  restd = sscanf(buf, fmt, &var2);                                      \
  ck_assert_msg(                                                        \
      res21 == restd,                                                   \
      "\nTest case failed (res) for input: \"%s\" with format \"%s\"\n" \
      "Return value mismatch:\n"                                        \
      "s21_sscanf returned %d\n"                                        \
      "   sscanf returned %d",                                          \
      buf, fmt, res21, restd);                                          \
  sprintf(bufs21, "%f", var1);                                          \
  sprintf(bufstd, "%f", var2);                                          \
  ck_assert_msg(strncmp(bufstd, bufs21, 16) == 0,                       \
                "\nTest case failed for input: \"%s\" with format "     \
                "\"%s\"\n%.20s\n%.20s\n",                               \
                buf, fmt, bufs21, bufstd);

START_TEST(int_test) {
  int res21, restd;
  int s21_dgt, std_dgt;
  unsigned s21_udgt, std_udgt;
  short int s21_sdgt, std_sdgt;
  unsigned short s21_sudgt, std_sudgt;
  long int s21_ldgt, std_ldgt;
  unsigned long s21_ludgt, std_ludgt;
  GEN_SCANF_TEST("+10000", "%d", s21_dgt, std_dgt)
  GEN_SCANF_TEST("0", "%d", s21_dgt, std_dgt)
  GEN_SCANF_TEST("-123450", "%d", s21_dgt, std_dgt)
  GEN_SCANF_TEST("2147483647", "%d", s21_dgt, std_dgt)
  GEN_SCANF_TEST("-2147483648", "%d", s21_dgt, std_dgt)
  GEN_SCANF_TEST("10000", "%u", s21_udgt, std_udgt)
  GEN_SCANF_TEST("0", "%u", s21_udgt, std_udgt)
  GEN_SCANF_TEST("-123450", "%u", s21_udgt, std_udgt)
  GEN_SCANF_TEST("4294967295", "%u", s21_udgt, std_udgt)
  GEN_SCANF_TEST("-4294967295", "%u", s21_udgt, std_udgt)
  GEN_SCANF_TEST("10000", "%hd", s21_sdgt, std_sdgt)
  GEN_SCANF_TEST("0", "%hd", s21_sdgt, std_sdgt)
  GEN_SCANF_TEST("–32768", "%hd", s21_sdgt, std_sdgt)
  GEN_SCANF_TEST("32767", "%hd", s21_sdgt, std_sdgt)
  GEN_SCANF_TEST("10000", "%hu", s21_sudgt, std_sudgt)
  GEN_SCANF_TEST("0", "%hu", s21_sudgt, std_sudgt)
  GEN_SCANF_TEST("–32768", "%hu", s21_sudgt, std_sudgt)
  GEN_SCANF_TEST("65535", "%hu", s21_sudgt, std_sudgt)
  GEN_SCANF_TEST("10000", "%ld", s21_ldgt, std_ldgt)
  GEN_SCANF_TEST("0", "%ld", s21_ldgt, std_ldgt)
  GEN_SCANF_TEST("-123450", "%ld", s21_ldgt, std_ldgt)
  GEN_SCANF_TEST("9223372036854775807", "%ld", s21_ldgt, std_ldgt)
  GEN_SCANF_TEST("-9223372036854775807", "%ld", s21_ldgt, std_ldgt)
  GEN_SCANF_TEST("10000", "%lu", s21_ludgt, std_ludgt)
  GEN_SCANF_TEST("0", "%lu", s21_ludgt, std_ludgt)
  GEN_SCANF_TEST("-123450", "%lu", s21_ludgt, std_ludgt)
  GEN_SCANF_TEST("18446744073709551615", "%lu", s21_ludgt, std_ludgt)
  GEN_SCANF_TEST("-9223372036854775807", "%lu", s21_ludgt, std_ludgt)
  GEN_SCANF_TEST("10000", "%3d", s21_dgt, std_dgt)
  GEN_SCANF_TEST("0", "%1d", s21_dgt, std_dgt)
  GEN_SCANF_TEST("-123450", "%20d", s21_dgt, std_dgt)
  GEN_SCANF_TEST("2147483647", "%10d", s21_dgt, std_dgt)
  GEN_SCANF_TEST("0xabcdef01223", "%x", s21_dgt, std_dgt)
  GEN_SCANF_TEST("0xabcdef01223", "%X", s21_dgt, std_dgt)
  GEN_SCANF_TEST("0xabcdef01223", "%2X", s21_dgt, std_dgt)
  GEN_SCANF_TEST("abcdef01223", "%X", s21_dgt, std_dgt)
  GEN_SCANF_TEST("01223", "%o", s21_dgt, std_dgt)
  GEN_SCANF_TEST("1223", "%o", s21_dgt, std_dgt)
  GEN_SCANF_TEST("01223", "%1o", s21_dgt, std_dgt)
  GEN_SCANF_TEST("01223", "%i", s21_dgt, std_dgt)
  GEN_SCANF_TEST("0xaBcdef01223", "%i", s21_dgt, std_dgt)
  GEN_SCANF_TEST("2147483", "%i", s21_dgt, std_dgt)
  GEN_SCANF_TEST("1223", "%i", s21_dgt, std_dgt)
  GEN_SCANF_TEST("abcdef01223", "%i", s21_dgt, std_dgt)
  GEN_SCANF_TEST("-2147483", "%i", s21_dgt, std_dgt)
  GEN_SCANF_TEST("-01223", "%i", s21_dgt, std_dgt)
  GEN_SCANF_TEST("-0xaBcdef01223", "%i", s21_dgt, std_dgt)
  GEN_SCANF_TEST("-0xaBcdef01223", "%x", s21_dgt, std_dgt)
  GEN_SCANF_TEST("-01223", "%o", s21_dgt, std_dgt)
  res21 = s21_sscanf("1500000", "%*d");
  restd = sscanf("1500000", "%*d");
  ck_assert_int_eq(res21, restd);
  res21 = s21_sscanf("1500000", "%*u");
  restd = sscanf("1500000", "%*u");
  ck_assert_int_eq(res21, restd);
  GEN_SCANF_TEST("18446744073709551632", "%lu", s21_ludgt, std_ludgt)
  GEN_SCANF_TEST("184467440737095516", "%u", s21_udgt, std_udgt)
  GEN_SCANF_TEST("184467440737095516", "%hu", s21_sudgt, std_sudgt)
  GEN_SCANF_TEST("184467440737095516", "%hd", s21_sdgt, std_sdgt)
  GEN_SCANF_TEST("184467440737095516", "%d", s21_dgt, std_dgt)
  GEN_SCANF_TEST("184467440737095516", "%ld", s21_ldgt, std_ldgt)
  GEN_SCANF_TEST("00fffffffaffffaff0", "%lx", s21_ludgt, std_ludgt)
  GEN_SCANF_TEST("00fffffffaffffaff0", "%x", s21_udgt, std_udgt)
  GEN_SCANF_TEST("00fffffffaffffaff0", "%hx", s21_sudgt, std_sudgt)
  GEN_SCANF_TEST("00fffffffaffffaff00", "%lx", s21_ludgt, std_ludgt)
  GEN_SCANF_TEST("00fffffffaffffaff00", "%x", s21_udgt, std_udgt)
  GEN_SCANF_TEST("00fffffffaffffaff00", "%hx", s21_sudgt, std_sudgt)
  GEN_SCANF_TEST("001000000000000000000010", "%lo", s21_ludgt, std_ludgt)
  GEN_SCANF_TEST("001000000000000000000010", "%o", s21_udgt, std_udgt)
  GEN_SCANF_TEST("001000000000000000000010", "%ho", s21_sudgt, std_sudgt)
  GEN_SCANF_TEST("0010000000000000000000010", "%lo", s21_ludgt, std_ludgt)
  GEN_SCANF_TEST("0010000000000000000000010", "%o", s21_udgt, std_udgt)
  GEN_SCANF_TEST("0010000000000000000000010", "%ho", s21_sudgt, std_sudgt)
  GEN_SCANF_TEST("000018446744073709551500", "%lu", s21_ludgt, std_ludgt)
  GEN_SCANF_TEST("000018446744073709551500", "%u", s21_udgt, std_udgt)
  GEN_SCANF_TEST("000018446744073709551500", "%hu", s21_sudgt, std_sudgt)
  GEN_SCANF_TEST("0000184467440737095515001", "%lu", s21_ludgt, std_ludgt)
  GEN_SCANF_TEST("0000184467440737095515001", "%u", s21_udgt, std_udgt)
  GEN_SCANF_TEST("0000184467440737095515001", "%hu", s21_sudgt, std_sudgt)
  GEN_SCANF_TEST("0009223372036854775800", "%ld", s21_ldgt, std_ldgt)
  GEN_SCANF_TEST("0009223372036854775800", "%d", s21_dgt, std_dgt)
  GEN_SCANF_TEST("0009223372036854775800", "%hd", s21_sdgt, std_sdgt)
  GEN_SCANF_TEST("00092233720368547758000", "%ld", s21_ldgt, std_ldgt)
  GEN_SCANF_TEST("00092233720368547758000", "%d", s21_dgt, std_dgt)
  GEN_SCANF_TEST(
      "000000000000000000100000000000000000000000000000000000000000000001",
      "%hd", s21_sdgt, std_sdgt)
  GEN_SCANF_TEST(
      "00000000000000000000000000000000000000000000000000000000000010001",
      "%hd", s21_sdgt, std_sdgt)
  GEN_SCANF_TEST("18446744073709551632", "%lu", s21_ludgt, std_ludgt)
  GEN_SCANF_TEST("9223372036854775808", "%ld", s21_ldgt, std_ldgt)
  GEN_SCANF_TEST("00000000000000000000000000000000000000000000000000", "%ld",
                 s21_ldgt, std_ldgt)
}

START_TEST(str_test) {
  int res21, restd;
  char* s21str = calloc(50, sizeof(char));
  char* stdstr = calloc(50, sizeof(char));
  char s21_c, std_c;
  GEN_SCANF_STR_TEST("hello world", "%s", s21str, stdstr)
  GEN_SCANF_STR_TEST(" hello world", "%s", s21str, stdstr)
  GEN_SCANF_STR_TEST("hello world", "%5s", s21str, stdstr)
  GEN_SCANF_TEST(" hello world", "%c", s21_c, std_c)
  GEN_SCANF_TEST("1", "%c", s21_c, std_c)
  GEN_SCANF_TEST("\n", "%c", s21_c, std_c)
  res21 = s21_sscanf("1500000.0", "%*c");
  restd = sscanf("1500000.0", "%*c");
  ck_assert_int_eq(res21, restd);
  res21 = s21_sscanf("1500000.0", "%*s");
  restd = sscanf("1500000.0", "%*s");
  ck_assert_int_eq(res21, restd);
  free(s21str);
  free(stdstr);
}

START_TEST(float_test) {
  int res21, restd;
  float s21_flt, std_flt;
  double s21_dbl, std_dbl;
  long double s21_ldbl, std_ldbl;
  char bufs21[200];
  char bufstd[200];
  GEN_SCANF_FLOAT_TEST("1.0", "%f", s21_flt, std_flt)
  GEN_SCANF_FLOAT_TEST("1.0", "%lf", s21_dbl, std_dbl)
  GEN_SCANF_FLOAT_TEST("1.0", "%Lf", s21_ldbl, std_ldbl)
  GEN_SCANF_FLOAT_TEST("1.0", "%g", s21_flt, std_flt)
  GEN_SCANF_FLOAT_TEST("1.0", "%G", s21_flt, std_flt)
  GEN_SCANF_FLOAT_TEST("1.0", "%e", s21_flt, std_flt)
  GEN_SCANF_FLOAT_TEST("1.0", "%E", s21_flt, std_flt)
  GEN_SCANF_FLOAT_TEST("12312312312312312312", "%Lf", s21_ldbl, std_ldbl)
  GEN_SCANF_FLOAT_TEST("112314243.123123123123123", "%f", s21_flt, std_flt)
  GEN_SCANF_MAX_LFLOAT_TEST("123123123123123123122.213617623761235712353",
                            "%Lf", s21_ldbl, std_ldbl)
  res21 = s21_sscanf("+nan", "%f", &s21_flt);
  ck_assert(!signbit(s21_flt) && isnan(s21_flt));
  res21 = s21_sscanf("-nan", "%f", &s21_flt);
  ck_assert(signbit(s21_flt) && isnan(s21_flt));
  GEN_SCANF_TEST("inf", "%f", s21_flt, std_flt)
  GEN_SCANF_TEST("-inf", "%f", s21_flt, std_flt)
  GEN_SCANF_TEST("inf", "%lf", s21_dbl, std_dbl)
  GEN_SCANF_TEST("inf", "%Lf", s21_ldbl, std_ldbl)
  GEN_SCANF_MAX_FLOAT_TEST("1.1e+20", "%f", s21_flt, std_flt)
  GEN_SCANF_MAX_FLOAT_TEST("1.1e+20", "%lf", s21_dbl, std_dbl)
  GEN_SCANF_MAX_LFLOAT_TEST("1.1e+20", "%Lf", s21_ldbl, std_ldbl)
  GEN_SCANF_MAX_FLOAT_TEST("1.1e-20", "%f", s21_flt, std_flt)
  GEN_SCANF_MAX_FLOAT_TEST("1.1e-20", "%lf", s21_dbl, std_dbl)
  GEN_SCANF_MAX_LFLOAT_TEST("1.1e-20", "%Lf", s21_ldbl, std_ldbl)
  res21 = s21_sscanf("1500000.0", "%*f");
  restd = sscanf("1500000.0", "%*f");
  ck_assert_int_eq(res21, restd);
  res21 = s21_sscanf("Inf", "%*f");
  restd = sscanf("Inf", "%*f");
  ck_assert_int_eq(res21, restd);
}

START_TEST(different_test) {
  int res21, restd;
  int s21_d, std_d;
  char s21_c, std_c;
  int s21_n, std_n;
  GEN_SCANF_TEST(" 1", "%d", s21_d, std_d)
  GEN_SCANF_TEST(" \n\n\n\t\t\t\t\t\t \n       1", "%d", s21_d, std_d)
  res21 = s21_sscanf(" 123 c\n%%", "%d %c %%%n", &s21_d, &s21_c, &s21_n);
  restd = sscanf(" 123 c\n%%", "%d %c %%%n", &std_d, &std_c, &std_n);
  ck_assert_int_eq(res21, restd);
  ck_assert_int_eq(s21_d, std_d);
  ck_assert_int_eq((int)s21_c, (int)std_c);
  ck_assert_int_eq(s21_n, std_n);
  res21 = s21_sscanf(" 123 c\n%%", " 124 c\n%%");
  restd = sscanf(" 123 c\n%%", " 124 c\n%%");
  ck_assert_int_eq(res21, restd);
  GEN_SCANF_TEST("", "%d", s21_d, std_d)
  void* s21_ptr;
  void* std_ptr;
  GEN_SCANF_TEST("0xFFFF", "%p", s21_ptr, std_ptr)
  GEN_SCANF_TEST("(nil)", "%p", s21_ptr, std_ptr)
  res21 = s21_sscanf("1", " %%");
  restd = sscanf("1", " %%");
  ck_assert_int_eq(res21, restd);
  short s21_sn, std_sn;
  res21 = s21_sscanf("12312312312312312312", "%*s%hn", &s21_sn);
  restd = sscanf("12312312312312312312", "%*s%hn", &std_sn);
  ck_assert_int_eq(res21, restd);
  ck_assert_int_eq(s21_sn, std_sn);
}

Suite* create_sscanf_suite(void) {
  Suite* s = suite_create("S21_SSCANF Tests");
  TCase* tc_core = tcase_create("Core");

  tcase_add_test(tc_core, int_test);
  tcase_add_test(tc_core, str_test);
  tcase_add_test(tc_core, float_test);
  tcase_add_test(tc_core, different_test);

  suite_add_tcase(s, tc_core);
  return s;
}