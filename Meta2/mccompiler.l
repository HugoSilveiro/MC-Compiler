
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
	#include "structs.h"
	#include "printer.h"
	
	int lineNumber = 1;
	int columnNumber = 0;
	int colComment;
	int lineComment;
	int treeFlag = 0;
	extern int yacc_errors;
	extern Node *tree;
	int flag = 0;
%}


%option yylineno
%X COMMENT
%%

"&"								{
									if(flag == 1)printf("AMP\n");
									if(flag == 0)return AMP;}
"&&"							{
									if(flag == 1)printf("AND\n");
									if(flag == 0)return AND;}
"="								{
									if(flag == 1)printf("ASSIGN\n");
									if(flag == 0)return ASSIGN;}
"*"								{
									if(flag == 1)printf("AST\n");
									if(flag == 0)return AST;}
"char"							{
									if(flag == 1)printf("CHAR\n");
									if(flag == 0)return CHAR;}
","								{
									if(flag == 1)printf("COMMA\n");
									if(flag == 0)return COMMA;}
"/"								{
									if(flag == 1)printf("DIV\n");
									if(flag == 0)return DIV;}
"else"							{
									if(flag == 1)printf("ELSE\n");
									if(flag == 0)return ELSE;}
"=="							{
									if(flag == 1)printf("EQ\n");
									if(flag == 0)return EQ;}

"for"							{	if(flag == 1)printf("FOR\n");
									if(flag == 0)return FOR;}
">="							{
									if(flag == 1)printf("GE\n");
									if(flag == 0)return GE;}

">"								{	if(flag == 1)printf("GT\n");
									if(flag == 0)return GT;}
"if"							{
									if(flag == 1)printf("IF\n");
									if(flag == 0)return IF;}
"int"							{
									if(flag == 1)printf("INT\n");
									if(flag == 0)return INT;}
"{"								{
									if(flag == 1)printf("LBRACE\n");
									if(flag == 0)return LBRACE;}
"<="							{
									if(flag == 1)printf("LE\n");
									if(flag == 0)return LE;}
"("								{
									if(flag == 1)printf("LPAR\n");
									if(flag == 0)return LPAR;}
"["								{
									if(flag == 1)printf("LSQ\n");
									if(flag == 0)return LSQ;}
"<"								{
									if(flag == 1)printf("LT\n");
									if(flag == 0)return LT;}
"-"								{
									if(flag == 1)printf("MINUS\n");
									if(flag == 0)return MINUS;}
"%" 							{
									if(flag == 1)printf("MOD\n");
									if(flag == 0)return MOD;}
"!="							{
									if(flag == 1)printf("NE\n");
									if(flag == 0)return NE;}
"!"								{
									if(flag == 1)printf("NOT\n");
									if(flag == 0)return NOT;}
"||" 							{
									if(flag == 1)printf("OR\n");
									if(flag == 0)return OR;}
"+" 							{
									if(flag == 1)printf("PLUS\n");
									if(flag == 0)return PLUS;}
"}"								{
									if(flag == 1)printf("RBRACE\n");
									if(flag == 0)return RBRACE;}
"return" 						{
									if(flag == 1)printf("RETURN\n");
									if(flag == 0)return RETURN;}
")"								{
									if(flag == 1)printf("RPAR\n");
									if(flag == 0)return RPAR;}
"]"								{
									if(flag == 1)printf("RSQ\n");
									if(flag == 0)return RSQ;}
";"								{
									if(flag == 1)printf("SEMI\n");
									if(flag == 0)return SEMI;}
"void"							{	if(flag == 1)printf("VOID\n");
									if(flag == 0)return VOID;}
"auto"|"break"|"case"|"const"|"continue"|"default"|"do"|"double"|"enum"|"extern"|"float"|"goto"|"long"|"register"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"volatile"|"while"|"++"|"--" 							{
																																																																if(flag == 1)printf("RESERVED(%s)\n", yytext);
																																																																if(flag == 0){yylval.string = strdup(yytext);return RESERVED;}}


{ID}							{	if(flag == 1)printf("ID(%s)\n", yytext);
									if(flag == 0){yylval.string = strdup(yytext); return ID;}}

{INTLIT}						{	if(flag == 1)printf("INTLIT(%s)\n", yytext);
									if(flag == 0){yylval.string = strdup(yytext); return INTLIT;}}

{STRLIT}						{	if(flag == 1)printf("STRLIT(%s)\n", yytext);
									if(flag == 0){yylval.string = strdup(yytext); return STRLIT;}}

{NOSTRLIT}						{	printf("Line %d, col %d: unterminated string constant\n", yylineno, (int)(columnNumber-yyleng+1));}

{NOCHRLIT}						{	printf("Line %d, col %d: unterminated char constant\n", yylineno, (int)(columnNumber-yyleng+1));}

{CHRLIT}						{	if(flag == 1)printf("CHRLIT(%s)\n", yytext);
									if(flag == 0){yylval.string=strdup(yytext); return CHRLIT;}}

{INVALIDSTRLIT}					{	printf("Line %d, col %d: invalid string constant (%s)\n", yylineno, (int)(columnNumber-yyleng+1), yytext);}

{INVALIDCHR}					{	printf("Line %d, col %d: invalid char constant (%s)\n", yylineno, (int)(columnNumber-yyleng+1), yytext);}

"/*"							{	BEGIN (COMMENT); {	colComment = columnNumber-1;	}lineComment=yylineno;}
<COMMENT>"*/"					{	BEGIN (0);}
<COMMENT>"\n"					{	columnNumber = 0;}
<COMMENT>.						{	;}
<COMMENT><<EOF>>				{	printf("Line %d, col %d: unterminated comment\n", lineComment,  colComment); yyterminate();}

"\n"							{	columnNumber= 0;}

"\t"							{	;}

" "								{	;}

. 								{	printf("Line %d, col %d: illegal character (%s)\n", yylineno, columnNumber, yytext);}


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
			flag = 1;
			yylex();
		}
		else if(strcmp(argv[1], "-1") == 0)
		{
			flag = 2;
			yylex();
		}
		else if(strcmp(argv[1], "-t") == 0)
		{
			treeFlag = 1;
		}



	}
	if(flag==0)
	{
		yyparse();
		if(yacc_errors == 0 && treeFlag == 1)
		{
			print_tree(tree, 0);
		}

	}
	return 0;
}
