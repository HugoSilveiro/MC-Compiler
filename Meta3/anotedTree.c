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
	else
	{
		////////
		printf("[Insertion on function definition]\n");
		
		Symbol * symbol;

		//inserir o symbolo na tabela global
		Table * global = search_table("global");


		//inserir o typespec concatenado com os parametros...

		//variavel para guardar o tipo de retorno da função
		char *func_type;
		func_type = strdup(get_function_typespec(node));

		//variavel para guardar a lista de parametros no formato (%s,...,)
		char *param_lists;
		param_lists = strdup(get_param_list_concatenated_function(node));

		//variavel para guardar os parametros no formato return(%s,...,);
		char *params_concat;
		params_concat = (char*) malloc(sizeof(func_type)+sizeof(param_lists));
		sprintf(params_concat,"%s%s" , func_type, param_lists);

		printf("Type: %s | param_lists: %s\n", func_type, param_lists);


		//criação do simbolo para a tabela global
		symbol = create_symbol(func_name, params_concat, 0);
		insert_symbol(global, symbol);

		//criar uma tabela nova
		Table * aux1;


		//inserir essa tabela à tabela de simbolos
		aux1 = insert_table(1, func_name);
		aux1->defined = 1;



		//inserir o simbolo de return
		symbol = create_symbol("return", func_type, 0);
		insert_symbol(aux1, symbol);


		//inserir os simbolos da lista de parametros
		//inserir os parametros como symbolos
		get_param_list_function(node, aux1);

		current_table = aux1;
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