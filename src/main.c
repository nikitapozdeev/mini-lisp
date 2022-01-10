#include <stdio.h>

static char* version = "0.0.1";
static char input[2048];

int main(int argc, char** argv) {
  printf("Mini-lisp version %s\n", version);
  puts("Press Ctrl+C to Exit\n");

  while (1) {
    fputs("mini-lisp > ", stdout);

    fgets(input, 2048, stdin);

    printf("You're type a %s", input);
  }
  return 0;
}