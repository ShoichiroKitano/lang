%{
#include <stdlib.h>
#include "node.h"
#include "y.tab.h"
#define YYDEBUG 1

extern int yylex();
extern int yyerror();

%}

%union {
  Node node;
  int op;
}

%token <node> INT_LITERAL
%token <node> IDENTIFIER
%type <node> statements statement arg args expression empty
%token DEF RETURN
%token<op> ADD

%%
compilation_unit
  : DEF IDENTIFIER '(' args ')' '{' statements '}' {
    nodes[0] = new_func((Identifier*)$2, (Args*)$4, (Statements*)$7);
  }

statements
  : empty
  | statement {
    Statements* stmts = new_statements();
    Statements_add(stmts, $1);
    $$ = stmts;
  }
  | statements statement {
    Statements_add((Statements*)$1, $2);
    $$ = $1;
  }

statement
  : expression

expression
  : INT_LITERAL
  | IDENTIFIER
  | expression ADD expression {
    $$ = new_binary_op($1, $2, $3);
  }

args
  : empty
  | arg {
    Args* args = new_args();
    Args_add((Args*)args, (Arg*)$1);
    $$ = args;
  }
  | args ',' arg {
    Args_add((Args*)$1, (Arg*)$3);
    $$ = $1;
  }

arg
  : IDENTIFIER IDENTIFIER {
    $$ = new_arg((Identifier*)$1, (Identifier*)$2);
  }

empty
  : {
    $$ = NULL;
  }
%%

int yyerror(char const *str) {
  extern char *yytext;
  fprintf(stderr, "parser error near %s\n", yytext);
  return 0;
}
