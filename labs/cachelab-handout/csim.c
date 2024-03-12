#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void print_help() {
  printf("-h\t this help guide\n");
  printf("-v\t optional verbose to display trace info\n");
  printf("-s <s>\t set index bits, total sets = 2**set_index_bits\n");
  printf("-E <E>\t lines per set\n");
  printf("-b <b>\t block bits, total blocks = 2**block_bits\n");
}

typedef struct cache_line {
  int valid;
  int tag;
  int block_size;
  char (*block)[];

} cache_line_t;

int main(int argc, char *argv[]) {

  if (argc <= 1 || strcmp("-h", argv[1]) == 0) {
    print_help();
    return 0;
  }

  char *tracefile;
  int verbose_flag = 0;
  int lines_per_set = 0;
  int set_index_bits = 0;
  int block_bits = 0;
  int i;
  for (i = 2; i < argc; i++) {
    if (strcmp("-v", argv[i]) == 0)
      verbose_flag = 1;
    if (strcmp("-t", argv[i]) == 0)
      tracefile = argv[i + 1];
    if (strcmp("-s", argv[i]) == 0)
      set_index_bits = atoi(argv[i + 1]);
    if (strcmp("-E", argv[i]) == 0)
      lines_per_set = atoi(argv[i + 1]);
    if (strcmp("-b", argv[i]) == 0)
      block_bits = atoi(argv[i + 1]);
  }

  int total_sets = 1 << set_index_bits;
  cache_line_t cache[total_sets][lines_per_set];

  FILE *fp = fopen(tracefile, "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  unsigned int addr;
  int size;
  char instruction;
  while (fscanf(fp, " %c %x,%d", &instruction, &addr, &size) == 3) {

    int set_mask = (1 << set_index_bits) - 1;
    int set_location = (addr >> block_bits) & set_mask;
    printf("SEt LOCATION: %x %x\n", set_location, addr >> block_bits);
    switch (instruction) {
    case 'I':
      break;
    case 'L':
      break;
    case 'M':
      break;
    case 'S':
      break;
    }
    printf("Instruction: %c ADDRESS: %x SIZE: %d\n", instruction, addr, size);
  }

  fclose(fp);

  printf("verbose: %d, tracefile: %s set_index_bits: %d lines_per_set: %d "
         "block_bits: %d\n",
         verbose_flag, tracefile, set_index_bits, lines_per_set, block_bits);
  printSummary(0, 0, 0);
  return 0;
}
