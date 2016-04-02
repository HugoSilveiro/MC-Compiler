#ifndef _STRUCTURES_H
#define _STRUCTURES_H
/* types for the nodes */
typedef enum {
	NODE_Program,
	NODE_Declaration,
	//Declaração de variáveis
	NODE_ArrayDeclaration,
	NODE_FuncDeclaration,
	NODE_FuncDefinition,
	NODE_ParamList,
	NODE_FuncBody,
	NODE_ParamDeclaration,
	//Statement_List
	NODE_StatList,
	NODE_If,
	NODE_For,
	NODE_Return,

	//Operadores
	NODE_Or,
	NODE_And,
	NODE_Eq,
	NODE_Ne,
	NODE_Lt,
	NODE_Gt,
	NODE_Le,
	NODE_Ge,
	NODE_Add,
	NODE_Sub,
	NODE_Mul,
	NODE_Div,
	NODE_Mod,
	NODE_Not,
	NODE_Minus,
	NODE_Plus,
	NODE_Addr,
	NODE_Deref,
	NODE_Store,
	NODE_Comma,
	NODE_Call,

	//Terminais
	NODE_Int,
	NODE_Char,
	NODE_Pointer,
	NODE_Void,
	NODE_Id,
	NODE_Intlit,
	NODE_Chrlit,
	NODE_Strlit,

	//Especial
	NODE_NULL


} Node_Type;
typedef struct Node_elem{
	Node_Type node_type;
	struct Node_elem *child;
	struct Node_elem *brother;
	//char * node_type;
	char * value;

} Node;

#endif
