#ifndef LOGIC_C_
#define LOGIC_C_

#include <stdio.h>
#include <string.h>

#include <ncurses.h>
#include <sqlite3.h>

#include "constants.h"
#include "imgs.h"
#include "utils.h"
#include "coms.h"

static void env_macro(char *macro, char *dest)
{
	strcpy(dest, getenv("HOME"));
	strcat(dest, macro);
}

static void rm (WINDOW *win, int *placement, char *file)
{
	int res = remove(file);
	char filename[200] = "";
	char rest[200] = "";
	strcpy(filename, file);
	strcpy(rest, file);
	error_print(win, placement, res, strcat(filename, " was deleted!"), strcat(rest, " was not deleted."));
}

/* This evil deserves explaining. According to the C standard, char * are
 * equivalent to void *, and vice versa. According to the POSIX standard,
 * a function pointer can be converted to a void* and back again. Therefore,
 * a function pointer can be converted to a char* (which is guarenteed to have
 * the same representation) and back again. */
char *file_locs[n_comics + 1][3] = {
	{NULL, NULL},
	{XKCD_HTML, XKCD_IMG, (char*)&get_xkcd},
	{BC_HTML, BC_IMG, (char*)&get_bc},
	{GARFIELD_HTML, GARFIELD_IMG, (char*)&get_garfield},
	{FAR_SIDE_HTML, FAR_SIDE_IMG, (char*)&get_far_side},
	{DILBERT_HTML, DILBERT_IMG, (char*)&get_dilbert},
	{FAMILY_CIRCUS_HTML, FAMILY_CIRCUS_IMG, (char*)&get_family_circus},
	{BLONDIE_HTML, BLONDIE_IMG, (char*)&get_blondie},
	{BEETLE_HTML, BEETLE_IMG, (char*)&get_beetle_bailey}
};

void rm_coms(WINDOW *win, int *c, int ccase)
{
	char temp[HOME_DIR_LEN];
	if (ccase != 999) {
		env_macro(file_locs[ccase][0], temp);
		rm(win, c, temp);
		env_macro(file_locs[ccase][1], temp);
		rm(win, c, temp);
	} else {
		for (int x = 1; x <= n_comics; x++)
			rm_coms(win, c, x);
	}
}

void get_coms(WINDOW *load_output, int *c, int ccase, sqlite3 *db)
{
	if (ccase != 999)
		((void(*)(WINDOW*, int*, sqlite3*))file_locs[ccase][2])(load_output, c, db);
	else
		for (int x = 1; x <= n_comics; x++)
			get_coms(load_output, c, x, db);
}

void show_coms(int ccase)
{
	char temp[HOME_DIR_LEN];
	if (ccase != 999) {
		env_macro(file_locs[ccase][1], temp);
		show_img(temp);
	} else {
		for (int x = 0; x <= 8; x++)
			show_coms(x);
	}
}

#endif /* LOGIC_C_ */
