#include <stdio.h>
#include <stdlib.h>
#include <readver.h>
#include <toup.h>

int main (void)
{
       char * str = (char*) malloc (STR_SIZE * sizeof(char));
       if (str == NULL) {
              fprintf (stderr, "Cannot allocate memory\n");
              return 1;
       }

       if (readver (str) != 0) {
              fprintf (stderr, "Failed\n");
              return 1;
       }

       printf ("%s\n", str);
       toup (str);
       printf ("%s\n", str);
       free (str);
       return 0;
}
