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
		if (DEBUG) printf("%s\n", NODE_NAME[temp->node_type]);
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
		else if(strcmp(NODE_NAME[temp->node_type], "Store") == 0){
			//Ver o tipo dos filhos
			temp->type = "int";
			get_inside_operator(temp);
			//get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Call") == 0)
		{
			//printf("call\n");
			temp->type = check_call_type(temp); 
			get_inside_funcBody(temp);

		}

		temp = temp->brother;
	}	
}

char * check_call_type(Node * node)
{
	if (DEBUG) printf("check_call_type\n");
	char * auxType;
	Node * temp = node->child;
	while(temp != NULL)
	{
		if (DEBUG) printf("%s\n", NODE_NAME[temp->node_type]);
		if(strcmp(NODE_NAME[temp->node_type], "Id") == 0){
			auxType = (char*)malloc(sizeof(get_type_Call(temp)));
			strcpy(auxType, get_type_Call(temp));
			if (DEBUG) printf("auxType: %s\n", auxType);
			return auxType;
		}
		else if(strcmp(NODE_NAME[temp->node_type], "IntLit") == 0){
			temp->type = "int";
		}
		else if(strcmp(NODE_NAME[temp->node_type], "ChrLit") == 0){
			temp->type = "char";
		}
		else if(strcmp(NODE_NAME[temp->node_type], "StrLit") == 0){
			
			get_inside_strlit(temp);
		}	

		temp = temp->brother;
	}
	return NULL;

}

char * get_type_Call(Node * node)
{	
	if (DEBUG) printf("get_type_Call\n");
	Symbol * symbol = search_symbol(node->value, current_table2);
	
	if(symbol!=NULL)
	{
		node->type = symbol->type;
		if (DEBUG) printf("get_type_call: %s\n", node->type);
		return type_call(node->type);
	}
	else
	{
		Table * table = search_table("global");
		Symbol * symbol2 = search_symbol(node->value, table);
		if(symbol2!=NULL)
		{
			
			node->type = symbol2->type;
			if (DEBUG) printf("get_type_call: %s\n", node->type);
			return type_call(node->type);	
		}	
	}
	return NULL;
}


char * type_call(char * type)
{
	int aux = strlen(type);
	char * new_aux = (char*)malloc(sizeof(type));
	int i;
	for(i = 0; i < aux; i++){
		if(type[i] != '('){
			new_aux[i] = type[i];
		}
		else if(type[i] == '('){
			if (DEBUG) printf("type_call: %s\n", new_aux);
			return new_aux;
		}
	}
	return NULL;
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
			temp->type =  get_expr_type(temp);
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
			get_inside_funcBody(temp);

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
			
			//temp->type = check_call_type(temp); 
			//get_inside_operator(temp);

			if (DEBUG) printf("call\n");
			temp->type = check_call_type(temp); 
			get_inside_funcBody(temp);


		}
		else if(strcmp(NODE_NAME[temp->node_type], "Return") == 0){
			get_inside_operator(temp);
		}	

		else{
			check_inside_funcBody(temp);
		}

		temp = temp->brother;
	}
}


char * get_expr_type(Node * node)
{
	Node * temp = node->child;
	char * aux;

	while(temp!=NULL)
	{
		if(strcmp(NODE_NAME[temp->node_type], "Id") == 0){
			aux = strdup(temp->value);
		}

		temp = temp->brother;
	}

	return aux;
}

void get_inside_operator(Node * node)
{
	if (DEBUG) printf("get_inside_operator\n");
	Node * temp = node->child;
	while(temp != NULL)
	{
		//printf("%s\n", NODE_NAME[temp->node_type]);
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
			get_inside_strlit(temp);
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Call") == 0)
		{
			
			//temp->type = check_call_type(temp); 
			//get_inside_operator(temp);

			if (DEBUG) printf("call\n");
			temp->type = check_call_type(temp); 
			get_inside_funcBody(temp);


		}
		else{
			if (DEBUG) printf("else: %s\n", NODE_NAME[temp->node_type]);
			check_inside_funcBody(temp);
		}	

		temp = temp->brother;
	}
}

void get_inside_id(Node * node)
{
	if (DEBUG) printf("[get_inside_id] node->value: %s\n", node->value);

	Symbol * symbol = search_symbol(node->value, current_table2);
	if(symbol!=NULL)
	{
		//printf("[get_inside_id] type: %s\n", symbol->type);
		node->type = symbol->type;
	}
	else
	{
		Table * table = search_table("global");
		Symbol * symbol2 = search_symbol(node->value, table);
		if(symbol2!=NULL)
		{
			//printf("[get_inside_id] type: %s\n", symbol2->type);
			node->type = symbol2->type;	
		}
		
	}
	
	

}

void get_inside_strlit(Node * node)
{
	int length = strlen(node->value)-1;

	char * aux;
	aux = (char*) malloc(sizeof(char)*(length+6));

	sprintf(aux, "char[%d]", length);

	printf("get_inside_strlit: %s\n", aux);
	node->type = aux;

	
}
	




