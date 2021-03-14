%{
#include <stdlib.h>
#include <stdio.h>
#include "compiler/node.h"
#include "compiler/y.tab.h"
// #define YYDEBUG 1

extern int yylex();
extern int yyerror(char const *str);

%}

%union {
  Node* node;
  int op;
}

%token <node> INT_LITERAL
%token <node> IDENTIFIER
%type <node> statements statement arg args expression empty definitions definition
%token DEF RETURN
%token<op> ADD

%%
compilation_unit : definitions { /* empty */ }

definitions
  : definition {
    nodes[node_length] = $1;
    node_length++;
  }
  | definitions definition {
    nodes[node_length] = $2;
    node_length++;
  }

definition
  : DEF IDENTIFIER '(' args ')' IDENTIFIER '{' statements '}' {
    $$ = (Node*)new_func((Identifier*)$2, (Identifier*)$6, (Args*)$4, (Statements*)$8);
  }

statements
  : empty
  | statement {
    Statements* stmts = (Statements*) new_statements();
    Statements_add(stmts, $1);
    $$ = (Node*)stmts;
  }
  | statements statement {
    Statements_add((Statements*)$1, $2);
    $$ = $1;
  }

statement
  : expression
  | RETURN expression {
    $$ = new_return($2);
  }

expression
  : INT_LITERAL
  | IDENTIFIER
  | expression ADD expression {
    $$ = new_binary_op($1, $2, $3);
  }

args
  : empty
  | arg {
    Args* args = (Args*)new_args();
    Args_add((Args*)args, (Arg*)$1);
    $$ = (Node*)args;
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
