#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "asm.h"

int yyparse();
extern FILE *yyin;

int main() {
  yyin = fopen("test.kl", "r");
  if (yyparse()) {
      fprintf(stderr, "Error ! Error ! Error !\n");
      exit(1);
  }
  to_asm(nodes, 1, "test.s");
}
