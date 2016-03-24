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


%left PLUS MINUS
%left COMMA
%left AND DIV MOD AST 
%left OR
%left LBRACE RBRACE
%right NOT

%%

Start: FuncDefDecDec FuncDefDecDec1;
FuncDefDecDec: FunctionDefinition | FunctionDeclaration | Declaration;
FuncDefDecDec1: Empty | FuncDefDecDec1 FuncDefDecDec ;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody;

FunctionBody: LBRACE Declaration1 Statement1 RBRACE;

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI;

FunctionDeclarator: Asterisk ID LPAR ParameterList RPAR;

ParameterList: ParameterDeclaration COMMA_ParameterDeclaration;

ParameterDeclaration: TypeSpec Asterisk | TypeSpec Asterisk ID;

Declaration: TypeSpec Declarator COMMA_Declarator SEMI;

Declaration1: Empty | Declaration1 Declaration;

TypeSpec: CHAR | INT | VOID;

Declarator: Asterisk ID | Asterisk ID LSQ INTLIT RSQ;

Statement: SEMI | Expr SEMI;

Statement: LBRACE Statement1 RBRACE;

Statement: IF LPAR Expr RPAR Statement ElseStatement;

Statement: FOR LPAR Expr0 SEMI Expr0 SEMI Expr0 RPAR Statement;
Expr0: Expr | Empty;

Statement1: Empty | Statement1 Statement;

Statement: RETURN SEMI | RETURN Expr SEMI;

ElseStatement: Empty | ELSE Statement;

Expr: Expr ASSIGN Expr | Expr COMMA Expr;

Expr: Expr AND Expr | Expr OR Expr;

Expr: Expr EQ Expr | Expr NE Expr | Expr LT Expr | Expr GT Expr | Expr LE Expr | Expr GE Expr;

Expr: Expr PLUS Expr| Expr MINUS Expr | Expr AST Expr | Expr DIV Expr| Expr MOD Expr;

Expr: AMP Expr | AST Expr | PLUS Expr |MINUS Expr |NOT Expr;

Expr: Expr LSQ Expr RSQ;

Expr: ID LPAR Expr_COMMAExpr RPAR;
Expr_COMMAExpr: Empty | Expr COMMA_Expr;
COMMA_Expr: Empty | COMMA Expr COMMA_Expr;

Expr: ID | INTLIT | CHRLIT | STRLIT | LPAR Expr RPAR;

Asterisk: Empty | Asterisk AST;

COMMA_Declarator: Empty | COMMA_Declarator COMMA Declarator;

COMMA_ParameterDeclaration: Empty | COMMA_ParameterDeclaration COMMA ParameterDeclaration;

Empty: ;


%%
