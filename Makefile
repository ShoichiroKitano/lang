.PHONY: clean build exec

exec: build exec_bin clean

build:
	yacc -dv parser.y
	lex tokenizer.l
	gcc main.c node.c y.tab.c lex.yy.c

exec_bin:
	./a.out

clean:
	rm a.out y.tab.c lex.yy.c y.output y.tab.h
