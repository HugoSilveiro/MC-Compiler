#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "printer.h"

void print_tree(Node *node, int level){
	print_points(level);

	if(node->node_type == NODE_Id || node->node_type == NODE_Intlit || node->node_type == NODE_Chrlit || node->node_type == NODE_Strlit){
		print_terminal(node);
	}
	else{
		printf("%s\n", NODE_NAME[node->node_type]);
	}

	Node *child = node->child;

	if(child != NULL){
		print_tree(child, level+1);

		while(child->brother != NULL){
			child = child->brother;
			print_tree(child, level+1);
		}

	}

	free(node);
}

void print_points(int n){
	while(n > 0){
		printf("..");
		n--;
	}
}

void print_terminal(Node *node){

	printf("%s(%s)\n", NODE_NAME[node->node_type], node->value);
}
