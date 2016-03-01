ID 				([a-z]|[A-Z]|"_")+([0-9]|[a-z]|[A-Z]|"_")*
INTLIT			[0-9]+
CHRLIT          [a-zA-Z]

%%

{CHRLIT}                            {printf("CHRLIT(%s)\n", yytext);}
{ID}								{printf("ID(%s)\n", yytext);}
{INTLIT}							{printf("INTLIT(%s)\n", yytext);}


%%
int main()
{
yylex();
return 0;
}

int yywrap()
{
return 1;
}
