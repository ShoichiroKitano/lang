void ObjectStack_init();
void ObjectStack_alloc(int size);
void ObjectStack_add(int index, void* root_object);
void* ObjectStack_get(int index);
void ObjectStack_free(int index);
