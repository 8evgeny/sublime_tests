#include <stdio.h>
#include "myenv.h"

int main (int argc, char ** argv)
{
       if (argc < 3) {
              fprintf (stderr, "Too few arguments\n");
              return 1;
       }
       mysetenv (argv[1], argv[2]);
       myprintenv (argv[1]);
       return 0;
}
