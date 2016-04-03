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

//Un -> 0 or 1
//Rep -> 0 or more

Start:  FunctionDefinition  Restart                                                					{
																										if(DEBUG)printf("Start1\n");
																										$$ = insert_node(NODE_Program);
																										tree=$$;
																										insert_child($$, $1, 0);
																										$$ = $1;
																										insert_brother($$, $2);


																									}
        | FunctionDeclaration Restart                                              					{
        																								if(DEBUG)printf("Start2\n");
        																								$$ = insert_node(NODE_Program);
																										tree=$$;
        																								insert_child($$, $1, 0);
																										$$ = $1;
																										insert_brother($$, $2);


        																							}
        | Declaration Restart                                                     					{
        																								if(DEBUG)printf("Start3\n");
        																								$$ = insert_node(NODE_Program);
																										tree=$$;
																										insert_child($$, $1, 0);
																										$$ = $1;
																										insert_brother($$, $2);


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
																										insert_child($$, $3, 0);
																										insert_child($$, $2, 0);
																										insert_child($$, $1, 0);
																										
																										


																									}
					;

FunctionDeclaration: 	TypeSpec FunctionDeclarator SEMI											{
																										if(DEBUG)printf("FunctionDeclaration\n");
																										$$ = insert_node(NODE_FuncDeclaration);

																										insert_child($$, $1, 0);
																										insert_child($$, $2, 0);

																									}
						;


FunctionDeclarator: Asterisk ID LPAR ParameterList RPAR												{
																										if(DEBUG)printf("FunctionDeclarator\n");

																										$$ = insert_term_node(NODE_Id, $2);
																										insert_brother($$, $1);
																										insert_brother($$, $4);

																									}
					;


FunctionBody: 	LBRACE Declaration_Un State_List_UN RBRACE		 									{
																										if(DEBUG)printf("FunctionBody\n");
																										$$ = insert_node(NODE_FuncBody);
																										insert_child($$, $2, 0);
																										insert_child($$, $3, 0);

																									}
				| LBRACE error RBRACE 																{
																										if(DEBUG)printf("Error on Function Body\n");
																										yacc_errors++;
																									}
				;

ParameterList: 	ParameterDeclaration COMMA_ParameterDeclaration										{
																										if(DEBUG)printf("ParameterList\n");

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

																									}
						;


COMMA_ParameterDeclaration: 	COMMA ParameterDeclaration COMMA_ParameterDeclaration				{
																										if(DEBUG)printf("COMMA_ParameterDeclaration\n");
																									}
								| Empty
								;



Declaration: TypeSpec Declarator COMMA_Declarator SEMI												{
																										if(DEBUG)printf("Declaration\n");

																										$$ = $2;


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
																									}
			;

Declaration_Un: Declaration Declaration_Un															{
																										if(DEBUG)printf("Declaration_Un\n");
																										$$ = $1;
																										insert_brother($$, $2);
																									}
		| Empty
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

																										nodeAux = insert_term_node(NODE_Intlit, $4);
																										insert_child($$, nodeAux, 0);

																										nodeAux = insert_term_node(NODE_Id, $2);
																										insert_child($$, nodeAux, 0);
																									}
				| Asterisk ID																		{
																										if(DEBUG)printf("Declarator[2]\n");
																										$$ = insert_node(NODE_Declaration);
																										nodeAux = insert_term_node(NODE_Id, $2);

																										insert_child($$, nodeAux, 0);
																										insert_brother(nodeAux, $1);




																									}
				;

COMMA_Declarator: 	COMMA Declarator COMMA_Declarator												{
																										if(DEBUG)printf("COMMA_Declarator\n");
																										$$ = $2;
																										insert_brother($2, $3);
																									}
					|  Empty
					;

Statement: 	error SEMI 																				{
																										if(DEBUG)printf("Statement Error\n");
																										yacc_errors++;
																									}
			| Statement_List																		{
																										if(DEBUG)printf("Statement\n");
																										$$ = $1;
																									}
			;

