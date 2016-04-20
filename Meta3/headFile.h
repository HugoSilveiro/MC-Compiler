
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
	"StrLit"

	"Null"
};

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

void print_tree(Node *node, int level);
void print_points(int n);
void print_terminal(Node *node);

Node * insert_node(Node_Type node_type);
Node * insert_term_node(Node_Type node_type, char* value);
void insert_child(Node * father, Node * child, int end);
void insert_brother(Node * node, Node * brother);
void changeOrder(Node * father,Node * child);


