SHELL=/bin/bash

COMPILER_DIR=./src/compiler

.PHONY: clean build_compiler exec_compiler build_compiler_test exec_compiler_test exec_util_test build_util_test

exec_compiler: build_compiler
	./bin/compiler

build_compiler:
	$(shell test ! -e bin && mkdir bin)
	cd src/compiler; yacc -dv parser.y
	cd src/compiler; lex tokenizer.l
	gcc src/compiler/*.c -o bin/compiler

exec_compiler_test: build_compiler_test
	./bin/compiler_test

build_compiler_test:
	$(shell test ! -e bin && mkdir bin)
	cd src/compiler; yacc -dv parser.y
	cd src/compiler; lex tokenizer.l
	g++ -lcriterion -I./src/compiler $(shell find ./src/compiler -name *.c | grep -vE 'main.c|y.tab.c|lex.yy.c') $(COMPILER_DIR)/y.tab.c $(COMPILER_DIR)/lex.yy.c test/compiler/*.cpp -o bin/compiler_test

exec_util_test: build_util_test
	./bin/util_test

build_util_test:
	$(shell test ! -e bin && mkdir bin)
	g++ -lcriterion -I./src ./src/util/*.c test/util/*.cpp -o bin/util_test

clean:
	cd src/compiler; rm y.tab.c lex.yy.c y.output y.tab.h
	cd bin; rm *
