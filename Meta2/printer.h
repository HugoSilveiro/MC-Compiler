#ifndef _PRINTER_H
#define _PRINTER_H

#include "structs.h"

/* list of names for the nodes of the abstract syntax tree */
static const char *NODE_NAME[] = {
	"Program",
	"VarPart",
	"FuncPart",
	"VarDecl",
	"FuncDecl",
	"FuncDef",
	"FuncDef2",
	"FuncParams",
	"Params",
	"VarParams",
	"Assign",
	"IfElse",
	"Repeat",
	"StatList",
	"ValParam",
	"While",
	"WriteLn",
	"Add",
	"And",
	"Call",
	"Div",
	"Eq",
	"Geq",
	"Gt",
	"Leq",
	"Lt",
	"Minus",
	"Mod",
	"Mul",
	"Neq",
	"Not",
	"Or",
	"Plus",
	"RealDiv",
	"Sub",
	"Id",
	"IntLit",
	"RealLit",
	"String"
};

void print_tree(Node *node, int level);
void print_points(int n);
void print_terminal(Node *node);

#endif
