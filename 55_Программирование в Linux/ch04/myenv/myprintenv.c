#include <stdlib.h>
#include <stdio.h>
#include "myenv.h"

void myprintenv (const char * name)
{
       char * value = getenv (name);
       if (value == NULL) {
              printf ("Variable %s doesn't exist\n");
              return;
       }
       printf ("%s=%s\n", name, value);
}
