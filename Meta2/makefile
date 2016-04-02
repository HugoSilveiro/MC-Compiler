all: mccompiler.zip mccompiler

mccompiler.zip: mccompiler.l mccompiler.y structs.h treeFuncs.h printer.h treeFuncs.c printer.c
	zip mccompiler.zip mccompiler.l mccompiler.y structs.h treeFuncs.h printer.h treeFuncs.c printer.c

mccompiler: y.tab.c lex.yy.c
	cc -o mccompiler y.tab.c lex.yy.c treeFuncs.c printer.c -ll -ly

y.tab.c y.tab.h: mccompiler.y
	yacc -d mccompiler.y

lex.yy.c: mccompiler.l
	lex mccompiler.l
