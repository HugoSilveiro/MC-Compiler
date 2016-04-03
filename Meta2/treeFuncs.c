#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "printer.h"
#include "treeFuncs.h"
#include "structs.h"

Node * insert_node(Node_Type node_type)
{
	//printf("insert_node\n");
	printf("insert_node:%s\n", NODE_NAME[node_type]);
	Node * node = (Node *) malloc(sizeof(Node));
	node->node_type = node_type;
	node->brother=NULL;
	node->child=NULL;

	return node;
}

Node * insert_term_node(Node_Type node_type, char* value)
{
	//printf("insert_term_node\n");
	Node * node = insert_node(node_type);
	node->value = value;
	return node;
}

void insert_child(Node * father, Node * child)
{
	//printf("insert_child\n");
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
	//printf("insert_brother\n");
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
