

#include "struct.h"

typedef struct _Table{
	int type;
	struct _Symbol *child;
	struct _Table *next;
} Table;


typedef struct _Symbol{
	char * name;
	char * type;
	int param;
	struct _Symbol *next;
} Symbol;


void start_symbol_table();
void insert_table(int type);