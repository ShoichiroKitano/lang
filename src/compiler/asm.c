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

// .global SYMBOL
static Directive* globl(const char func_name[]) {
  char tmp[255];
  Directive* self = Directive_new();
  self->operands = Array_create();
  strcpy(self->name, ".globl");
  sprintf(tmp, "_%s", func_name);
  Array_add(self->operands, Symbol_new(tmp));
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

void add_func(Func* func, Array* asms) {
  int i;
  SymTable sym_table;
  VarSymbol var;
  BinaryExpression *be;
  Return *stmt;
  char tmp[255];

  Array_add(asms, globl(func->name->value));
  Array_add(asms, func_p2align());
  sprintf(tmp, "_%s", func->name->value);
  Array_add(asms, Label_new(tmp));
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

  // TODO: 引数を使わない場合は実行しない
  sprintf(tmp, "%d", SymTable_stack_flame_size(sym_table));
  Array_add(asms, mnemonic2("subq", (AST*)IntIm_new(tmp), (AST*)Register_new("rsp")));
  for(i = 0; i < sym_table.vsyms_length; i++) {
    if(sym_table.vsyms[i].declared_position == 0) {
      sprintf(tmp, "%d", SymTable_stack_offset(sym_table, sym_table.vsyms[i].name));
      if(i == 0) Array_add(asms, mnemonic2("movl", (AST*)Register_new("edi"), (AST*)Offset_new(tmp, Register_new("rbp"))));
      if(i == 1) Array_add(asms, mnemonic2("movl", (AST*)Register_new("esi"), (AST*)Offset_new(tmp, Register_new("rbp"))));
    }
  }

  //ローカル変数をテーブルに追加

  for(i = 0; i < func->body->length; i++) {
    if(is_node_type("Return", func->body->statements[i]->node_type)) {
      stmt = (Return*) func->body->statements[i];

      if(is_node_type("BinaryExpression", stmt->return_value->node_type)) {
        be = (BinaryExpression*) stmt->return_value;
        if(is_node_type("IValue", be->left->node_type)) {
          sprintf(tmp, "%d", ((IValue *)(be->left))->value);
          Array_add(asms, mnemonic2("movl", (AST*)IntIm_new(tmp), (AST*)Register_new("eax")));
        } else { // Identifier
          sprintf(tmp, "%d", SymTable_stack_offset(sym_table, ((Identifier*)(be->left))->value));
          Array_add(asms, mnemonic2("movl", (AST*)Offset_new(tmp, Register_new("rbp")), (AST*)Register_new("eax")));
        }
        if(is_node_type("IValue", be->left->node_type)) {
          sprintf(tmp, "%d", ((IValue *)(be->right))->value);
          Array_add(asms, mnemonic2("addl", (AST*)IntIm_new(tmp), (AST*)Register_new("eax")));
        } else {
          sprintf(tmp, "%d", SymTable_stack_offset(sym_table, ((Identifier*)(be->right))->value));
          Array_add(asms, mnemonic2("addl", (AST*)Offset_new(tmp, Register_new("rbp")), (AST*)Register_new("eax")));
        }
      } else {
        printf("return value fail %s\n", func->body->statements[i]->node_type);
      }

      // TODO: 引数を使わない場合は実行しない
      sprintf(tmp, "%d", SymTable_stack_flame_size(sym_table));
      Array_add(asms, mnemonic2("addq", (AST*)IntIm_new(tmp), (AST*)Register_new("rsp")));

      Array_add(asms, mnemonic1("popq", (AST*)Register_new("rbp")));
      Array_add(asms, mnemonic0("retq"));
    } else {
      printf("fail %s\n", func->body->statements[i]->node_type);
    }
  }
}

static void write_empty_line(AST* ast, FILE* file) {
  fprintf(file, "\n");
}

void to_asm(Node** nodes, int node_length, char* file_name) {
  FILE *file;
  int i;
  Array* asms = Array_create();
  AST dummy;
  dummy.write = write_empty_line;

  file = fopen(file_name, "w");

  for(i = 0; i < node_length; i++) {
    add_func((Func*)nodes[i], asms);
    if(i != (node_length - 1)) Array_add(asms, &dummy);
  }

  for(i = 0; i < asms->len; i++) {
    AST_write((AST*)Array_get(asms, i), file);
  }

  fclose(file);
}
