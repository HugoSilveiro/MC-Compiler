#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "semantics.h"
#include "printer.h"

extern Table * symbol_table;
Table * current_table = NULL;

#define S_DEBUG 0


char * errors_list[] = {"Conflicting types (got %s, expected %s)\n",
"Invalid use of void type in declaration\n",
"Lvalue required\n",
"Operator %s cannot be applied to type %s\n",
"Operator %s cannot be applied to types %s, %s\n",
"Symbol %s already defined\n",
"Symbol %s is not a function\n",
"Unknown symbol %s\n",
"Wrong number of arguments to function %s (got %d, required %d)\n"};  


void build_table(Node* tree)
{
	if(S_DEBUG){
		printf("build_table\n");
	}

	Node* temp = tree->child;
	while(temp != NULL)
	{
		if(S_DEBUG)printf("%s\n", NODE_NAME[temp->node_type]);
		check_node(temp);
		temp = temp->brother;
	}

}


void check_node(Node* tree)
{
	if(S_DEBUG)printf("check_node-> %s\n",  NODE_NAME[tree->node_type]);

	if(strcmp("ArrayDeclaration", NODE_NAME[tree->node_type]) == 0)
	{
		insert_array_declaration(tree);
	}
	else if(strcmp("Declaration", NODE_NAME[tree->node_type]) == 0)
	{
		insert_declaration(tree);
	}	
	else if(strcmp("FuncDeclaration", NODE_NAME[tree->node_type]) == 0)
	{
		insert_function_declaration(tree);
	}
	else if(strcmp("FuncDefinition", NODE_NAME[tree->node_type]) == 0)
	{
		if(S_DEBUG)printf("FuncDefinition\n");
		insert_function_definition(tree);
	}



}

void insert_declaration(Node * tree)
{
	char * name;
	char * type;
	name = strdup(get_name(tree));
	type = strdup(get_type_declaration(tree));

	int param = 0;
	Symbol * symbol = create_symbol(name, type, param);

	if(current_table != NULL){
		if(search_symbol(name, current_table)==NULL)
		{
			insert_symbol(current_table, symbol);
		}
		else
		{
			//error
			printf(errors_list[5], name);
		}	
	}
	else{
		Table * global = search_table("global");
		if(search_symbol(name, global)==NULL)
		{
			insert_symbol(global, symbol);		
		}

	}
	
	
	
}

void insert_array_declaration(Node * tree)
{
	char * name;
	name = strdup(get_name(tree));

	char * type;
	type = strdup(get_type(tree));

	int param = 0;
	Symbol * symbol = create_symbol(name, type, param);

	if(current_table != NULL){
		if(search_symbol(name, current_table)==NULL)
		{
			insert_symbol(current_table, symbol);		
		}
		else
		{
			//error
			printf(errors_list[5], name);
		}
		
	}
	else{
		Table * global = search_table("global");
		if(search_symbol(name, global)==NULL)
		{
			insert_symbol(global, symbol);		
		}
		
		
	}


}

char * get_name(Node* tree)
{
	if(S_DEBUG)printf("get_name\n");
	Node* temp = tree->child;
	while(temp != NULL){
		if(S_DEBUG)printf("%s\n", NODE_NAME[temp->node_type]);
		if(strcmp(NODE_NAME[temp->node_type], "Id") == 0){
			if(S_DEBUG)printf("%s\n", temp->value);
			return temp->value;
		}
		if(temp->brother != NULL)
		{
			temp = temp->brother;
		}
	}
	return NULL;
}

char * octal_function(int value)
{
	int decimal= 0;
	int i = 0;
	while(value!=0)
	{
		decimal = decimal + (value % 10) * pow_f(8,i++);
		value = value/10;
	}
    char * aux;
    aux = (char*) malloc(sizeof(char)* i);
    sprintf(aux, "%d", decimal);

    return aux;
}

