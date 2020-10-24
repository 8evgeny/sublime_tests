#include <sys/uio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE(array) (sizeof(array)/sizeof(array[0]))

int main (int argc, char ** argv)
{
       int i, fd;
       int tfields[] = {    100,     /* Name */
                            8,       /* Mode */
                            8,       /* UID */
                            8,       /* GID */
                            12 };    /* Size (octal) */

       struct iovec tarhead [ARR_SIZE(tfields)];

       if (argc < 2) {
              fprintf (stderr, "Too few arguments\n");
              return 1;
       }

       for (i = 0; i < ARR_SIZE (tfields); i++)
       {
              tarhead[i].iov_base = (char *)
                     malloc (sizeof (char) * tfields[i]);

              if (tarhead[i].iov_base == NULL) {
                     fprintf (stderr, "Cannot allocate "
                            "memory for tarhead[%d]\n", i);
                     return 1;
              }

              tarhead[i].iov_len = tfields[i];
       }

       fd = open (argv[1], O_RDONLY);
       if (fd == -1) {
              fprintf (stderr, "Cannot open file "
                            "(%s)\n", argv[1]);
              return 1;
       }

       if (readv (fd, tarhead, ARR_SIZE (tarhead)) <= 0) {
              fprintf (stderr, "Cannot read header\n");
              return 1;
       }

       printf ("name: %s\n", tarhead[0].iov_base);
       printf ("mode: %s\n", tarhead[1].iov_base);
       printf ("uid: %d\n", 
              strtol (tarhead[2].iov_base, NULL, 8));
       printf ("gid: %d\n", 
              strtol (tarhead[3].iov_base, NULL, 8));
       printf ("size: %d\n", 
              strtol (tarhead[4].iov_base, NULL, 8));	

       for (i = 0; i < ARR_SIZE (tarhead); i++)
              free (tarhead[i].iov_base);

       close (fd);
       return 0;
}
