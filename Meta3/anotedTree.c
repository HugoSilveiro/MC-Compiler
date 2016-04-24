#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "anotedTree.h"

void get_anoted_Tree(Node* tree)
{
	Node* temp = tree->child;

	while(temp!=NULL)
	{
		if(strcmp("FuncDefinition", NODE_NAME[tree->node_type]) == 0)
		{
			printf("FuncDefinition\n");
			insert_function_definition(tree);
		}
	}
}

void insert_function_definition(tree)
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
		current_table = aux;
		insert_function_funcBody(node);
		current_table = NULL;

	}
	
}

void insert_function_funcBody(Node * node)
{
	if(DEBUG){
		printf("insert_function_funcBody\n");
	}
	Node * temp = node->child;
	while(temp != NULL){

		if(strcmp(NODE_NAME[temp->node_type], "FuncBody") == 0)
		{
			
			get_operators(temp);
		}
		temp = temp->brother;
	}
}

void get_operators(Node * node)
{
	Node * temp = node->child;

	while(temp!= NULL)
	{
		if(strcmp(NODE_NAME[temp->node_type], "EQ") == 0)
		{
			//TODO	
		}

	}

}