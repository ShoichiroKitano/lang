%{
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "y.tab.h"
#define YYDEBUG 1

extern int yylex();
extern int yyerror();

%}

%union {
  Node node;
}

%token <node> INT_LITERAL
%token <node> IDENTIFIER
%type <node> statements statement arg args expression
%token ADD DEF RETURN

%%
statements
  : statement {
    Statements* stmts = new_statements($1);
    $$ = stmts;
  }
  | statements statement {
    Statements_add((Statements*)$1, $2);
    $$ = $1;
  };
statement
  : /* empty */
  | expression
  | DEF IDENTIFIER '(' args ')' '{' statements '}' {
    $$ = new_func((Identifier*)$2, (Args*)$4, (Statements*)$7);
  };
expression
  : INT_LITERAL
  | IDENTIFIER
  /* | expression ADD expression {
      $$ = new_binary_op((Expression*)$1, $2, (Exression*)$3);
  };
  */
args
  : /* empty */
  | arg {
    Args* args = new_args();
    Args_add((Args*)args, (Arg*)$1);
    $$ = args;
  }
  | args ',' arg {
    Args_add((Args*)$1, (Arg*)$3);
    $$ = $1;
  };
arg
  : IDENTIFIER IDENTIFIER {
    $$ = new_arg((Identifier*)$1, (Identifier*)$2);
  };
%%

int
yyerror(char const *str)
{
    extern char *yytext;
    fprintf(stderr, "parser error near %s\n", yytext);
    return 0;
}

int main(void)
{
    extern int yyparse(void); // 関数スコープでプロトタイプ宣言
    extern FILE *yyin;

    yyin = fopen("test.kl", "r");
    if (yyparse()) {
        fprintf(stderr, "Error ! Error ! Error !\n");
        exit(1);
    }
}
