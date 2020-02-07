#ifndef COM_REG_C_
#define COM_REG_C_

#include <stdlib.h>
#include <stdio.h> // not sure if this is truly necessary, but...
#include <regex.h>

#include "url.h"

char *regexp (char *string, char *patrn, int *begin, int *end) {
  int i, w=0, len;
  char *word = NULL;
  regex_t rgT;
  regmatch_t match;
  regcomp(&rgT,patrn,REG_EXTENDED);
  if ((regexec(&rgT,string,1,&match,0)) == 0) {
    *begin = (int)match.rm_so;
    *end = (int)match.rm_eo;
    len = *end-*begin;
    word=malloc(len+1);
    for (i=*begin; i<*end; i++) {
      word[w] = string[i];
      w++; }
    word[w]=0;
  }
  regfree(&rgT);
  return word;
}

char *get_com_url(char *file /* to search */, char *pattern /* to search file for */) {
  /* open file */
  char * buffer = 0;
  FILE *fp;
  fp = fopen(file, "r+");
  /* get size of file for buffer */
  if (fp) {
    fseek(fp, 0, SEEK_END);
    int length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    buffer = malloc(length);
    if (buffer) {
      fread (buffer, 1, length, fp);
    }
  }
  /* init variables for regex */
  int b, e;
  /* perform regex */
  char *url;
  url = regexp(buffer, pattern, &b, &e);
  /* extract answer */
  return url;
}

#endif /* COM_REG_C_ */
