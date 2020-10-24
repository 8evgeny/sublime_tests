#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "toup.h"

void toup (char * str)
{
       int i;
       for (i = 0; i < strlen (str); i++)
              str[i] = toupper (str[i]);	
}
