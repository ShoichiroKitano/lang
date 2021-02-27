#include <stdio.h>
#include <stdlib.h>
#include "node.h"

int yyparse();
extern FILE *yyin;

int main() {
  Func* f;

  yyin = fopen("test.kl", "r");
  if (yyparse()) {
      fprintf(stderr, "Error ! Error ! Error !\n");
      exit(1);
  }
  f = (Func*)nodes[0];
  printf("%s\n", f->name->value);
}
