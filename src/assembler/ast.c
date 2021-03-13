#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "assembler/ast.h"

void AST_write(AST* self, FILE* file) {
  self->write(self, file);
}

static void Directive_write(AST* self, FILE* file) {
  int i;
  Directive* dire = (Directive*) self;
  AST* a;

  fprintf(file, "%s ", dire->name);
  for(i = 0; i < dire->operands->len; i++) {
    a = (AST*)Array_get(dire->operands, i);
    a->write(a, file);
    if(i != dire->operands->len - 1) fprintf(file, ", ");
  }
  fprintf(file, "\n");
}

Directive* Directive_new() {
  Directive* self = (Directive*)malloc(sizeof(Directive));
  strcpy(self->type, "Directive");
  self->write = Directive_write;
  return self;
}

static int is_numeric(AST *a) {
  if(strcmp(a->type, "IntIm") == 0) return 1;
  if(strcmp(a->type, "HexIm") == 0) return 1;
  return 0;
}

static void Mnemonic_write(AST* self, FILE* file) {
  int i;
  Mnemonic* mn = (Mnemonic*) self;
  AST* a;

  fprintf(file, "  %s", mn->name);
  for(i = 0; i < mn->operands->len; i++) {
    fprintf(file, " ");
    a = (AST*)Array_get(mn->operands, i);
    if(is_numeric(a)) fprintf(file, "$");
    a->write(a, file);
    if(i != mn->operands->len - 1) fprintf(file, ",");
  }
  fprintf(file, "\n");
}

Mnemonic* Mnemonic_new() {
  Mnemonic* self = (Mnemonic*)malloc(sizeof(Mnemonic));
  strcpy(self->type, "Mnemonic");
  self->write = Mnemonic_write;
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

static void Label_write(AST* self, FILE* file) {
  fprintf(file, "%s:\n", ((Label*)self)->value);
}

Label* Label_new(const char value[]) {
  Label* self = (Label*)malloc(sizeof(Label));
  strcpy(self->type, "Label");
  self->write = Label_write;
  strcpy(self->value, value);
  return self;
}

static void Register_write(AST* self, FILE* file) {
  fprintf(file, "%%%s", ((Register*)self)->value);
}

Register* Register_new(const char value[]) {
  Register* self = (Register*)malloc(sizeof(Register));
  strcpy(self->type, "Register");
  self->write = Register_write;
  strcpy(self->value, value);
  return self;
}
