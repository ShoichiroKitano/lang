#ifndef __SYM_TABLE_H
#define __SYM_TABLE_H

typedef struct {
  char type[255];
  char name[255];
  int declared_position;
} VarSymbol;

typedef struct {
  VarSymbol vsyms[255];
  int vsyms_length;
} SymTable;

#endif

int SymTable_stack_offset(SymTable tbl, const char var[]);
int SymTable_stack_flame_size(SymTable tbl);
