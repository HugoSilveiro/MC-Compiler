

#include "printer.h"


void get_anoted_Tree(Node* tree);

void insert_funct_definition(Node * tree);

void insert_funcBody(Node * node);

void check_inside_funcBody(Node * node);

void get_inside_funcBody(Node * node);

void get_inside_id(Node * node);

void get_inside_operator(Node * node);

void get_inside_strlit(Node * node);

char * check_call_type(Node * node);

char * get_type_Call(Node * node);

char * type_call(char * type);

char * get_expr_type(Node * node);

char * get_deref_type(Node * node);

char * get_add_type(Node * node);

char * return_symbol_name(Symbol * symbol);

char * get_operator_type_result(Node * node);