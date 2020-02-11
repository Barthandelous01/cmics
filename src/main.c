#include "menu.h"
#include "imgs.c"
#include "coms.h"
#include "url.h"
#include "dirs.h"
#include "constants.h"

int main(void)
{

    /*
     * Initialization for main logic.
     * Mostly ncurses crap here.
     */

    /* ncurses init */
    initscr();
    clear();
    noecho();
    cbreak();
    raw();
    start_color();
    /* init color pairs */
    init_pair(ERROR, COLOR_RED, COLOR_BLACK);
    init_pair(SUCCESS, COLOR_GREEN, COLOR_BLACK);
    curs_set(0);		/* makes cursor invisible */

    /* Calculate size of window */
    int y, x;
    getmaxyx(stdscr, y, x);

    /* Temporary variables */
    int n_main_choices = 3;
    /* Window variables */
    WINDOW *my_win;
    WINDOW *comic_win;
    WINDOW *echo_buffer;
    WINDOW *load_output;
    /* Choice holding variables */
    int c1;
    int c2;
    /* result holding variables */
    int result1 = 0;
    int result2 = 0;
    /* current selection variables */
    int highlight_main = 1;
    int highlight_comics = 1;
    /* initializing new windows */
    my_win = newwin(y - 1, 21, 0, 0);
    comic_win = newwin(y - 1, 20, 0, 21);
    echo_buffer = newwin(1, x - 1, y - 1, 0);
    load_output = newwin(y - 1, x - 41, 0, 41);
    /* initialize keypads for windows */
    keypad(comic_win, TRUE);
    keypad(my_win, TRUE);
    refresh();			/* Refresh stdscr. necessary for showing other windows. */
    print_main_menu(my_win, highlight_main);
    wprintw(echo_buffer, "%s",
	    "Use the <up> and <down> keys to move, or press <a> to select all.");
    wrefresh(echo_buffer);

    /*
     * Main GUI logic loop.
     * someday, this might get multiple selections.
     */

    /* Main event loop */
    while (1) {
	if (result1 != 0)
	    goto MENU;		/* menu acheived, skip this loop */
	c1 = wgetch(my_win);
	switch (c1) {
	case KEY_UP:
	    if (highlight_main == 1)
           highlight_main = n_main_choices;
	    else
           --highlight_main;
	    break;
	case KEY_DOWN:
       if (highlight_main == n_main_choices)
            highlight_main = 1;
       else
            ++highlight_main;
       break;
	case 97:
       result1 = 999;
       break;
	case 10:
       result1 = highlight_main;
       break;
	default:
       break;
	}
	print_main_menu(my_win, highlight_main);
    MENU:if (result1 != 0) {
       print_comic_menu(comic_win, highlight_comics);
       while (1) {
            c2 = wgetch(comic_win);
            switch (c2) {
            case KEY_UP:
                 if (highlight_comics == 1)
                      highlight_comics = n_comics;
                 else
                      --highlight_comics;
                 break;
            case KEY_DOWN:
                 if (highlight_comics == n_comics)
                      highlight_comics = 1;
                 else
                      ++highlight_comics;
                 break;
            case 97:
                 result2 = 999;
                 break;
            case 10:
                 result2 = highlight_comics;
                 break;
            default:
                 break;
            }
            print_comic_menu(comic_win, highlight_comics);
            if (result2 != 0) {
                 goto LOGIC;
            }
       }
	}
    }
    /*
     * Goto out of the selection loop
     * (only way to not kill the loops, unfortunately).
     * main backend-logic
     * for downloading, and all that good stuff.
     */

    /* main downloading logic goes here */
    /* This starts the third window */
LOGIC:box(load_output, 0, 0);
    wrefresh(load_output);
    /* here's where directory checks and such go */
    int c = 1;			/* holds place for placement in download window */
    check_dirs(load_output, &c);
    switch (result1) {	/* first main switch */
    case 1:{
    case 2:{			/* start of 'download comics' */
         switch (result2) {
         case 1: {
              get_xkcd(load_output, &c);
         } break;
         case 2: {
              get_bc(load_output, &c);
         } break;
         case 999: {
              get_xkcd(load_output, &c);
              get_bc(load_output, &c);
         } break;
         }
    }	break;		/* end of 'download comics' */
    case 3:{			/* start of 'show comics' */
         switch (result2) {
         case 1: {
              show_img(XKCD_IMG);
         } break;
         case 2: {
              show_img(BC_IMG);
         } break;
         }
    } break;			/* end of 'remove comics' */
    }	break;		/* end of 'show comics' */
    case 999:{			/* begin 'show all' */
         printf("%d", c);
    }	break;		/* end 'show all' */
    }

    /*
     * This is the de-init.
     * Mostly ncurses crap, too.
     */

    /* delete windows */
    delwin(my_win);
    delwin(comic_win);
    delwin(echo_buffer);

    /* removes artifacts. Press any key to quit. */
    refresh();
    getch();
    endwin();
    return 0;
}
