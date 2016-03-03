
ID 				([a-z]|[A-Z]|"_")+([0-9]|[a-z]|[A-Z]|"_")*
INTLIT			[0-9]+
STRLIT			"\""([^"\n])*"\""

%{
	#define YY_USER_ACTION columnNumber += yyleng;
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	int lineNumber = 1;
	int columnNumber = 0;
	int colComment;
	int lineComment;
%}

%X COMMENT
%%

"&"									{printf("AMP\n");}
"&&"								{printf("AND\n");}
"="									{printf("ASSIGN\n");}
"*"									{printf("AST\n");}
"char"								{printf("CHAR\n");}
","									{printf("COMMA\n");}
"/"									{printf("DIV\n");}
"else"								{printf("ELSE\n");}
"=="								{printf("EQ\n");}
"for"								{printf("FOR\n");}
">="								{printf("GE\n");}
">"									{printf("GT\n");}
"if"								{printf("IF\n");}
"int"								{printf("INT\n");}
"{"									{printf("LBRACE\n");}
"<="								{printf("LE\n");}
"("									{printf("LPAR\n");}
"["									{printf("LSQ\n");}
"<"									{printf("LT\n");}
"-"									{printf("MINUS\n");}
"%" 								{printf("MOD\n");}
"!="								{printf("NE\n");}
"!"									{printf("NOT\n");}
"||" 								{printf("OR\n");}
"+" 								{printf("PLUS\n");}
"}"									{printf("RBRACE\n");}
"return" 							{printf("RETURN\n");}
")"									{printf("RPAR\n");}
"]"									{printf("RSQ\n");}
";"									{printf("SEMI\n");}
"void"								{printf("VOID\n");}
"auto"|"break"|"case"|"const"|"continue"|"default"|"do"|"double"|"enum"|"extern"|"float"|"goto"|"long"|"register"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"volatile"|"while"|"++"|"--" 	{ printf("RESERVED(%s)\n", yytext); }



{ID}								{printf("ID(%s)\n", yytext);}
{INTLIT}							{printf("INTLIT(%s)\n", yytext);}
{STRLIT}							{printf("STRLIT(%s)\n", yytext);}

"/*"								{BEGIN (COMMENT);}
<COMMENT>"*/"						{BEGIN (0);}
<COMMENT>"\n"						{columnNumber = 0;}
<COMMENT>.							{;}
<COMMENT><<EOF>>					{printf("Line %d, col %d: unterminated comment\n", lineComment,  columnNumber);}
"\n"								{columnNumber= 0;}
"\t"								{;}
" "									{;}
. 									{printf("Line %d, col %d: illegal character\n", lineComment,  columnNumber);}


%%
int main(int argc, char* argv[])
{
if(argc>1)
{
	if(strcmp(argv[1], "-l")==0)
{
	yylex();

}
}
return 0;
}

int yywrap()
{
return 1;
}
