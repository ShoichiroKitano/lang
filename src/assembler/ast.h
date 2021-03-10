#ifndef __AST_H
#define __AST_H

#include "util/fcc.h"

typedef struct {
  char type[255];
} AST;

typedef struct Directive Directive;
typedef struct Operand Operand;
typedef struct Symbol Symbol;

struct Directive {
  char type[255];
  char name[10];
  Operand* operands;
};

struct Symbol {
  char value[255];
};

DEF_FCC(Operands)

#endif
