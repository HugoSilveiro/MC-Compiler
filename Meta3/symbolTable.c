#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "printer.h"
#define DEBUG 0

extern Table * symbol_table;

void start_symbol_table()
{
	Symbol *symbol ;
	Table * aux;
	//Tabela Global
	aux = insert_table(0, "global");
	//iniciar a funçao atoi
	symbol = create_symbol("atoi", "int(char*)", 0);
	insert_symbol(aux, symbol);

	//iniciar itoa
	symbol = create_symbol("itoa", "char*(int, char*)", 0);
	insert_symbol(aux, symbol);

	//iniciar puts
	symbol = create_symbol("puts", "int(char*)", 0);
	insert_symbol(aux, symbol);


}

//type==0 -> Global | type==1 -> Function
//insert table on symbol_table
Table * insert_table(int type, char * name)
{
	if(DEBUG)
	{
		printf("[insert_table]\n");
	}

	Table * table = (Table *) malloc(sizeof(Table));
	table->type = type;
	table->name = name;
	table->next = NULL;
	table->child= NULL;

	//declared and defined
	table->declared = 0;
	table->defined = 0;

	Table * aux;
	Table * aux_before;

	if(symbol_table!=NULL)
	{
		for(aux = symbol_table; aux; aux=aux->next)
		{
			aux_before = aux;
		}
		aux_before->next = table;
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
		printf("[create symbol] name: %s | type: %s | param: %d\n", name, type, param);
	}
	Symbol * symbol = (Symbol *) malloc(sizeof(Symbol));

	symbol->name = name;
	symbol->type = type;
	symbol->param = param;

	symbol->next = NULL;
	return symbol;
}

//function to insert symbol on table
void insert_symbol(Table * table, Symbol * symbol)
{
	if(DEBUG)
	{
		printf("[insert_symbol]\n");
	}
	Symbol * aux ;
	Symbol * aux_before;

	if(table->child)
	{
		for(aux = table->child;aux;aux = aux->next)
		{
			aux_before = aux;
		}
		aux_before->next = symbol;
	}
	else
	{
		table->child = symbol;
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

	return NULL;
}

//function to search for a specific table
Table * search_table(char * name)
{
	if(DEBUG)
		printf("[search_table] name: %s\n", name);

	Table * aux;

	for(aux = symbol_table;aux; aux= aux->next)
	{
		if(strcmp(aux->name, name)==0)
		{
			if(DEBUG)
			{
				printf("[Table Found] name: %s\n", name);
			}

			return aux;
		}
	}
	return NULL;

}
