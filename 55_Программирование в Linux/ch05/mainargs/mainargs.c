#include <stdio.h>

int main (int a, char ** b)
{
       int i;
       for (i = 0; i < a; i++)
              printf ("%d: %s\n", i, b[i]);
       return 0;
}
