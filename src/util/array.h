#ifndef __UTIL_ARRAY_H
#define __UTIL_ARRAY_H

typedef struct {
  void** e;
  int len;
  int cap;
} Array;

Array* Array_new(int cap);
Array* Array_create();
void Array_destroy(Array* self);
void Array_add(Array* self, void* e);
void Array_interrupt(Array* self, int i, void* e);
void* Array_get(Array* self, int i);

#endif
