#include <string.h>
#include <stdio.h>
#include <string.h>

#include "struct.h"

#define DEBUG 1

void start_symbol_table()
{
	//Tabela Global
	insert_table(0);


}

//type==0 -> Global | type==1 -> Function
//insert table on symbol_table
void insert_table(int type)
{
	if(DEBUG)
	{
		printf("[insert_table]\n");
	}

	Table * table = (Table *) malloc(sizeof(Table));
	table->type = type;
	table->next = NULL;
	table->child= NULL;


	Table * aux;
	Table * aux_before;

	if(symbol_table!=NULL)
	{
		for(aux = symbol_table; aux; aux=aux->next)
		{
			aux_before = aux;
		}
		aux_before = table;
	}
	else
	{
		symbol_table = table;
	}
	return table;
}

//function to create symbol without attaching it to any table
Symbol * create_symbol(char *name, char * type, int param)
{
	if(DEBUG)
	{
		printf("[create symbol] name: %s | type: %s | param: %s\n", name, type, param);
	}
	Symbol * symbol = (Symbol *) malloc(sizeof(Symbol));

	symbol->name = name;
	symbol->type = type;
	symbol->param = param;

	symbol->next = NULL,
	return symbol;
}

//function to insert symbol on table
void insert_symbol(Table * table, Symbol * symbol)
{
	if(DEBUG)
	{
		printf("[insert_symbol]\n");
	}

	Symbol * aux = table->child;
	if(aux==NULL)
	{
		aux->next = symbol;
	}
	else
	{
		while(aux!=NULL)
		{
			aux=aux->next;
		}
		aux->next = symbol;
	}
}

//function to search for a specific symbol- if found return symbol, else returns NULL
Symbol * search_symbol(char *name, Table * table)
{

	if(DEBUG)
		printf("[search_symbol] name: %s\n", name);
	
	Symbol *aux;
	for(aux = table->child; aux; aux = aux->next)
	{
		if(strcmp(aux->name, name) == 0)
		{
			if(DEBUG)
				printf("[Symbol found] name: %s\n", name);
			return aux;	
		}
	}

	return NULL,
}

//function to search for a specific table
Table * search_table(char * name)
{
	if(DEBUG)
		printf("[search_table] name: %s\n", name);

	Table * aux;

	//TODO
}