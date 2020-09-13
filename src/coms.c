#ifndef COMS_C_
#define COMS_C_

#include <string.h>
#include <time.h>
#include <sqlite3.h>
#include <stdio.h>		// not sure if this is truly necessary, but...
#include <stdlib.h>
#include <curl/curl.h>
#include <regex.h>

#include "constants.h"
#include "utils.h"

static int get_url(char *url, char *file)
{
     FILE *fp = NULL;
     CURL *handle = curl_easy_init();
     if (handle) {
          fp = fopen(file, "w");
          if (fp) {
               curl_easy_setopt(handle, CURLOPT_URL, url);
               curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, NULL);
               curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);
          } else {
               return 1;
          }
     } else {
          return 1;
     }
     CURLcode result = curl_easy_perform(handle);
     if (result)
          return 1;

     curl_easy_cleanup(handle);
     fclose(fp);
     return 0;
}

static char *regexp(char *string, char *patrn, int *begin, int *end)
{
    int i, w = 0, len;
    char *word = NULL;
    regex_t rgT;
    regmatch_t match;
    regcomp(&rgT, patrn, REG_EXTENDED);
    if ((regexec(&rgT, string, 1, &match, 0)) == 0) {
         *begin = (int) match.rm_so;
         *end = (int) match.rm_eo;
         len = *end - *begin;
         word = malloc(len + 1);
         for (i = *begin; i < *end; i++) {
              word[w] = string[i];
              w++;
         }
         word[w] = 0;
    }
    regfree(&rgT);
    return word;
}

static char *get_com_url(char *file /* to search */ ,
                  char *pattern /* to search file for */ )
{
     /* open file */
     char *buffer = 0;
     FILE *fp;
     fp = fopen(file, "r+");
     /* get size of file for buffer */
     if (fp) {
          fseek(fp, 0, SEEK_END);
          int length = ftell(fp);
          fseek(fp, 0, SEEK_SET);
          buffer = malloc(length);
          if (buffer) {
               fread(buffer, 1, length, fp);
          }
     }
     /* init variables for regex */
     int b, e;
     /* perform regex */
     char *url;
     url = regexp(buffer, pattern, &b, &e);
     /* extract answer */
     fclose(fp);
     free(buffer);
     return url;
}

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

static void env_macro(char *macro, char *dest)
{
     strcpy(dest, getenv("HOME"));
     strcat(dest, macro);
}

int get_xkcd(WINDOW * win, int *placement, sqlite3 *db)
{
     char temp[200];
     env_macro(XKCD_HTML, temp);
     win_print(win, placement, 2, "===> XKCD");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://xkcd.com/", temp);
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     url = get_com_url(temp, "https://imgs.xkcd.com/comics/[^2]*.png");
     win_print(win, placement, 2, "==> Downloading image");
     env_macro(XKCD_IMG, temp);
     int res2 = get_url(url, temp);
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     log_sql(db, "xkcd", res2, url);
     free(url);
     return 0;
}

int get_bc(WINDOW *win, int *placement, sqlite3 *db)
{
     char temp[200];
     env_macro(BC_HTML, temp);
     win_print(win, placement, 2, "===> BC");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://johnhartstudios.com/bc/", temp);
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     char final[100] = "https://johnhartstudios.com";
     url = get_com_url(temp, "/bcstrips/[^\"]*");
     strcat(final, url);
     win_print(win, placement, 2, "==> Downloading image");
     env_macro(BC_IMG, temp);
     int res2 = get_url(final, temp);
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     log_sql(db, "bc", res2, final);
     free(url);
     return 0;
}

int get_garfield(WINDOW *win, int *placement, sqlite3 *db)
{
     char temp[200];
     env_macro(GARFIELD_HTML, temp);
     win_print(win, placement, 2, "===> Garfield");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://www.gocomics.com/garfield/", temp);
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     url = get_com_url(temp, "https://assets.amuniversal.com/[1234567890abcde]*");
     win_print(win, placement, 2, "==> Downloading image");
     env_macro(GARFIELD_IMG, temp);
     int res2 = get_url(url, temp);
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     log_sql(db, "garfield", res2, url);
     free(url);
     return 0;
}

int get_far_side (WINDOW *win, int *placement, sqlite3 *db)
{
     char temp[200];
     env_macro(FAR_SIDE_HTML, temp);
     win_print(win, placement, 2, "===> The Far Side");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://www.thefarside.com", temp);
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     url = get_com_url(temp, "https://assets.thefarside.com/uploads/splash[^\"]*.(png|gif|jpg)");
     env_macro(FAR_SIDE_IMG, temp);
     win_print(win, placement, 2, "==> Downloading image");
     int res2 = get_url(url, temp);
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     log_sql(db, "far_side", res2, url);
     free(url);
     return 0;
}

int get_dilbert (WINDOW *win, int *placement, sqlite3 *db)
{
     char temp[200];
     env_macro(DILBERT_HTML, temp);
     win_print(win, placement, 2, "===> Dilbert");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://dilbert.com", temp);
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     url = get_com_url(temp, "assets.amuniversal.com/([a-f]|[[:digit:]]){32}");
     env_macro(DILBERT_IMG, temp);
     char *final = NULL;
     final = malloc(150);
     strcpy(final, "https://");
     strcat(final, url);
     win_print(win, placement, 2, "==> Downloading image");
     int res2 = get_url(final, temp);
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     log_sql(db, "dilbert", res2, final);
     free(final);
     free(url);
     return 0;
}

int get_family_circus(WINDOW *win, int *placement, sqlite3 *db)
{
     char temp[200];
     env_macro(FAMILY_CIRCUS_HTML, temp);
     win_print(win, placement, 2, "===> Family Circus");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://www.arcamax.com/thefunnies/familycircus/", temp);
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     char final[200] = "https://www.arcamax.com/";
     url = get_com_url(temp, "/newspics/[^&\"]*.(jpg|gif|png)");
     win_print(win, placement, 2, "==> Downloading image");
     strcat(final, url);
     env_macro(FAMILY_CIRCUS_IMG, temp);
     int res2 = get_url(final, temp);
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     log_sql(db, "family_circus", res2, final);
     free(url);
     return 0;
}

int get_beetle_bailey(WINDOW *win, int *placement, sqlite3 *db)
{
     char temp[200];
     env_macro(BEETLE_HTML, temp);
     win_print(win, placement, 2, "===> Beetle Bailey");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://www.arcamax.com/thefunnies/beetlebailey", temp);
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     char final[200] = "https://www.arcamax.com/";
     url = get_com_url(temp, "/newspics/[^n&]*.(gif|jpg|png)");
     win_print(win, placement, 2, "==> Downloading image");
     strcat(final, url);
     env_macro(BEETLE_IMG, temp);
     int res2 = get_url(final, temp);
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     log_sql(db, "beetle_bailey", res2, final);
     free(url);
     return 0;
}

int get_blondie(WINDOW *win, int *placement, sqlite3 *db)
{
     char temp[200];
     env_macro(BLONDIE_HTML, temp);
     win_print(win, placement, 2, "===> Blondie");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://www.arcamax.com/thefunnies/blondie", temp);
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     char final[200] = "https://www.arcamax.com/";
     url = get_com_url(temp, "/newspics/[^n&]*.jpg");
     win_print(win, placement, 2, "==> Downloading image");
     strcat(final, url);
     env_macro(BLONDIE_IMG, temp);
     int res2 = get_url(final, temp);
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     log_sql(db, "blondie", res2, final);
     free(url);
     return 0;
}

#endif    /* COMS_C_ */
