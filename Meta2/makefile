all: mccompiler.zip mccompiler

mccompiler.zip: mccompiler.l mccompiler.y structs.h treeFuncs.h printer.h 
	zip mccompiler.zip mccompiler.l mccompiler.y structs.h treeFuncs.h printer.h

mccompiler: y.tab.c lex.yy.c
	gcc -g -o mccompiler y.tab.c lex.yy.c treeFuncs.h printer.h

y.tab.c y.tab.h: mccompiler.y
	yacc -d mccompiler.y

lex.yy.c: mccompiler.l
	lex mccompiler.l
