lex mccompiler.l
yacc -d mccompiler.y
cc -o mccompiler y.tab.c lex.yy.c treeFuncs.c printer.c symbolTable.c semantics.c -ll -ly
zip mccompiler.zip mccompiler.l mccompiler.y structs.h treeFuncs.h printer.h symbolTable.h semantics.h treeFuncs.c printer.c symbolTable.c semantics.c 
