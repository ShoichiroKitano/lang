#include <fstream>
#include <iostream>
#include <string>
#include <iterator>

#include <criterion/criterion.h>
#include <stdio.h>
#include "asm.h"

int yyparse();
extern FILE *yyin;

void assert_file(const char actual[], const char expect[]) {
  std::ifstream out_stream(actual);
  std::string actual_str((std::istreambuf_iterator<char>(out_stream)), std::istreambuf_iterator<char>());

  std::ifstream expect_stream(expect);
  std::string expect_str((std::istreambuf_iterator<char>(expect_stream)), std::istreambuf_iterator<char>());

  cr_expect_str_eq(actual_str.c_str(), expect_str.c_str());
}

Test(to_asm, add) {
  char out[] = "./test/out/add.s";
  yyin = fopen("./test/fixture/compiler/add.kl", "r");
  yyparse();

  to_asm(nodes, 1, out);

  assert_file(out, "./test/fixture/compiler/add_expect.s");
}
