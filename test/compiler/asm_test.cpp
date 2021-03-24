#include <fstream>
#include <iostream>
#include <string>
#include <iterator>

#include <criterion/criterion.h>
#include <stdio.h>
#include "compiler/asm.h"
#include "compiler/node.h"

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
  node_length = 0;
  yyparse();

  to_asm(nodes, node_length, out);

  assert_file(out, "./test/fixture/compiler/add_expect.s");
}

//Test(to_asm, object) {
//  char out[] = "./test/out/object.s";
//  yyin = fopen("./test/fixture/compiler/object.kl", "r");
//  node_length = 0;
//  yyparse();
//
//  to_asm(nodes, node_length, out);
//
//  assert_file(out, "./test/fixture/compiler/object_expect.s");
//}
