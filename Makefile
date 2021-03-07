SHELL=/bin/bash

.PHONY: clean build_compiler exec_compiler build_compiler_test exec_compiler_test

exec_compiler: build_compiler
	./bin/compiler

build_compiler:
	test ! -e bin && mkdir bin
	cd src/compiler; yacc -dv parser.y
	cd src/compiler; lex tokenizer.l
	gcc src/compiler/*.c -o bin/compiler

exec_compiler_test: build_compiler_test
	./bin/compiler

build_test:
	test ! -e bin && mkdir bin
	cd src/compiler; yacc -dv parser.y
	cd src/compiler; lex tokenizer.l
	g++ -lcriterion -I./src/compiler $(filter-out ./src/compiler/main.c, $(wildcard ./src/compiler/*.c)) test/compiler/*.cpp -o bin/compiler_test

clean:
	cd src/compiler; y.tab.c lex.yy.c y.output y.tab.h
	cd bin; rm *
