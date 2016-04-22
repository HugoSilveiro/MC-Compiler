#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "semantics.h"
#include "printer.h"

extern Table * symbol_table;
Table * current_trable;

#define DEBUG 1

int build_table(Node* tree)
{
	if(DEBUG){
		printf("build_table\n");
	}

	Node* temp = tree->child;
	while(temp != NULL)
	{
		check_node(temp);
		temp = temp->brother;
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


void insert_function_declaration(Node * node)
{

	if(DEBUG)
	{
		printf("[insert_function_declaration]\n");
	}
	//get_param_list(node);
	

	Symbol * symbol; 

	//inserir o symbolo na tabela global
	Table * global = search_table("global");

	//inserir o typespec concatenado com os parametros...
	char params_concat[300];
	char temp1[100];
	char temp2[100];
	strcpy(temp1, get_function_typespec(node));
	strcpy(temp2, get_param_list_concatenated_function(node));
	
	snprintf(params_concat, 300,"%s%s" , temp1, temp2);
	printf("params_concat: %s\n", params_concat);

	symbol = create_symbol(get_function_name(node), params_concat, 0);
	insert_symbol(global, symbol);

	//criar uma tabela nova
	Table * aux;
	
	//inserir essa tabela à tabela de simbolos
	aux = insert_table(1, get_function_name(node));

	//inserir o simbolo de return
	symbol = create_symbol("return", get_function_typespec(node), 0);
	insert_symbol(aux, symbol);


	//inserir os simbolos da lista de parametros
	//inserir os parametros como symbolos
	get_param_list_function(node, aux);
	

}



char * get_param_list_concatenated_function(Node * node)
{
	Node* temp = node->child;
	Node* found= NULL;
	while(temp != NULL){
		if(strcmp(NODE_NAME[temp->node_type], "ParamList") == 0){
			found = temp;
		}
		temp = temp->brother;
	}

	temp = found->child;
	char * aux;
	aux = (char*)malloc(sizeof(char)*200);
	int i = 0;
	int cx;
	while(temp!=NULL)
	{
		if(strcmp(NODE_NAME[temp->node_type], "ParamDeclaration") == 0){
			
			if(i == 0)
			{
				cx = snprintf(aux, 300,"(%s", get_param_decl(temp));
			}
			else
			{
				cx = cx + snprintf(aux + cx ,300, ",%s", get_param_decl(temp));
			}
			i = i+1;
		}

		temp = temp->brother;
	} 
	snprintf(aux + cx,300, ")");
	return aux;
}

char * get_param_decl(Node * node)
{
	char * type ;
	Node * temp;
	Symbol * symbol = NULL;
	temp = node->child;
	while(temp!=NULL)
	{
		
		if(strcmp(NODE_NAME[temp->node_type], "IntLit") == 0)
		{
			//memset(value, '\0', sizeof("int"));
			type = (char*)malloc(sizeof(char)*4);
			strcpy(type, "int");
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Char") == 0)
		{
			//memset(value, '\0', sizeof("char"));
			type = (char*)malloc(sizeof(char)*5);
			strcpy(type, "char");
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Int") == 0)
		{
			type = (char*)malloc(sizeof(char)*3);
			//memset(value, '\0', sizeof("int"));
			strcpy(type, "int");
		}
		//falta tratar o asterisco

		temp = temp->brother;
	}
	if(DEBUG)printf("get_param_decl: %s\n", type);
	return type;
}


void get_param_list_function(Node * node, Table* function)
{
	Node* temp = node->child;
	Node* found= NULL;
	while(temp != NULL){
		if(strcmp(NODE_NAME[temp->node_type], "ParamList") == 0){
			found = temp;
		}
		temp = temp->brother;
	}


	temp = found->child;
	while(temp!=NULL)
	{
		if(strcmp(NODE_NAME[temp->node_type], "ParamDeclaration") == 0){
			get_param_declaration(temp, function);
		}
		temp = temp->brother;
	} 

}

void get_param_declaration(Node * node, Table *function)
{
	char * type ;
	char * id ;
	Node * temp;
	Symbol * symbol = NULL;
	temp = node->child;
	while(temp!=NULL)
	{
		printf("[param_declaration] %s\n", NODE_NAME[temp->node_type]);
		
		if(strcmp(NODE_NAME[temp->node_type], "IntLit") == 0)
		{
			//memset(value, '\0', sizeof("int"));
			type = (char*)malloc(sizeof(char)*4);
			strcpy(type, "int");
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Char") == 0)
		{
			//memset(value, '\0', sizeof("char"));
			type = (char*)malloc(sizeof(char)*5);
			strcpy(type, "char");
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Int") == 0)
		{
			type = (char*)malloc(sizeof(char)*3);
			//memset(value, '\0', sizeof("int"));
			strcpy(type, "int");
		}
		//falta tratar o asterisco
		else
		{
			id = (char*)malloc(sizeof(temp->value));
			strcpy(id, temp->value);
		}
		temp = temp->brother;
	}

	printf("id: %s | type: %s\n", id, type);
	symbol = create_symbol(id, type, 1);
	insert_symbol(function, symbol);
}

//get function name on function declaration
char * get_function_name(Node * node)
{
	Node* temp = node->child;
	while(temp != NULL){
		if(strcmp(NODE_NAME[temp->node_type], "Id") == 0){
			return temp->value;
		}
		temp = temp->brother;
	}
	return NULL;
}

//get typespec-> falta tratar dos deref
char * get_function_typespec(Node * node)
{


	char * value;
	Node * temp = node->child;

	while(temp != NULL){
		if(strcmp(NODE_NAME[temp->node_type], "IntLit") == 0)
		{
			//memset(value, '\0', sizeof("int"));
			strcpy(value, "int");
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Char") == 0)
		{
			//memset(value, '\0', sizeof("char"));
			strcpy(value, "char");
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Int") == 0)
		{
			//memset(value, '\0', sizeof("int"));
			strcpy(value, "int");
		}
		else
		{
			//TODO ASTERISK...
			if(DEBUG)
			{
				printf("[élse on typespec] Node_type: %s \n", NODE_NAME[temp->node_type]);
				
			}
		}
		temp = temp->brother;
	}

	return value;
}