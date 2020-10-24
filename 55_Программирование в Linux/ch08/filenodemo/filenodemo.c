#include <stdio.h>
#include <unistd.h>

#define ARR_SIZE(array) (sizeof(array)/sizeof(array[0]))
char buffer[4096];

int main (int argc, char ** argv)
{
       FILE * ifile;
       int fd;
       int nbytes;

       if (argc < 2) {
              fprintf (stderr, "Too few arguments\n");
              return 1;
       }

       ifile = fopen (argv[1], "r");
       if (ifile == NULL) {
              fprintf (stderr, "Cannot open file "
                                   "(%s)\n", argv[1]);
              return 1;
       }

       if ((fd = fileno (ifile)) == -1) {
              fprintf (stderr, "Cannot get descriptor\n");
              return 1;
       }

       while ((nbytes = read (fd, buffer, ARR_SIZE (buffer))) > 0)
                     write (1, buffer, nbytes);
       fclose (ifile);
       return 0;
}
