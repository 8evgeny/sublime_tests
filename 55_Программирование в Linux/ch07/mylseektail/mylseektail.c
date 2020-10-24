#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUF_SIZE 4096
char buffer[BUF_SIZE];

int main (int argc, char ** argv)
{
       int fd;
       off_t nback;
       ssize_t nbytes;
       char arg_emsg[] = "Too few arguments\n";
       char file_emsg[] = "Cannot open input file\n";
       char close_emsg[] = "Cannot close file\n";	

       if (argc < 3) {
              write (2, arg_emsg, strlen (arg_emsg));
              return 1;
       }

       fd = open (argv[1], O_RDONLY);
       if (fd == -1) {
              write (2, file_emsg, strlen (file_emsg));
              return 1;
       }

       nback = abs (atoi (argv[2]));	
       lseek (fd, 0, SEEK_END);
       if (nback > lseek (fd, 0, SEEK_CUR))
              lseek (fd, 0, SEEK_SET);
       else
              lseek (fd, -nback, SEEK_END);

       while ((nbytes = read (fd, buffer, BUF_SIZE)) > 0)
              write (1, buffer, nbytes);

       if (close (fd) == -1) {
              write (2, close_emsg, strlen (close_emsg));
              return 1;
       }
       return 0;
}
