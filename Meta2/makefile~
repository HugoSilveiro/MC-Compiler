all: mccompiler.zip mccompiler

mccompiler.zip: mccompiler.l mccompiler.y structs.h treeFuncs.c 
	zip mccompiler.zip mccompiler.l mccompiler.y structs.h treeFuncs.c

mccompiler: y.tab.c lex.yy.c
	gcc -g -o mccompiler y.tab.c lex.yy.c treeFuncs.c

y.tab.c y.tab.h: mccompiler.y
	yacc -d mccompiler.y

lex.yy.c: mccompiler.l
	lex mccompiler.l
