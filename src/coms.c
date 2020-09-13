#ifndef COMS_C_
#define COMS_C_

#include <string.h>
#include <time.h>
#include <sqlite3.h>
#include <stdlib.h>

#include "com_reg.h"
#include "constants.h"
#include "url.h"
#include "utils.h"

static int log_sql(sqlite3 *db, char *name, int success, char *url)
{
     int rc;
     char *errMsg = 0;
     char *command = malloc(500);
     if (command == NULL) {
          fprintf (stderr, "%s", "Error allocating memory for SQL command.\n");
          exit(-1);
     }

     /* time */
     time_t curtime;
     struct tm *loc_time;
     curtime = time (NULL);
     loc_time = localtime(&curtime);

     /* build command */
     sprintf(command, "INSERT INTO requests (COMIC, SUCCESS, URL, TIME) "\
             "VALUES ('%s', %d, '%s', '%s');", name, success, url, asctime(loc_time));

     rc = sqlite3_exec(db, command, NULL, 0, &errMsg);

     if (rc != SQLITE_OK) {
          fprintf (stderr, "SQL Error: %s\n", errMsg);
          sqlite3_free(errMsg);
          exit(1);
     }
     free(command);
     return 0;
}

char *env_macro(char *macro)
{
     char *result = (char *)malloc(200 + strlen(macro));
     if (result == NULL) {
         fprintf(stderr, "%s", "Error allocating memory.");
         exit(-1);
     }
     strcpy(result, getenv("HOME"));
     strcat(result, macro);
     return result;
}

int get_xkcd(WINDOW * win, int *placement, sqlite3 *db)
{
     win_print(win, placement, 2, "===> XKCD");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://xkcd.com/", env_macro(XKCD_HTML));
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     url = get_com_url(env_macro(XKCD_HTML), "https://imgs.xkcd.com/comics/[^2]*.png");
     win_print(win, placement, 2, "==> Downloading image");
     int res2 = get_url(url, env_macro(XKCD_IMG));
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     log_sql(db, "xkcd", res2, url);
     free(url);
     return 0;
}

int get_bc(WINDOW *win, int *placement, sqlite3 *db)
{
     win_print(win, placement, 2, "===> BC");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://johnhartstudios.com/bc/", env_macro(BC_HTML));
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     char final[100] = "https://johnhartstudios.com";
     url = get_com_url(env_macro(BC_HTML), "/bcstrips/[^\"]*");
     strcat(final, url);
     win_print(win, placement, 2, "==> Downloading image");
     int res2 = get_url(final, env_macro(BC_IMG));
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     log_sql(db, "bc", res2, final);
     free(url);
     return 0;
}

int get_garfield(WINDOW *win, int *placement, sqlite3 *db)
{
     win_print(win, placement, 2, "===> Garfield");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://www.gocomics.com/garfield/", env_macro(GARFIELD_HTML));
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     url = get_com_url(env_macro(GARFIELD_HTML), "https://assets.amuniversal.com/[1234567890abcde]*");
     win_print(win, placement, 2, "==> Downloading image");
     int res2 = get_url(url, env_macro(GARFIELD_IMG));
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     log_sql(db, "garfield", res2, url);
     free(url);
     return 0;
}

int get_far_side (WINDOW *win, int *placement, sqlite3 *db)
{
     win_print(win, placement, 2, "===> The Far Side");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://www.thefarside.com", env_macro(FAR_SIDE_HTML));
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     url = get_com_url(env_macro(FAR_SIDE_HTML), "https://assets.thefarside.com/uploads/splash[^\"]*.(png|gif|jpg)");
     win_print(win, placement, 2, "==> Downloading image");
     int res2 = get_url(url, env_macro(FAR_SIDE_IMG));
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     log_sql(db, "far_side", res2, url);
     free(url);
     return 0;
}

int get_dilbert (WINDOW *win, int *placement, sqlite3 *db)
{
     win_print(win, placement, 2, "===> Dilbert");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://dilbert.com", env_macro(DILBERT_HTML));
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     url = get_com_url(env_macro(DILBERT_HTML), "assets.amuniversal.com/([a-f]|[[:digit:]]){32}");
     char *final = NULL;
     final = malloc(150);
     strcpy(final, "https://");
     strcat(final, url);
     win_print(win, placement, 2, "==> Downloading image");
     int res2 = get_url(final, env_macro(DILBERT_IMG));
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     log_sql(db, "dilbert", res2, final);
     free(final);
     free(url);
     return 0;
}

int get_family_circus(WINDOW *win, int *placement, sqlite3 *db)
{
     win_print(win, placement, 2, "===> Family Circus");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://www.arcamax.com/thefunnies/familycircus/", env_macro(FAMILY_CIRCUS_HTML));
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     char final[200] = "https://www.arcamax.com/";
     url = get_com_url(env_macro(FAMILY_CIRCUS_HTML), "/newspics/[^&\"]*.(jpg|gif|png)");
     win_print(win, placement, 2, "==> Downloading image");
     strcat(final, url);
     int res2 = get_url(final, env_macro(FAMILY_CIRCUS_IMG));
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     log_sql(db, "family_circus", res2, final);
     free(url);
     return 0;
}

int get_beetle_bailey(WINDOW *win, int *placement, sqlite3 *db)
{
     win_print(win, placement, 2, "===> Beetle Bailey");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://www.arcamax.com/thefunnies/beetlebailey", env_macro(BEETLE_HTML));
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     char final[200] = "https://www.arcamax.com/";
     url = get_com_url(env_macro(BEETLE_HTML), "/newspics/[^n&]*.(gif|jpg|png)");
     win_print(win, placement, 2, "==> Downloading image");
     strcat(final, url);
     int res2 = get_url(final, env_macro(BEETLE_IMG));
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     log_sql(db, "beetle_bailey", res2, final);
     free(url);
     return 0;
}

int get_blondie(WINDOW *win, int *placement, sqlite3 *db)
{
     win_print(win, placement, 2, "===> Blondie");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://www.arcamax.com/thefunnies/blondie", env_macro(BLONDIE_HTML));
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     char final[200] = "https://www.arcamax.com/";
     url = get_com_url(env_macro(BLONDIE_HTML), "/newspics/[^n&]*.jpg");
     win_print(win, placement, 2, "==> Downloading image");
     strcat(final, url);
     int res2 = get_url(final, env_macro(BLONDIE_IMG));
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     log_sql(db, "blondie", res2, final);
     free(url);
     return 0;
}

#endif    /* COMS_C_ */
