#ifndef COMS_C_
#define COMS_C_

#include "com_reg.c"
#include "utils.c"

int get_xkcd(WINDOW * win, int *placement)
{
     win_print(win, placement, 2, "===> XKCD");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://www.xkcd.com/", XKCD_HTML);
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     url = get_com_url(XKCD_HTML, "https://imgs.xkcd.com/comics/[^2]*.png");
     win_print(win, placement, 2, "==> Downloading image");
     int res2 = get_url(url, XKCD_IMG);
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     free(url);
     return 0;
}

int get_bc(WINDOW *win, int *placement)
{
     win_print(win, placement, 2, "===> BC");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://johnhartstudios.com/bc/", BC_HTML);
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     char final[100] = "https://johnhartstudios.com";
     url = get_com_url(BC_HTML, "/bcstrips/[^\"]*");
     snprintf(final, sizeof(final), "%s%s", final, url);
     win_print(win, placement, 2, "==> Downloading image");
     int res2 = get_url(final, BC_IMG);
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     free(url);
     return 0;
}

int get_garfield(WINDOW *win, int *placement)
{
     win_print(win, placement, 2, "===> Garfield");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://garfield.com", GARFIELD_HTML);
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     url = get_com_url(GARFIELD_HTML, "https://[^\"]*.gif");
     win_print(win, placement, 2, "==> Downloading image");
     int res2 = get_url(url, GARFIELD_IMG);
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     free(url);
     return 0;
}

int get_far_side (WINDOW *win, int *placement)
{
     win_print(win, placement, 2, "===> The Far Side");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://www.thefarside.com", FAR_SIDE_HTML);
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     url = get_com_url(FAR_SIDE_HTML, "https://assets.thefarside.com/uploads/splash[^\"]*.jpg");
     win_print(win, placement, 2, "==> Downloading image");
     int res2 = get_url(url, FAR_SIDE_IMG);
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     free(url);
     return 0;
}

int get_dilbert (WINDOW *win, int *placement)
{
     win_print(win, placement, 2, "===> Dilbert");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://dilbert.com", DILBERT_HTML);
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     url = get_com_url(DILBERT_HTML, "assets.amuniversal.com/([a-f]|[[:digit:]]){32}");
     char *final = NULL;
     final = malloc(150);
     strcpy(final, "https://");
     strcat(final, url);
     win_print(win, placement, 2, "==> Downloading image");
     int res2 = get_url(url, DILBERT_IMG);
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
     int res = get_url("https://www.arcamax.com/thefunnies/familycircus/", FAMILY_CIRCUS_HTML);
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     url = get_com_url(FAMILY_CIRCUS_HTML, "https://www.arcamax.com/newspics/.*.jpg");
     win_print(win, placement, 2, "==> Downloading image");
     int res2 = get_url(url, FAMILY_CIRCUS_IMG);
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     free(url);
     return 0;
}

int get_beetle_bailey(WINDOW *win, int *placement)
{
     win_print(win, placement, 2, "===> Beetle Bailey");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://www.arcamax.com/thefunnies/beetlebailey", BEETLE_HTML);
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     char final[200] = "https://www.arcamax.com/";
     url = get_com_url(BEETLE_HTML, "/newspics/[^&]*.gif");
     win_print(win, placement, 2, "==> Downloading image");
     strcat(final, url);
     int res2 = get_url(final, BEETLE_IMG);
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     free(url);
     return 0;
}

int get_blondie(WINDOW *win, int *placement)
{
     win_print(win, placement, 2, "===> Blondie");
     win_print(win, placement, 2, "==> Downloading Site");
     int res = get_url("https://www.arcamax.com/thefunnies/blondie", BLONDIE_HTML);
     error_print(win, placement, res, "Site downloaded!",
                 "Site not found");
     win_print(win, placement, 2, "==> Finding URL of image");
     char *url = NULL;
     url = malloc(100);
     char final[200] = "https://www.arcamax.com/";
     url = get_com_url(BLONDIE_HTML, "/newspics/[^&]*.gif");
     win_print(win, placement, 2, "==> Downloading image");
     strcat(final, url);
     int res2 = get_url(final, BLONDIE_IMG);
     error_print(win, placement, res2, "Image downloaded",
                 "Image not found");
     free(url);
     return 0;
}

#endif				/* COMS_C_ */
