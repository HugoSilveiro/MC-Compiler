#ifndef _STRUCTURES_H
#define _STRUCTURES_H

/* types for the nodes */
typedef enum {
	NODE_PROGRAM,
	NODE_VAR_PART,
	NODE_FUNC_PART,
	NODE_VAR_DECL,
	NODE_FUNC_DECL,
	NODE_FUNC_DEF,
	NODE_FUNC_DEF_2,
	NODE_FUNC_PARAMS,
	NODE_PARAMS,
	NODE_VAR_PARAMS,
	NODE_ASSIGN,
	NODE_IF_ELSE,
	NODE_REPEAT,
	NODE_STAT_LIST,
	NODE_VAL_PARAM,
	NODE_WHILE,
	NODE_WRITE_LN,
	NODE_ADD,		/* addition */
	NODE_AND,
	NODE_CALL,
	NODE_DIV,		/* division with truncation; op = 'div';  result = integer-type; ISO 7185-page 54 */
	NODE_EQ,
	NODE_GEQ,
	NODE_GT,
	NODE_LEQ,
	NODE_LT,
	NODE_MINUS,		/* sign-inversion (minus sign) */
	NODE_MOD,		/* modulo */
	NODE_MUL,		/* multiplication */
	NODE_NEQ,
	NODE_NOT,
	NODE_OR,
	NODE_PLUS,		/* identity (plus sign) */
	NODE_REAL_DIV,	/* normal division; op = '/'; result = real-type; ISO 7185-page 54 */
	NODE_SUB,		/* subtraction */
	NODE_ID,
	NODE_INTLIT,
	NODE_CHRLIT,
	NODE_STRLIT,
	NODE_NULL		/* used for temp nodes */

} Node_Type;
typedef struct Node_elem{
	Node_Type node_type;
	struct Node_elem *child;
	struct Node_elem *brother;
	//char * node_type;
	char * value;

} Node;

#endif