int pow_f(int base, int exponent){
    
    int half_pow;
    if(exponent == 0)
    {
        return 1;
    }
    else if (exponent < 0){
        return 1 / pow_f(base, -exponent);
    }
    else if (exponent % 2 == 0)
    {
    	half_pow = pow_f(base, exponent / 2);
        return half_pow * half_pow;
    }
    else{
        return base * pow_f(base, exponent - 1);
    }

}
char * get_type(Node* tree)
{
	if(S_DEBUG)printf("get_type\n");
	Node* temp = tree->child;
	char * value;
	char* type;
	char* finalType;
	int i;
	int numberPointers = 0;
	while(temp != NULL){
		if(S_DEBUG)printf("while: %s\n", NODE_NAME[temp->node_type]);


		if(strcmp(NODE_NAME[temp->node_type], "IntLit") == 0)
		{
			//memset(value, '\0', sizeof("int"));
			if(S_DEBUG)printf("get_type: %c\n", temp->value[0]);
			if(temp->value[0] == '0')
			{
				value = (char*) malloc(sizeof(octal_function(atoi(temp->value))));
				strcpy(value, octal_function(atoi(temp->value)));	
				//printf("VALUE0: %s\n", value);
			}
			else
			{
				value = (char*)malloc(sizeof(temp->value));
				strcpy(value, temp->value);
				//printf("VALUE1: %s\n", value);
			}			
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Void") == 0)
		{
			//memset(value, '\0', sizeof("int"));
			type = (char*)malloc(sizeof("void"));
			strcpy(type, "void");
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Char") == 0)
		{
			type = (char*)malloc(sizeof("char"));
			strcpy(type, "char");
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Int") == 0)
		{
			type = (char*)malloc(sizeof("int"));
			strcpy(type, "int");
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Pointer")==0)
		{
			numberPointers++;
			//strcat(type, "*");
		}
		temp = temp->brother;
	}
	for(i = 0; i < numberPointers; i++){
		type = concat(type, "*");
	}
	//printf("type:%s | value: %s\n", type, value);
	finalType = (char*) malloc(strlen(type)+strlen(value)+1);
	
	sprintf(finalType, "%s[%s]", type, value);
	return finalType;
}

char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char * get_type_declaration(Node* tree)
{
	if(S_DEBUG)printf("get_type_declaration\n");
	Node* temp = tree->child;
	//char value[10];
	char* type;
	int numberPointers = 0;
	int i;
	
	while(temp != NULL){
		if(S_DEBUG)printf("while: %s\n", NODE_NAME[temp->node_type]);
		if(strcmp(NODE_NAME[temp->node_type], "Void") == 0)
		{
			//memset(value, '\0', sizeof("int"));
			type = (char*)malloc(sizeof("void"));
			strcpy(type, "void");
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Char") == 0)
		{
			if(S_DEBUG)printf("->Char\n");
			type = (char*) malloc(sizeof("char"));			
			strcpy(type, "char");
			//strcpy(finalType, type);
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Int") == 0)
		{
			if(S_DEBUG)printf("->Int\n");
			type = (char*) malloc(sizeof("int"));
			strcpy(type, "int");
			//strcpy(finalType, type);
		}
		//printf("next_temp:%s\n", NODE_NAME[temp->brother->node_type]);
		else if(strcmp(NODE_NAME[temp->node_type], "Pointer") == 0)
		{
			if(S_DEBUG)printf(">Pointer\n");
			numberPointers++;
			//type = (char*)realloc(type, sizeof(type)+1*sizeof("*"));
			//strcat(type, "*");
		}
		temp = temp->brother;
	}

	for(i = 0; i < numberPointers; i++){
		type = concat(type, "*");
	}
	

	//finalType = (char*) malloc(sizeof(type);
	//strcpy()
	//if(S_DEBUG)printf("finalType: %s\n", finalType);
	return type;
}

void insert_function_definition(Node * node)
{
	if(S_DEBUG)
	{
		printf("[insert_function_definition]\n");	
	}	

	//function name:
	char * func_name;
	func_name = strdup(get_function_name(node));

	Table *aux;
	aux = search_table(func_name);

	if((strcmp(func_name, "atoi")==0 || strcmp(func_name, "itoa")==0 || strcmp(func_name, "puts")==0))
	{

		Symbol * symbol;

		
		char *func_type;
		func_type = strdup(get_function_typespec(node));
		
		//criar uma tabela nova
		Table * aux1;


		//inserir essa tabela à tabela de simbolos
		aux1 = search_table( func_name);
		if(aux1->defined==0)
		{
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
	else
	{
		if(aux!=NULL)
		{
			//inserir os simbolos da lista de parametros
			//inserir os parametros como symbolos
			get_param_list_function(node, aux);
			aux->defined = 1;
			current_table = aux;
			insert_function_funcBody(node);
			current_table = NULL;

		}
		else
		{

			////////
			if(S_DEBUG)printf("[Insertion on function definition]\n");
			
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
			params_concat = (char*) malloc(strlen(func_type)+strlen(param_lists)+1);
			sprintf(params_concat,"%s%s" , func_type, param_lists);

			if(S_DEBUG)printf("Type: %s | param_lists: %s\n", func_type, param_lists);


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
	
}

void insert_function_funcBody(Node * node)
{
	if(S_DEBUG){
		printf("insert_function_funcBody\n");
	}
	Node * temp = node->child;
	while(temp != NULL){

		if(strcmp(NODE_NAME[temp->node_type], "FuncBody") == 0)
		{
			
			build_table(temp);
		}
		temp = temp->brother;
	}
}


void insert_function_declaration(Node * node)
{

	if(S_DEBUG)
	{
		printf("[insert_function_declaration]\n");
	}


	Symbol * symbol;

	//inserir o symbolo na tabela global
	Table * global = search_table("global");

	//function name:
	char * func_name;
	func_name = strdup(get_function_name(node));
	Table * find = search_table(func_name);


	if(strcmp(func_name,"atoi")!=0 && strcmp(func_name,"itoa")!=0 && strcmp(func_name,"puts")!=0)
	{
		if(find==NULL)
		{
			
			//inserir o typespec concatenado com os parametros...

			//variavel para guardar o tipo de retorno da função
			char *func_type;
			func_type = strdup(get_function_typespec(node));

			//variavel para guardar a lista de parametros no formato (%s,...,)
			char *param_lists;
			param_lists = strdup(get_param_list_concatenated_function(node));

			//printf("param_list: %s\n", param_lists);

			//variavel para guardar os parametros no formato return(%s,...,);
			char *params_concat;
			params_concat = (char*) malloc(strlen(func_type)+strlen(param_lists)+1);
			sprintf(params_concat,"%s%s" , func_type, param_lists);



			//criação do simbolo para a tabela global
			symbol = create_symbol(func_name, params_concat, 0);
			insert_symbol(global, symbol);

			//criar uma tabela nova
			Table * aux;

			//inserir essa tabela à tabela de simbolos
			aux = insert_table(1, func_name);



			//inserir o simbolo de return
			symbol = create_symbol("return", func_type, 0);
			insert_symbol(aux, symbol);





		}

	}
	
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
	aux = (char*)malloc(sizeof(char)*1000);
	int i = 0;
	int cx;
	while(temp!=NULL)
	{
		if(strcmp(NODE_NAME[temp->node_type], "ParamDeclaration") == 0){

			if(i == 0)
			{
				cx = sprintf(aux,"(%s", get_param_decl(temp));
			}
			else
			{
				cx = cx + sprintf(aux + cx , ",%s", get_param_decl(temp));
			}
			i = i+1;
		}

		temp = temp->brother;
	}

	sprintf(aux + cx, ")");

	return aux;
}

char * get_param_decl(Node * node)
{
	char * type;
	Node * temp;
	temp = node->child;
	int numberPointers = 0;
	int i;
	while(temp!=NULL)
	{

		if(strcmp(NODE_NAME[temp->node_type], "Void") == 0)
		{
			//memset(value, '\0', sizeof("int"));
			type = (char*)malloc(sizeof("void"));
			strcpy(type, "void");
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Char") == 0)
		{
			//memset(value, '\0', sizeof("char"));
			type = (char*)malloc(sizeof("char"));
			strcpy(type, "char");
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Int") == 0)
		{
			type = (char*)malloc(sizeof("int"));
			//memset(value, '\0', sizeof("int"));
			strcpy(type, "int");
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Pointer") == 0)
		{
			//type = (char*)realloc(type, sizeof(type)+ sizeof("*"));
			//strcat(type, "*");
			numberPointers++;
		}


		//falta tratar o asterisco

		temp = temp->brother;
	}
	for(i = 0; i < numberPointers; i++){
		type = concat(type, "*");
	}

	if(S_DEBUG)printf("get_param_decl: %s\n", type);
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
	char * type;
	char * id = NULL;
	Node * temp;
	Symbol * symbol = NULL;
	temp = node->child;
	int numberPointers = 0;
	int i;
	while(temp!=NULL)
	{
		if(S_DEBUG)printf("[param_declaration] %s\n", NODE_NAME[temp->node_type]);

		if(strcmp(NODE_NAME[temp->node_type], "Void") == 0)
		{
			//memset(value, '\0', sizeof("int"));
			type = (char*)malloc(sizeof("void"));
			strcpy(type, "void");
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Char") == 0)
		{
			//memset(value, '\0', sizeof("char"));
			type = (char*)malloc(sizeof("char"));
			strcpy(type, "char");
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Int") == 0)
		{
			type = (char*)malloc(sizeof("int"));
			//memset(value, '\0', sizeof("int"));
			strcpy(type, "int");
		}
		//falta tratar o asterisco
		else if(strcmp(NODE_NAME[temp->node_type], "Pointer")==0)
		{
			//type = (char*)realloc(type, sizeof(type)+sizeof("*"));
			//strcat(type, "*");
			numberPointers++;
		}
		else if (strcmp(NODE_NAME[temp->node_type], "Id")== 0)
		{
			id = (char*)malloc(sizeof(temp->value));
			strcpy(id, temp->value);	
		}

		temp = temp->brother;
	}

	for(i = 0; i < numberPointers; i++){
		type = concat(type, "*");
	}


	if(id!=NULL)
	{
		symbol = create_symbol(id, type, 1);
		insert_symbol(function, symbol);
	}

	

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
	int numberPointers = 0;
	int i;
	while(temp != NULL){

		if(strcmp(NODE_NAME[temp->node_type], "Char") == 0)
		{
			//memset(value, '\0', sizeof("char"));
			value = (char* )malloc(sizeof("char"));
			strcpy(value, "char");
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Void") == 0)
		{
			//memset(value, '\0', sizeof("int"));
			value = (char*)malloc(sizeof("void"));
			strcpy(value, "void");
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Int") == 0)
		{
			//memset(value, '\0', sizeof("int"));
			value = (char* )malloc(sizeof("int"));
			strcpy(value, "int");
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Pointer")== 0)
		{
			//value = (char*)realloc(value, sizeof("*")+sizeof(value));
			//strcat(value, "*");
			numberPointers++;
		}
		else
		{
			//TODO ASTERISK...
			if(S_DEBUG)
			{
				printf("[élse on typespec] Node_type: %s \n", NODE_NAME[temp->node_type]);

			}
		}
		temp = temp->brother;
	}

	for(i = 0; i < numberPointers; i++){
		value = concat(value, "*");
	}


	return value;
}
