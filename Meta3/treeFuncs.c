#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "printer.h"
#include "treeFuncs.h"
#include "structs.h"

Node * insert_node(Node_Type node_type)
{
	//printf("insert_node\n");
	//printf("insert_node:%s\n", NODE_NAME[node_type]);
	Node * node = (Node *) malloc(sizeof(Node));
	if(node!=NULL)
	{
		node->node_type = node_type;
		node->brother=NULL;
		node->child=NULL;	
	}
	return node;
}

Node * insert_term_node(Node_Type node_type, char* value)
{
	//printf("insert_term_node: %s\n", value);
	Node * node = insert_node(node_type);
	node->value = value;
	return node;
}

void insert_child(Node * father, Node * child)
{
	//printf("end: %d\n", end);
	//printf("insert_child: %s -> %s\n", NODE_NAME[father->node_type], NODE_NAME[child->node_type]);

	Node * temp = father->child;

	if(temp==NULL)
	{
		child->father = father;
		father->child = child;
	}
	else
	{
		child->brother = father->child;
		child->father = father;
		father->child = child;
	}
	
	

}
/*
void changeOrder(Node * father, Node * child)
{
	Node * temp = father->child;
	father->child = child;
	child->brother = temp;


}
void changeOrder1(Node * node, Node * brother)
{
	Node * temp = node->brother;
	node->brother = brother;
	brother->brother = temp;


}
*/

void insert_brother(Node * brother, Node * node)
{
	//printf("insert_brother\n");

	Node * aux = brother;

	if(aux!=NULL && node!=NULL)
	{
		while(aux->brother != NULL)
		{
			aux = aux->brother;
		}
		aux->brother = node;
		node->father = brother->father;
	}
}
