
ID 				([a-z]|[A-Z]|"_")+([0-9]|[a-z]|[A-Z]|"_")*
INTLIT			[0-9]+
ESCAPE			"\\"([0-7]){1,3}|"\\n"|"\\t"|"\\\\"|"\\'"|"\\\""
STRLIT			"\""(([^"\\\n]|{ESCAPE})*)"\""
CHRLIT			("'"([^'\\\n])"'")|("'"{ESCAPE}"'")


%{
	#define YY_USER_ACTION columnNumber += yyleng; lineNumber = yylineno;
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <stdbool.h>
	int lineNumber = 1;
	int columnNumber = 0;
	int colComment;
	int lineComment;

	bool flag = 0;
%}


%option yylineno
%X COMMENT
%%

"&"									{if(flag)printf("AMP\n");}
"&&"								{if(flag)printf("AND\n");}
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
"{"									{if(flag)printf("LBRACE\n");}
"<="								{if(flag)printf("LE\n");}
"("									{if(flag)printf("LPAR\n");}
"["									{if(flag)printf("LSQ\n");}
"<"									{if(flag)printf("LT\n");}
"-"									{if(flag)printf("MINUS\n");}
"%" 								{if(flag)printf("MOD\n");}
"!="								{if(flag)printf("NE\n");}
"!"									{if(flag)printf("NOT\n");}
"||" 								{if(flag)printf("OR\n");}
"+" 								{if(flag)printf("PLUS\n");}
"}"									{if(flag)printf("RBRACE\n");}
"return" 							{if(flag)printf("RETURN\n");}
")"									{if(flag)printf("RPAR\n");}
"]"									{if(flag)printf("RSQ\n");}
";"									{if(flag)printf("SEMI\n");}
"void"								{if(flag)printf("VOID\n");}
"auto"|"break"|"case"|"const"|"continue"|"default"|"do"|"double"|"enum"|"extern"|"float"|"goto"|"long"|"register"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"volatile"|"while"|"++"|"--" 	{ if(flag)printf("RESERVED(%s)\n", yytext); }



{ID}								{if(flag)printf("ID(%s)\n", yytext);}
{INTLIT}							{if(flag)printf("INTLIT(%s)\n", yytext);}
{STRLIT}							{if(flag)printf("STRLIT(%s)\n", yytext);}
{CHRLIT}							{if(flag)printf("CHRLIT(%s)\n", yytext);}


"/*"								{BEGIN (COMMENT); {	colComment = columnNumber-1;	}lineComment=yylineno;}
<COMMENT>"*/"						{BEGIN (0);}
<COMMENT>"\n"						{columnNumber = 0;}
<COMMENT>.							{;}
<COMMENT><<EOF>>					{printf("Line %d, col %d: unterminated comment\n", lineComment,  colComment); yyterminate();}
"\n"								{columnNumber= 0;}
"\t"								{;}
" "									{;}
. 									{printf("Line %d, col %d: illegal character ('%s')\n", yylineno, columnNumber, yytext);}


%%
int main(int argc, char* argv[])
{
if(argc>1)
{

	if(strcmp(argv[1], "-l")==0)
{
	flag = 1;

}
yylex();
}
return 0;
}

int yywrap()
{
return 1;
}
