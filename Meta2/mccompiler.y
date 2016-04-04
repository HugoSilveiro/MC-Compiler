%{
	#define DEBUG 0
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	#include "structs.h"
	#include "treeFuncs.h"
	#include "printer.h"

	extern int lineNumber;
	extern int columnNumber;
	extern int yyleng;
	extern int yylineno;
	extern char * yytext;

	Node *tree = NULL;
	Node *nodeAux;
	Node *nodeAux2;

	int yacc_errors = 0;

	int yylex(void);
	void yyerror (char *s);
%}

%union{
    char *string;
	struct Node_elem* node;
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


%type <node> Start
%type <node> FunctionDefinition
%type <node> FunctionDeclaration
%type <node> Declaration
%type <node> Restart
%type <node> TypeSpec
%type <node> FunctionDeclarator
%type <node> FunctionBody
%type <node> Declarator
%type <node> Expressions_List
%type <node> Declaration_Un
%type <node> State_List_UN
%type <node> Asterisk
%type <node> Statement_List
%type <node> Statement


%type <node> ParameterList
%type <node> ParameterDeclaration
%type <node> Empty
%type <node> COMMA_Declarator
%type <node> Expr
%type <node> Expression_Un

%type <node> ExprCOMMA_Expr
%type <node> COMMA_Expr


%type <node> COMMA_ParameterDeclaration
%type <node> Statement_Un
%type <node> St





%nonassoc "then"
%nonassoc ELSE



%left COMMA
%right ASSIGN
%left OR
%left AND
%left EQ NE
%left GE LE GT LT
%left PLUS MINUS
%left AST DIV MOD
%right NOT AMP
%left LPAR RPAR LSQ RSQ LBRACE RBRACE




%%

//Un -> 0 or 1
//Rep -> 0 or more

Start:  FunctionDefinition  Restart                                                					{
																										if(DEBUG)printf("Start1\n");
																										$$ = insert_node(NODE_Program);
																										tree=$$;
																										insert_child($$, $1, 0);

																										insert_brother($1, $2);


																									}
        | FunctionDeclaration Restart                                              					{
        																								if(DEBUG)printf("Start2\n");
        																								$$ = insert_node(NODE_Program);
																										tree=$$;
        																								insert_child($$, $1, 0);

																										insert_brother($1, $2);


        																							}
        | Declaration Restart                                                     					{
        																								if(DEBUG)printf("Start3\n");
        																								$$ = insert_node(NODE_Program);
																										tree=$$;
																										insert_child($$, $1, 0);

																										insert_brother($1, $2);


        																							}
        ;

Restart: FunctionDefinition Restart                                             					{
																										if(DEBUG)printf("Restart1\n");

																										$$ = $1;
																										insert_brother($$, $2);

																									}
            | FunctionDeclaration Restart															{
																										if(DEBUG)printf("Restart2\n");
																										$$ = $1;
																										insert_brother($$, $2);
																									}
            | Declaration Restart																	{
																										if(DEBUG)printf("Restart1\n");
																										$$ = $1;
																										insert_brother($$, $2);

																									}
            | Empty																					{
																										$$ = NULL;
																									}
            ;

FunctionDefinition: TypeSpec FunctionDeclarator FunctionBody										{
																										if(DEBUG)printf("FunctionDefinition\n");
																										$$ = insert_node(NODE_FuncDefinition);
																										insert_child($$, $1, 0);
																										insert_brother($1, $2);
																										insert_brother($1, $3);




																									}
					;

FunctionDeclaration: 	TypeSpec FunctionDeclarator SEMI											{
																										if(DEBUG)printf("FunctionDeclaration\n");
																										$$ = insert_node(NODE_FuncDeclaration);
																										insert_child($$, $2, 0);
																										insert_child($$, $1, 0);

																									}
						;


FunctionDeclarator: Asterisk ID LPAR ParameterList RPAR												{
																										if(DEBUG)printf("FunctionDeclarator\n");
																										nodeAux = insert_term_node(NODE_Id, $2);
																										if($1 != NULL){
																											$$ = $1;
																											insert_brother($$, nodeAux);
																											insert_brother($$, $4);
																										}
																										else{
																											$$ = nodeAux;
																											insert_brother($$, $4);
																										}

																									}
					;


FunctionBody: 	LBRACE Declaration_Un State_List_UN RBRACE		 									{
																										if(DEBUG)printf("FunctionBody\n");
																										$$ = insert_node(NODE_FuncBody);

																										if($2 == NULL && $3 == NULL){

																										}
																										else{
																											if($2 != NULL){
																												insert_child($$, $2, 0);

																												insert_brother($2, $3);
																											}
																											else{
																												insert_child($$, $3, 0);
																											}

																										}

																									}
				| LBRACE error RBRACE 																{
																										if(DEBUG)printf("Error on Function Body\n");
																										yacc_errors++;
																										$$ = NULL;
																									}
				;

ParameterList: 	ParameterDeclaration COMMA_ParameterDeclaration										{
																										if(DEBUG)printf("ParameterList\n");
																										$$ = insert_node(NODE_ParamList);
																										insert_child($$, $1, 0);
																										insert_brother($1, $2);


																									}
				;

ParameterDeclaration: 	TypeSpec Asterisk															{
																										if(DEBUG)printf("ParameterDeclaration[1]\n");
																										$$ = insert_node(NODE_ParamDeclaration);
																										insert_child($$, $1, 0);
																										insert_brother($1, $2);

																									}
						| TypeSpec Asterisk ID 														{
																										if(DEBUG)printf("ParameterDeclaration[2]\n");
																										$$ = insert_node(NODE_ParamDeclaration);
																										insert_child($$, $1, 0);
																										insert_brother($1, $2);
																										nodeAux = insert_term_node(NODE_Id, $3);
																										insert_brother($1, nodeAux);

																									}
						;


COMMA_ParameterDeclaration: 	COMMA ParameterDeclaration COMMA_ParameterDeclaration				{
																										if(DEBUG)printf("COMMA_ParameterDeclaration\n");
																										$$ = $2;
																										insert_brother($2, $3);
																									}
								| Empty																{
																										$$ = NULL;
																									}
								;



Declaration: TypeSpec Declarator COMMA_Declarator SEMI												{
																										if(DEBUG)printf("Declaration\n");

																										$$ = $2;
																										/*
																										if($3 != NULL){
																											insert_brother($$, $3);
																										}
																										Node * aux = $$;
																										nodeAux = $1;
																										while(aux!=NULL){
																											nodeAux.brother = aux->child;
																											nodeAux.father
																										}*/
																										insert_child($$, $1, 0);
																										if($3 != NULL){

																											insert_brother($$, $3);
																											//printf("inside: %s\n", NODE_NAME[$1->node_type]);
																											if(strcmp(NODE_NAME[$1->node_type], "Int") == 0){
																												nodeAux = insert_node(NODE_Int);
																											}
																											insert_child($3, nodeAux, 0);

																										}

																									}
			| error SEMI 																			{
																										if(DEBUG)printf("Error on Declaration\n");
																										yacc_errors++;
																										$$ = NULL;
																									}
			;

Declaration_Un: Declaration Declaration_Un															{
																										if(DEBUG)printf("Declaration_Un\n");

																										insert_brother($$, $2);
																										$$ = $1;
																									}
		| Empty																						{
																										$$ = NULL;
																									}
		;

TypeSpec: 	CHAR 																					{
																										if(DEBUG)printf("TypeSpec[CHAR]\n");
																										$$ = insert_node(NODE_Char);

																									}
			| INT 																					{
																										if(DEBUG)printf("TypeSpec[INT]\n");
																										$$ = insert_node(NODE_Int);
																									}
			| VOID 																					{
																										if(DEBUG)printf("TypeSpec[VOID]\n");
																										$$ = insert_node(NODE_Void);
																									}
			;


Declarator: 	Asterisk ID LSQ INTLIT RSQ  														{
																										if(DEBUG)printf("Declarator[1]\n");
																										$$ = insert_node(NODE_ArrayDeclaration);
																										nodeAux2 = insert_term_node(NODE_Id, $2);
																										nodeAux = insert_term_node(NODE_Intlit, $4);
																										if($1 != NULL){
																												$$->child = $1;
																												insert_brother($$->child, nodeAux2);
																												insert_brother($$->child, nodeAux);
																										}
																										else{
																											insert_child($$, nodeAux2, 0);
																											insert_brother(nodeAux2, nodeAux);
																										}



																										//insert_child($$, nodeAux, 0);
																									}
				| Asterisk ID																		{
																										if(DEBUG)printf("Declarator[2]\n");
																										$$ = insert_node(NODE_Declaration);
																										nodeAux = insert_term_node(NODE_Id, $2);
																										if($1 != NULL){
																											$$->child = $1;
																											insert_brother($$->child, nodeAux);
																										}
																										else{
																											insert_child($$, nodeAux, 0);
																										}





																									}
				;

COMMA_Declarator: 	COMMA Declarator COMMA_Declarator												{
																										if(DEBUG)printf("COMMA_Declarator\n");
																										$$ = $2;
																										insert_brother($2, $3);
																									}
					|  Empty																		{
																										$$ = NULL;
																									}
					;

Statement: 	error SEMI 																				{
																										if(DEBUG)printf("Statement Error\n");
																										yacc_errors++;
																										$$ = NULL;
																									}
			| Statement_List																		{
																										if(DEBUG)printf("Statement\n");
																										$$ = $1;
																									}
			;

Statement_List: 	 Expression_Un SEMI																{
																										if(DEBUG)printf("Expression_Un SEMI\n");
																										$$ = $1;
																									}
					| LBRACE St RBRACE															{
																										if(DEBUG)printf("LBRACE StRep RBRACE\n");
																										$$ = $2;
																									}
					| LBRACE Statement RBRACE																{
																										if(DEBUG)printf("LBRACE St RBRACE\n");
																										$$ = $2;
																									}

					| LBRACE RBRACE																	{
																										if(DEBUG)printf("LBRACE RBRACE\n");
																										$$ = NULL;
																									}
					| LBRACE error RBRACE															{
																										if(DEBUG)printf("LBRACE error RBRACE\n");
																										yacc_errors++;
																										$$ = NULL;
																									}
					| IF LPAR Expr RPAR Statement   %prec "then"									{
																										if(DEBUG)printf("IF LPAR Expr RPAR Statement");
																										$$ = insert_node(NODE_If);
																										insert_child($$, $3, 0);
																										if($5 != NULL){
																												insert_brother($3, $5);
																										}
																										else{
																											nodeAux = insert_node(NODE_NULL);
																											insert_brother($3, nodeAux);
																										}
																										nodeAux = insert_node(NODE_NULL);
																										insert_brother($3, nodeAux);

																									}
					| IF LPAR Expr RPAR Statement ELSE Statement 									{
																										if(DEBUG)printf("IF LPAR Expr RPAR Statement ELSE Statement \n");
																										$$ = insert_node(NODE_If);
																										insert_child($$, $3, 0);
																										if($5 != NULL){
																												insert_brother($3, $5);
																										}
																										else{
																											nodeAux = insert_node(NODE_NULL);
																											insert_brother($3, nodeAux);
																										}
																										if($7 != NULL){
																												insert_brother($3, $7);
																										}
																										else{
																											nodeAux = insert_node(NODE_NULL);
																											insert_brother($3, nodeAux);
																										}


																									}
					| FOR LPAR Expression_Un SEMI Expression_Un SEMI Expression_Un RPAR Statement	{
																										if(DEBUG)printf("For Cycle\n");
																										$$ = insert_node(NODE_For);

																										if($3 != NULL){
																												insert_child($$, $3, 0);
																										}
																										else{
																											nodeAux = insert_node(NODE_NULL);
																											insert_child($$, nodeAux, 0);
																										}
																										if($5 != NULL){
																												insert_child($$->child, $5, 0);
																										}
																										else{
																											nodeAux = insert_node(NODE_NULL);
																											insert_child($$->child, nodeAux, 0);
																										}
																										if($7 != NULL){
																												insert_child($$->child, $7, 0);
																										}
																										else{
																											nodeAux = insert_node(NODE_NULL);
																											insert_child($$->child, nodeAux, 0);
																										}
																										if($9 != NULL){
																												insert_brother($$->child, $9);
																										}
																										else{
																											nodeAux = insert_node(NODE_NULL);
																											insert_child($$->child, nodeAux, 0);
																										}







																									}
					| RETURN Expression_Un SEMI 													{
																										if(DEBUG)printf("RETURN Expression_Un SEMI \n");

																										$$ = insert_node(NODE_Return);

																										if($2 != NULL)
																										{
																											insert_child($$, $2, 0);
																										}
																										else{
																											nodeAux = insert_node(NODE_NULL);
																											insert_child($$, nodeAux, 0);
																										}

																									}
					;

St:  Statement Statement Statement_Un 																			{
																										if(DEBUG)printf("St\n");
																										if($1 != NULL && $2 != NULL){
																											$$ = insert_node(NODE_StatList);
																											insert_child($$, $1, 0);
																											insert_brother($1, $2);
																											insert_brother($1, $3);
																										}
																										else{
																											if($1 != NULL && $2 == NULL){
																												$$ = $1;
																												insert_brother($$, $3);
																											}
																											else if($2 != NULL && $1 == NULL){
																												$$ = $2;
																												insert_brother($$, $3);
																											}
																											else if($2 == NULL && $1 == NULL){
																												$$ = $3;
																											}
																										}


																									}
	;


State_List_UN: 	Empty																				{
																										$$ = NULL;
																									}
				| Statement_List State_List_UN														{
																										if(DEBUG)printf("State_List_UN\n");
																										if($1 != NULL){
																											$$ = $1;
																											insert_brother($$,$2);
																										}
																										else{
																											$$ = $2;
																										}

																									}
				;

Statement_Un: 	Empty																				{
																										$$ = NULL;
																									}
			| Statement Statement_Un																{
																										if(DEBUG)printf("Statement_Un\n");
																										if($1 != NULL){
																											$$ = $1;
																											insert_brother($$,$2);
																										}
																										else{
																											$$ = $2;
																										}

																									}
			;

Expr: 	Expressions_List 																			{
																										$$ = $1;
																									}
		| Expr COMMA Expressions_List																{
																										if(DEBUG)printf("Expr\n");
																										$$ = insert_node(NODE_Comma);

																										insert_child($$, $1, 0);
																										insert_brother($1, $3);
																									}
		;


Expressions_List:  	Expressions_List ASSIGN Expressions_List										{
																										if(DEBUG)printf("Expressions_List ASSIGN Expressions_List\n");
																										$$ = insert_node(NODE_Store);
																										insert_child($$, $1, 0);
																										insert_brother($1, $3);

																									}
					| Expressions_List AND Expressions_List											{
																										if(DEBUG)printf("Expressions_List AND Expressions_List\n");
																										$$ = insert_node(NODE_And);
																										insert_child($$, $1, 0);
																										insert_brother($1, $3);

																									}
					| Expressions_List OR Expressions_List											{
																										if(DEBUG)printf("Expressions_List OR Expressions_List\n");
																										$$ = insert_node(NODE_Or);
																										insert_child($$, $1, 0);
																										insert_brother($1, $3);

																									}
					| Expressions_List EQ Expressions_List											{
																										if(DEBUG)printf("Expressions_List EQ Expressions_List\n");
																										$$ = insert_node(NODE_Eq);
																										insert_child($$, $1, 0);
																										insert_brother($1, $3);

																									}
					| Expressions_List NE Expressions_List											{
																										if(DEBUG)printf("Expressions_List NE Expressions_List\n");
																										$$ = insert_node(NODE_Ne);
																										insert_child($$, $1, 0);
																										insert_brother($1, $3);
																									}
					| Expressions_List LT Expressions_List											{
																										if(DEBUG)printf("Expressions_List LT Expressions_List\n");
																										$$ = insert_node(NODE_Lt);
																										insert_child($$, $1, 0);
																										insert_brother($1, $3);
																									}
					| Expressions_List GT Expressions_List											{
																										if(DEBUG)printf("Expressions_List GT Expressions_List\n");
																										$$ = insert_node(NODE_Gt);
																										insert_child($$, $1, 0);
																										insert_brother($1, $3);
																									}
					| Expressions_List LE Expressions_List											{
																										if(DEBUG)printf("Expressions_List LE Expressions_List\n");
																										$$ = insert_node(NODE_Le);
																										insert_child($$, $1, 0);
																										insert_brother($1, $3);
																									}
					| Expressions_List GE Expressions_List											{
																										if(DEBUG)printf("Expressions_List GE Expressions_List\n");
																										$$ = insert_node(NODE_Ge);
																										insert_child($$, $1, 0);
																										insert_brother($1, $3);
																									}
					| Expressions_List PLUS Expressions_List										{
																										if(DEBUG)printf("Expressions_List PLUS Expressions_List\n");
																										$$ = insert_node(NODE_Add);
																										insert_child($$, $1, 0);
																										insert_brother($1, $3);
																									}
					| Expressions_List MINUS Expressions_List										{
																										if(DEBUG)printf("Expressions_List MINUS Expressions_List\n");
																										$$ = insert_node(NODE_Sub);
																										insert_child($$, $1, 0);
																										insert_brother($1, $3);
																									}
					| Expressions_List AST Expressions_List											{
																										if(DEBUG)printf("Expressions_List AST Expressions_List\n");
																										$$ = insert_node(NODE_Mul);
																										insert_child($$, $1, 0);
																										insert_brother($1, $3);
																									}
					| Expressions_List DIV Expressions_List											{
																										if(DEBUG)printf("Expressions_List DIV Expressions_List\n");
																										$$ = insert_node(NODE_Div);
																										insert_child($$, $1, 0);
																										insert_brother($1, $3);
																									}
					| Expressions_List MOD Expressions_List											{
																										if(DEBUG)printf("Expressions_List MOD Expressions_List\n");
																										$$ = insert_node(NODE_Mod);
																										insert_child($$, $1, 0);
																										insert_brother($1, $3);
																									}
					| AMP Expressions_List															{
																										if(DEBUG)printf("AMP Expressions_List\n");
																										$$ = insert_node(NODE_Addr);
																										insert_child($$, $2, 0);
																									}
					| AST Expressions_List															{
																										if(DEBUG)printf("AST Expressions_List\n");
																										$$ = insert_node(NODE_Deref);
																										insert_child($$, $2, 0);
																									}
					| PLUS Expressions_List															{
																										if(DEBUG)printf("PLUS Expressions_List\n");
																										$$ = insert_node(NODE_Plus);
																										insert_child($$, $2, 0);
																									}
					| MINUS Expressions_List														{
																										if(DEBUG)printf("MINUS Expressions_List\n");
																										$$ = insert_node(NODE_Minus);
																										insert_child($$, $2, 0);
																									}
					| NOT Expressions_List															{
																										if(DEBUG)printf("NOT Expressions_List\n");
																										$$ = insert_node(NODE_Not);
																										insert_child($$, $2, 0);
																									}
					| ID LPAR ExprCOMMA_Expr RPAR													{
																										if(DEBUG)printf("ID LPAR ExprCOMMA_Expr RPAR\n");
																										$$ = insert_node(NODE_Call);
																										nodeAux = insert_term_node(NODE_Id, $1);
																										insert_child($$, nodeAux, 0);
																										insert_brother(nodeAux, $3);
																										//$$ = insert_node();
																									}
					| LPAR Expr RPAR																{
																										if(DEBUG)printf("LPAR Expr RPAR\n");
																										//$$ = insert_node(NODE_Call);
																										//insert_child($$, $1);
																										$$ = $2;
																									}
					| ID																			{
																										if(DEBUG)printf("ID\n");
																										$$ = insert_term_node(NODE_Id, $1);
																									}
					| INTLIT																		{
																										if(DEBUG)printf("INTLIT\n");
																										$$ = insert_term_node(NODE_Intlit, $1);
																									}
					| CHRLIT																		{
																										if(DEBUG)printf("CHRLIT\n");
																										$$ = insert_term_node(NODE_Chrlit, $1);
																									}
					| STRLIT																		{
																										if(DEBUG)printf("STRLIT\n");
																										$$ = insert_term_node(NODE_Strlit, $1);
																									}
					| ID LPAR error RPAR 															{
																										if(DEBUG)printf("ID LPAR error RPAR \n");
																										yacc_errors++;
																										$$ = NULL;
																									}
					| LPAR error RPAR 																{
																										if(DEBUG)printf("LPAR error RPAR \n");
																										yacc_errors++;
																										$$ = NULL;
																									}
					| Expressions_List LSQ Expr RSQ													{
																										if(DEBUG)printf("Expressions_List LSQ Expr RSQ	\n");
																										$$ = insert_node(NODE_Deref);
																										nodeAux = insert_node(NODE_Add);

																										insert_child($$, nodeAux, 0);
																										insert_child(nodeAux, $1, 0);
																										insert_brother($1, $3);
																									}

					;



ExprCOMMA_Expr: Expressions_List COMMA_Expr															{
																										if(DEBUG)printf("Expressions_List COMMA_Expr\n");
																										$$ = $1;
																										insert_brother($$, $2);
																									}
				| Empty																				{
																										$$ = NULL;
																									}
				;

COMMA_Expr: Empty 																					{
																										$$ = NULL;
																									}
			| COMMA Expressions_List COMMA_Expr 													{
																										if(DEBUG)printf("COMMA_Expr\n");
																										$$ = $2;
																										insert_brother($$, $3);


																									}
			;


Expression_Un: 	Expr																				{
																										if(DEBUG)printf("Expression_Un\n");
																										$$ = $1;
																									}
		| Empty																						{

																										$$ = NULL;

																									}
		;



Asterisk: 	 Asterisk	AST																		{
																										if(DEBUG)printf("Asterisk\n");
																										$$ = insert_node(NODE_Pointer);
																										insert_brother($$, $1);

																									}
			| Empty																					{
																										$$ = NULL;
																									}
			;

Empty: 																								{
																										if(DEBUG)printf("Empty\n");
																									}
	;

%%

void yyerror (char *s) {
	printf ("Line %d, col %d: %s: %s\n",yylineno, (int)(columnNumber - strlen(yytext)+1), s, yytext);
}
