#include <stdlib.h>
#include <stdio.h>
#include "myenv.h"

void mysetenv (const char * name, const char * value)
{
       printf ("Setting variable %s\n", name);
       setenv (name, value, 1);
}
