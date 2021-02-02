%{
#include <stdio.h>
#include "node.h"
#include "y.tab.h"

int
yywrap(void)
{
    return 1;
}
%}
%%

"+" {
  return ADD;
}
"\n" ;
"(" {
  return '('; }
")" {
  return ')'; }
"{" {
  return '{'; }
"}" {
  return '}'; }
"," {
  return ','; }
" " ;

"def" {
  return DEF;
}

"return" {
  return RETURN;
}

[1-9][0-9]* {
    int tmp;
    sscanf(yytext, "%d", &tmp);
    yylval.node = new_ivalue(tmp);
    return INT_LITERAL;
}

[A-Za-z][A-Za-z0-9]* {
    yylval.node = new_identifier(yytext);
    return IDENTIFIER;
}

%%
