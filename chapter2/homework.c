#include "homework.h"
#include <limits.h>
#include <stdio.h>

int garble(int x, int y) {
  int x_first_byte = x & 0xFF;
  int y_rest_bytes = y & (~(0xFF));
  int result = y_rest_bytes | x_first_byte;
  return result;
}

int replace_byte(unsigned int x, int i, unsigned char b) {
  int shift_bytes = i << 3;
  int mask = ~(0xFF << shift_bytes);
  int byte_mask = b << shift_bytes;
  unsigned int result = (x & mask) | byte_mask;
  return result;
}

int get_msb(int x) {
  int num_bits = (sizeof(int) - 1) << 3;
  int mask = 0xFF << num_bits;
  int result = ((x & mask) >> num_bits);
  result = result & 0xFF; // clear out all other bits
  return result;
}

int get_lsb(int x) {
  int result = x & 0xFF; // clear out all other bits
  return result;
}

int any_bit_set(int x) {
  int bits = sizeof(int) << 3;
  // but why?
  return (((-x) | x) >> (bits - 1)) & 1;
}

int any_bit_zero(int x) { return x != -1; }

int any_bit_set_in_least_sig_byte(int x) {
  int result = any_bit_set(get_lsb(x));
  return result;
}

int any_bit_zero_in_most_sig_byte(int x) {
  int right_shift_val = (sizeof(int) - 1) << 3;
  int bits = (sizeof(int) << 3) - 1;
  int msb = get_msb(x);
  // set sign bit to 1;
  // right arithmetic shift sets all left bits to 1 before msb in bit string
  int masked = msb | ((1 << bits) >> (right_shift_val - 1));
  return any_bit_zero(masked);
}

int int_shifts_are_arithmetic(void) {
  int bits = (sizeof(int) << 3) - 1;
  return ((1 << bits) >> bits) == -1;
}

unsigned int srl(unsigned int x, int k) { return 0; }
