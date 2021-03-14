#include <stdio.h>
#include <stdlib.h>
#include "compiler/node.h"
#include "compiler/asm.h"

int yyparse();
extern FILE *yyin;

int main() {
  yyin = fopen("test.kl", "r");
  node_length = 0;
  if (yyparse()) {
      fprintf(stderr, "Error ! Error ! Error !\n");
      exit(1);
  }
  to_asm(nodes, 1, "test.s");
}
