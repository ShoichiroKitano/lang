#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler/asm.h"
#include "compiler/sym_table.h"
#include "assembler/ast.h"

DEF_FCC(AssemblerCode)
DEF_FCC_IMPLE(AssemblerCode)

static int is_node_type(const char* a, const char* b) {
  return strcmp(a, b) == 0;
}

// .global SYMBL
static Directive* globl(const char func_name[]) {
  Directive* self = Directive_new();
  self->operands = Operands_new();
  strcpy(self->name, ".globl");
  Operands_add(self->operands, Symbol_new(func_name));
  return self;
}

// .p2align 4, 0x90
static Directive* func_p2align() {
  Directive* self = Directive_new();
  strcpy(self->name, ".p2align");
  self->operands = Operands_new();
  Operands_add(self->operands, IntIm_new("4"));
  Operands_add(self->operands, HexIm_new("0x90"));
  return self;
}

static Mnemonic* mnemonic1(const char name[], AST* operand) {
  Mnemonic* self = Mnemonic_new();
  strcpy(self->name, name);
  self->operands = Operands_new();
  Operands_add(self->operands, operand);
  return self;
}

static Mnemonic* mnemonic2(const char name[], AST* operand1, AST* operand2) {
  Mnemonic* self = Mnemonic_new();
  strcpy(self->name, name);
  self->operands = Operands_new();
  Operands_add(self->operands, operand1);
  Operands_add(self->operands, operand2);
  return self;
}

static Mnemonic* mnemonic0(const char name[]) {
  Mnemonic* self = Mnemonic_new();
  strcpy(self->name, name);
  self->operands = Operands_new();
  return self;
}

void write_func(Func* func, AssemblerCode* asms, FILE* file) {
  int i;
  SymTable sym_table;
  VarSymbol var;
  BinaryExpression *be;
  Return *stmt;
  char tmp[25];

  AssemblerCode_add(asms, globl(func->name->value));
  AssemblerCode_add(asms, func_p2align());
  AssemblerCode_add(asms, Label_new(func->name->value));
  AssemblerCode_add(asms, mnemonic1("pushq", (AST*)Register_new("rbp")));
  AssemblerCode_add(asms, mnemonic2("movq", (AST*)Register_new("rsp"), (AST*)Register_new("rbp")));

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
        AssemblerCode_add(asms, mnemonic2("movl", (AST*)IntIm_new(tmp), (AST*)Register_new("eax")));
        sprintf(tmp, "%d", ((IValue *)(be->right))->value);
        AssemblerCode_add(asms, mnemonic2("addl", (AST*)IntIm_new(tmp), (AST*)Register_new("eax")));
      } else {
        printf("return value fail %s\n", func->body->statements[i]->node_type);
      }
      AssemblerCode_add(asms, mnemonic1("popq", (AST*)Register_new("rbp")));
      AssemblerCode_add(asms, mnemonic0("retq"));
    } else {
      printf("fail %s\n", func->body->statements[i]->node_type);
    }
  }
}

void to_asm(Node** nodes, int size, char* file_name) {
  FILE *file;
  int i;
  AssemblerCode* asms = AssemblerCode_new();

  file = fopen(file_name, "w");

  write_func((Func*)nodes[0], asms, file);
  for(i = 0; i < AssemblerCode_len(asms); i++) {
    AST_write((AST*)AssemblerCode_get(asms, i), file);
  }

  fclose(file);
}
