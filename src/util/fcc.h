#ifndef __FCC_H
#define __FCC_H

#include "util/array.h"

#define DEF_FCC(type) \
  typedef struct type { \
    Array* a; \
  } type; \
  type* type##_new() { \
    type* self = (type*)malloc(sizeof(type)); \
    self->a = create_array(); \
    return self; \
  } \
  void type##_add(type* fcc, void* element) { Array_add(fcc->a, element); } \
//  type##_destroy(type* fcc) { return ; } \
//  type##_len(type* fcc) { return fcc->a->len; } \

#endif
