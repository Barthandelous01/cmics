#include "curses.h"
#include "menu.h"
#include "dirs.h"
#include "constants.h"
#include "logic.h"
#include "cli.h"

#include <netdb.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <config.h>
#include <stdlib.h>
#include <getopt.h>

void usage()
{
     printf("%s", "\
The C based comics downloader\n\
\n\
USAGE:\n\
    cmics [Vh] [dsr]\n\
\n\
OPTIONS:\n\
-V, --version                   Print version info and exit\n\
-h, --help                      Print this  message and exit\n\
-r, --remove                    Remove comic files by name\n\
-s, --display                   Display comics by name\n\
-d, --download                  Download comics by name\n\
\n\
Omission of any arguments starts an ncurses-based UI.");
     exit(0);
}

void version()
{
     printf("%s", PACKAGE_STRING "\nCopyright (C) 2020 Barthandelous01\n\
License RBSD 3-Clause License.\n\
This is free software; you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.");
     exit(0);
}

int main(int argc, char **argv)
{
     /* do a very cursory check for internet connection */
     char *hostname;
     struct hostent *hostinfo;
     hostname = "archlinux.org";
     hostinfo = gethostbyname(hostname);
     
     if (hostinfo == NULL) {
         fprintf(stderr, "%s", "No internet connection found.");
         exit(-1);
     }

     /* parse options */
     static int quiet = 0;
     static struct option longopts[] = {
          {"version",   no_argument,         NULL,    'V'},
          {"download",  required_argument,   NULL,    'd'},
          {"display",   required_argument,   NULL,    's'},
          {"remove",    required_argument,   NULL,    'r'},
          {"help",      no_argument,         NULL,    'h'}
     };
     int ch = 0;
     while ((ch = getopt_long(argc, argv, "Vd:s:r:h", longopts, NULL)) != -1) {
          switch(ch) {
          case 'V':
               quiet = 1;
               version();
               break;
          case 'h':
               quiet = 1;
               usage();
               break;
          case 'd':
               quiet = 1;
               optind--;
               for ( ;optind < argc && *argv[optind] != '-'; optind++) {
                    get_coms(NULL, 0, com(argv[optind]));
               }
               break;
          case 's':
               quiet = 1;
               optind--;
               for ( ;optind < argc && *argv[optind] != '-'; optind++) {
                    show_coms(com(argv[optind]));
               }
               break;
          case 'r':
               quiet = 1;
               optind--;
               for ( ;optind < argc && *argv[optind] != '-'; optind++) {
                    rm_coms(NULL, 0, com(argv[optind]));
               }
               break;
          default:
               quiet = 1;
               break;
          }
     }
     if (quiet == 0) {
          do_curses_main();
     }

     /* if we made it this far, everything's working great! */
     return 0;
}
