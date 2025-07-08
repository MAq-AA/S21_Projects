#include "test/s21_test.h"

int main(void) {
  Suite *s21_sprintf = create_sprintf_suite();
  Suite *s21_sscanf = create_sscanf_suite();

  SRunner *sr = srunner_create(s21_sprintf);
  srunner_add_suite(sr, s21_sscanf);

  srunner_run_all(sr, CK_NORMAL);
  int failed = srunner_ntests_failed(sr);
  printf("%d", failed);
  srunner_free(sr);
  return EXIT_SUCCESS;
}