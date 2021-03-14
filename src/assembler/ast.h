#ifndef __AST_H
#define __AST_H

#include <stdio.h>
#include "util/array.h"

#define IMPLEMENTS_AST \
  char type[255]; \
  void (*write)(AST* self, FILE* file);

typedef struct AST AST;
struct AST {
  char type[255];
  void (*write)(AST* self, FILE *file);
};

typedef struct Directive Directive;
typedef struct Mnemonic Mnemonic;
typedef struct Operand Operand;
typedef struct Symbol Symbol;
typedef struct IntIm IntIm;
typedef struct HexIm HexIm;
typedef struct Label Label;
typedef struct Register Register;
typedef struct Offset Offset;

struct Directive { IMPLEMENTS_AST
  char name[10];
  Array* operands;
};

struct Mnemonic { IMPLEMENTS_AST
  char name[10];
  Array* operands;
};

struct Symbol { IMPLEMENTS_AST
  char value[255];
};

struct IntIm { IMPLEMENTS_AST
  char value[255];
};

struct HexIm { IMPLEMENTS_AST
  char value[255];
};

struct Label { IMPLEMENTS_AST
  char value[255];
};

struct Register { IMPLEMENTS_AST
  char value[255];
};

struct Offset  { IMPLEMENTS_AST
  char value[255];
  Register* reg;
};

#endif

void AST_write(AST* self, FILE* file);
Offset* Offset_new(const char value[], Register *reg);
Register* Register_new(const char value[]);
Label* Label_new(const char value[]);
HexIm* HexIm_new(const char value[]);
IntIm* IntIm_new(const char value[]);
Symbol* Symbol_new(const char value[]);
Mnemonic* Mnemonic_new();
Directive* Directive_new();
