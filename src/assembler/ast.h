#ifndef __AST_H
#define __AST_H

#include <stdio.h>
#include "util/fcc.h"

#define IMPLEMENTS_AST \
  char type[255]; \
  void (*write)(AST* self, FILE* file);

typedef struct AST AST;
struct AST {
  char type[255];
  void (*write)(AST* self, FILE *file);
};

void AST_write(AST* self, FILE* file);

DEF_FCC(Operands)

typedef struct Directive Directive;
typedef struct Operand Operand;
typedef struct Symbol Symbol;
typedef struct IntIm IntIm;
typedef struct HexIm HexIm;

struct Directive { IMPLEMENTS_AST
  char name[10];
  Operands* operands;
};
Directive* Directive_new();

struct Symbol { IMPLEMENTS_AST
  char value[255];
};
Symbol* Symbol_new(const char value[]);

struct IntIm { IMPLEMENTS_AST
  char value[255];
};
IntIm* IntIm_new(const char value[]);

struct HexIm { IMPLEMENTS_AST
  char value[255];
};
HexIm* HexIm_new(const char value[]);

#endif
