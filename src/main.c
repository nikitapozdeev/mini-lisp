#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <string.h>

static char buffer[2048];

/* readline polyfill */
char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgetc(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

void add_history(char* unused) {}

#elif __APPLE__
#include <editline/readline.h>
#elif __linux__
#include <editline/readline.h>
#include <editline/history.h>
#endif

static char* version = "0.0.1";

int main(int argc, char** argv) {
  printf("Mini-lisp version %s\n", version);
  puts("Press Ctrl+C to Exit\n");

  while (1) {
    char* input = readline("mini-lisp > ");
    
    add_history(input);

    printf("You're type a %s\n", input);

    free(input);
  }
  return 0;
}