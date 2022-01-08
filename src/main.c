#include <netdb.h>
#include <sqlite3.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#ifdef HAVE_CONFIG_H
#  include <config.h>
#else
#  define PACKAGE_STRING	/* silence errors */
#endif
#include <stdlib.h>
#include <getopt.h>

#include "curses.h"
#include "dirs.h"
#include "constants.h"
#include "logic.h"
#include "coms.h"



/* boilerplate functions */
static void usage()
{
	printf("%s", "\
The C based comics downloader\n\
\n\
USAGE:\n\
    cmics [Vha] [dsr]\n\
\n\
OPTIONS:\n\
-V, --version                   Print version info and exit\n\
-h, --help                      Print this  message and exit\n\
-r, --remove                    Remove comic files by name\n\
-s, --display                   Display comics by name\n\
-d, --download                  Download comics by name\n\
-a, --archive                   Display comic history\n\
-X, --proxy                     Set a proxy for libcurl\n\
\n\
Omission of any arguments starts an ncurses-based UI.");
	exit(0);
}

static void version()
{
	printf("%s", PACKAGE_STRING "\nCopyright (C) 2020-2022 Barthandelous01\n\
License RBSD 3-Clause License.\n\
This is free software; you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.");
	exit(0);
}

/* some utility functions */
static int callback (void *data, int argc, char **argv, char **azColName)
{
	int i;
	for(i = 0; i<argc; i++){
		if (strcmp(azColName[i], "COMIC")==0)
			printf("Comic: %s\n", argv[i]);
		else if (strcmp(azColName[i], "URL")==0)
			printf("Image URL: %s\n", argv[i]);
		else if (strcmp(azColName[i], "TIME")==0)
			printf("Time retreived: %s\n", argv[i]);
		else if (strcmp(azColName[i], "SUCCESS") == 0)
			if (atoi(argv[i]) != 0){
				printf("Download not successful.\n");
			}
	}
	printf("\n");
	return 0;
}

static int help()
{
	printf("%s", "\
I didn't recognize that. Available options are:\n\
\n\
    xkcd\n\
    bc\n\
    garfield\n\
    far_side\n\
    dilbert\n\
    family_circus\n\
    blondie\n\
    beetle_bailey\n\
    . (for every comic)\n");
	return 11;
}

static int com(char *name)
{
	if (strcmp(name, "xkcd") == 0)
		return 1;
	else if (strcmp(name, "bc") == 0)
		return 2;
	else if (strcmp(name, "garfield") == 0)
		return 3;
	else if (strcmp(name, "far_side") == 0)
		return 4;
	else if (strcmp(name, "dilbert") == 0)
		return 5;
	else if (strcmp(name, "family_circus") == 0)
		return 6;
	else if (strcmp(name, "blondie") == 0)
		return 7;
	else if (strcmp(name, "beetle_bailey") == 0)
		return 8;
	else if (strcmp(name, ".") == 0)
		return 999;
	else
		return help();
}

static void env_macro(char *macro, char *dest)
{
	strcpy(dest, getenv("HOME"));
	strcat(dest, macro);
}

/* main */
int main(int argc, char **argv)
{
	/* initialize database */
	sqlite3 *db;
	char *zZerrMsg = 0;
	int rc;
	char temp[100];
	env_macro(DB, temp);
	rc = sqlite3_open(temp, &db);
	if (rc) {
		fprintf(stderr, "%s: %s", "Couldn't open database", sqlite3_errmsg(db));
		return 1;
	} else {
		char *sql = "CREATE TABLE IF NOT EXISTS requests ("\
			"ID         INTEGER PRIMARY KEY AUTOINCREMENT,"\
			"COMIC      TEXT        NOT NULL,"\
			"SUCCESS    INTEGER     NOT NULL,"\
			"URL        TEXT        NOT NULL,"\
			"TIME       TEXT        NOT NULL"\
			");";
		rc = sqlite3_exec(db, sql, NULL, 0, &zZerrMsg);
		if (rc != SQLITE_OK) {
			fprintf (stderr, "%s:%s\n", "SQL error: ", zZerrMsg);
			sqlite3_free(zZerrMsg);
			return 1;
		}
	}

	/* This is commented out until I can do it through a proxy */
	/* do a very cursory check for internet connection */
	/* char *hostname; */
	/* struct hostent *hostinfo; */
	/* hostname = "archlinux.org"; */
	/* hostinfo = gethostbyname(hostname); */
	proxy = NULL;

	/* if (hostinfo == NULL) { */
	/* 	fprintf(stderr, "%s", "No internet connection found."); */
	/* 	exit(-1); */
	/* } */

	/* parse options */
	static int quiet = 0;
	static struct option longopts[] = {
		{"version",   no_argument,         NULL,    'V'},
		{"download",  required_argument,   NULL,    'd'},
		{"display",   required_argument,   NULL,    's'},
		{"remove",    required_argument,   NULL,    'r'},
		{"help",      no_argument,         NULL,    'h'},
		{"archive",   no_argument,         NULL,    'a'},
		{"proxy",     required_argument,   NULL,    'x'}
	};
	int ch = 0;
	while ((ch = getopt_long(argc, argv, "Vhad:s:r:x:", longopts, NULL)) != -1) {
		switch(ch) {
		case 'V':
			quiet = 1;
			version();
			break;
		case 'h':
			quiet = 1;
			usage();
			break;
		case 'x':
			proxy = argv[--optind];
			break;
		case 'd':
			quiet = 1;
			optind--;
			for ( ;optind < argc && *argv[optind] != '-'; optind++) {
				get_coms(NULL, 0, com(argv[optind]), db);
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
		case 'a':
			quiet = 1;
			char *sql_dump = "SELECT * FROM requests";
			rc = sqlite3_exec(db, sql_dump, callback, NULL, &zZerrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "SQL Error: %s\n", zZerrMsg);
				sqlite3_free(zZerrMsg);
				exit(1);
			}
			break;
		default:
			quiet = 1;
			break;
		}
	}
	if (quiet == 0) {
		do_curses_main(db);
	}

	/* if we made it this far, everything's working great! */
	sqlite3_close(db);
	return 0;
}
