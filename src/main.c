#include "menu.h"
#include "imgs.c"
#include "coms.h"
#include "url.h"
#include "dirs.h"
#include "constants.h"
#include "rm.c"

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
          /* remove comics */
          switch (result2) {
          case 1: {
               rm(load_output, &c, XKCD_IMG);
               rm(load_output, &c, XKCD_HTML);
          } break;
          case 2: {
               rm(load_output, &c, BC_IMG);
               rm(load_output, &c, BC_HTML);
          } break;
          case 3: {
               rm(load_output, &c, GARFIELD_IMG);
               rm(load_output, &c, GARFIELD_HTML);
          } break;
          case 4: {
               rm(load_output, &c, FAR_SIDE_IMG);
               rm(load_output, &c, FAR_SIDE_HTML);
          } break;
          case 5: {
               rm(load_output, &c, DILBERT_IMG);
               rm(load_output, &c, DILBERT_HTML);
          } break;
          case 999: {
               rm(load_output, &c, XKCD_IMG);
               rm(load_output, &c, XKCD_HTML);
               rm(load_output, &c, BC_IMG);
               rm(load_output, &c, BC_HTML);
               rm(load_output, &c, GARFIELD_IMG);
               rm(load_output, &c, GARFIELD_HTML);
               rm(load_output, &c, FAR_SIDE_IMG);
               rm(load_output, &c, FAR_SIDE_HTML);
               rm(load_output, &c, DILBERT_IMG);
               rm(load_output, &c, DILBERT_HTML);
          } break;
          }
          /* end remove comics */
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
          case 999: {
               get_xkcd(load_output, &c);
               get_bc(load_output, &c);
               get_garfield(load_output, &c);
               get_far_side(load_output, &c);
               get_dilbert(load_output, &c);
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
          case 999: {
               show_img(XKCD_IMG);
               show_img(BC_IMG);
               show_img(GARFIELD_IMG);
               show_img(FAR_SIDE_IMG);
               show_img(DILBERT_IMG);
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
