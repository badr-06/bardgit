#include <stdlib.h>

 

int main()

{

    int *p1 = (int*)malloc(16 * sizeof(int));

    p1 = func(p1);

    free(p1);

}

 

int * func(int *p)

{

   *p++ = 0;

   return p;

 }