#include <stdlib.h>
#include "util/array.h"

static void alloc_cap(Array* self);

void Array_interrupt(Array* self, int index, void* e) {
  int i;
  alloc_cap(self);
  for(i = self->len; i > index; i--) {
    self->e[i] = self->e[i - 1];
  }
  self->e[index] = e;
  self->len++;
}

Array* Array_new(int cap) {
  Array* self = (Array*) malloc(sizeof(Array));
  self->len = 0;
  self->cap = cap;
  self->e = (void**) malloc(sizeof(void*) * self->cap);
  return self;
}

Array* Array_create() {
  return Array_new(1);
}

void Array_destroy(Array* self) {
  free(self->e);
  free(self);
}

void Array_add(Array* self, void* e) {
  alloc_cap(self);
  self->e[self->len] = e;
  self->len++;
}

void* Array_get(Array* self, int i) {
  return self->e[i];
}

static void alloc_cap(Array* self) {
  if(self->len < self->cap) return;
  self->cap *= 2;
  self->e = (void**) realloc(self->e, sizeof(void*) * self->cap);
}

