#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "printer.h"
#include "structs.h"

Node * insert_node(char * node_type);
Node * insert_term_node(char * node_type, char* value);
void insert_child(Node * father, Node * child);
void insert_brother(Node * node, Node * brother);

Node * insert_node(char * node_type)
{
	Node * node = (Node *) malloc(sizeof(Node));
	node->node_type = node_type;
	node->brother=NULL;
	node->child=NULL;

	return node;
}

Node * insert_term_node(char * node_type, char* value)
{
	Node * node = insert_node(node_type);
	node->value = value;
	return node;
}

void insert_child(Node * father, Node * child)
{

	Node * temp = father->child;

	if(temp==NULL)
	{
		father->child = child;
	}
	else
	{
		while(temp->brother != NULL)
		{
			temp = temp->brother;
		}
		temp->brother = child;
	}

}


void insert_brother(Node * node, Node * brother)
{
	Node * temp = node->brother;
	if(temp==NULL)
	{
		node->brother = brother;
	}
	else
	{
		while(temp->brother!=NULL)
		{
			temp = temp->brother;
		}
		temp->brother=brother;
	}
}
void print_tree(Node *node, int level){

	print_points(level);

	if(node->node_type == NODE_ID || node->node_type == NODE_INTLIT || node->node_type == NODE_CHRLIT || node->node_type == NODE_STRLIT){
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
