#include <limits.h>
#include <stdio.h>

int is_little_endian() {
  int v = 0x1234567;
  char *p = (char *)&v;

  printf("%d", p[0]);
  printf("%d", p[63]);
  return 0;
}

// 2.59
// print the least significant bytes of x and rest of y
// ex. x = 0x89ABCDEF,  y = 0x76543210
// prints 0x765432EF
int garble(int x, int y) {
  int mask = x & 0xFF;
  int result = (y & 0xFFFFFFFF00) | mask;
  return result;
}

// 2.60
// replaces byte i in x, by byte b
int replace_byte(unsigned int x, int i, unsigned char b) {
  int shift_bytes = i * 8;
  int mask = ~(0xFF << shift_bytes);
  int byte_mask = b << shift_bytes;
  unsigned int result = (x & mask) | byte_mask;

  // printf("2.60 inputs: (%X, %d, %X), mask: 0x%X, byte_mask: 0x%X, result:
  // %X\n",
  //        x, i, b, mask, byte_mask, result);
  return result;
}

// Get the most significant byte
int get_msb(int x) {
  int num_bits = (sizeof(int) - 1) << 3;
  int mask = 0xFF << num_bits;
  int result = ((x & mask) >> num_bits);
  result = result & 0xFF; // clear out all other bits
  /* printf("most significant byte of %X is %X\n", x, result); */
  return result;
}

// least significant byte
int get_lsb(int x) {
  int result = x & 0xFF; // clear out all other bits
  /* printf("least significant byte of %X is %X\n", x, result); */
  return result;
}

// 2.61 #A
// is any bit set to 1
// becareful with sign bit
int any_bit_set(int x) {
  int drop_sign = x & INT_MAX;
  int result = drop_sign != 0;
  /*   printf("2.61 A: %X has any bit set to 1? %d\n", x, result); */
  return result;
}

// 2.61 #B
// is any bit set to 0
// becareful with sign bit
int any_bit_zero(int x) {
  int drop_sign = x & INT_MAX;
  int result = drop_sign != INT_MAX;
  printf("2.61 B: %X has any bit set to 0? %d\n", drop_sign, result);
  return result;
}

// 2.61 #C
// is any bit set to 1 in least significant byte
// becareful with sign bit
int any_bit_set_in_least_sig_byte(int x) {
  int result = any_bit_set(get_lsb(x));
  printf("2.61 C:(%X) %d\n", x, result);
  return result;
}

// 2.61 #D
// is any bit set to 0 in most significant byte
// becareful with sign bit
int any_bit_zero_in_most_sig_byte(int x) {
  // need to or with INT_MAX because we have to set he high order bits to 1
  // since we are truncating to msb
  // TODO: this is wrong  because msb contains the high order zero bits
  int result = any_bit_zero(get_msb(x) | INT_MAX);
  printf("2.61 D:(%X) %d\n", get_msb(x), result);
  return result;
}

int main() {

  get_msb(0x12345678);
  get_msb(0xFA56789A);
  garble(0x89ABCDEF, 0x76543210);
  replace_byte(0x12345678, 2, 0xAB);
  replace_byte(0x12345678, 0, 0xAB);
  any_bit_set(INT_MIN);
  any_bit_set(0);
  any_bit_set(11);

  any_bit_zero(INT_MAX);
  any_bit_zero(0);
  any_bit_zero(11);

  any_bit_set_in_least_sig_byte(0xFF00);
  any_bit_set_in_least_sig_byte(0xFF0F);

  any_bit_zero_in_most_sig_byte(0xFF00);
  any_bit_zero_in_most_sig_byte(0xFF0F);
  any_bit_zero_in_most_sig_byte(INT_MAX);
  return 0;
}
