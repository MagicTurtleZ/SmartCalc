#include "./back.h"
#include "check.h"

START_TEST(format_1) {
  char check_str[256] =
      "cos(x - 10 ^ 2) * 2 mod (-5) + sin(1) + tan(1) + acos(1) + asin(1) + "
      "atan(1) + sqrt(1) + ln(1) + log(1)";
  char exp_str[256] =
      "c(~5.000000 - 10 ^ 2) * 2 % (~5) + s(1) + t(1) + a(1) + i(1) + n(1) + "
      "q(1) + l(1) + o(1)";
  string_format(check_str, -5);
  ck_assert_str_eq(check_str, exp_str);
}
END_TEST

Suite *s21_string_format(void) {
  Suite *suite = suite_create("\033[01;36mFORMAT\033[0m");
  TCase *tcase_test = tcase_create("FORMAT");

  tcase_add_test(tcase_test, format_1);

  suite_add_tcase(suite, tcase_test);
  return suite;
}

START_TEST(polish_1) {
  char check_str[256] =
      "cos(x - 10 ^ 2) * 2 mod -5 + sin(1) + tan(1) + acos(1) + asin(1) + "
      "atan(1) + sqrt(1) + ln(1) + log(1)";
  char exp_str[256] =
      "5.000000 ~10 2 ^-c2 *5 ~%1 s+1 t+1 a+1 i+1 n+1 q+1 l+1 o+";
  char polish_str[256] = {0};
  string_format(check_str, -5);
  to_polish(check_str, polish_str);
  ck_assert_str_eq(polish_str, exp_str);
}
END_TEST

Suite *s21_to_polish(void) {
  Suite *suite = suite_create("\033[01;36mPOLISH\033[0m");
  TCase *tcase_test = tcase_create("POLISH");

  tcase_add_test(tcase_test, polish_1);

  suite_add_tcase(suite, tcase_test);
  return suite;
}

START_TEST(calc_1) {
  char input_str[256] = "cos(x - 10 ^ 2) * 2";
  char polish_str[256] = {0};
  double res = 0;
  double exp_res = 0.256107;
  string_format(input_str, -5);
  to_polish(input_str, polish_str);
  calc_comp(polish_str, &res);
  // printf("%lf\n", res);
  ck_assert_double_eq_tol(res, exp_res, 0.0001);
}
END_TEST

START_TEST(calc_2) {
  char input_str[256] = "8 + 10 / 2 * sin(x)";
  char polish_str[256] = {0};
  double res = 0;
  double exp_res = 8.19178;
  string_format(input_str, -5);
  to_polish(input_str, polish_str);
  calc_comp(polish_str, &res);
  // printf("%lf\n", res);
  ck_assert_double_eq_tol(res, exp_res, 0.0001);
}
END_TEST

Suite *s21_calc_comp(void) {
  Suite *suite = suite_create("\033[01;36mCALC\033[0m");
  TCase *tcase_test = tcase_create("CALC");

  tcase_add_test(tcase_test, calc_1);
  tcase_add_test(tcase_test, calc_2);

  suite_add_tcase(suite, tcase_test);
  return suite;
}

int main(void) {
  Suite *tests_list[] = {s21_string_format(), s21_to_polish(), s21_calc_comp(),
                         NULL};

  int failed_count = 0;

  for (int i = 0; tests_list[i] != NULL; i++) {
    SRunner *suite_runner = srunner_create(tests_list[i]);
    srunner_set_fork_status(suite_runner, CK_NOFORK);
    srunner_run_all(suite_runner, CK_NORMAL);
    failed_count = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);
  }
  return failed_count == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
