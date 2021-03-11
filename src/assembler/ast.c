#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "assembler/ast.h"

DEF_FCC_IMPLE(Operands)

void AST_write(AST* self, FILE* file) {
  self->write(self, file);
}

static void Directive_write(AST* self, FILE* file) {
  int i;
  Directive* dire = (Directive*) self;
  AST* a;

  fprintf(file, "%s ", dire->name);
  for(i = 0; i < Operands_len(dire->operands); i++) {
    a = (AST*)Operands_get(dire->operands, i);
    a->write(a, file);
    if(i != Operands_len(dire->operands) - 1) fprintf(file, ", ");
  }
  fprintf(file, "\n");
}

Directive* Directive_new() {
  Directive* self = (Directive*)malloc(sizeof(Directive));
  strcpy(self->type, "Directive");
  self->write = Directive_write;
  return self;
}

static void Symbol_write(AST* self, FILE* file) {
  fprintf(file, "%s", ((Symbol*)self)->value);
}

Symbol* Symbol_new(const char value[]) {
  Symbol* self = (Symbol*)malloc(sizeof(Symbol));
  strcpy(self->type, "Symbol");
  self->write = Symbol_write;
  strcpy(self->value, value);
  return self;
}

static void IntIm_write(AST* self, FILE* file) {
  fprintf(file, "%s", ((IntIm*)self)->value);
}

IntIm* IntIm_new(const char value[]) {
  IntIm* self = (IntIm*)malloc(sizeof(IntIm));
  strcpy(self->type, "IntIm");
  self->write = IntIm_write;
  strcpy(self->value, value);
  return self;
}

static void HexIm_write(AST* self, FILE* file) {
  fprintf(file, "%s", ((HexIm*)self)->value);
}

HexIm* HexIm_new(const char value[]) {
  HexIm* self = (HexIm*)malloc(sizeof(HexIm));
  strcpy(self->type, "HexIm");
  self->write = HexIm_write;
  strcpy(self->value, value);
  return self;
}
