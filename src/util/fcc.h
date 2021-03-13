#ifndef __FCC_H
#define __FCC_H

#include "util/array.h"

typedef struct {
  Array* a;
} FCC;

void FCC_add(void* fcc, void* element);
int FCC_len(void* fcc);
void* FCC_get(void* fcc, int i);

#define DEF_FCC(type) \
  typedef struct { \
    Array* a; \
  } type; \
  type* type##_new();

#define DEF_FCC_IMPLE(type) \
  type* type##_new() { \
    type* self = (type*)malloc(sizeof(type)); \
    self->a = create_array(); \
    return self; \
  }
#endif
