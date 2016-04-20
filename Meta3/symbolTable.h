

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
Symbol * create_symbol(char *name, char * type, int param);
void insert_symbol(Table * table, Symbol * symbol);
Symbol * search_symbol(char *name, Table * table);
Table * search_table(char * name);