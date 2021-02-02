#!/bin/bash

echo '##################parser##################'
yacc -vd parser.y

echo '##################tokenizer##################'
lex tokenizer.l

echo '##################compile##################'
gcc node.c lex.yy.c y.tab.c

#./a.out
