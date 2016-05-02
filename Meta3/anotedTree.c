#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "anotedTree.h"
#include "printer.h"

#define DEBUG_A 0
#define ERRORS 0

extern Table * symbol_table;
Table * current_table2 = NULL;

void get_anoted_Tree(Node* tree)
{
	if (DEBUG_A) printf("[get_anoted_tree]\n");
	Node* temp = tree->child;
	while(temp!=NULL)
	{
		if (DEBUG_A) printf("%s\n", NODE_NAME[temp->node_type]);
		
		if(strcmp("FuncDefinition", NODE_NAME[temp->node_type]) == 0)
		{
			if(DEBUG_A)printf("FuncDefinition\n");
			insert_funct_definition(temp);
		}
		
		temp= temp->brother;
	}
}

void insert_funct_definition(Node * node)
{

	if(DEBUG_A)
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
	if(DEBUG_A){
		printf("insert_function_funcBody\n");
	}
	Node * temp = node->child;
	while(temp != NULL){

		if(strcmp(NODE_NAME[temp->node_type], "FuncBody") == 0)
		{
			get_inside_funcBody(temp);
			//check_inside_funcBody(temp);
		}
		temp = temp->brother;
	}
}

void check_inside_funcBody(Node * node)
{
	if(DEBUG_A){
		printf("check_inside_funcBody\n");
	}
	Node * temp = node->child;
	while(temp != NULL){
		if (DEBUG_A) printf("%s\n", NODE_NAME[temp->node_type]);
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
			//printf("gotr: %s\n",);
			//temp->type = get_operator_type_result(temp);
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
		else if(strcmp(NODE_NAME[temp->node_type], "Addr") ==0)
		{
			get_inside_addr(temp);
		}
		else if(strcmp(NODE_NAME[temp->node_type], "StrLit") ==0)
		{
			if(DEBUG_A) printf("Strlit node_type: %s\n", NODE_NAME[temp->node_type]);
			get_inside_funcBody(node);
		}

		temp = temp->brother;
	}	
}

