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
  cr_expect_eq(*(int*)Array_get(a, 2), 2);
  cr_expect_eq(*(int*)Array_get(a, 3), 3);
  cr_expect_eq(a->len, 3);
  cr_expect_eq(a->cap, 4);
  Array_destroy(a);
}
