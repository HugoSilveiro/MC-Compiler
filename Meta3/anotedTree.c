#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "anotedTree.h"
#include "printer.h"

#define DEBUG 0

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
			if(DEBUG)printf("FuncDefinition\n");
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
		current_table2 = aux;
		insert_funcBody(node);
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
			
			check_inside_funcBody(temp);
		}
		temp = temp->brother;
	}
}

void check_inside_funcBody(Node * node)
{
	if(DEBUG){
		printf("check_inside_funcBody\n");
	}
	Node * temp = node->child;
	while(temp != NULL){
		printf("%s\n", NODE_NAME[temp->node_type]);
		if(strcmp(NODE_NAME[temp->node_type], "If") == 0)
		{
			
			get_inside_funcBody(temp);
		}
		else if(strcmp(NODE_NAME[temp->node_type], "For") == 0)
		{
			
			get_inside_funcBody(temp);
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Return") == 0){
			get_inside_operator(temp);
		}
		temp = temp->brother;
	}	
}

void get_inside_funcBody(Node * node)
{
	Node * temp = node->child;

	while(temp!= NULL)
	{
		if(DEBUG)printf("[get_inside_funcBody] %s\n",NODE_NAME[temp->node_type] );
		if(strcmp(NODE_NAME[temp->node_type], "Eq") == 0)
		{
			
			temp->type = "int"; 
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Ne") == 0)
		{
			temp->type = "int"; 
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Lt") == 0)
		{
			temp->type = "int"; 
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Gt") == 0)
		{
			temp->type = "int"; 
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Le") == 0)
		{
			temp->type = "int"; 
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Ge") == 0)
		{
			temp->type = "int"; 
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "And") == 0)
		{	
			temp->type = "int"; 
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Or") == 0)
		{	
			temp->type = "int"; 
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Add") == 0)
		{	
			temp->type =  "int";
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Sub") == 0)
		{
			temp->type = "int";
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Mul") == 0)
		{
			temp->type = "int"; 
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Div") == 0)
		{
			temp->type = "int"; 
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Mod") == 0)
		{
			temp->type = "int"; 
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Not") == 0)
		{
			temp->type = "int"; 
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Minus") == 0)
		{
			temp->type = "int"; 
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Plus") == 0)
		{
			temp->type = "int"; 
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Addr") == 0)
		{
			temp->type = "int"; 
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Deref") == 0)
		{	
			temp->type = "int"; 
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Store") == 0)
		{
			temp->type = "int"; 
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Comma") == 0)
		{
			temp->type = "int"; 
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Call") == 0)
		{
			temp->type = "int"; 
			get_inside_operator(temp);

		}


		temp = temp->brother;
	}
}


void get_inside_operator(Node * node)
{
	Node * temp = node->child;
	while(temp != NULL)
	{
		printf("%s\n", NODE_NAME[temp->node_type]);
		if(strcmp(NODE_NAME[temp->node_type], "Id") == 0){
			get_inside_id(temp);
		}
		else if(strcmp(NODE_NAME[temp->node_type], "IntLit") == 0){
			temp->type = "int";
		}
		else if(strcmp(NODE_NAME[temp->node_type], "ChrLit") == 0){
			temp->type = "char";
		}
		else if(strcmp(NODE_NAME[temp->node_type], "StrLit") == 0){
			temp->type = "string";
		}	

		temp = temp->brother;
	}
}

void get_inside_id(Node * node)
{

	Symbol * symbol = search_symbol(node->value, current_table2);

	if(symbol!=NULL)
	{
		node->type = symbol->type;

	}
}

void get_inside_strlit(Node * node)
{

	if(DEBUG)printf("node->value: %s size: %lu\n", node->value, sizeof(node->value));
	
}
	


void get_inside_chrlit(Node * node)
{
	if(DEBUG)node->type = "char";
}


