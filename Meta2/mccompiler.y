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

Start: FunctionDefinition FuncDefDecDec | FunctionDeclaration  FuncDefDecDec| Declaration  FuncDefDecDec;
FuncDefDecDec:  FunctionDefinition FuncDefDecDec | FunctionDeclaration FuncDefDecDec | Declaration FuncDefDecDec | Empty;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody;

FunctionBody: LBRACE Declaration1 Statement1 RBRACE;

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI;

FunctionDeclarator: Asterisk ID LPAR ParameterList RPAR;

ParameterList: ParameterDeclaration COMMA_ParameterDeclaration;

ParameterDeclaration: TypeSpec Asterisk | TypeSpec Asterisk ID;

Declaration: TypeSpec Declarator COMMA_Declarator SEMI;
//In case of brackets -> [0,inf[
Declaration1: Empty | TypeSpec Declarator COMMA_Declarator SEMI;

TypeSpec: CHAR | INT | VOID;

Declarator: Asterisk ID | Asterisk ID LSQ INTLIT RSQ;

Statement: SEMI | Expr SEMI;

Statement: LBRACE Statement1 RBRACE;

 /*Falta a ELSE Statement*/
Statement: IF LPAR Expr RPAR Statement ElseStatement;

Statement: FOR LPAR Expr0 SEMI Expr0 SEMI Expr0 RPAR Statement;
Expr0: Expr | Empty;

//In case of brackets -> [0,inf[
Statement1: Empty | Statement1 Statement;

Statement: RETURN SEMI | RETURN Expr SEMI;

ElseStatement: Empty | Else Statement;

Expr: Expr ASSIGN Expr | Expr COMMA Expr;

Expr: Expr AND Expr | Expr OR Expr;

Expr: Expr EQ Expr | Expr NE Expr | Expr LT Expr | Expr GT Expr | Expr LE Expr | Expr GE Expr;

Expr: Expr PLUS Expr| Expr MINUS Expr | Expr AST Expr | Expr DIV Expr| Expr MOD Expr;

Expr: AMP Expr | AST Expr | PLUS Expr |MINUS Expr |NOT Expr;

Expr: Expr LSQ Expr RSQ;

 /*Falta a Expr COMMA Expr*/
Expr: ID LPAR RPAR;

Expr: ID | INTLIT | CHRLIT | STRLIT | LPAR Expr RPAR;

Asterisk: Empty | Asterisk  AST;

COMMA_Declarator: Empty | COMMA_Declarator COMMA Declarator;

COMMA_ParameterDeclaration: Empty | COMMA_ParameterDeclaration COMMA ParameterDeclaration;

Empty: ;

FunctionDefinition: ID  {$$ = $1; printf("%d\n", $1);}
	;
%%