Statement_List: 	 Expression_Un SEMI																{
																										if(DEBUG)printf("Expression_Un SEMI\n");
																									}
					| LBRACE St RBRACE																{
																										if(DEBUG)printf("LBRACE St RBRACE\n");
																									}
					| LBRACE RBRACE																	{
																										if(DEBUG)printf("LBRACE RBRACE\n");
																									}
					| LBRACE error RBRACE															{
																										if(DEBUG)printf("LBRACE error RBRACE\n");
																										yacc_errors++;
																									}
					| IF LPAR Expr RPAR Statement   %prec "then"									{
																										if(DEBUG)printf("IF LPAR Expr RPAR Statement");
																									}
					| IF LPAR Expr RPAR Statement ELSE Statement 									{
																										if(DEBUG)printf("IF LPAR Expr RPAR Statement ELSE Statement \n");
																									}
					| FOR LPAR Expression_Un SEMI Expression_Un SEMI Expression_Un RPAR Statement	{
																										if(DEBUG)printf("For Cycle\n");
																									}
					| RETURN Expression_Un SEMI 													{
																										if(DEBUG)printf("RETURN Expression_Un SEMI \n");
																									}
					;

St: Statement Statement_Un																			{
																										if(DEBUG)printf("St\n");
																									}
	;

State_List_UN: Empty | Statement_List State_List_UN													{
																										if(DEBUG)printf("State_List_UN\n");
																									}
				;

Statement_Un: 	Empty
			| Statement Statement_Un																{
																										if(DEBUG)printf("Statement_Un\n");
																									}
			;

Expr: 	Expressions_List 																			{
																										$$ = $1;
																									}
		| Expr COMMA Expressions_List																{
																										if(DEBUG)printf("Expr\n");
																										insert_child($$, $1, 0);
																										insert_brother($$, $3);
																									}
		;


