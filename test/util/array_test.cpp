#include <criterion/criterion.h>
#include "util/array.h"

Test(Array, add) {
  Array* a = Array_new(1);
  int i1 = 1;
  int i2 = 2;
  int i3 = 3;
  Array_add(a, &i1);
  Array_add(a, &i2);
  Array_add(a, &i3);
  cr_expect_eq(*(int*)Array_get(a, 0), 1);
  cr_expect_eq(*(int*)Array_get(a, 1), 2);
  cr_expect_eq(*(int*)Array_get(a, 2), 3);
  cr_expect_eq(a->len, 3);
  cr_expect_eq(a->cap, 4);
  Array_destroy(a);
}

Test(Array, interrupt) {
  Array* a = Array_new(1);
  int i1 = 1;
  int i2 = 2;
  int i3 = 3;
  Array_add(a, &i1);
  Array_add(a, &i3);

  Array_interrupt(a, 1, &i2);
  cr_expect_eq(*(int*)Array_get(a, 0), 1);
  cr_expect_eq(*(int*)Array_get(a, 1), 2);
  cr_expect_eq(*(int*)Array_get(a, 2), 3);
  cr_expect_eq(a->len, 3);
  cr_expect_eq(a->cap, 4);
  Array_destroy(a);
}
