#ifndef COMS_C_
#define COMS_C_

#include "com_reg.c"
#include "utils.c"

int get_xkcd(WINDOW *win, int placement) {
  win_print(win, &placement, 2, "==> Downloading Site");
  int res = get_url("https://www.xkcd.com/", XKCD_HTML);
  error_print(win, &placement, res, "Site downloaded!", "Site not found");
  win_print(win, &placement, 2, "==> Finding URL of image");
  char *url = NULL;
  url = malloc(100);
  url = get_com_url(XKCD_HTML, "https://imgs.xkcd.com/comics/[^2]*.png");
  win_print(win, &placement, 2, "==> Downloading image");
  int res2 = get_url(url, XKCD_IMG);
  error_print(win, &placement, res2, "Image downloaded", "Image not found");
  free(url);
  return 0;
}

#endif /* COMS_C_ */