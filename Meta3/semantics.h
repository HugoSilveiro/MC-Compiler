
#include "printer.h"

int build_table(Node* tree);
void check_node(Node* tree);
char * get_name(Node* tree);
char * get_type(Node* tree);
char * get_type_declaration(Node* tree);

void insert_function_definition(Node * node);
void check_func_body(Node * node);


void insert_function_declaration(Node * node);
char * get_function_typespec(Node * node);
char * get_function_name(Node * node);
void get_param_list_global(Node * node, Table* global, char * return_value);

void get_param_list_function(Node * node, Table* function);
void get_param_declaration(Node * node, Table *function);

char * get_param_decl(Node * node);
char * get_param_list_concatenated_function(Node * node);
