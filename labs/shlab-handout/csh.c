#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int MAX_LINE_CHARS = 256;
int CMD_MAX_ARGS = 30;
int MAX_WORD_CHAR = 100;
size_t EOW = -1;

void run(int argc, char *argv[]);
void usage(void);
void loop(void);
char *get_next_word(char *buf, size_t buf_size, size_t start, size_t *pos);
char **build_argv(char *buf, size_t buf_size, int *argc);
void readline(char *buf, size_t *size);
void eval(char *cmd, char **argv, int argc);

int main(int argc, char *argv[]) {
  run(argc, argv);
  return 0;
}

char *version = "0.0.1\0";

void run(int argc, char *argv[]) {

  if (argc == 1) {
    loop();
  } else {

    if (strcmp("--help", argv[1]) == 0) {
      usage();
    } else if (strcmp("-v", argv[1]) == 0) {
      printf("version %s\n", version);
    } else {
      printf("invalid argument [%s]\n", argv[1]);
      exit(1);
    }
  }

  return;
}

void usage(void) {
  printf("c shell\n");
  printf("\t -v\t get the version\n");
}

void loop(void) {
  while (1) {
    printf("csh> ");
    fflush(stdout);

    char buf[MAX_LINE_CHARS];
    size_t num_read;
    readline(buf, &num_read);

    // printf("buf [%s]\n", buf);
    int argc;
    char **argv = build_argv(buf, num_read, &argc);
    // int i;
    // for (i = 0; i < argc; i++) {
    //   printf("prog [%s] Arg %d=%s\n", argv[0], i, argv[i]);
    // }
    eval(buf, argv, argc);
  }
}

char *get_next_word(char *buf, size_t buf_size, size_t start,
                    size_t *next_word_pos) {

  if (start > buf_size)
    return NULL;

  size_t sz = 0;
  size_t curr = start;
  while (buf[curr] != ' ' && curr < buf_size) {
    ++curr;
    ++sz;
  }

  char *dest = (char *)malloc(sizeof(char) * (sz + 1));
  dest[sz + 1] = '\0';

  strncpy(dest, buf + start, sz);
  *next_word_pos = curr + 1;

  return dest;
}

char **build_argv(char *buf, size_t buf_size, int *argc) {

  int arg_count = 0;
  size_t pos = 0;
  char *word;
  char **argv = malloc(sizeof(char *) * CMD_MAX_ARGS);
  while ((word = get_next_word(buf, buf_size, pos, &pos)) != NULL) {
    argv[arg_count++] = word;
  }
  *argc = arg_count;
  return argv;
}

void readline(char *buf, size_t *size) {

  read(STDIN_FILENO, buf, MAX_LINE_CHARS);
  size_t curr = 0;
  while (buf[curr] != '\n') {
    ++curr;
  }
  buf[curr] = '\0';
  *size = curr;
}

void eval(char *cmd, char **argv, int argc) {
  if (strcmp(argv[0], "quit") == 0) {
    exit(0);
  } else {
    printf("Reply: %s\n", cmd);
  }
}
