#ifndef LOGIC_C_
#define LOGIC_C_

#include <ncurses.h>
#include <stdio.h>
#include <string.h>
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

/* how I wish there was a better way... */
void rm_coms(WINDOW *win, int *c, int ccase)
{
	char temp[200];
	switch (ccase) {
	case 1: {
		env_macro(XKCD_HTML, temp);
		rm(win, c, temp);
		env_macro(XKCD_IMG, temp);
		rm(win, c, temp);
	} break;
	case 2: {
		env_macro(BC_HTML, temp);
		rm(win, c, temp);
		env_macro(BC_IMG, temp);
		rm(win, c, temp);
	} break;
	case 3: {
		env_macro(GARFIELD_HTML, temp);
		rm(win, c, temp);
		env_macro(GARFIELD_IMG, temp);
		rm(win, c, temp);
	} break;
	case 4: {
		env_macro(FAR_SIDE_HTML, temp);
		rm(win, c, temp);
		env_macro(FAR_SIDE_IMG, temp);
		rm(win, c, temp);
	} break;
	case 5: {
		env_macro(DILBERT_HTML, temp);
		rm(win, c, temp);
		env_macro(DILBERT_IMG, temp);
		rm(win, c, temp);
	} break;
	case 6: {
		env_macro(FAMILY_CIRCUS_HTML, temp);
		rm(win, c, temp);
		env_macro(FAMILY_CIRCUS_IMG, temp);
		rm(win, c, temp);
	} break;
	case 7: {
		env_macro(BLONDIE_HTML, temp);
		rm(win, c, temp);
		env_macro(BLONDIE_IMG, temp);
		rm(win, c, temp);
	} break;
	case 8: {
		env_macro(BEETLE_HTML, temp);
		rm(win, c, temp);
		env_macro(BEETLE_IMG, temp);
		rm(win, c, temp);
	} break;
	case 999: {
		for (int x = 1; x <= 8; x++)
			rm_coms(win, c, x);
	} break;
	}

}

void get_coms(WINDOW *load_output, int *c, int ccase, sqlite3 *db)
{
	switch (ccase) {
	case 1: {
		get_xkcd(load_output, c, db);
	} break;
	case 2: {
		get_bc(load_output, c, db);
	} break;
	case 3: {
		get_garfield(load_output, c, db);
	} break;
	case 4: {
		get_far_side(load_output, c, db);
	} break;
	case 5: {
		get_dilbert(load_output, c, db);
	} break;
	case 6: {
		get_family_circus(load_output, c, db);
	} break;
	case 7: {
		get_blondie(load_output, c, db);
	} break;
	case 8: {
		get_beetle_bailey(load_output, c, db);
	} break;
	case 999: {
		for (int x = 1; x <= 8; x++)
			get_coms(load_output, c, x, db);
	} break;
	}
}

void show_coms(int ccase)
{
	char temp[200];
	switch (ccase) {
	case 1: {
		env_macro(XKCD_IMG, temp);
		show_img(temp);
	} break;
	case 2: {
		env_macro(BC_IMG, temp);
		show_img(temp);
	} break;
	case 3: {
		env_macro(GARFIELD_IMG, temp);
		show_img(temp);
	} break;
	case 4: {
		env_macro(FAR_SIDE_IMG, temp);
		show_img(temp);
	} break;
	case 5: {
		env_macro(DILBERT_IMG, temp);
		show_img(temp);
	} break;
	case 6: {
		env_macro(FAMILY_CIRCUS_IMG, temp);
		show_img(temp);
	} break;
	case 7: {
		env_macro(BLONDIE_IMG, temp);
		show_img(temp);
	} break;
	case 8: {
		env_macro(BEETLE_IMG, temp);
		show_img(temp);
	} break;
	case 999: {
		for (int x = 0; x <= 8; x++)
			show_coms(x);
	} break;
	}
}

#endif /* LOGIC_C_ */
