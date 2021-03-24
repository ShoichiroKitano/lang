#include <stdlib.h>
#include "compiler/object_stack.h"

static void** sp;
static int start;
static int end;

void ObjectStack_add(int index, void* root_object) {
  sp[start+index] = root_object;
}

void* ObjectStack_get(int index) {
  return sp[start+index];
}

void ObjectStack_init() {
  sp = (void**) malloc(sizeof(void*) * 255);
  start = -1;
  end = -1;
}

void ObjectStack_alloc(int size) {
  start = end + 1;
  end = start + (size - 1);
}

void ObjectStack_free(int size) {
  end = start - 1;
  start = end - (size - 1);
}
