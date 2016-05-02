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


void get_inside_store(Node * node)
{
	Node * temp;
	temp = node->child;
	if(temp!=NULL)
	{
		node->type = temp->type;
	}
}

void check_call_type(Node * node)
{
	Node * temp;
	temp = node->child;
	if(temp!=NULL)
	{
		if(type_call(temp->type)!=NULL)
		{
			node->type = strdup( type_call(temp->type));	
		}
	}
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
			new_aux[i] = '\0';
			return new_aux;
		}
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
			

			temp->type = "int"; 
 
			get_inside_funcBody(temp);




		}
		else if(strcmp(NODE_NAME[temp->node_type], "Ne") == 0)
		{

			temp->type = "int";  
			get_inside_funcBody(temp);


		}
		else if(strcmp(NODE_NAME[temp->node_type], "Lt") == 0)
		{
			temp->type = "int"; 
			get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Gt") == 0)
		{
			temp->type = "int"; 
			get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Le") == 0)
		{
			temp->type = "int"; 
			get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Ge") == 0)
		{
			temp->type = "int"; 
			get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "And") == 0)
		{	
			temp->type = "int"; 
			get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Or") == 0)
		{	
			temp->type = "int"; 
			get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Add") == 0)
		{	

			get_inside_funcBody(temp);
			get_add_type(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Sub") == 0)
		{
			temp->type = "int";
			get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Mul") == 0)
		{
			temp->type = "int"; 
			get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Div") == 0)
		{
			temp->type = "int"; 
			get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Mod") == 0)
		{
			temp->type = "int"; 
			get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Not") == 0)
		{
			temp->type = "int"; 
			get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Minus") == 0)
		{
			temp->type = "int"; 
			get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Plus") == 0)
		{
			temp->type = "int"; 
			get_inside_funcBody(temp);

		}
		else if(strcmp(NODE_NAME[temp->node_type], "Addr") == 0)
		{
			get_inside_funcBody(temp);
			get_inside_addr(temp); 
			//temp->type = "int"; 

			//get_inside_funcBody(temp);

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

			get_inside_funcBody(temp);
			get_inside_store(temp);
		}
		else if(strcmp(NODE_NAME[temp->node_type], "Comma") == 0)
		{
			get_inside_funcBody(temp);
			get_inside_comma(temp);

		}
		
		else if(strcmp(NODE_NAME[temp->node_type], "Call") == 0)
		{
			
			//temp->type = check_call_type(temp); 
			//get_inside_funcBody(temp);

			if (DEBUG_A) printf("call\n");
			get_inside_funcBody(temp);
			check_call_type(temp); 


		}
		else if(strcmp(NODE_NAME[temp->node_type], "Return") == 0){
			get_inside_funcBody(temp);
		}
		else if(strcmp(NODE_NAME[temp->node_type], "If") == 0)
		{
			
			get_inside_funcBody(temp);
		}
		else if(strcmp(NODE_NAME[temp->node_type], "For") == 0)
		{
			
			get_inside_funcBody(temp);
		}
		else if(strcmp(NODE_NAME[temp->node_type], "StatList")==0)
		{
			get_inside_funcBody(temp);
		}	
		
		temp = temp->brother;
	}
}

/*
char * is_Add(Node * node)
{
	Node * child1 = node->child;
	Node * child2 = child1->brother;	
}

char * is_sub(Node * node)
{
	Node * child1 = node->child;
	Node * child2 = child1->brother;

}

char is_Mul(Node * node)
{
	Node * child1 = node->child;
	Node * child2 = child1->brother;
}

char is_Div(Node * node)
{
	Node * child1 = node->child;
	Node * child2 = child1->brother;
}

char is_Mod(Node * node)
{
	Node * child1 = node->child;
	Node * child2 = child1->brother;
}

char is_Not(Node * node)
{
	Node * child1 = node->child;
	Node * child2 = child1->brother;
}

char is_Minus(Node * node)
{
	Node * child1 = node->child;
	Node * child2 = child1->brother;
}

char is_Plus(Node * node)
{
	Node * child1 = node->child;
	Node * child2 = child1->brother;
}
*/
void get_inside_comma(Node * node)
{
	Node * temp1;
	temp1 = node->child;

	if(temp1!=NULL)
	{
		Node * temp2 = temp1->brother;
		if(temp2 != NULL)
		{
			node->type = temp2->type;
		}
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
	Node * child = node->child;
	
	if(child!=NULL)
	{
		return child->type;
	}
	return NULL;
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
			node->type = temp1->type;
		}	
	}
}


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




