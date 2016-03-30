%{
	#define DEBUG 2>1
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>


	extern int lineNumber;
	extern int columnNumber;
	extern char * yytext;

	void yyerror (char *s);
%}

%union{
    char *value;
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
%token RESERVED
%token ID
%token INTLIT
%token STRLIT
%token CHRLIT

%nonassoc "then"
%nonassoc ELSE
%left AND
%left OR
%right ASSIGN
%left COMMA



%%

Start: FuncDefDecDec FuncDefDecDec1
	{if(DEBUG)printf("Start\n");};

FuncDefDecDec: 	FunctionDefinition
				| FunctionDeclaration
				| Declaration;
FuncDefDecDec1: Empty
				| FuncDefDecDec1 FuncDefDecDec ;

FunctionDefinition: 	TypeSpec FunctionDeclarator FunctionBody
	{if(DEBUG)printf("FunctionDefinition\n");};

FunctionBody: 	LBRACE Declaration1 Statement1 RBRACE {if(DEBUG)printf("FunctionBody\n");}
				| LBRACE error RBRACE 	{if(DEBUG)printf("Error on Function Body\n");} ;

Declaration1: 	Declaration Declaration1 
				| Empty;

Statement1: 	Statement Statement1
				| Empty;

FunctionDeclaration: TypeSpec FunctionDeclarator SEMI
	{if(DEBUG)printf("FunctionDeclaration\n");};

FunctionDeclarator: Asterisk ID LPAR ParameterList RPAR
	{if(DEBUG)printf("FunctionDeclarator\n");};

Asterisk: 	Empty
			| Asterisk AST;

ParameterList: ParameterDeclaration COMMA_ParameterDeclaration
	{if(DEBUG)printf("ParameterList\n");};

COMMA_ParameterDeclaration: 	Empty
								| COMMA_ParameterDeclaration COMMA ParameterDeclaration;

ParameterDeclaration: 	TypeSpec Asterisk
						{if(DEBUG)printf("ParameterDeclaration[1]\n");}
						| TypeSpec Asterisk ID
						{if(DEBUG)printf("ParameterDeclaration[2]\n");};

Declaration: TypeSpec Declarator COMMA_Declarator SEMI 
	{if(DEBUG)printf("Declaration\n");}
			| error SEMI {if(DEBUG)printf("Error on Declaration\n");};

COMMA_Declarator: 	Empty
					| COMMA_Declarator COMMA Declarator ;

TypeSpec: 	CHAR
	{if(DEBUG)printf("TypeSpec[CHAR]\n");}
			| INT
	{if(DEBUG)printf("TypeSpec[INT]\n");}
			| VOID
	{printf("TypeSpec[VOID]\n");};

Declarator: 	Asterisk ID
	{if(DEBUG)printf("Declarator[1]\n");}
				| Asterisk ID LSQSTATE INTLITSTATE RSQSTATE
	{if(DEBUG)printf("Declarator[2]\n");};

LSQSTATE: 	LSQ
	{if(DEBUG)printf("LSQ\n");};

RSQSTATE: RSQ
	{if(DEBUG)printf("RSQ\n");};

INTLITSTATE: INTLIT
	{if(DEBUG)printf("INTLIT");};

Statement: 	SEMI
	{if(DEBUG)printf("Statement[1]\n");}
			| Expr SEMI
	{if(DEBUG)printf("Statement[1]\n");};
			|LBRACE Statement1 RBRACE
	   {if(DEBUG)printf("Statement[2]\n");} ;
	   		|StateIF
			|FOR LPAR Expr0 SEMI Expr0 SEMI Expr0 RPAR Statement
			{if(DEBUG)printf("For Cycle\n");}

StateIF: 	IF LPAR Expr RPAR Statement   %prec "then"
			|IF LPAR Expr RPAR Statement ELSE Statement
			{if(DEBUG)printf("IF\n");}


Statement: 	RETURN SEMI
			{if(DEBUG)printf("Return Without Value\n");}
			| RETURN Expr SEMI
			{if(DEBUG)printf("Return With Value\n");};
Expr0: 	Empty
		| Expr;



Expr: 	Expr ASSIGN Expr
		|Expr COMMA Expr;

Expr: 	Expr AND Expr
		|Expr OR Expr;

//Expr: Expr COMP Expr ;

//Expr: Expr OPS Expr;

//Expr: OTHER Expr;

//Expr: Expr LSQ Expr RSQ;

//Expr: ID LPAR Expr_COMMAExpr RPAR;

//Expr_COMMAExpr: 	Empty
					//| Expr COMMA_Expr;
//COMMA_Expr: 	Empty
				//| COMMA Expr COMMA_Expr;

Expr:	LPAR Expr RPAR
		| ID
		| INTLIT
		|CHRLIT
		| STRLIT;


//AND_OR: 	AND
			//| OR;

//COMP: 	EQ
			//| NE
			//| LT
			//| GT
			//| LE
			//| GE;
//OPS: 	PLUS
		//| MINUS
		//| AST
		//| DIV
		//| MOD;
//OTHER: 	AMP
			//| AST
			//| PLUS
			//| MINUS |NOT;

Empty: {if(DEBUG)printf("Empty\n");};


%%

void yyerror (char *s) {
printf ("Line %d, col %d: %s: %s\n",lineNumber, columnNumber-((int) strlen(yytext))+1, s, yytext);
}
