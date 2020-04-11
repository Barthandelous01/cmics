#include "menu.h"
#include "dirs.h"
#include "constants.h"
#include "logic.h"

#include <ncurses.h>

/* variable for menu items */
static char *main_menu[] = {
     "Remove old comics",
     " Download comics ",
     "   View comics   "
};


/* Variable for menu formatting */
static char *comics[] = {
     "     XKCD      ",
     "      BC       ",
     "    Garfield   ",
     "  The Far Side ",
     "    Dilbert    ",
     " Family Circus ",
     "    Blondie    ",
     " Beetle Bailey "
};

void do_curses_main()
{
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

     /* Window variables */
     WINDOW *my_win;
     WINDOW *comic_win;
     WINDOW *echo_buffer;
     WINDOW *load_output;

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

     /* set echo buffer */
     print_menu(my_win, highlight_main, comics, n_main_choices);
     wprintw(echo_buffer, "%s",
             "Use the <up> and <down> keys to move, or press <a> to select all.");
     wrefresh(echo_buffer);

     /* Gets results for menu */
     result1 = get_menu(my_win, &highlight_main, n_main_choices, main_menu);
     result2 = get_menu(comic_win, &highlight_comics, n_comics, comics);

     /* main downloading logic goes here */

     /* This starts the third window */
     box(load_output, 0, 0);
     wrefresh(load_output);
     /* here's where directory checks and such go */
     int c = 1;			/* holds place for placement in download window */
     check_dirs(load_output, &c);
     switch (result1) {	/* first main switch */
     case 1:{
          rm_coms(load_output, &c, result2);
     }	break;

     case 2: {
          rm_coms(load_output, & c, result2);
     } break;

     case 3:{
          show_coms(result2);
     } break;
          /* end show comics */

     case 999:{
          rm_coms(load_output, &c, result2);
          get_coms(load_output, &c, result2);
          show_coms(result2);
     } break;
     }

     /* delete windows */
     delwin(my_win);
     delwin(comic_win);
     delwin(load_output);
     wmove(echo_buffer, 0,0);
     wprintw(echo_buffer, "%s",
             "Press any key to quit.                                                                 ");
     wrefresh(echo_buffer);

     /* removes artifacts. Press any key to quit. */
     refresh();
     getch();
     delwin(echo_buffer);
     endwin();
}
