#include <string.h>
#include <stdio.h>
#include <string.h>

#include "semantics.h"
#include "symbolTable.h"

extern Table * symbol_table;
Table * current_trable;

#define DEBUG 1

int build_table(Node* tree)
{
	Node* temp = tree->child;
	while(temp != NULL)
	{
		check_node(temp);
	}
	
}
/*
funcDeclaration
TypeSpec
declaration
*/

void check_node(Node* tree)
{
	Symbol *symbol;
	char name[100], type[100];
	int param;
	if(strcmp("ArrayDeclaration"), NODE_NAME[tree->node_type])
	{
		name = get_name(tree);
		type = get_type(tree);
		param = 0;
		insert_symbol(symbol_table, symbol);
	}
	else if(strcmp("FunctionDeclaration", NODE_NAME[tree->node_type]))
	{
		insert_function_declaration(tree);
	}
}

char * get_name(Node* tree)
{
	while(tree->child != NULL){
		if(strcmp(NODE_NAME[tree->child], "Id") == 0){
			return tree->child->value;
		}
	}
}
char * get_type(Node* tree)
{
	char aux[10];
	while(tree->child != NULL){
		if(strcmp(NODE_NAME[tree->child], "IntLit") == 0){
			aux = tree->child->value;
		}
		else if()
	}
}


void insert_function_declaration(Node * tree)
{
	if(DEBUG)
	{
		printf("[insert_function_declaration] Node_value: %s \n", tree->value);
	}

	//inserir o symbolo na tabela global

	//criar uma tabela nova
	//Table * aux;

	//inserir essa tabela `a tabela de simbolos
	//aux = insert_table(1, tree->value);

	//inserir o simbolo de return

	//inserir os simbolos da lista de parametros

	/*
	
	
	*/

}