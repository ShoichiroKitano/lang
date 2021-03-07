#include <stdio.h>
#include <string.h>
#include "asm.h"
#include "sym_table.h"

int is_node_type(const char* a, const char* b) {
  return strcmp(a, b) == 0;
}

void write_func(Func* func, FILE *file) {
  int i;
  SymTable sym_table;
  VarSymbol var;
  BinaryExpression *be;
  Return *stmt;

  fprintf(file, ".globl %s\n", func->name->value);
  fprintf(file, ".p2align 4, 0x90\n");
  fprintf(file, "%s:\n", func->name->value);
  fprintf(file, "  pushq %%rbp\n");
  fprintf(file, "  movq %%rsp, %%rbp\n");

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
        fprintf(file, "  movl $%d, %%eax\n", ((IValue *)(be->left))->value);
        fprintf(file, "  addl $%d, %%eax\n", ((IValue *)(be->right))->value);
      } else {
        printf("return value fail %s\n", func->body->statements[i]->node_type);
      }

      fprintf(file, "  popq %%rbp\n");
      fprintf(file, "  retq\n");
    } else {
      printf("fail %s\n", func->body->statements[i]->node_type);
    }
  }
}

void to_asm(Node** nodes, int size, char* file_name) {
  FILE *file;

  file = fopen(file_name, "w");

  write_func((Func*)nodes[0], file);

  fclose(file);
}
