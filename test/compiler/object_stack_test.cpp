#include <criterion/criterion.h>
#include "compiler/object_stack.h"

Test(ObjectStack_add, 確保した領域にデータを保存) {
  int i0 = 0;
  int i1 = 1;
  ObjectStack_init();
  ObjectStack_alloc(2);
  ObjectStack_add(0, &i0);
  ObjectStack_add(1, &i1);
  cr_expect_eq(*(int *)ObjectStack_get(0), 0);
  cr_expect_eq(*(int *)ObjectStack_get(1), 1);
}

Test(ObjectStack_add, 指定するインデックスは確保した領域のオフセットになる) {
  int i00 = 0;
  int i01 = 1;
  int i10 = 2;
  int i11 = 3;
  ObjectStack_init();
  ObjectStack_alloc(2);
  ObjectStack_add(0, &i00);
  ObjectStack_add(1, &i01);
  ObjectStack_alloc(2);
  ObjectStack_add(0, &i10);
  ObjectStack_add(1, &i11);
  cr_expect_eq(*(int *)ObjectStack_get(0), 2);
  cr_expect_eq(*(int *)ObjectStack_get(1), 3);
  ObjectStack_free(2);
  cr_expect_eq(*(int *)ObjectStack_get(0), 0);
  cr_expect_eq(*(int *)ObjectStack_get(1), 1);
}
