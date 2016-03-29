
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
	#include "y.tab.h"
	int lineNumber = 1;
	int columnNumber = 0;
	int colComment;
	int lineComment;

	bool flagTokens = false;
	bool flagErrors = false;
%}


%option yylineno
%X COMMENT
%%

"&"								{
									if(flagTokens)printf("AMP\n");
									if(flagErrors)return AMP;}
"&&"							{
									if(flagTokens)printf("AND\n");
									if(flagErrors)return AND;}
"="								{
									if(flagTokens)printf("ASSIGN\n");
									if(flagErrors)return ASSIGN;}
"*"								{
									if(flagTokens)printf("AST\n");
									if(flagErrors)return AST;}
"char"							{
									if(flagTokens)printf("CHAR\n");
									if(flagErrors)return CHAR;}
","								{
									if(flagTokens)printf("COMMA\n");
									if(flagErrors)return COMMA;}
"/"								{
									if(flagTokens)printf("DIV\n");
									if(flagErrors)return DIV;}
"else"							{
									if(flagTokens)printf("ELSE\n");
									if(flagErrors)return ELSE;}
"=="							{
									if(flagTokens)printf("EQ\n");
									if(flagErrors)return EQ;}
"for"							{	if(flagTokens)printf("FOR\n");
									if(flagErrors)return FOR;}
">="							{
									if(flagTokens)printf("GE\n");
									if(flagErrors)return GE;}
">"								{	if(flagTokens)printf("GT\n");
									if(flagErrors)return GT;}
"if"							{
									if(flagTokens)printf("IF\n");
									if(flagErrors)return IF;}
"int"							{
									if(flagTokens)printf("INT\n");
									if(flagErrors)return INT;}
"{"								{
									if(flagTokens)printf("LBRACE\n");
									if(flagErrors)return LBRACE;}
"<="							{
									if(flagTokens)printf("LE\n");
									if(flagErrors)return LE;}
"("								{
									if(flagTokens)printf("LPAR\n");
									if(flagErrors)return LPAR;}
"["								{
									if(flagTokens)printf("LSQ\n");
									if(flagErrors)return LSQ;}
"<"								{
									if(flagTokens)printf("LT\n");
									if(flagErrors)return LT;}
"-"								{
									if(flagTokens)printf("MINUS\n");
									if(flagErrors)return MINUS;}
"%" 							{
									if(flagTokens)printf("MOD\n");
									if(flagErrors)return MOD;}
"!="							{
									if(flagTokens)printf("NE\n");
									if(flagErrors)return NE;}
"!"								{
									if(flagTokens)printf("NOT\n");
									if(flagErrors)return NOT;}
"||" 							{
									if(flagTokens)printf("OR\n");
									if(flagErrors)return OR;}
"+" 							{
									if(flagTokens)printf("PLUS\n");
									if(flagErrors)return PLUS;}
"}"								{
									if(flagTokens)printf("RBRACE\n");
									if(flagErrors)return RBRACE;}
"return" 						{
									if(flagTokens)printf("RETURN\n");
									if(flagErrors)return RETURN;}
")"								{
									if(flagTokens)printf("RPAR\n");
									if(flagErrors)return RPAR;}
"]"								{
									if(flagTokens)printf("RSQ\n");
									if(flagErrors)return RSQ;}
";"								{
									if(flagTokens)printf("SEMI\n");
									if(flagErrors)return SEMI;}
"void"							{	if(flagTokens)printf("VOID\n");
									if(flagErrors)return AMP;}
"auto"|"break"|"case"|"const"|"continue"|"default"|"do"|"double"|"enum"|"extern"|"float"|"goto"|"long"|"register"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"volatile"|"while"|"++"|"--" 							{
																																																																if(flagTokens)printf("RESERVED(%s)\n", yytext);
																																																																if(flagErrors)return yytext;}


{ID}								{if(flagTokens)printf("ID(%s)\n", yytext); yylval = yytext; return ID;}

{INTLIT}							{if(flagTokens)printf("INTLIT(%s)\n", yytext); return INTLIT;}
{STRLIT}							{if(flagTokens)printf("STRLIT(%s)\n", yytext); return STRLIT;}

{NOSTRLIT}							{printf("Line %d, col %d: unterminated string constant\n", yylineno, (int)(columnNumber-yyleng+1));}
{NOCHRLIT}							{printf("Line %d, col %d: unterminated char constant\n", yylineno, (int)(columnNumber-yyleng+1));}
{CHRLIT}							{if(flagTokens)printf("CHRLIT(%s)\n", yytext); return CHRLIT;}

{INVALIDSTRLIT}							{printf("Line %d, col %d: invalid string constant (%s)\n", yylineno, (int)(columnNumber-yyleng+1), yytext);}
{INVALIDCHR}							{printf("Line %d, col %d: invalid char constant (%s)\n", yylineno, (int)(columnNumber-yyleng+1), yytext);}

"/*"								{BEGIN (COMMENT); {	colComment = columnNumber-1;	}lineComment=yylineno;}
<COMMENT>"*/"							{BEGIN (0);}
<COMMENT>"\n"							{columnNumber = 0;}
<COMMENT>.							{;}
<COMMENT><<EOF>>						{printf("Line %d, col %d: unterminated comment\n", lineComment,  colComment); yyterminate();}
"\n"								{columnNumber= 0;}
"\t"								{;}
" "									{;}
. 									{printf("Line %d, col %d: illegal character (%s)\n", yylineno, columnNumber, yytext);}


%%

int yywrap(){
	return 1;
}

int main(int argc, char* argv[])
{
	if(argc>1)
	{

		if(strcmp(argv[1], "-l")==0)
		{
			flagTokens = true;
		}
		else if(strcmp(argv[1], "-1") == 0)
		{
			flagErrors = true;
		}

	}

	yyparse();
	return 0;
}