char * check_call_type(Node * node)
{
	if (DEBUG_A) printf("check_call_type\n");
	char * auxType = NULL;
	Node * temp = node->child;
	while(temp != NULL)
	{
		if (DEBUG_A) printf("%s\n", NODE_NAME[temp->node_type]);
		if(strcmp(NODE_NAME[temp->node_type], "Id") == 0){
			auxType = (char*)malloc(sizeof(get_type_Call(temp)));
			strcpy(auxType, get_type_Call(temp));
			if (DEBUG_A) printf("auxType: %s\n", auxType);

			if(ERRORS) check_num_args(temp);
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

/*
//erros check num arguments
void check_num_args(Node * temp)
{
	Table * table;
	Symbol * symbol;
	table = search_table("global");
	symbol = search_symbol(temp->value, table);
	int caller, called;
	if(symbol!=NULL)
	{
		called = num_args(temp->type);	
	}
	if(temp->type!=NULL)
	{
		caller = num_args(temp->type);
	}

	if(called != caller)
	{
	 	printf(errors_list[8], temp->value, caller, called);
	}
}

int num_args(char * string)
{
	int comma = 0;
	int i;
	for(i = 0;i<strlen(string)-1;i++)
	{
		if(string[i] == ','){
			comma++;
		}
	}
	return comma+1;
}
*/
char * get_type_Call(Node * node)
{	
	if (DEBUG_A) printf("get_type_Call\n");
	Symbol * symbol = search_symbol(node->value, current_table2);
	
	if(symbol!=NULL)
	{
		node->type = symbol->type;
		if (DEBUG_A) printf("get_type_call: %s\n", node->type);
		return type_call(node->type);
	}
	else
	{
		Table * table = search_table("global");
		Symbol * symbol2 = search_symbol(node->value, table);
		if(symbol2!=NULL)
		{
			
			node->type = symbol2->type;
			if (DEBUG_A) printf("get_type_call: %s\n", node->type);
			return type_call(node->type);	
		}	
	}
	return NULL;
}


char * type_call(char * type)
{
	int aux = strlen(type);
	char * new_aux = (char*)malloc(aux+1);
	int i;
	for(i = 0; i < aux; i++){
		if(type[i] != '('){
			new_aux[i] = type[i];
		}
		else if(type[i] == '('){
			if (DEBUG_A) printf("type_call: %s\n", new_aux);
			new_aux[i] = '\0';
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
		if(DEBUG_A)printf("[get_inside_funcBody] %s\n",NODE_NAME[temp->node_type] );

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
		else if(strcmp(NODE_NAME[temp->node_type], "Eq") == 0)
		{
			
			temp->type = get_operator_type_result(temp); 
			get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Ne") == 0)
		{
			temp->type = get_operator_type_result(temp);; 
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
			//printf("Add\n");
			//temp->type = get_add_type(temp);
			//temp->type = "int*";
			/*Node * temp2 = temp->child;
			while(temp2!= NULL){
				printf("child->node_type: %s\n", NODE_NAME[temp2->node_type]);
				printf("child->value: %s\n", temp2->value);
				printf("child->type: %s\n", temp2->type);
				temp2 = temp2->child;
			}*/
			//temp->type =  get_expr_type(temp);
			get_inside_operator(temp);
			get_add_type(temp);

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
			get_inside_funcBody(temp);
			get_inside_addr(temp); 
			//temp->type = "int"; 

			//get_inside_operator(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Deref") == 0)
		{	
			//printf("Deref\nchild:%s\n", NODE_NAME[temp->child->node_type]);
			get_inside_funcBody(temp);
			get_deref_type(temp);
			//get_deref_type(temp); 
			

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Store") == 0)
		{
			//printf("gotr: %s\n",get_operator_type_result(temp));
			//temp->type = get_operator_type_result(temp); 
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

			if (DEBUG_A) printf("call\n");
			temp->type = check_call_type(temp); 
			get_inside_funcBody(temp);


		}
		else if(strcmp(NODE_NAME[temp->node_type], "Return") == 0){
			get_inside_operator(temp);
		}
		else if(strcmp(NODE_NAME[temp->node_type], "If") == 0)
		{
			
			get_inside_funcBody(temp);
		}
		else if(strcmp(NODE_NAME[temp->node_type], "For") == 0)
		{
			
			get_inside_funcBody(temp);
		}	

		else{
			check_inside_funcBody(temp);
		}

		temp = temp->brother;
	}
}



void get_inside_addr(Node * node)
{
	Node * temp;
	temp = node->child;
	if(temp!=NULL)
	{
		node->type = temp->type;
		node->type = concat(node->type, "*");
	}
	
}

char * get_operator_type_result(Node * node)
{
	Node * child1 = node->child;
	Node * child2 = child1->brother;
	char * childType1 = NULL;
	char * childTypeAux1 = NULL;
	char * childType2 = NULL;
	char * childTypeAux2 = NULL;
	char intType[4] = "int";
	//OPERADORES TEM SEMPRE FILHO1 e FILHO2
	//IR BUSCAR OS TIPOS DE CADA FILHO A TABELA
	if(child1->value != NULL){
		if (DEBUG_A) printf("%s\n", NODE_NAME[child1->node_type]);
		//printf("%s\n", NODE_NAME[child2->node_type]);
		if(strcmp(NODE_NAME[child1->node_type], "Id") == 0){
			
			Symbol * symbol1 = (Symbol *) malloc(sizeof(Symbol));
			symbol1 = search_symbol(child1->value, current_table2);
			childType1 = (char*)malloc(sizeof(return_symbol_name(symbol1)));
			strcpy(childType1,return_symbol_name(symbol1));
			if (DEBUG_A) printf("child1 type: %s\n", childType1);	
		}
		else if(strcmp(NODE_NAME[child1->node_type], "IntLit") == 0){
			childType1 = (char*)malloc(sizeof(intType));
			strcpy(childType1, intType);
			if (DEBUG_A) printf("child1 type: %s\n", childType1);
		}
		else{
			if (DEBUG_A) printf("%s\n",NODE_NAME[child1->node_type]);
			get_inside_funcBody(child1);
		}
		
	}
	else if(child1->value == NULL){
		if (DEBUG_A) printf("null\n");
		childType1 = (char*)malloc(sizeof(get_operator_type_result(child1)));
		strcpy(childType1, get_operator_type_result(child1));
		if (DEBUG_A) printf("child2 type: %s\n", childType1);
	}


	// SAME
	if (DEBUG_A) printf("%s\n", NODE_NAME[child2->node_type]);


	if(child2->value != NULL){
		if (DEBUG_A) printf("%s\n", NODE_NAME[child2->node_type]);
		if(strcmp(NODE_NAME[child2->node_type], "Id") == 0){
			
			Symbol * symbol2 = (Symbol *) malloc(sizeof(Symbol));
			symbol2 = search_symbol(child2->value, current_table2);
			childType2 = (char*)malloc(sizeof(return_symbol_name(symbol2)));
			strcpy(childType2,return_symbol_name(symbol2));
			if (DEBUG_A) printf("child2 type: %s\n", childType2);	
		}
		else if(strcmp(NODE_NAME[child2->node_type], "IntLit") == 0){
			childType2 = (char*)malloc(sizeof(intType));
			strcpy(childType2, intType);
			if (DEBUG_A) printf("child2 type: %s\n", childType2);
			//printf("Int\n");
		}
		
	}
	else if(child2->value == NULL){
		if (DEBUG_A) printf("null\n");
		if(strcmp(NODE_NAME[child2->node_type], "Call")){
			if (DEBUG_A) printf("Call\n");
			childType2 = (char*)malloc(sizeof(check_call_type(child2)));
			strcpy(childType2, check_call_type(child2));
			if (DEBUG_A) printf("child2 type: %s\n", childType2);
		}
		else{
			childType2 = (char*)malloc(sizeof(get_operator_type_result(child2)));
			strcpy(childType2, get_operator_type_result(child2));
			if (DEBUG_A) printf("child2 type: %s\n", childType2);
		}
	}

	// CASOS EM QUE SEJA CHAR*, CHAR** CHAR****** ETC... PASSAR SO A CHAR PARA COMPARAÇAO
	if(childType1[0] == 'c'){
		//printf("char inicio\n");
		childTypeAux1 = (char*)malloc(sizeof("char"));
		strcpy(childTypeAux1, "char");
		//printf("char fim\n");
	}
	if(childType2[0] == 'c'){
		childTypeAux2 = (char*)malloc(sizeof("char"));
		strcpy(childTypeAux2, "char");
	}


	//COMPARAÇAO
	if(strcmp(childType1, childType2) == 0){
		//printf("iguais\n");
		return childType1;
	}

	else if(strcmp(childType1, "int") == 0 && (strcmp(childTypeAux2, "char")) == 0)
	{
		return childType2;
	}
	else if(strcmp(childType2, "int") == 0 && strcmp(childTypeAux1, "char") == 0)
	{
		return childType1;
	}
	
	else{
		return NULL;
	}
	
	
}

char * return_symbol_name(Symbol * symbol)
{

	return symbol->type;

}

void get_add_type(Node * node)
{
	Node * temp1;
	Node * temp2;
	temp1 = node->child;
	if(temp1!=NULL)
	{
		temp2 = temp1->brother;
		if(temp2!=NULL)
		{
			node->type = "int*";
		}	
	}
}

/*
char * get_add_type(Node * temp)
{
	if (DEBUG_A) printf("get_add_type\n");
	Node * temp2 = temp->child;
	while(temp2!= NULL){
		char * addType = NULL;
		if (DEBUG_A) printf("child->node_type: %s\n", NODE_NAME[temp2->node_type]);
		if (DEBUG_A) printf("child->value: %s\n", temp2->value);
		if (DEBUG_A) printf("child->type: %s\n", temp2->type);
		if(temp2->value != NULL){
			Symbol * symbol = (Symbol *) malloc(sizeof(Symbol));
			symbol = search_symbol(temp2->value, current_table2);
			if(symbol!=NULL)
			{
				addType = (char*)malloc(sizeof(return_symbol_name(symbol)));
				strcpy(addType,return_symbol_name(symbol));
				return addType;
				//printf("addType: %s\n", addType);
			
			}
			else{
				if (DEBUG_A) printf("global table\n");
				Table * table = search_table("global");
				Symbol * symbol = (Symbol *) malloc(sizeof(Symbol));
				symbol = search_symbol(temp2->value, table);
				if(symbol!=NULL){
					if (DEBUG_A) printf("symbol global != NULL\n");
					addType = (char*)malloc(sizeof(return_symbol_name(symbol)));
					strcpy(addType,return_symbol_name(symbol));
					if (DEBUG_A) printf("addType: %s\n", addType);
					addType[strlen(addType)-1] = '\0';
					return addType;	
				}

			}		
		}
		
		temp2 = temp2->child;
		
	}
	return NULL;

}

*/

void get_deref_type(Node * node)
{
	Node * temp = node->child;
	if(temp!=NULL)
	{
		node->type = strdup(temp->type);
		node->type[strlen(temp->type)-1] = '\0';
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
	if (DEBUG_A) printf("get_inside_operator\n");
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

			if (DEBUG_A) printf("call\n");
			temp->type = check_call_type(temp); 
			get_inside_funcBody(temp);


		}
		else{
			if (DEBUG_A) printf("else: %s\n", NODE_NAME[temp->node_type]);
			get_inside_funcBody(temp->father);
		}	

		temp = temp->brother;
	}
}

void get_inside_id(Node * node)
{
	if (DEBUG_A) printf("[get_inside_id] node->value: %s\n", node->value);

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

	//int length = strlen(node->value)-1;;

	int length = parse_strlit(node->value);
	
	char * aux;
	aux = (char*) malloc(sizeof(char)*(length+6));


	sprintf(aux, "char[%d]", length);

	//printf("get_inside_strlit: %s\n", aux);
	node->type = aux;

	
}
	

int is_escape3(char a, char b, char c)
{
	int value = 0;
	if(isdigit(a)&& a-'0'<=7 )
	{
		value++;
		if(isdigit(b)&& b-'0'<=7)
		{
			value++;
			if(isdigit(c) && c-'0' <=7)
			{
				value++;
			}
		}
	}
	return value;
}

int parse_strlit(char * string)
{
	int scape2 = 0;
	int scape3 = 0;

	int length = strlen(string)-1;
	int i;
	for(i = 0;i<length-1;i++)
	{
		if(string[i]=='\\')
		{
			if(string[i+1] == 'n' || string[i+1] == 't' || string[i+1] == '\'' || string[i+1] == '"' || string[i+1] == '\\')
			{
				scape2++;
			}
		}
	}

	for(i = 0;i<length-2;i++)
	{
		if(string[i]=='\\')
		{
			int value =is_escape3(string[i+1], string[i+2], string[i+3]); 
			if(value!=0)
			{
				scape3=scape3+value;
			}
		}
	}

	length = length -scape2-scape3;
	return length;
}




