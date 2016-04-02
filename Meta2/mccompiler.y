%{
	#define DEBUG 2<1
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>


	extern int lineNumber;
	extern int columnNumber;
	extern int yyleng;
	extern int yylineno;
	extern char * yytext;
	int yylex(void);
	void yyerror (char *s);
%}

%union{
    char *string;
}

%token AMP
%token AND
%token ASSIGN
%token AST
%token CHAR
%token COMMA
%token DIV
%token ELSE
%token EQ
%token FOR
%token GE
%token GT
%token IF
%token INT
%token LBRACE
%token LE
%token LPAR
%token LSQ
%token LT
%token MINUS
%token MOD
%token NE
%token NOT
%token OR
%token PLUS
%token RBRACE
%token RETURN
%token RPAR
%token RSQ
%token SEMI
%token VOID
%token <string> RESERVED
%token <string> ID
%token <string> INTLIT
%token <string> STRLIT
%token <string> CHRLIT

%nonassoc "then"
%nonassoc ELSE



%left AMP
%left AND
%left OR
%left NOT
%left EQ NE
%left GE LE GT LT
%left MOD AST DIV
%left MINUS PLUS
%left LSQ RSQ
%left LPAR RPAR
%right ASSIGN
%left COMMA

%%



Start: FuncDefDecDec FuncDefDecDec1 									{if(DEBUG)printf("Start\n");}
		;
FuncDefDecDec: 	FunctionDefinition
				| FunctionDeclaration
				| Declaration
				;
FuncDefDecDec1: Empty
				| FuncDefDecDec1 FuncDefDecDec
				;
FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody			{if(DEBUG)printf("FunctionDefinition\n");}
					;

FunctionDeclaration: 	TypeSpec FunctionDeclarator SEMI				{if(DEBUG)printf("FunctionDeclaration\n");}
						;


FunctionDeclarator: Asterisk ID LPAR ParameterList RPAR					{if(DEBUG)printf("FunctionDeclarator\n");}
				;


FunctionBody: 	LBRACE DeclNot StateSpec RBRACE		 					{if(DEBUG)printf("FunctionBody\n");}
				| LBRACE error RBRACE 									{if(DEBUG)printf("Error on Function Body\n");}
				;

ParameterList: 	ParameterDeclaration COMMA_ParameterDeclaration			{if(DEBUG)printf("ParameterList\n");}
				;

ParameterDeclaration: 	TypeSpec Asterisk									{if(DEBUG)printf("ParameterDeclaration[1]\n");}
						| TypeSpec Asterisk ID 								{if(DEBUG)printf("ParameterDeclaration[2]\n");}
						;


COMMA_ParameterDeclaration: 	COMMA ParameterDeclaration COMMA_ParameterDeclaration
								| Empty
								;



Declaration: TypeSpec Declarator COMMA_Declarator SEMI						{if(DEBUG)printf("Declaration\n");}
			| error SEMI 													{if(DEBUG)printf("Error on Declaration\n");}
			;

DeclNot: Declaration DeclNot
		| Empty
		;

TypeSpec: 	CHAR 															{if(DEBUG)printf("TypeSpec[CHAR]\n");}
			| INT 															{if(DEBUG)printf("TypeSpec[INT]\n");}
			| VOID 															{if(DEBUG)printf("TypeSpec[VOID]\n");}
			;


Declarator: 	Asterisk ID LSQ INTLIT RSQ  								{if(DEBUG)printf("Declarator[1]\n");}
				| Asterisk ID												{if(DEBUG)printf("Declarator[2]\n");}
				;

COMMA_Declarator: 	COMMA Declarator COMMA_Declarator
					|  Empty
					;

Statement: 	error SEMI 														{if(DEBUG)printf("Statement Error\n");}
			| Statement_List
			;

Statement_List: 	 Expr0 SEMI												{if(DEBUG)printf("Statement[1]\n");}
					| LBRACE St RBRACE										{if(DEBUG)printf("Statement[2]\n");}
					| LBRACE RBRACE
					| LBRACE error RBRACE
					| IF LPAR Expr RPAR Statement   %prec "then"
					| IF LPAR Expr RPAR Statement ELSE Statement 			{if(DEBUG)printf("IF\n");}
					| FOR LPAR Expr0 SEMI Expr0 SEMI Expr0 RPAR Statement	{if(DEBUG)printf("For Cycle\n");}
					| RETURN Expr0 SEMI 										{if(DEBUG)printf("Return With Value\n");}
					;

St: Statement StateNot
	;

StateSpec: Empty | Statement_List StateSpec;


StateNot: 	Empty
			| Statement StateNot;


Expr: ExprNew | Expr COMMA ExprNew;

ExprNew:  ExprNew ASSIGN ExprNew
		| ExprNew AND ExprNew
		| ExprNew OR ExprNew
		| ExprNew EQ ExprNew
		| ExprNew NE ExprNew
		| ExprNew LT ExprNew
		| ExprNew GT ExprNew
		| ExprNew LE ExprNew
		| ExprNew GE ExprNew
		| ExprNew PLUS ExprNew
		| ExprNew MINUS ExprNew
		| ExprNew AST ExprNew
		| ExprNew DIV ExprNew
		| ExprNew MOD ExprNew
		| AMP ExprNew
		| AST ExprNew
		| PLUS ExprNew
		| MINUS ExprNew
		| NOT ExprNew
		| ID LPAR ExprNew COMMA_Expr RPAR
		| ID LPAR RPAR
		| LPAR Expr RPAR
		| ID
		| INTLIT
		| CHRLIT
		| STRLIT
		| ID LPAR error RPAR 												{if(DEBUG)printf("Expr Error\n");}
		| LPAR error RPAR 													{if(DEBUG)printf("Expr Error\n");}
		| ExprNew LSQ Expr RSQ
		;



COMMA_Expr: 	COMMA ExprNew COMMA_Expr
				| Empty
				;

Expr0: 	Expr
		| Empty
		;



Asterisk: 	AST Asterisk
			| Empty
			;


Empty: 			{if(DEBUG)printf("Empty\n");};

%%

void yyerror (char *s) {
	printf ("Line %d, col %d: %s: %s\n",yylineno, (int)(columnNumber - strlen(yytext)+1), s, yytext);
}
