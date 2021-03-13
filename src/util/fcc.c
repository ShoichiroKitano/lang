#include "util/fcc.h"


void FCC_add(void* fcc, void* element) {
  Array_add(((FCC*)fcc)->a, element);
}

int FCC_len(void* fcc) {
  return ((FCC*)fcc)->a->len;
}

void* FCC_get(void* fcc, int i) {
  return Array_get(((FCC*)fcc)->a, i);
}
