#include <stdlib.h>
#include "util/array.h"

Array* Array_new(int cap) {
  Array* self = (Array*) malloc(sizeof(Array));
  self->len = 0;
  self->cap = cap;
  self->e = (void**) malloc(sizeof(void*) * self->cap);
  return self;
}

Array* create_array() {
  return Array_new(1);
}

void Array_destroy(Array* self) {
  free(self->e);
  free(self);
}

void Array_add(Array* self, void* e) {
  if(self->len == self->cap) {
    self->cap *= 2;
    self->e = (void**) realloc(self->e, sizeof(void*) * self->cap);
  }
  self->e[self->len] = e;
  self->len++;
}

void* Array_get(Array* self, int i) {
  return self->e[i];
}
