#include <stdlib.h>
#include <stdio.h>

#define typename(x) _Generic((x),        /* Get the name of a type */             \
                                                                                  \
        _Bool: "_Bool",                  unsigned char: "unsigned char",          \
         char: "char",                     signed char: "signed char",            \
    short int: "short int",         unsigned short int: "unsigned short int",     \
          int: "int",                     unsigned int: "unsigned int",           \
     long int: "long int",           unsigned long int: "unsigned long int",      \
long long int: "long long int", unsigned long long int: "unsigned long long int", \
        float: "float",                         double: "double",                 \
  long double: "long double",                   char *: "pointer to char",        \
       void *: "pointer to void",                int *: "pointer to int",         \
      default: "other")

int main()
{
	int a;
    char b;
    char* c;
    int* d;
    void* e;

       printf("%s\n", typename(e||e));
    //printf("%s\n", typename(+e) );
    //printf("%s\n", typename(-e) );

    
	return 0;
}
