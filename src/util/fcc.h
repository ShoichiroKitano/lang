#ifndef __FCC_H
#define __FCC_H

#include "util/array.h"

#define DEF_FCC(type) \
  typedef struct type { \
    Array* a; \
  } type; \
  type* type##_new(); \
  void type##_add(type* fcc, void* element); \
  int type##_len(type* fcc); \
  void* type##_get(type* fcc, int i);

#define DEF_FCC_IMPLE(type) \
  type* type##_new() { \
    type* self = (type*)malloc(sizeof(type)); \
    self->a = create_array(); \
    return self; \
  } \
  void type##_add(type* fcc, void* element) { Array_add(fcc->a, element); } \
  int type##_len(type* fcc) { return fcc->a->len; } \
  void* type##_get(type* fcc, int i) { return Array_get(fcc->a, i); }
#endif
