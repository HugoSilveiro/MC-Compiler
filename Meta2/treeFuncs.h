#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H


#include "structs.h"
#include "printer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Node * insert_node(Node_Type node_type);
Node * insert_term_node(Node_Type node_type, char* value);
void insert_child(Node * father, Node * child);
void insert_brother(Node * node, Node * brother);

#endif