Expressions_List:  	Expressions_List ASSIGN Expressions_List										{
																										if(DEBUG)printf("Expressions_List ASSIGN Expressions_List\n");
																										$$ = insert_node(NODE_Store);
																										/*insert_brother($$, $1);
																										insert_brother($$, $3);*/
																									}
					| Expressions_List AND Expressions_List											{
																										if(DEBUG)printf("Expressions_List AND Expressions_List\n");
																										$$ = insert_node(NODE_And);
																										/*insert_brother($$, $1);
																										insert_brother($$, $3);*/
																										
																									}
					| Expressions_List OR Expressions_List											{
																										if(DEBUG)printf("Expressions_List OR Expressions_List\n");
																										$$ = insert_node(NODE_Or);
																										/*insert_brother($$, $1);
																										insert_brother($$, $3);*/
																									
																									}
					| Expressions_List EQ Expressions_List											{
																										if(DEBUG)printf("Expressions_List EQ Expressions_List\n");
																										$$ = insert_node(NODE_Eq);
																										/*insert_brother($$, $1);
																										insert_brother($$, $3);*/
																										
																									}
					| Expressions_List NE Expressions_List											{
																										if(DEBUG)printf("Expressions_List NE Expressions_List\n");
																										$$ = insert_node(NODE_Ne);
																										/*insert_brother($$, $1);
																										insert_brother($$, $3);*/
																									}
					| Expressions_List LT Expressions_List											{
																										if(DEBUG)printf("Expressions_List LT Expressions_List\n");
																										$$ = insert_node(NODE_Lt);
																										/*insert_brother($$, $1);
																										insert_brother($$, $3);*/
																									}
					| Expressions_List GT Expressions_List											{
																										if(DEBUG)printf("Expressions_List GT Expressions_List\n");
																										$$ = insert_node(NODE_Gt);
																										/*insert_brother($$, $1);
																										insert_brother($$, $3);*/
																									}
					| Expressions_List LE Expressions_List											{
																										if(DEBUG)printf("Expressions_List LE Expressions_List\n");
																										$$ = insert_node(NODE_Le);
																										/*insert_brother($$, $1);
																										insert_brother($$, $3);*/
																									}
					| Expressions_List GE Expressions_List											{
																										if(DEBUG)printf("Expressions_List GE Expressions_List\n");
																										$$ = insert_node(NODE_Ge);
																										/*insert_brother($$, $1);
																										insert_brother($$, $3);*/
																									}
					| Expressions_List PLUS Expressions_List										{
																										if(DEBUG)printf("Expressions_List PLUS Expressions_List\n");
																										$$ = insert_node(NODE_Add);
																										/*insert_brother($$, $1);
																										insert_brother($$, $3);*/
																									}
					| Expressions_List MINUS Expressions_List										{
																										if(DEBUG)printf("Expressions_List MINUS Expressions_List\n");
																										$$ = insert_node(NODE_Sub);
																										/*insert_brother($$, $1);
																										insert_brother($$, $3);*/
																									}
					| Expressions_List AST Expressions_List											{
																										if(DEBUG)printf("Expressions_List AST Expressions_List\n");
																										$$ = insert_node(NODE_Mul);
																										/*insert_brother($$, $1);
																										insert_brother($$, $3);*/
																									}
					| Expressions_List DIV Expressions_List											{
																										if(DEBUG)printf("Expressions_List DIV Expressions_List\n");
																										$$ = insert_node(NODE_Div);
																										/*insert_brother($$, $1);
																										insert_brother($$, $3);*/
																									}
					| Expressions_List MOD Expressions_List											{
																										if(DEBUG)printf("Expressions_List MOD Expressions_List\n");
																										$$ = insert_node(NODE_Mod);
																										/*insert_brother($$, $1);
																										insert_brother($$, $3);*/
																									}
					| AMP Expressions_List															{
																										if(DEBUG)printf("AMP Expressions_List\n");
																										$$ = insert_node(NODE_Addr);
																										//insert_brother($$, $2);
																									}
					| AST Expressions_List															{
																										if(DEBUG)printf("AST Expressions_List\n");
																										$$ = insert_node(NODE_Deref);
																										//insert_brother($$, $2);
																									}
					| PLUS Expressions_List															{
																										if(DEBUG)printf("PLUS Expressions_List\n");
																										$$ = insert_node(NODE_Plus);
																										//insert_brother($$, $2);
																									}
					| MINUS Expressions_List														{
																										if(DEBUG)printf("MINUS Expressions_List\n");
																										$$ = insert_node(NODE_Minus);
																										//insert_brother($$, $2);
																									}
					| NOT Expressions_List															{
																										if(DEBUG)printf("NOT Expressions_List\n");
																										$$ = insert_node(NODE_Not);
																										//insert_brother($$, $2);
																									}
					| ID LPAR ExprCOMMA_Expr RPAR													{
																										if(DEBUG)printf("ID LPAR ExprCOMMA_Expr RPAR\n");
																									}
					| LPAR Expr RPAR																{
																										if(DEBUG)printf("LPAR Expr RPAR\n");
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
																									}
					| LPAR error RPAR 																{
																										if(DEBUG)printf("LPAR error RPAR \n");
																										yacc_errors++;
																									}
					| Expressions_List LSQ Expr RSQ													{
																										if(DEBUG)printf("Expressions_List LSQ Expr RSQ	\n");
																									}
					;



ExprCOMMA_Expr: Expressions_List COMMA_Expr															{
																										if(DEBUG)printf("Expressions_List COMMA_Expr\n");
																									}
				| Empty
				;

COMMA_Expr: Empty | COMMA_Expr COMMA Expressions_List												{
																										if(DEBUG)printf("COMMA_Expr\n");
																									}
			;


Expression_Un: 	Expr																				{
																										if(DEBUG)printf("Expression_Un\n");
																										$$ = $1;
																									}
		| Empty
		;



Asterisk: 	AST Asterisk																			{
																										if(DEBUG)printf("Asterisk\n");
																										$$ = insert_node(NODE_Pointer);
																										insert_brother($$, $2);

																									}
			| Empty
			;

Empty: 																								{
																										if(DEBUG)printf("Empty\n");
																										$$ = NULL;
																									}
	;

%%

void yyerror (char *s) {
	printf ("Line %d, col %d: %s: %s\n",yylineno, (int)(columnNumber - strlen(yytext)+1), s, yytext);
}
