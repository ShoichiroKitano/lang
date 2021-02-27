.PHONY: clean build_compiler exec

exec: build_compiler exec_bin

build_compiler:
	cd src/compiler; yacc -dv parser.y
	cd src/compiler; lex tokenizer.l
	gcc src/compiler/*.c -o bin/compiler

exec_bin:
	./bin/compiler

clean:
	cd src/compiler; y.tab.c lex.yy.c y.output y.tab.h
	cd bin; rm compier
