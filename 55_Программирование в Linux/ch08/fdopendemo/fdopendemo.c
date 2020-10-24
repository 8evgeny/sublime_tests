#include <stdio.h>
#include <fcntl.h>

int main (int argc, char ** argv)
{
       int fd;
       FILE * ifile;
       char ch;

       if (argc < 2) {
              fprintf (stderr, "Too few arguments\n");
              return 1;
       }

       fd = open (argv[1], O_RDONLY);
       if (fd == -1) {
              fprintf (stderr, "Cannot open file "
                            "(%s)\n", argv[1]);
              return 2;
       }

       ifile = fdopen (fd, "r");
       if (ifile == NULL) {
              fprintf (stderr, "Cannot create file pointer\n");
              return 3;
       }

       while ((ch = fgetc (ifile)) != EOF)
              fputc (ch, stdout);

       close (fd);
       return 0;
}
