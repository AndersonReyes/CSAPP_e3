#include "../lib/Unity/src/unity.h"
#include "homework.h"
#include <limits.h>

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_get_lsb(void) {
  int result = get_lsb(0xABFF);
  TEST_ASSERT_EQUAL_HEX(0xFF, result);
}

void test_get_msb(void) {
  int result = get_msb(0x12345678);
  TEST_ASSERT_EQUAL_HEX(0x12, result);
}

void test_garble(void) {
  TEST_ASSERT_EQUAL_HEX(0x765432EF, garble(0x89ABCDEF, 0x76543210));
  TEST_ASSERT_EQUAL_HEX(0x89ABCD10, garble(0x76543210, 0x89ABCDEF));
}

void test_replace_byte(void) {
  TEST_ASSERT_EQUAL_HEX(0x1234AB78, replace_byte(0x12345678, 1, 0xAB));
  TEST_ASSERT_EQUAL_HEX(0xBA345678, replace_byte(0x12345678, 3, 0xBA));
}

void test_any_bit_set(void) {
  TEST_ASSERT_EQUAL_INT(1, any_bit_set(1));
  TEST_ASSERT_EQUAL_INT(1, any_bit_set(INT_MAX));
  TEST_ASSERT_EQUAL_INT(1, any_bit_set(3455534));
  TEST_ASSERT_EQUAL_INT(0, any_bit_set(0));
  TEST_ASSERT_EQUAL_INT(1, any_bit_set(INT_MIN));
}

void test_any_bit_zero(void) {
  TEST_ASSERT_EQUAL_INT(0, any_bit_zero(-1));
  TEST_ASSERT_EQUAL_INT(1, any_bit_zero(1));
  TEST_ASSERT_EQUAL_INT(1, any_bit_zero(3455534));
  TEST_ASSERT_EQUAL_INT(1, any_bit_zero(0));
  TEST_ASSERT_EQUAL_INT(1, any_bit_zero(INT_MIN));
}

void test_any_bit_set_in_least_sig_byte(void) {
  TEST_ASSERT_EQUAL_INT(1, any_bit_set_in_least_sig_byte(0xFFFF));
  TEST_ASSERT_EQUAL_INT(1, any_bit_set_in_least_sig_byte(0x0001));
  TEST_ASSERT_EQUAL_INT(0, any_bit_set_in_least_sig_byte(0x1100));
}

void test_any_bit_zero_in_most_sig_byte(void) {
  int bits = (sizeof(int) << 3) - 1;
  TEST_ASSERT_EQUAL_INT(1, any_bit_zero_in_most_sig_byte(1 << bits));
  TEST_ASSERT_EQUAL_INT(1, any_bit_zero_in_most_sig_byte(0x0001));
  TEST_ASSERT_EQUAL_INT(0, any_bit_zero_in_most_sig_byte(-1));
}

void test_int_shifts_are_arithmetic(void) {
  TEST_ASSERT_EQUAL_INT(1, int_shifts_are_arithmetic());
}

void test_srl(void) { TEST_ASSERT_EQUAL_INT(2, srl(1, 2)); }

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_get_lsb);
  RUN_TEST(test_get_msb);
  RUN_TEST(test_garble);
  RUN_TEST(test_replace_byte);
  RUN_TEST(test_any_bit_set);
  RUN_TEST(test_any_bit_zero);
  RUN_TEST(test_any_bit_set_in_least_sig_byte);
  RUN_TEST(test_any_bit_zero_in_most_sig_byte);
  RUN_TEST(test_int_shifts_are_arithmetic);
  RUN_TEST(test_srl);

  return UNITY_END();
}
