#ifndef __SYM_TABLE__
#define __SYM_TABLE__

typedef struct VarSymbol {
  Identifier type;
  Identifier name;
  int declared_position;
} VarSymbol;

typedef FunSymbol {
  Func* func;
} FunSymbol;

typedef struct SymTable {
  FuncSymbol* fsyms[255];
  VarSymbol* vsyms[255];
} SymTable;

#endif
