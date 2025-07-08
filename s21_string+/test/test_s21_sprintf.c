#include <locale.h>

#include "s21_test.h"

#define GEN_TEST(fmt, ...)                                                     \
  res21 = s21_sprintf(bufs21, fmt, ##__VA_ARGS__);                             \
  restd = sprintf(bufstd, fmt, ##__VA_ARGS__);                                 \
  ck_assert_msg(strncmp(bufs21, bufstd, 16) == 0,                              \
                "\nFormat: '%s'\nExpected: '%s'\nActual:   '%s'", fmt, bufstd, \
                bufs21);                                                       \
  ck_assert_int_eq(res21, restd);

#define GEN_N_TEST(fmt, ...)                                                   \
  res21 = s21_sprintf(bufs21, fmt, __VA_ARGS__, &s21_n);                       \
  restd = sprintf(bufstd, fmt, __VA_ARGS__, &std_n);                           \
  ck_assert_msg(strcmp(bufs21, bufstd) == 0,                                   \
                "\nFormat: '%s'\nExpected: '%s'\nActual:   '%s'", fmt, bufstd, \
                bufs21);                                                       \
  ck_assert_int_eq(res21, restd);                                              \
  ck_assert_int_eq(s21_n, std_n);

START_TEST(int_test) {
  int res21, restd;
  char bufs21[512] = {0};
  char bufstd[512] = {0};
  GEN_TEST("%d", __INT32_MAX__)
  GEN_TEST("%u", __UINT32_MAX__)
  GEN_TEST("%hd", __INT16_MAX__)
  GEN_TEST("%ld", __INT64_MAX__)
  GEN_TEST("%lu", __UINT64_MAX__)
  GEN_TEST("%hu", __UINT16_MAX__)
  GEN_TEST("%x", __INT32_MAX__)
  GEN_TEST("%x", __UINT32_MAX__)
  GEN_TEST("%hx", __INT16_MAX__)
  GEN_TEST("%lx", __INT64_MAX__)
  GEN_TEST("%lx", __UINT64_MAX__)
  GEN_TEST("%hx", __UINT16_MAX__)
  GEN_TEST("%d", -__INT32_MAX__)
  GEN_TEST("%u", -__UINT32_MAX__)
  GEN_TEST("%hd", -__INT16_MAX__)
  GEN_TEST("%ld", -__INT64_MAX__)
  GEN_TEST("%lu", -__UINT64_MAX__)
  GEN_TEST("%hu", -__UINT16_MAX__)
  GEN_TEST("%x", -__INT32_MAX__)
  GEN_TEST("%x", -__UINT32_MAX__)
  GEN_TEST("%hx", -__INT16_MAX__)
  GEN_TEST("%lx", -__INT64_MAX__)
  GEN_TEST("%lx", -__UINT64_MAX__)
  GEN_TEST("%hx", -__UINT16_MAX__)
  GEN_TEST("%x", 12345)
  GEN_TEST("%X", 12345)
  GEN_TEST("%i", 12345)
  GEN_TEST("%o", 12345)
  GEN_TEST("%#x", -__INT32_MAX__)
  GEN_TEST("%#x", -__UINT32_MAX__)
  GEN_TEST("%#hx", -__INT16_MAX__)
  GEN_TEST("%#lx", -__INT64_MAX__)
  GEN_TEST("%#lx", -__UINT64_MAX__)
  GEN_TEST("%#hx", -__UINT16_MAX__)
  GEN_TEST("%#x", 12345)
  GEN_TEST("%#X", 12345)
  GEN_TEST("%#o", 12345)
  GEN_TEST("%p", (void *)__UINT64_MAX__)
  GEN_TEST("%p", S21_NULL)
  GEN_TEST("%13d", 12345)
  GEN_TEST("%160d", 12345)
  GEN_TEST("%.17d", 12345)
  GEN_TEST("%.100d", 12345)
  GEN_TEST("%-17d", 12345)
  GEN_TEST("%-100d", 12345)
  GEN_TEST("%-.13d", 12345)
  GEN_TEST("%-.130d", 12345)
  GEN_TEST("%0d", 12345)
  GEN_TEST("%013d", 12345)
  GEN_TEST("%0100d", 12345)
  GEN_TEST("%0d", 12345)
  GEN_TEST("%013d", 12345)
  GEN_TEST("%0100d", 12345)
  GEN_TEST("%100.13d", 12345)
  GEN_TEST("%10.13d", 12345)
  GEN_TEST("%10.5d", 12345)
  GEN_TEST("%6.10d", 12345)
  GEN_TEST("%+10.5d", 12345)
  GEN_TEST("%+10.10d", 12345)
  GEN_TEST("%+10.50d", 12345)
  GEN_TEST("% 10.5d", 12345)
  GEN_TEST("% 10.10d", 12345)
  GEN_TEST("% 10.50d", 12345)
}

START_TEST(str_char_test) {
  int res21, restd;
  char bufs21[512] = {0};
  char bufstd[512] = {0};
  GEN_TEST("%s", "asd")
  GEN_TEST("%10s", "asd")
  GEN_TEST("%-10s", "asd")
  GEN_TEST("%.10s", "asd")
  GEN_TEST("%-.10s", "asd")
  GEN_TEST("%10.10s", "asd")
  GEN_TEST("%5.10s", "asd")
  GEN_TEST("%10.5s", "asd")
  GEN_TEST("%-10.10s", "asd")
  GEN_TEST("%-5.10s", "asd")
  GEN_TEST("%-10.5s", "asd")
  GEN_TEST("%10s", "hello world!!!")
  GEN_TEST("%-10s", "hello world!!!")
  GEN_TEST("%.10s", "hello world!!!")
  GEN_TEST("%-.10s", "hello world!!!")
  GEN_TEST("%10.10s", "hello world!!!")
  GEN_TEST("%5.10s", "hello world!!!")
  GEN_TEST("%10.5s", "hello world!!!")
  GEN_TEST("%-10.10s", "hello world!!!")
  GEN_TEST("%-5.10s", "hello world!!!")
  GEN_TEST("%-10.5s", "hello world!!!")
  char *tmp_str = S21_NULL;
  GEN_TEST("%s", tmp_str)
  GEN_TEST("%10s", tmp_str)
  GEN_TEST("%.3s", tmp_str)
  GEN_TEST("%10.3s", tmp_str)
  GEN_TEST("%-10s", tmp_str)
  GEN_TEST("%-.3s", tmp_str)
  GEN_TEST("%-10.3s", tmp_str)
  GEN_TEST("%.7s", tmp_str)
  GEN_TEST("%10.7s", tmp_str)
  GEN_TEST("%-10s", tmp_str)
  GEN_TEST("%-.7s", tmp_str)
  GEN_TEST("%-10.7s", tmp_str)
  GEN_TEST("%s", "")
  GEN_TEST("%10s", "")
  GEN_TEST("%.5s", "")
  GEN_TEST("%10.3s", "")
  GEN_TEST("%-10s", "")
  GEN_TEST("%-.3s", "")
  GEN_TEST("%-10.3s", "")
}

START_TEST(float_test) {
  int res21, restd;
  char bufs21[512] = {0};
  char bufstd[512] = {0};
  GEN_TEST("%.20f", __FLT_MAX__)
  GEN_TEST("%f", __FLT_MIN__)
  GEN_TEST("%.20f", -__FLT_MAX__)
  GEN_TEST("%10.50Lf", __LDBL_MIN__)
  GEN_TEST("%10.50f", __FLT_MIN__)
  GEN_TEST("%10.10f", __FLT_MIN__)
  GEN_TEST("%50.10f", __FLT_MIN__)
  GEN_TEST("%f", 1.0)
  GEN_TEST("%-10.3f", 1.0)
  GEN_TEST("%#f", 1.0)
  GEN_TEST("%f", 1.1)
  GEN_TEST("%#f", 1.1)
  GEN_TEST("%-f", 1.1)
  GEN_TEST("%-#f", 1.1)
  GEN_TEST("%-f", 1123234342.0)
  GEN_TEST("%.3f", 0.0000000001)
  GEN_TEST("%.0f", 0.0000000001)
  GEN_TEST("%f", NAN)
  GEN_TEST("%f", INFINITY)
  GEN_TEST("% f", NAN)
  GEN_TEST("% f", INFINITY)
  GEN_TEST("%+f", NAN)
  GEN_TEST("%+f", INFINITY)
  GEN_TEST("%f", -NAN)
  GEN_TEST("%f", -INFINITY)
  GEN_TEST("%300.50f", __FLT_MIN__)
  GEN_TEST("%-.50f", __FLT_MIN__)
  GEN_TEST("% .50f", __FLT_MIN__)

  GEN_TEST("%E", __FLT_MAX__)
  GEN_TEST("%e", __FLT_MAX__)
  GEN_TEST("%e", __FLT_MIN__)
  GEN_TEST("%e", -__FLT_MAX__)
  GEN_TEST("%10.18e", __FLT_MIN__)
  GEN_TEST("%10.10Le", __LDBL_MIN__)
  GEN_TEST("%10.10e", __FLT_MIN__)
  GEN_TEST("%50.10e", __FLT_MIN__)
  GEN_TEST("%e", 1.0)
  GEN_TEST("%#e", 1.0)
  GEN_TEST("%e", 1.1)
  GEN_TEST("%#e", 1.1)
  GEN_TEST("%-e", 1.1)
  GEN_TEST("%-#e", 1.1)
  GEN_TEST("%-e", 1123234342.0)
  GEN_TEST("%.3e", 0.0000000001)
  GEN_TEST("%e", NAN)
  GEN_TEST("%e", INFINITY)
  GEN_TEST("%e", -NAN)
  GEN_TEST("%e", -INFINITY)
  GEN_TEST("%300.18e", __FLT_MIN__)
  GEN_TEST("%-.18e", __FLT_MIN__)
  GEN_TEST("% .18e", __FLT_MIN__)

  GEN_TEST("%G", __FLT_MAX__)
  GEN_TEST("%g", __FLT_MAX__)
  GEN_TEST("%g", __FLT_MIN__)
  GEN_TEST("%g", -__FLT_MAX__)
  GEN_TEST("%10.18g", __FLT_MIN__)
  GEN_TEST("%10.10g", __FLT_MIN__)
  GEN_TEST("%10.10Lg", __LDBL_MIN__)
  GEN_TEST("%50.10g", __FLT_MIN__)
  GEN_TEST("%g", 1.0)
  GEN_TEST("%#g", 1.0)
  GEN_TEST("%g", 1.1)
  GEN_TEST("%#g", 1.1)
  GEN_TEST("%-g", 1.1)
  GEN_TEST("%-#g", 1.1)
  GEN_TEST("%-g", 1123234342.0)
  GEN_TEST("%.3g", 0.0000000001)
  GEN_TEST("%g", NAN)
  GEN_TEST("%g", INFINITY)
  GEN_TEST("%g", -NAN)
  GEN_TEST("%g", -INFINITY)
  GEN_TEST("%300.18g", __FLT_MIN__)
  GEN_TEST("%-.18g", __FLT_MIN__)
  GEN_TEST("% .18g", __FLT_MIN__)
}

START_TEST(different_test) {
  int res21, restd;
  char bufs21[512] = {0};
  char bufstd[512] = {0};
  int s21_n;
  int std_n;
  GEN_N_TEST("%d%n", 123)
  GEN_N_TEST("%d%%%n", 123123123)
  GEN_N_TEST("% 100.10d%%%n", 123123123)
  GEN_N_TEST("%lc%n", L'a')
  GEN_N_TEST("%lc%n", L'г')
  GEN_N_TEST("%lc%n", L'Ω')
  GEN_N_TEST("%lc%n", L'试')
  GEN_N_TEST("%lc%n", L'😊')
  GEN_TEST("%-lc", L'😊')
  GEN_TEST("%-10c", 'd')
  GEN_TEST("%10c", 'd')
  char *tmp_str = S21_NULL;
  GEN_TEST("%-s", tmp_str)
  GEN_TEST("%-ls", L"😊")
  GEN_TEST("%-10.6ls", L"🌍 Hello!")
  GEN_TEST("%10.6ls", L"🌍 Hello!")
  GEN_TEST("%%%%%%%%%%%%%%%%%%%%%%%%%%%%")
  GEN_TEST("%*.*d", 20, 10, 123)
  GEN_TEST("%.*d", 10, 123)
  GEN_TEST("%*d", 10, 123)
  GEN_TEST(
      "slabsjdfbskadjnvsndvjnfskdvksnvlkjsabdlkvjlsadlvnlksanvknaskvnalsnvnskdj"
      "vnksanvknaskdvnnaskvnkfajnkvnvknfdvknjfnavkfnvkjandfkvjnadkfvnkanvkdajnf"
      "kvandkfvjnakfnvk")
  short int ss21_n;
  short int sstd_n;
  GEN_TEST("sdsf%hn", &ss21_n)
  GEN_TEST("sdsf%hn", &sstd_n)
  ck_assert_int_eq(ss21_n, sstd_n);
  long int ls21_n;
  long int lstd_n;
  GEN_TEST("sdsf%ln", &ls21_n)
  GEN_TEST("sdsf%ln", &lstd_n)
  ck_assert_int_eq(ls21_n, lstd_n);
}

START_TEST(mix_test) {
  int res21, restd;
  char bufs21[512] = {0};
  char bufstd[512] = {0};
  int s21_n;
  int std_n;
  GEN_TEST("%s %d %X %p%p%ls%g%f%.4s%n", "asd", 8888, 255, S21_NULL,
           (void *)0xFFFFFFFF, L"asdas", 1000000000000.1, 0.0000000000001,
           "hello", &s21_n)
  GEN_TEST("%s %d %X %p%p%ls%g%f%.4s%n", "asd", 8888, 255, S21_NULL,
           (void *)0xFFFFFFFF, L"asdas", 1000000000000.1, 0.0000000000001,
           "hello", &std_n)
  ck_assert_int_eq(s21_n, std_n);
}

Suite *create_sprintf_suite(void) {
  Suite *s = suite_create("S21_SPRINTF Tests");
  TCase *tc_core = tcase_create("Core");
  setlocale(LC_ALL, "en_US.UTF-8");
  tcase_add_test(tc_core, int_test);
  tcase_add_test(tc_core, str_char_test);
  tcase_add_test(tc_core, float_test);
  tcase_add_test(tc_core, different_test);
  tcase_add_test(tc_core, mix_test);

  suite_add_tcase(s, tc_core);
  return s;
}
