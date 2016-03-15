%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

%}



%token ID

%%

start: FunctionDefinition

FunctionDefinition: ID  {$$ = $1; printf("%d\n", $1);}
	;
%%
