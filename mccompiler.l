ID 				([a-z]|[A-Z]|"_")+([0-9]|[a-z]|[A-Z]|"_")*
INTLIT			[0-9]+
CHRLIT          [a-zA-Z]

%%


"{"									{printf("LBRACE\n");}
"<="								{printf("LE\n");}
"("									{printf("LPAR\n");}
"["									{printf("LSQ\n");}
"<"									{printf("LT\n");}
"-"									{printf("MINUS\n");}
"%" 								{printf("MOD\n");}
"!="								{printf("NE\n");}
"!"									{printf("NOT\n");}
"||" 								{printf("OR\n");}
"+" 								{printf("PLUS\n");}
"}"									{printf("RBRACE\n");}
"return" 							{printf("RETURN\n");}
")"									{printf("RPAR\n");}
"]"									{printf("RSQ\n");}
";"									{printf("SEMI\n");}
"void"								{printf("VOID\n");}
"++"								{printf("RESERVED\n");}


{CHRLIT}                            {printf("CHRLIT(%s)\n", yytext);}
{ID}								{printf("ID(%s)\n", yytext);}
{INTLIT}							{printf("INTLIT(%s)\n", yytext);}

%%
int main(int argc, char* argv[])
{
if(argc>1)
{
	if(strcmp(argv[1], "-l")==0)
{
	yylex();

}
}
return 0;
}

int yywrap()
{
return 1;
}
