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
void garble(int x, int y) {
  int mask = x & 0xFF;
  int result = (y & 0xFFFFFFFF00) | x;
  printf("2.59 inputs (%X, %X): mask %X, result %X\n", x, y, mask, result);
}

// 2.60
// replaces byte i in x, by byte b
void replace_byte(unsigned int x, int i, unsigned char b) {
  int shift_bytes = i * 8;
  int mask = ~(0xFF << shift_bytes);
  int byte_mask = b << shift_bytes;
  unsigned int result = (x & mask) | byte_mask;

  printf("2.60 inputs: (%X, %d, %X), mask: 0x%X, byte_mask: 0x%X, result: %X\n",
         x, i, b, mask, byte_mask, result);
}

int main() {
  is_little_endian();

  garble(0x89ABCDEF, 0x76543210);
  replace_byte(0x12345678, 2, 0xAB);
  replace_byte(0x12345678, 0, 0xAB);
  return 0;
}
