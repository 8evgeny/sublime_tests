#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "print_up.h"

void print_up (const char * str)
{
       int i;
       for (i = 0; i < strlen (str); i++) 
              printf ("%c", toupper (str[i]));

       printf ("\n");
}
