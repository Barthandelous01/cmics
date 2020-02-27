#include "menu.h"
#include "imgs.h"
#include "coms.h"
#include "url.h"
#include "dirs.h"
#include "constants.h"
#include "logic.h"

int main(void)
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
          /* download comics */
          switch (result2) {
          case 1: {
               get_xkcd(load_output, &c);
          } break;
          case 2: {
               get_bc(load_output, &c);
          } break;
          case 3: {
               get_garfield(load_output, &c);
          } break;
          case 4: {
               get_far_side(load_output, &c);
          } break;
          case 5: {
               get_dilbert(load_output, &c);
          } break;
          case 6: {
               get_family_circus(load_output, &c);
          } break;
          case 7: {
               get_blondie(load_output, &c);
          } break;
          case 8: {
               get_beetle_bailey(load_output, &c);
          } break;
          case 999: {
               get_xkcd(load_output, &c);
               get_bc(load_output, &c);
               get_garfield(load_output, &c);
               get_far_side(load_output, &c);
               get_dilbert(load_output, &c);
               get_family_circus(load_output, &c);
               get_blondie(load_output, &c);
               get_beetle_bailey(load_output, &c);
          } break;
          }
          /* end download comics */
     } break;

     case 3:{
          /* show comics */
          switch (result2) {
          case 1: {
               show_img(XKCD_IMG);
          } break;
          case 2: {
               show_img(BC_IMG);
          } break;
          case 3: {
               show_img(GARFIELD_IMG);
          } break;
          case 4: {
               show_img(FAR_SIDE_IMG);
          } break;
          case 5: {
               show_img(DILBERT_IMG);
          } break;
          case 6: {
               show_img(FAMILY_CIRCUS_IMG);
          } break;
          case 7: {
               show_img(BLONDIE_IMG);
          } break;
          case 8: {
               show_img(BEETLE_IMG);
          } break;
          case 999: {
               show_img(XKCD_IMG);
               show_img(BC_IMG);
               show_img(GARFIELD_IMG);
               show_img(FAR_SIDE_IMG);
               show_img(DILBERT_IMG);
               show_img(FAMILY_CIRCUS_IMG);
               show_img(BLONDIE_IMG);
               show_img(BEETLE_IMG);
          } break;
          }
          /* end show comics */
     } break;

     case 999:{
          /* begin all main menu */
          /* This'll be last, until all the others are built in */
          switch (result2) {
          case 1: {
               rm(load_output, &c, XKCD_IMG);
               rm(load_output, &c, XKCD_HTML);
               get_xkcd(load_output, &c);
               show_img(XKCD_IMG);
          } break;
          case 2: {
               rm(load_output, &c, BC_IMG);
               rm(load_output, &c, BC_HTML);
               get_bc(load_output, &c);
               show_img(BC_IMG);
          } break;
          case 3: {
               rm(load_output, &c, GARFIELD_IMG);
               rm(load_output, &c, GARFIELD_HTML);
               get_garfield(load_output, &c);
               show_img(GARFIELD_IMG);
          } break;
          case 4: {
               rm(load_output, &c, FAR_SIDE_IMG);
               rm(load_output, &c, FAR_SIDE_HTML);
               get_far_side(load_output, &c);
               show_img(FAR_SIDE_IMG);
          } break;
          case 5: {
               rm(load_output, &c, DILBERT_IMG);
               rm(load_output, &c, DILBERT_HTML);
               get_dilbert(load_output, &c);
               show_img(DILBERT_IMG);
          } break;
          case 6: {
               rm(load_output, &c, FAMILY_CIRCUS_IMG);
               rm(load_output, &c, FAMILY_CIRCUS_HTML);
               get_family_circus(load_output, &c);
               show_img(FAMILY_CIRCUS_IMG);
          } break;
          case 7: {
               rm(load_output, &c, BLONDIE_IMG);
               rm(load_output, &c, BLONDIE_HTML);
               get_blondie(load_output, &c);
               show_img(BLONDIE_IMG);
          } break;
          case 8: {
               rm(load_output, &c, BEETLE_IMG);
               rm(load_output, &c, BEETLE_HTML);
               get_beetle_bailey(load_output, &c);
               show_img(BEETLE_IMG);
          } break;
          case 999: {
               rm(load_output, &c, XKCD_IMG);
               rm(load_output, &c, XKCD_HTML);
               get_xkcd(load_output, &c);
               show_img(XKCD_IMG);
               rm(load_output, &c, BC_IMG);
               rm(load_output, &c, BC_HTML);
               get_bc(load_output, &c);
               show_img(BC_IMG);
               rm(load_output, &c, GARFIELD_IMG);
               rm(load_output, &c, GARFIELD_HTML);
               get_garfield(load_output, &c);
               show_img(GARFIELD_IMG);
               rm(load_output, &c, FAR_SIDE_IMG);
               rm(load_output, &c, FAR_SIDE_HTML);
               get_far_side(load_output, &c);
               show_img(FAR_SIDE_IMG);
               rm(load_output, &c, DILBERT_IMG);
               rm(load_output, &c, DILBERT_HTML);
               get_dilbert(load_output, &c);
               show_img(DILBERT_IMG);
               rm(load_output, &c, FAMILY_CIRCUS_IMG);
               rm(load_output, &c, FAMILY_CIRCUS_HTML);
               get_family_circus(load_output, &c);
               show_img(FAMILY_CIRCUS_IMG);
               rm(load_output, &c, BLONDIE_IMG);
               rm(load_output, &c, BLONDIE_HTML);
               get_blondie(load_output, &c);
               show_img(BLONDIE_IMG);
               rm(load_output, &c, BEETLE_IMG);
               rm(load_output, &c, BEETLE_HTML);
               get_beetle_bailey(load_output, &c);
               show_img(BEETLE_IMG);
          } break;
          }
          /* end all main menu */
     }	break;
     }

     /*
      * This is the de-init.
      * Mostly ncurses crap, too.
      */

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
     return 0;
}
