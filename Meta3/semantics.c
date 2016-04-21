#include <string.h>
#include <stdio.h>
#include <string.h>

#include "semantics.h"
#include "printer.h"

extern Table * symbol_table;
Table * current_trable;

void check_node(Node* tree);
char * get_name(Node* tree);
char * get_type(Node* tree);
#define DEBUG 1

int build_table(Node* tree)
{
	if(DEBUG){
		printf("build_table\n");
	}
	Node* temp = tree;
	while(temp != NULL)
	{
		check_node(temp);
		if(temp->brother != NULL)
		{
			temp = temp->brother;
		}
		
	}
	
}


void check_node(Node* tree)
{
	Symbol *symbol;
	char name[100], type[100];
	int param;
	if(strcmp("ArrayDeclaration", NODE_NAME[tree->node_type]) == 0)
	{
		strcpy(name, get_name(tree));
		strcpy(type, get_type(tree));
		param = 0;
		symbol = create_symbol(name, type, param);
		insert_symbol(symbol_table, symbol);
	}
	else if(strcmp("Declaration", NODE_NAME[tree->node_type]) == 0)
	{
		strcpy(name, get_name(tree));
		strcpy(type, get_type(tree));
		param = 0;
		symbol = create_symbol(name, type, param);
		insert_symbol(symbol_table, symbol);
	}
	else if(strcmp("FunctionDeclaration", NODE_NAME[tree->node_type]))
	{
		insert_function_declaration(tree);
	}
	else if(strcmp("TypeSpec", NODE_NAME[tree->node_type]) == 0)
	{

	}
	else if(strcmp("FuncDefinition", NODE_NAME[tree->node_type]) == 0)
	{

	}


}

char * get_name(Node* tree)
{
	Node* temp = tree->child;
	while(temp != NULL){
		if(strcmp(NODE_NAME[tree->child->node_type], "Id") == 0){
			return tree->child->value;
		}
		if(temp->brother != NULL)
		{
			temp = temp->brother;
		}
	}
	return NULL;
}
char * get_type(Node* tree)
{
	Node* temp = tree->child;
	char value[10];
	char type[10];
	char* finalType;
	while(temp != NULL){
		if(strcmp(NODE_NAME[tree->child->node_type], "IntLit") == 0)
		{
			strcpy(value, tree->child->value);
		}
		else if(strcmp(NODE_NAME[tree->child->node_type], "Char") == 0)
		{
			strcpy(type, NODE_NAME[tree->child->node_type]);
		}
		else if(strcmp(NODE_NAME[tree->child->node_type], "Int") == 0)
		{
			strcpy(type, NODE_NAME[tree->child->node_type]);
		}
		if(temp->brother != NULL)
		{
			temp = temp->brother;
		}
	}
	sprintf(finalType, "%s[%s]", type, value);
	return finalType;
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