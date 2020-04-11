#ifndef COMS_C_
#define COMS_C_

#include <string.h>
#include <stdlib.h>

#include "com_reg.h"
#include "constants.h"
#include "url.h"
#include "utils.h"

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

int get_xkcd(WINDOW * win, int *placement)
{
     win_print(win, placement, 2, "===> XKCD");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://www.xkcd.com/", env_macro(XKCD_HTML));
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
     free(url);
     return 0;
}

int get_bc(WINDOW *win, int *placement)
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
     snprintf(final, sizeof(final), "%s%s", final, url);
     win_print(win, placement, 2, "==> Downloading image");
     int res2 = get_url(final, env_macro(BC_IMG));
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     free(url);
     return 0;
}

int get_garfield(WINDOW *win, int *placement)
{
     win_print(win, placement, 2, "===> Garfield");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://garfield.com", env_macro(GARFIELD_HTML));
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     url = get_com_url(env_macro(GARFIELD_HTML), "https://[^\"]*.gif");
     win_print(win, placement, 2, "==> Downloading image");
     int res2 = get_url(url, env_macro(GARFIELD_IMG));
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     free(url);
     return 0;
}

int get_far_side (WINDOW *win, int *placement)
{
     win_print(win, placement, 2, "===> The Far Side");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://www.thefarside.com", env_macro(FAR_SIDE_HTML));
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     url = get_com_url(env_macro(FAR_SIDE_HTML), "https://assets.thefarside.com/uploads/splash[^\"]*.jpg");
     win_print(win, placement, 2, "==> Downloading image");
     int res2 = get_url(url, env_macro(FAR_SIDE_IMG));
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     free(url);
     return 0;
}

int get_dilbert (WINDOW *win, int *placement)
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
     int res2 = get_url(url, env_macro(DILBERT_IMG));
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     free(final);
     free(url);
     return 0;
}

int get_family_circus(WINDOW *win, int *placement)
{
     win_print(win, placement, 2, "===> Family Circus");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://www.arcamax.com/thefunnies/familycircus/", env_macro(FAMILY_CIRCUS_HTML));
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     url = get_com_url(env_macro(FAMILY_CIRCUS_HTML), "https://www.arcamax.com/newspics/.*.jpg");
     win_print(win, placement, 2, "==> Downloading image");
     int res2 = get_url(url, env_macro(FAMILY_CIRCUS_IMG));
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     free(url);
     return 0;
}

int get_beetle_bailey(WINDOW *win, int *placement)
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
     url = get_com_url(env_macro(BEETLE_HTML), "/newspics/[^&]*.gif");
     win_print(win, placement, 2, "==> Downloading image");
     strcat(final, url);
     int res2 = get_url(final, env_macro(BEETLE_IMG));
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     free(url);
     return 0;
}

int get_blondie(WINDOW *win, int *placement)
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
     url = get_com_url(env_macro(BLONDIE_HTML), "/newspics/[^&]*.gif");
     win_print(win, placement, 2, "==> Downloading image");
     strcat(final, url);
     int res2 = get_url(final, env_macro(BLONDIE_IMG));
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     free(url);
     return 0;
}

#endif				/* COMS_C_ */
