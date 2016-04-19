#ifndef _PRINTER_H
#define _PRINTER_H

#include "structs.h"

/* list of names for the nodes of the abstract syntax tree */
static const char *NODE_NAME[] = {
	"Program",
	"Declaration",

	"ArrayDeclaration",
	"FuncDeclaration",
	"FuncDefinition",
	"ParamList",
	"FuncBody",
	"ParamDeclaration",

	"StatList",
	"If",
	"For",
	"Return",


	"Or",
	"And",
	"Eq",
	"Ne",
	"Lt",
	"Gt",
	"Le",
	"Ge",
	"Add",
	"Sub",
	"Mul",
	"Div",
	"Mod",
	"Not",
	"Minus",
	"Plus",
	"Addr",
	"Deref",
	"Store",
	"Comma",
	"Call",


	"Int",
	"Char",
	"Pointer",
	"Void",
	"Id",
	"IntLit",
	"ChrLit",
	"StrLit",


	"Null"
};

void print_tree(Node *node, int level);
void print_points(int n);
void print_terminal(Node *node);


#endif
