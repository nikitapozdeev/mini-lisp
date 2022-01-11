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

#include "mpc.h"

static char* version = "0.0.1";

int main(int argc, char** argv) {
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expression = mpc_new("expression");
  mpc_parser_t* Minilisp = mpc_new("minilisp");

  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                            \
      number     : /-?[0-9]+/ ;                                  \
      operator   : '+' | '-' | '*' | '/' ;                       \
      expression : <number> | '(' <operator> <expression>+ ')' ; \
      minilisp   : /^/ <operator> <expression>+ /$/ ;            \
    ",
    Number, Operator, Expression, Minilisp
    );

  printf("Mini-lisp version %s\n", version);
  puts("Press Ctrl+C to Exit\n");

  while (1) {
    char* input = readline("mini-lisp > ");
    
    add_history(input);

    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Minilisp, &r)) {
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
  }

  mpc_cleanup(4, Number, Operator, Expression, Minilisp);
  return 0;
}