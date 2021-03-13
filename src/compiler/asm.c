#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler/asm.h"
#include "compiler/sym_table.h"
#include "assembler/ast.h"
#include "util/array.h"

static int is_node_type(const char* a, const char* b) {
  return strcmp(a, b) == 0;
}

// .global SYMBL
static Directive* globl(const char func_name[]) {
  Directive* self = Directive_new();
  self->operands = Array_create();
  strcpy(self->name, ".globl");
  Array_add(self->operands, Symbol_new(func_name));
  return self;
}

// .p2align 4, 0x90
static Directive* func_p2align() {
  Directive* self = Directive_new();
  strcpy(self->name, ".p2align");
  self->operands = Array_create();
  Array_add(self->operands, IntIm_new("4"));
  Array_add(self->operands, HexIm_new("0x90"));
  return self;
}

static Mnemonic* mnemonic1(const char name[], AST* operand) {
  Mnemonic* self = Mnemonic_new();
  strcpy(self->name, name);
  self->operands = Array_create();
  Array_add(self->operands, operand);
  return self;
}

static Mnemonic* mnemonic2(const char name[], AST* operand1, AST* operand2) {
  Mnemonic* self = Mnemonic_new();
  strcpy(self->name, name);
  self->operands = Array_create();
  Array_add(self->operands, operand1);
  Array_add(self->operands, operand2);
  return self;
}

static Mnemonic* mnemonic0(const char name[]) {
  Mnemonic* self = Mnemonic_new();
  strcpy(self->name, name);
  self->operands = Array_create();
  return self;
}

void write_func(Func* func, Array* asms, FILE* file) {
  int i;
  SymTable sym_table;
  VarSymbol var;
  BinaryExpression *be;
  Return *stmt;
  char tmp[25];

  Array_add(asms, globl(func->name->value));
  Array_add(asms, func_p2align());
  Array_add(asms, Label_new(func->name->value));
  Array_add(asms, mnemonic1("pushq", (AST*)Register_new("rbp")));
  Array_add(asms, mnemonic2("movq", (AST*)Register_new("rsp"), (AST*)Register_new("rbp")));

  sym_table.vsyms_length = 0;
  //引数をテーブルに追加
  for(i = 0; i < func->args->length; i++) {
    strcpy(var.type, func->args->args[i]->type->value);
    strcpy(var.name, func->args->args[i]->variable->value);
    var.declared_position = 0;
    sym_table.vsyms[sym_table.vsyms_length] = var;
    sym_table.vsyms_length++;
  }

  //ローカル変数をテーブルに追加

  for(i = 0; i < func->body->length; i++) {
    if(is_node_type(func->body->statements[i]->node_type, "Return")) {
      stmt = (Return*) func->body->statements[i];

      if(is_node_type(stmt->return_value->node_type, "BinaryExpression")) {
        be = (BinaryExpression*) stmt->return_value;
        sprintf(tmp, "%d", ((IValue *)(be->left))->value);
        Array_add(asms, mnemonic2("movl", (AST*)IntIm_new(tmp), (AST*)Register_new("eax")));
        sprintf(tmp, "%d", ((IValue *)(be->right))->value);
        Array_add(asms, mnemonic2("addl", (AST*)IntIm_new(tmp), (AST*)Register_new("eax")));
      } else {
        printf("return value fail %s\n", func->body->statements[i]->node_type);
      }
      Array_add(asms, mnemonic1("popq", (AST*)Register_new("rbp")));
      Array_add(asms, mnemonic0("retq"));
    } else {
      printf("fail %s\n", func->body->statements[i]->node_type);
    }
  }
}

void to_asm(Node** nodes, int size, char* file_name) {
  FILE *file;
  int i;
  Array* asms = Array_create();

  file = fopen(file_name, "w");

  write_func((Func*)nodes[0], asms, file);
  for(i = 0; i < asms->len; i++) {
    AST_write((AST*)Array_get(asms, i), file);
  }

  fclose(file);
}
