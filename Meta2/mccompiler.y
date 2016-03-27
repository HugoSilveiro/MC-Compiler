%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>


	extern int lineNumber;
	extern int columnNumber;
	extern char * yytext;
	
	void yyerror (char *s);
%}

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
%token RESERVED
%token ID
%token INTLIT
%token STRLIT
%token CHRLIT

%nonassoc AMP ELSE IF


%left PLUS MINUS
%left LBRACE RBRACE
%left LPAR RPAR
%left  LSQ RSQ
%right NOT
%left AND DIV MOD AST
%left OR
%right ASSIGN
%left COMMA


%%

Start: FuncDefDecDec FuncDefDecDec1 				{printf("Start\n");};
FuncDefDecDec: FunctionDefinition | FunctionDeclaration | Declaration; 
FuncDefDecDec1: Empty | FuncDefDecDec1 FuncDefDecDec ;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody 	{printf("FunctionDefinition\n");};

FunctionBody: LBRACE Declaration1 Statement1 RBRACE			{printf("FunctionBody\n");}; 

Declaration1: Empty | Declaration1 Declaration ;

Statement1: Empty | Statement1 Statement;

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI {printf("FunctionDeclaration\n");};

FunctionDeclarator: Asterisk ID LPAR ParameterList RPAR {printf("FunctionDeclarator\n");};

Asterisk: Empty | Asterisk AST;

ParameterList: ParameterDeclaration COMMA_ParameterDeclaration {printf("ParameterList\n");};

COMMA_ParameterDeclaration: Empty | COMMA_ParameterDeclaration COMMA ParameterDeclaration;

ParameterDeclaration: TypeSpec Asterisk {printf("ParameterDeclaration[1]\n");} | TypeSpec Asterisk ID  {printf("ParameterDeclaration[2]\n");};

Declaration: TypeSpec Declarator COMMA_Declarator SEMI {printf("Declaration\n");};

COMMA_Declarator: Empty | COMMA_Declarator COMMA Declarator ;

TypeSpec: CHAR  {printf("TypeSpec[CHAR]\n");} | INT {printf("TypeSpec[INT]\n");} | VOID {printf("TypeSpec[VOID]\n");};

Declarator: Asterisk ID  {printf("Declarator[1]\n");} | Asterisk ID LSQ INTLIT RSQ {printf("Declarator[2]\n");};;

Statement: SEMI {printf("Statement[1]\n");} | Expr SEMI 	{printf("Statement[1]\n");};;

Statement: LBRACE Statement1 RBRACE {printf("Statement[2]\n");} ;

Statement: IF LPAR Expr RPAR Statement ElseStatement {printf("IF\n");};

ElseStatement: Empty | ELSE Statement;

Statement: FOR LPAR Expr0 SEMI Expr0 SEMI Expr0 RPAR Statement {printf("For Cycle\n");};

Expr0: Expr | Empty;

Statement: RETURN SEMI {printf("Return Without Value\n");} | RETURN Expr SEMI {printf("Return With Value\n");};

Expr: Expr ASSIGN_COMMA Expr;

Expr: Expr AND_OR Expr;

Expr: Expr COMP Expr ;

Expr: Expr OPS Expr;

Expr: OTHER Expr;

Expr: Expr LSQ Expr RSQ;

Expr: ID LPAR Expr_COMMAExpr RPAR;
Expr_COMMAExpr: Empty | Expr COMMA_Expr;
COMMA_Expr: Empty | COMMA Expr COMMA_Expr;

Expr: ID_LITS | LPAR Expr RPAR;

ASSIGN_COMMA: ASSIGN | COMMA;
AND_OR: AND | OR;
ID_LITS: ID | INTLIT |CHRLIT | STRLIT;
COMP: EQ | NE | LT | GT | LE | GE;
OPS: PLUS | MINUS | AST | DIV | MOD;
OTHER: AMP| AST | PLUS | MINUS |NOT;

Empty: {printf("Empty\n");};


%%

void yyerror (char *s) {
printf ("Line %d, col %d: %s: %s\n",lineNumber, columnNumber-((int) strlen(yytext))+1, s, yytext);
}