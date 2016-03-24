%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

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

%%

 /*Falta FunctionDefinition FunctionDeclaration Declaration */
start: FunctionDefinition | FunctionDeclaration | Declaration;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody;

 /*Falta a Declaration e Statement */
FunctionBody: LBRACE RBRACE;

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI;

 /*Falta o AST */
FunctionDeclarator: ID LPAR ParameterList RPAR;

 /*Falta o COMMA ParameterDeclaration */
ParameterList: ParameterDeclaration;

 /*Falta o AST ID*/
ParameterDeclaration: TypeSpec;

 /*Falta o COMMA Declarator */
Declaration: TypeSpec Declarator SEMI;

TypeSpec: CHAR | INT | VOID;

 /*Falta o AST e LSQ INTLIT RSQ*/
Declarator: ID;


Statement: SEMI | Expr SEMI;

 /*Falta a Statement*/
Statement: LBRACE RBRACE;

 /*Falta a ELSE Statement*/
Statement: IF LPAR Expr RPAR Statement;

 /*Falta a Expr*/
Statement: FOR LPAR SEMI SEMI RPAR Statement;

 /*Falta a Expr/
Statement: RETURN SEMI;

Expr: Expr ASSIGN Expr | Expr COMMA Expr;

Expr: Expr AND Expr | Expr OR Expr;

Expr: Expr EQ Expr | Expr NE Expr | Expr LT Expr | Expr GT Expr | Expr LE Expr | Expr GE Expr;

Expr: Expr PLUS Expr| Expr MINUS Expr | Expr AST Expr | Expr DIV Expr| Expr MOD Expr;

Expr: AMP Expr | AST Expr | PLUS Expr |MINUS Expr |NOT Expr;

Expr: Expr LSQ Expr RSQ;

 /*Falta a Expr COMMA Expr*/
Expr: ID LPAR RPAR;

Expr: ID | INTLIT | CHRLIT | STRLIT | LPAR Expr RPAR;



FunctionDefinition: ID  {$$ = $1; printf("%d\n", $1);}
	;
%%
