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