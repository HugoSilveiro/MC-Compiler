#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "anotedTree.h"
#include "printer.h"

#define DEBUG 1

extern Table * symbol_table;
Table * current_table2 = NULL;

void get_anoted_Tree(Node* tree)
{
	if (DEBUG) printf("[get_anoted_tree]\n");
	Node* temp = tree->child;
	while(temp!=NULL)
	{
		if (DEBUG) printf("%s\n", NODE_NAME[temp->node_type]);

		
		if(strcmp("FuncDefinition", NODE_NAME[temp->node_type]) == 0)
		{
			printf("FuncDefinition\n");
			insert_funct_definition(temp);
		}
		
		temp= temp->brother;
	}
}

void insert_funct_definition(Node * node)
{

	if(DEBUG)
	{
		printf("[insert_function_definition]\n");	
	}	

	//function name:
	char * func_name;
	func_name = strdup(get_function_name(node));

	Table *aux;
	aux = search_table(func_name);

	if(aux!=NULL)
	{
		aux->defined = 1;
		current_table2 = aux;
		insert_function_funcBody(node);
		current_table2 = NULL;

	}
	
}

void insert_funcBody(Node * node)
{
	if(DEBUG){
		printf("insert_function_funcBody\n");
	}
	Node * temp = node->child;
	while(temp != NULL){

		if(strcmp(NODE_NAME[temp->node_type], "FuncBody") == 0)
		{
			
			//get_operators(temp);
		}
		temp = temp->brother;
	}
}

void get_inside_funcBody(Node * node)
{
	Node * temp = node->child;

	while(temp!= NULL)
	{
		/*if(strcmp(NODE_NAME[temp->node_type], "EQ") == 0)
		{
			//TODO	
			strcpy(temp->type, "Int"); 
			get_inside_operator(temp);
			

		}*/
		if(strcmp("Id", NODE_NAME[temp->node_type]) == 0)
		{
			printf("Found id\n");
			get_inside_id(temp);
		}
		temp = temp->brother;
	}

}


void get_inside_operator(Node * node)
{
	Node * temp = node->child;
	while(temp != NULL)
	{
		if(strcmp(NODE_NAME[temp->node_type], "Id") == 0){
			get_inside_id(temp);
		}
	}
}

void get_inside_id(Node * node)
{

	printf("-------------NODE_VALUE: %s\n", node->value);
	Symbol * symbol = search_symbol(node->value, current_table2);

	if(symbol!=NULL)
	{
		node->type = symbol->type;

	}
}