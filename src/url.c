#ifndef URL_C_
#define URL_C_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_url(char *url, char *file) {
  char command[100];
  strcpy(command, "curl -s ");
  strcat(command, url);
  strcat(command, " > ");
  strcat(command, file);
  int result = system(command);
  return result;
}

#endif /* URL_C_ */
