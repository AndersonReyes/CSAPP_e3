// Get the least significant byte
int get_lsb(int x);
// Get the most significant byte
int get_msb(int x);

// 2.59
// print the least significant bytes of x and rest of y
// ex. x = 0x89ABCDEF,  y = 0x76543210
// prints 0x765432EF
int garble(int x, int y);

// 2.60
// replaces byte i in x, by byte b
int replace_byte(unsigned int x, int i, unsigned char b);

// 2.61 #A
// is any bit set to 1
// becareful with sign bit
int any_bit_set(int x);

// 2.61 #B
// is any bit set to 0
// becareful with sign bit
int any_bit_zero(int x);

// 2.61 #C
// is any bit set to 1 in least significant byte
// becareful with sign bit
int any_bit_set_in_least_sig_byte(int x);

// 2.61 #D
// is any bit set to 0 in most significant byte
// becareful with sign bit
int any_bit_zero_in_most_sig_byte(int x);

// 2.62
// return 1 if machine uses arrithmetic left overator, 0 otherwise
int int_shifts_are_arithmetic(void);

// 2.63
// perform logic right shift using arithmetic
unsigned int srl(unsigned int x, int k);
