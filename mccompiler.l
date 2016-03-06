
ID 				([a-z]|[A-Z]|"_")+([0-9]|[a-z]|[A-Z]|"_")*
INTLIT			[0-9]+
ESCAPE			"\\"([0-7]){1,3}|"\\n"|"\\t"|"\\\\"|"\\'"|"\\\""
NOTESCAPE		\\.|\\[8-9]{1,3}
STRLIT			"\""(([^"\\\n]|{ESCAPE})*)"\""
CHRLIT			("'"([^'\\\n]|{ESCAPE})"'")


NOSTRLIT 		\"([^\"\n]|{ESCAPE})*
NOCHRLIT		\'({ESCAPE}*|(\\.|[^'\n\\]))*\\?

INVALIDCHR		\'([^'\n\\]|{NOTESCAPE})*\'
INVALIDSTRLIT	\"([^"\n\\]|{NOTESCAPE})*\"


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

	bool flag = false;
%}


%option yylineno
%X COMMENT
%%

"&"									{if(flag)printf("AMP\n");}
"&&"								{if(flag)printf("AND\n");}
"="									{if(flag)printf("ASSIGN\n");}
"*"									{if(flag)printf("AST\n");}
"char"								{if(flag)printf("CHAR\n");}
","									{if(flag)printf("COMMA\n");}
"/"									{if(flag)printf("DIV\n");}
"else"								{if(flag)printf("ELSE\n");}
"=="								{if(flag)printf("EQ\n");}
"for"								{if(flag)printf("FOR\n");}
">="								{if(flag)printf("GE\n");}
">"									{if(flag)printf("GT\n");}
"if"								{if(flag)printf("IF\n");}
"int"								{if(flag)printf("INT\n");}
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

{NOSTRLIT}							{printf("Line %d, col %d: unterminated string constant\n", yylineno, (int)(columnNumber-yyleng+1));}
{NOCHRLIT}							{printf("Line %d, col %d: unterminated char constant\n", yylineno, (int)(columnNumber-yyleng+1));}
{CHRLIT}							{if(flag)printf("CHRLIT(%s)\n", yytext);}

{INVALIDSTRLIT}						{printf("Line %d, col %d: invalid string constant (%s)\n", yylineno, (int)(columnNumber-yyleng+1), yytext);}
{INVALIDCHR}						{printf("Line %d, col %d: invalid char constant (%s)\n", yylineno, (int)(columnNumber-yyleng+1), yytext);}

"/*"								{BEGIN (COMMENT); {	colComment = columnNumber-1;	}lineComment=yylineno;}
<COMMENT>"*/"						{BEGIN (0);}
<COMMENT>"\n"						{columnNumber = 0;}
<COMMENT>.							{;}
<COMMENT><<EOF>>					{printf("Line %d, col %d: unterminated comment\n", lineComment,  colComment); yyterminate();}
"\n"								{columnNumber= 0;}
"\t"								{;}
" "									{;}
. 									{printf("Line %d, col %d: illegal character (%s)\n", yylineno, columnNumber, yytext);}


%%
int main(int argc, char* argv[])
{
if(argc>1)
{

	if(strcmp(argv[1], "-l")==0)
	{
		flag = true;
	}

}
yylex();
return 0;
}

int yywrap()
{
return 1;
}
