#ifndef __SYM_TABLE__
#define __SYM_TABLE__

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
