

#include "printer.h"


void get_anoted_Tree(Node* tree);

void insert_funct_definition(Node * tree);

void insert_funcBody(Node * node);

void check_inside_funcBody(Node * node);

void get_inside_funcBody(Node * node);

void get_inside_id(Node * node);

void get_inside_operator(Node * node);

void get_inside_strlit(Node * node);

void check_call_type(Node * node);

char * type_call(char * type);

char * get_expr_type(Node * node);

void get_deref_type(Node * node);

void get_add_type(Node * node);

char * return_symbol_name(Symbol * symbol);

char * get_operator_type_result(Node * node);

void get_inside_addr(Node * node);

int is_escape3(char a, char b, char c);

int parse_strlit(char * string);

void get_inside_comma(Node * node);

void get_inside_store(Node * node);

//ERRORS
void check_num_args(Node * temp);

//OPERATORS

void is_Add(Node * node);

void is_Sub(Node * node);

void is_Mul_Div_Mod(Node * node);

void is_Plus_Minus(Node * node);

//NUMBER OF POINTERS

int return_pointers(char * value);

int aux_Arrray_Declarations(char * value);

void aux_pointer(Node* node, int aux_value);