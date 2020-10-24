#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <getopt.h>
#include <stdlib.h>

#define ARR_SIZE(array) (sizeof(array)/sizeof(array[0]))

int main (int argc, char ** argv)
{
       int i, opt, ifd, ofd = 1, nflag = 0;
       char ch;
       off_t pos;
       size_t count;
       char help_str[] = "Usage: readblock OPTIONS FILENAME\n"
              "OPTIONS:\n"
              "-h, --help\n"
              "-o, --output <filename>\n"
              "-p, --position <number>\n"
              "-c, --count <number>\n"
              "-n, --newline\n";

       char unkn_emsg[] = "Unknown error\n";
       char ifile_emsg[] = "Cannot open input file\n";
       char ofile_emsg[] = "Cannot open output file\n";
       char close_emsg[] = "Cannot close file\n";
       char lseek_emsg[] = "Cannot set I/O position\n";

       char * ofname = NULL;
       char * pos_str = NULL;
       char * count_str = NULL;

       const struct option long_opts[] = {
              { "help", no_argument, NULL, 'h' },
              { "output", required_argument, NULL, 'o' },
              { "position", required_argument, NULL, 'p' },
              { "count", required_argument, NULL, 'c' },
              { "newline", no_argument, NULL, 'n' },
              { NULL, 0, NULL, 0 }
       };

       while ((opt = getopt_long (argc, argv, "ho:p:c:n",
                            long_opts, NULL)) != -1) {
              switch (opt) {
                     case 'h':
                     write (1, help_str, ARR_SIZE (help_str));
                     return 0;

                     case 'o':
                     ofname = optarg;
                     break;

                     case 'p':
                     pos_str = optarg;
                     break;

                     case 'c':
                     count_str = optarg;
                     break;

                     case 'n':
                     nflag = 1;
                     break;

                     case '?':
                     write (2, help_str, ARR_SIZE (help_str));
                     return 1;

                     default:
                     write (2, unkn_emsg, ARR_SIZE (unkn_emsg));
                     return 2;
              }
       }

       if (count_str == NULL) {
              write (2, help_str, ARR_SIZE (help_str));
              return 3;
       }
       count = abs(atoi(count_str));

       if (pos_str != NULL) pos = abs (atoi (pos_str));
       else pos = 0;

       if (optind >= argc) {
              write (2, help_str, ARR_SIZE (help_str));
              return 4;
       }

       if (ofname != NULL) {
              ofd = open (ofname, O_WRONLY | O_CREAT | O_TRUNC,
                     S_IRUSR | S_IWUSR | S_IRGRP); /* 0640 */
              if (ofd == -1) {
                     write (2, ofile_emsg, ARR_SIZE (ofile_emsg));
                     return 5;
              }
       }

       ifd = open (argv[optind], O_RDONLY);
       if (ifd == -1) {
              write (2, ifile_emsg, ARR_SIZE (ifile_emsg));
              return 6;
       }

       if (pos > lseek (ifd, 0, SEEK_END)) {
              count = 0;
       }
       else if (lseek (ifd, pos, SEEK_SET) == -1) {
              write (2, lseek_emsg, ARR_SIZE (lseek_emsg));
              return 7;
       }

       for (i = 0; i < count; i++) {
              if (read (ifd, &ch, 1) <= 0) break;
              write (ofd, &ch, 1);
       }

       if (nflag) write (ofd, "\n", 1);

       if (close (ifd) == -1) {
              write (2, close_emsg, ARR_SIZE (close_emsg));
              return 8;
       }

       if (ofd != 1) {
              if (close (ofd) == -1) {
                     write (2, close_emsg, 
                            ARR_SIZE (close_emsg));
                     return 9;
              }
       }
       return 0;
}
