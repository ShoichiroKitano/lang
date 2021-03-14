#include <string.h>
#include "compiler/sym_table.h"

int SymTable_stack_offset(SymTable tbl, const char var[]) {
  int i;
  int offset;

  offset = 0;
  for(i = 0; i < tbl.vsyms_length; i++) {
    offset -= 4;
    if(strcmp(tbl.vsyms[i].name, var) == 0) break;
  }
  return offset;
}

int SymTable_stack_flame_size(SymTable tbl) {
  int i;
  int size;
  int mod;

  size = 0;

  for(i = 0; i < tbl.vsyms_length; i++) {
    size += 4;
  }

  mod = size % 16;
  if(mod != 0) {
    size += (16 - mod);
  }

  return size;
}
