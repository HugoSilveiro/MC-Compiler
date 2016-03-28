#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Node * insert_node(char * node_type)
{
	Node * node = (Node *) malloc(sizeof(Node));
	node->node_type = node_type;
	node->right=NULL;
	node->left=NULL;

	return node;
}

Node * insert_term_node(char * node_type, char* value)
{
	Node * node = insert_node(node_type);
	node->vale = value;
	return node;
}

void insert_child(Node * father, Node * child)
{

	Node * temp = father->left;

	if(temp==NULL)
	{
		father->left = child;
	}
	else
	{
		while(temp->right != NULL)
		{
			temp = temp->right;
		}
		temp->right = child;
	}

}
